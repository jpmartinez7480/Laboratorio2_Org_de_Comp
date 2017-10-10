#include "Buffer.cpp"

#include <list>
#include <iterator>

using std::list;

class Procesador
{
	public:
		Procesador();
		~Procesador();
		int readFile_Mips(string);
		int readFile_Registers(string);
		int searchDataRegister(string);
		int ALU(int,int,string);
		int add(int,int);
		int sub(int,int);
		int mul(int,int);
		int div(int,int);
		int addi(int,int);
		int subi(int,int);
		void j(string);
		void sw(string,int);
		void showContent();
		void ejecutar();
		void etapaIF();
		void etapaID();
		void etapaEX();
		void etapaMEM();
		void etapaWB();
		int Hazard_DataDetector();
		//void NOP();
		static const string regs[32];
		static const string op[11];
	private:
		list<Instruction>::iterator PC;
		list<Instruction> instructions; //lista con las instrucciones mips
		Instruction inst;
		Register registers[32];
		Register stackPointer[1000];
		Control lineControl;
		Buffer buffer_if_id;
		Buffer buffer_id_ex;
		Buffer buffer_ex_mem;
		Buffer buffer_mem_wb;

};