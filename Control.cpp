#include "Control.h"

Control::Control()
{
	setRegDst(0);
	setJump(0);
	setBranch(0);
	setMemRead(0);
	setMemToReg(0);
	setMemWrite(0);
	setALUSrc(0);
	setRegWrite(0);
}

void Control::setRegDst(int rd){
	regDst = rd;
}

void Control::setJump(int j){
	jump = j;
}

void Control::setBranch(int b){
	branch = b;
}

void Control::setMemRead(int mr){
	memRead = mr;
}

void Control::setMemToReg(int mtr){
	memToReg = mtr;
}

void Control::setMemWrite(int mw){
	memWrite = mw;
}

void Control::setALUSrc(int as){
	ALUSrc = as;
}

void Control::setRegWrite(int rw){
	regWrite = rw;
}

int Control::getRegDst(){
	return regDst;
}

int Control::getJump(){
	return jump;
}

int Control::getBranch(){
	return branch;
}

int Control::getMemRead(){
	return memRead;
}

int Control::getMemToReg(){
	return memToReg;
}

int Control::getMemWrite(){
	return memWrite;
}

int Control::getALUSrc(){
	return ALUSrc;
}

int Control::getRegWrite(){
	return regWrite;
}


