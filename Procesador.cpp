#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include "Procesador.h"

using namespace std;

const string Procesador::regs[32]  = {"$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra"};

const string Procesador::op[11] = {"add","sub","mul","div","addi","subi","lw","sw","beq","j"};

Procesador::Procesador()
{
	for(int i = 0; i < 32; i++)
		registers[i] =Register(); 
	for(int i = 0; i < 1000; i++)
		stackPointer[i] = Register();
	lineControl = Control();
}

Procesador::~Procesador(){}


int Procesador::readFile_Mips(string nfile)
{
	fstream FILE;
	char *linea;
	FILE.open(nfile.c_str(),ios::in);
	if(!FILE)	return 0;
	else
	{
		string line;
		int j = 0;
		while(!FILE.eof())
		{
			string inst[5];
			getline(FILE,line);
			if(line!=""){
				char *cstr = new char[line.length() + 1];
				strcpy(cstr,line.c_str());
				linea = strtok(cstr," ");
				if(line[line.length() - 1] == ':'){
					Instruction i;
					i.setInstructionLabel(linea,"L");
					instructions.push_back(i);
				}
				else if(line[line.length()-1]!=':'){
					while(linea){
						inst[j] = linea;
						j++;
						linea = strtok(NULL,", ");
					}	
					j = 0;
					Instruction i;
					if(inst[0] != "j" && inst[0] != "lw" && inst[0] !="sw" && inst[0] != "beq")
						i = Instruction(inst[0],inst[1],inst[2],inst[3]);
					else if(inst[0] == "lw" || inst[0] == "sw")
						i = Instruction(inst[0],inst[1],inst[2]);
					else if(inst[0] == "beq")
						i.InstructionBeq(inst[1],inst[2],inst[3]);
					else if(inst[0] == "j")
						i = Instruction(inst[1]);
					instructions.push_back(i);
				}
			}
		}
		FILE.close();
		return 1;
	}
}

int Procesador::readFile_Registers(string nfile)
{
	fstream FILE;
	string reg;
	int value;
	FILE.open(nfile.c_str(),ios::in);
	if(!FILE)	return 0;
	else{
		string linea;
		getline(FILE,linea);
		while(FILE >> reg >> value)	registers[searchDataRegister(reg)].setRegister(value);
		FILE.close();
		return 1;
	}
}

void Procesador::showContent()
{
	cout << endl;
	cout << "********** Registros **********"<<endl;
	cout << "-------" << "-----" << endl; 
	cout << "|" <<regs[0] << setw(2) << "| " <<  registers[0].getRegister() << "  |" <<endl;
	cout << "-------" << "-----" << endl;
	for(int i = 1; i < 32; i++){
		cout << "|" <<regs[i] << setw(4) << "| " <<registers[i].getRegister() << "  |"<< endl;
		cout << "-------" << "-----" << endl;
	}
}

int Procesador::searchDataRegister(string r)
{
	int cnt = 0;
	while(regs[cnt] != r)	cnt++;
	return cnt;
}

int Procesador::add(int r1,int r2){
	return r1+r2;
}

int Procesador::sub(int r1,int r2){
	return r1-r2;
}

int Procesador::mul(int r1, int r2){
	return r1*r2;
}

int Procesador::div(int r1, int r2){
	return r1/r2;
}

int Procesador::addi(int r1,int n){
	return r1 + n;
}

int Procesador::subi(int r1, int n){
	return r1 - n;
}

void Procesador::sw(string r, int pos){
	stackPointer[999-pos/4].setRegister(registers[searchDataRegister(r)].getRegister());
}

void Procesador::j(string label)
{
	int i = 0;
	Instruction _i;
	list<Instruction>::iterator aux;
	aux = instructions.begin();
	while(aux!=instructions.end())
	{
		_i = *aux;
		if(_i.getLabel() != label){
			i++;
			aux++;
		}		
		else {
			PC = aux++;	
			aux = instructions.end();
		}
	}
	*PC = _i;
	ejecutar();
}

int Procesador::ALU(int v1, int v2, string op)
{
	int res;
	if(op == "add")	res = add(v1,v2);
	else if(op == "sub" || op == "beq")	res = sub(v1,v2);
	else if(op == "mul") res = mul(v1,v2);
	else if(op == "div") res = div(v1,v2);
	else if(op == "addi") res = addi(v1,v2);
	else if(op == "subi") res = subi(v1,v2);
	return res;
}

void Procesador::etapaIF(){
	buffer_if_id.setBuffer_if_id(inst);
	buffer_id_ex.getBufferControl() = Control(); 
	cout << "IF: " << buffer_if_id.getBufferInstruction().getInstruction() << endl;
}

void Procesador::etapaID()
{
	
	if(buffer_if_id.getBufferInstruction().getInstruction() != "sw" && buffer_if_id.getBufferInstruction().getInstruction()!= "lw"  && buffer_if_id.getBufferInstruction().getInstruction()!= "j" && buffer_if_id.getBufferInstruction().getInstruction()!= "addi" && buffer_if_id.getBufferInstruction().getInstruction()!= "subi"){
		buffer_id_ex.setBuffer_id_ex(buffer_if_id.getBufferInstruction(), registers[searchDataRegister(buffer_if_id.getBufferInstruction().getRegisterRs())].getRegister(),registers[searchDataRegister(buffer_if_id.getBufferInstruction().getRegisterRt())].getRegister());
		//buffer_id_ex.getBufferControl().setRegDst(1);
	}
	else if(buffer_if_id.getBufferInstruction().getInstruction() == "sw" || buffer_if_id.getBufferInstruction().getInstruction()== "lw" || buffer_if_id.getBufferInstruction().getInstruction()== "addi" || buffer_if_id.getBufferInstruction().getInstruction()== "subi"){
		buffer_id_ex.setBuffer_id_ex(buffer_if_id.getBufferInstruction(), registers[searchDataRegister(buffer_if_id.getBufferInstruction().getRegisterRs())].getRegister(),buffer_if_id.getBufferInstruction().getOffset()); //string, int, string
		//buffer_id_ex.getBufferControl().setALUSrc(1); //el segundo operando de la alu viende del signo extendido
	}
	//añadir beq
	buffer_ex_mem.getBufferControl() = Control();
	cout << "ID: " << buffer_id_ex.getBufferInstruction().getInstruction() << endl;
}

void Procesador::etapaEX()
{
	Hazard_DataDetector();
	if(buffer_id_ex.getBufferInstruction().getInstruction() == "lw"){
		buffer_ex_mem.setBuffer_ex_mem(buffer_id_ex.getBufferInstruction(),ALU(buffer_id_ex.getRsValue(),buffer_id_ex.getSignExtended(),"addi"));
		//buffer_ex_mem.getBufferControl().setMemRead(1);
	}
	else if(buffer_id_ex.getBufferInstruction().getInstruction() == "sw"){
		buffer_ex_mem.setBuffer_ex_mem(buffer_id_ex.getBufferInstruction(),ALU(buffer_id_ex.getRsValue(),buffer_id_ex.getSignExtended(),"addi"));
		//buffer_ex_mem.getBufferControl().setMemWrite(1);
	}
	else if(buffer_id_ex.getBufferInstruction().getInstruction() == "beq"){
		buffer_ex_mem.setBuffer_ex_mem(buffer_id_ex.getBufferInstruction(),ALU(buffer_id_ex.getRsValue(),buffer_id_ex.getRtValue(),"sub"));
		//buffer_ex_mem.getBufferControl().setBranch(1);
	}
	else{
		buffer_ex_mem.setBuffer_ex_mem(buffer_id_ex.getBufferInstruction(),ALU(buffer_id_ex.getRsValue(),buffer_id_ex.getRtValue(),buffer_id_ex.getBufferInstruction().getInstruction()));
		//buffer_ex_mem.getBufferControl().setRegWrite(1);
		//buffer_ex_mem.getBufferControl().setRegDst(1);
	}
	
	cout << "EX: " << buffer_ex_mem.getBufferInstruction().getInstruction() << endl;
	
}

void Procesador::etapaMEM()
{
	if(buffer_ex_mem.getBufferControl().getMemWrite() == 1)
		sw(buffer_ex_mem.getBufferInstruction().getRegisterRs(),buffer_ex_mem.getALU_result());
	else if(buffer_ex_mem.getBufferControl().getMemRead() == 1){
		int value = stackPointer[999-buffer_ex_mem.getALU_result()/4].getRegister();
		buffer_mem_wb.setBuffer_mem_wb(buffer_ex_mem.getBufferInstruction(),value); 
		//buffer_mem_wb.getBufferControl().setMemToReg(1);
	}
	else{
		buffer_mem_wb.setBuffer_mem_wb(buffer_ex_mem.getBufferInstruction(),buffer_ex_mem.getALU_result());
		//buffer_mem_wb.getBufferControl().setRegWrite(1);
	}
	cout << "MEM: " << buffer_mem_wb.getBufferInstruction().getInstruction() << endl;

}

void Procesador::etapaWB()
{
	if(buffer_mem_wb.getBufferControl().getMemToReg() == 1){
		registers[searchDataRegister(buffer_ex_mem.getBufferInstruction().getRegisterRs())].setRegister(buffer_ex_mem.getALU_result());
		//buffer_mem_wb.getBufferControl().setMemToReg(0);
	}
	else if(buffer_mem_wb.getBufferControl().getRegWrite() == 1){
		registers[searchDataRegister(buffer_mem_wb.getBufferInstruction().getRegisterRd())].setRegister(buffer_ex_mem.getALU_result());	
		//buffer_mem_wb.getBufferControl().setRegWrite(0);
	}
	cout << "termino la etapa" << endl;

}

int Procesador::Hazard_DataDetector()  //recuerda modificar para forwarding
{
	if(buffer_ex_mem.getBufferControl().getRegDst() != 0 && 
		buffer_ex_mem.getBufferInstruction().getRegisterRd() == buffer_id_ex.getBufferInstruction().getRegisterRs()){
		cout << "Hazard: " << buffer_id_ex.getBufferInstruction().getRegisterRs() << endl;
		return 1;
	}
	else if(buffer_ex_mem.getBufferControl().getRegDst() != 0 && 
			buffer_ex_mem.getBufferInstruction().getRegisterRd() == buffer_id_ex.getBufferInstruction().getRegisterRt()){
				cout << "Hazard: " << buffer_id_ex.getBufferInstruction().getRegisterRt() << endl;
				return 2;
			}

	else if(buffer_mem_wb.getBufferControl().getRegDst() != 0 &&
	   		buffer_mem_wb.getBufferInstruction().getRegisterRd() == buffer_ex_mem.getBufferInstruction().getRegisterRs()){
				cout << "Hazard: " << buffer_ex_mem.getBufferInstruction().getRegisterRd() << endl;
				return 3;
		}
				
	else if(buffer_mem_wb.getBufferControl().getRegDst() != 0 &&
			buffer_mem_wb.getBufferInstruction().getRegisterRd() == buffer_id_ex.getBufferInstruction().getRegisterRt()){
				cout << "Hazard: " << buffer_ex_mem.getBufferInstruction().getRegisterRd() << endl;
				return 4;
	}
				
	else if(buffer_id_ex.getBufferInstruction().getRegisterRt() == buffer_if_id.getBufferInstruction().getRegisterRs() || 
			buffer_id_ex.getBufferInstruction().getRegisterRt() == buffer_if_id.getBufferInstruction().getRegisterRt()){
			//poner en espera
			return 5;
		}	
}	

void Procesador::ejecutar()
{
	PC = instructions.begin();
	int size = 4 + instructions.size();
	int cnt = 1;
	//while(PC != instrucciones.end() && !buffer_mem_wb.getStatus()) {
	while(cnt < size+1){	
		if(PC != instructions.end()){
			inst = *PC;
			PC++;

		}
		cout << "Inicio ciclo" <<endl; 
		if(buffer_mem_wb.getStatus())
			etapaWB();
		if(buffer_ex_mem.getStatus())
			etapaMEM();
		if(buffer_id_ex.getStatus())
			etapaEX();
		if(buffer_if_id.getStatus())
			etapaID();
		etapaIF();
		cnt++;
		cout << "Fin ciclo " << endl;

	}
}


