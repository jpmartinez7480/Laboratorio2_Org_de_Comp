 #include "Register.h"

Register::Register(){
	value = 0;
}
void Register::setRegister(int v){
	value = v;
}

int Register::getRegister(){
	return value;
}

