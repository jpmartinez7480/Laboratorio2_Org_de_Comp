#include <string>
using std::string;

class Control
{
	public:
		Control();
		void setRegDst(int rd);
		void setJump(int j);
		void setBranch(int b);
		void setMemRead(int mr);
		void setMemToReg(int mtr);
		void setMemWrite(int mw);
		void setALUSrc(int as);
		void setRegWrite(int rw);
		int getRegDst();
		int getJump();
		int getBranch();
		int getMemRead();
		int getMemToReg();
		int getMemWrite();
		int getALUSrc();
		int getRegWrite();
		
	private:
		int regDst;
		int jump;
		int branch;
		int memRead;
		int memToReg;
		int memWrite;
		int ALUSrc;
		int regWrite;
};
