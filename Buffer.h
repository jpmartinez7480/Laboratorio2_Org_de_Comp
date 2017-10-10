#include "Instruction.cpp"
#include "Register.cpp"
#include "Control.cpp"

#include <list> 
#include <iterator>

class Buffer
{
	public:
		Buffer();
		void setBuffer_if_id(Instruction);
		//void Buffer(Instruction i);
		void setBuffer_id_ex(Instruction, int, int);
		void setBuffer_ex_mem(Instruction, int);
		void setBuffer_mem_wb(Instruction, int);
		void setRsValue(int);
		void setRtValue(int);
		void setALU_result(int);
		void setSignExtended(int);
		void setStatus(bool);
		Instruction getBufferInstruction();
		Control getBufferControl();
		int getRsValue();
		int getRtValue();
		int getALU_result();
		int getSignExtended();
		bool getStatus();
	private:
		Instruction i;
		Control bufferControl;
		int rsValue;
		int rtValue;
		int ALU_result;
		int signExtended;
		bool status;
};	
