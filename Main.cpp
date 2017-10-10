#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>

#include "Procesador.cpp"

using std::cout;
using std::endl;
using std::cin;
using std::cerr;
using std::string;
using std::stringstream;

 
int main()
{
	string pause;
	string cad;
	int ans;
	string file_mips = "";
	string file_regs = "";
	string file_salida;
	Procesador procesador = Procesador();
	do
	{
		system("clear");
		cout << endl;
		cout << "****** ORGANIZACION DE COMPUTADORES ******" << endl;
		cout << "        ****** laboratorio 2 ******" << endl;
		cout << "Menu de opciones" << endl;
		cout << "1.Leer archivo de instrucciones Mips" << endl;
		cout << "2.Leer archivo de registros" << endl;
		cout << "3.Ejecutar" << endl;
		cout << "4.Reiniciar Todo" << endl;
		cout << "5.Salir" << endl;
		cout << "Ingrese opcion: ";
		getline(cin,cad);
		stringstream mystream(cad);
		string msje = mystream >> ans ? "entrada valida\n" : "entrada incorrecta\n";
		cout << msje;
		switch(ans)
		{
			case 1:
				system("clear");
				cout << "*** Lectura de archivo mips ***" << endl;
				cout << "Ingrese el nombre del archivo junto a su extension (ejemplo.ext): ";
				cin >>  file_mips;
				if(procesador.readFile_Mips(file_mips) == 1) 
					cout << "La lectura se realizo satisfactoriamente" << endl;
				else{
					cout << "La lectura de archivo no pudo ser completada. Revise el archivo" << endl;
					file_mips = "";
				}
				cout << "Presione cualquier tecla para continuar...";
				cin >> pause;
				break;
			case 2:
				system("clear");
				cout << "*** Lectura de archivos de registros ***" << endl;
				cout << "Ingrese el nombre del archivo junto a su extension (ejemplo.ext): ";
				cin >> file_regs;
				if(procesador.readFile_Registers(file_regs) == 1){
					cout << "La lectura se realizo satisfactoriamente" << endl;
					procesador.showContent();
				}
				else{
					cout << "La lectura de archivo no pudo ser completada. Revise el archivo" << endl;
					file_regs = "";
				}
				cout << "Presione cualquier tecla para continuar...";
				cin >> pause;
				break;
			case 3:
				system("clear");
				if(file_mips != "" && file_regs != ""){
						procesador.ejecutar();
						procesador.showContent();	
					}
				else if(file_mips == "" && file_regs != "")
					cout << "Falta leer el archivo de instrucciones mips" << endl;
				else if(file_mips != "" && file_regs == "")
					cout << "Falta leer el archivo de registros" << endl;
				else
					cout << "Falta leer el archivo de instrucciones mips" << endl;
				cout << "Presione una tecla para continuar...";
				cin >> pause;
				break;
				case 4:
					procesador.~Procesador();
					procesador = Procesador();
					cout << "Registros y stackPointer reiniciados..." << endl;
					cout << "Presione una tecla para continuar... "<< endl;
					cin >> pause;
					break;
			case 5:
				cout << "Gracias por su preferencia" << endl;
				break;
			default:
				cout << "Ingrese una operacion valida" << endl;
		}
		if(ans > 0 && ans <=4) ans = 0;	
	}while(ans!=5);

	return 0;
}