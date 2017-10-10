#include "Buffer.h"

Buffer::Buffer(){}

void Buffer::setBuffer_if_id(Instruction inst){ 
	i = inst;
	setStatus(true);
}

void Buffer::setBuffer_id_ex(Instruction inst, int rs, int rt)
{
	i = inst;
	if(inst.getInstruction() != "lw" && inst.getInstruction() != "sw" && inst.getInstruction() != "addi" && inst.getInstruction() != "subi"){
		setRsValue(rs);
		setRtValue(rt);
		bufferControl.setRegDst(1);
	}
	else if(inst.getInstruction() == "lw" || inst.getInstruction() == "sw" || inst.getInstruction() == "addi" || inst.getInstruction() == "subi"){
		setRsValue(rs);
		setSignExtended(rt);
	}
	setStatus(true);

}

void Buffer::setBuffer_ex_mem(Instruction inst, int alr)
{
	i = inst;
	setALU_result(alr);
	setStatus(true);
	if(i.getInstruction() == "lw") bufferControl.setMemRead(1);
	else if(i.getInstruction() == "sw") bufferControl.setMemWrite(1);
	else if(i.getInstruction() == "beq" && alr == 0) bufferControl.setBranch(1);
	else{
		bufferControl.setRegWrite(1);
		bufferControl.setRegDst(1);
	}
}

void Buffer::setBuffer_mem_wb(Instruction inst, int data)
{
	i = inst;
	setALU_result(data);
	setStatus(true);
	if(i.getInstruction() == "lw") bufferControl.setMemToReg(1);
	else bufferControl.setRegWrite(1);
}

void Buffer::setRsValue(int rs) { rsValue = rs;}

void Buffer::setRtValue(int rt) {rtValue = rt;}

void Buffer::setALU_result(int alr){ALU_result = alr;}

void Buffer::setSignExtended(int se){signExtended = se;}

void Buffer::setStatus(bool tf){status = tf;}

int Buffer::getRsValue(){ return rsValue;}

int Buffer::getRtValue(){return rtValue;}

int Buffer::getALU_result(){return ALU_result;}

int Buffer::getSignExtended(){return signExtended;}

bool Buffer::getStatus(){return status;}

Instruction Buffer::getBufferInstruction(){return i;}

Control Buffer::getBufferControl(){return bufferControl;}