 #include <string>

using std::string;

 class Instruction
 {
 	public:
 		Instruction();
 		Instruction(string i, string rd, string rs, string rt); //tipo R
 		Instruction(string i, string rs, string offset); //lw, sw
 		void InstructionBeq(string rs, string rt, string label); //beq
 		Instruction(string label); //j
 		void setInstructionLabel(string,string);
 		void setInstruction(string);
 		void setRegisterRd(string);
 		void setRegisterRs(string);
 		void setRegisterRt(string);
 		void setOffset(int);
 		void setLabel(string);
 		string getInstruction();
 		string getRegisterRd();
 		string getRegisterRs();
 		string getRegisterRt();
 		string getLabel();
 		int getOffset();

 	private:
 		int offset;
 		string rd;
 		string rs;
 		string rt;
 		string label;
 		string instruction;
 };