#include "Instruction.h"

 Instruction::Instruction()
 {
 	offset = 0;
 	rs = "";
 	rd = "";
 	rt = "";
 	label = "";
 }

 Instruction::Instruction(string i, string rd, string rs, string rt)
 {
 	if(i != "addi" && i != "subi"){
 		setInstruction(i);
 		setRegisterRd(rd);
 		setRegisterRs(rs);
 		setRegisterRt(rt);
 	}
 	else{
 		setInstruction(i);
 		setRegisterRd(rd);
 		setRegisterRs(rs);
 		setRegisterRt(rd);
 		int _offset = atoi(rt.c_str());
 		setOffset(_offset);
 	}
 	
 }

 Instruction::Instruction(string i, string rs, string offset)
 {
 	setInstruction(i);
 	setRegisterRs(rs);
 	char aux = offset[0];
 	int _offset = aux;
 	setOffset(_offset);
 }

 void Instruction::InstructionBeq(string rs, string rt, string label)
 {
 	setInstruction("beq");
 	setRegisterRs(rs);
 	setRegisterRt(rt);
 	setLabel(label);
 }

 Instruction::Instruction(string label)
 {
 	setInstruction("j");
 	setLabel(label+":");
 }

void Instruction::setInstructionLabel(string linea, string t){
	setLabel(linea);
	setInstruction(t);
}

 void Instruction::setInstruction(string i){
 	instruction = i;
 }

 void Instruction::setRegisterRd(string reg){
 	rd = reg;
 }

 void Instruction::setRegisterRs(string reg){
 	rs = reg;
 }

 void Instruction::setRegisterRt(string reg){
 	rt = reg;
 }

 void Instruction::setOffset(int o){
 	offset = o;
 }

 void Instruction::setLabel(string l){
 	label = l;
}

string Instruction::getInstruction(){
	return instruction;
}

string Instruction::getRegisterRd(){
	return rd;
}

string Instruction::getRegisterRs(){
	return rs;
}

string Instruction::getRegisterRt(){
	return rt;
}

int Instruction::getOffset(){
	return offset;
}

string Instruction::getLabel(){
	return label;
}
