/*
 * MaestroEsclavo.cpp
 *
 *  Created on: 13 abr. 2020
 *      Author: Kike
 */

#include "MaestroEsclavo.h"

//AUTORES
//Mario Bermejo Sánchez
//Enrique Moreno Ávila
//CURSO -> Segundo
//Hora Laboratorio -> Lunes 8:30

#include "MaestroEsclavo.h"

TramaControl tramaRecibida2;		//Trama que se va a recibir
char car2;					//estas variables basicamente son las mismas que de F3, remodificadas para el protocolo Maestro-Esclavo
bool escribir2 = false;
extern HANDLE Pantalla;
int contador2 = 1;
ofstream fsal2;
extern ofstream flogM;
extern ofstream flogE;
bool ME = false; //variable que controla que no se cree un log(de f5) en el maestro esclavo

bool Finfich2 = false;
unsigned char campoDireccion;// variable para distinguir entre si se ha seleccionado maestro-seleccion o maestro-sondeo
bool PonerColor = false;//variable para saber cuando poner color en el mensaje tamaño fichero
int colorFichero2 = 0;//Color leido del fichero
char autores2[254];//Autores leidos del fichero
int lAutores2 = 0;//Longitud del campo autores

int recibirME(HANDLE PuertoCOM, int &campo) {
	car2 = RecibirCaracter(PuertoCOM);
	int color;
	if (car2 != 0) {	//Recibimos datos

		switch (campo) {
		case 1:
			if (car2 == 22) {
				tramaRecibida2.S = car2;
				campo++;
			} else {
				if (car2 == '{') {
					escribir2 = true;
				} else {
					if (car2 == '}') {
						PonerColor = true;
						Finfich2 = true;
						escribir2 = false;
						contador2 = 1;
						fsal2.close();
						SetConsoleTextAttribute(Pantalla, colorFichero2);
						printf("Fichero recibido.\n");

						if (flogM.is_open()) {
							char m[MAX];
							strcpy(m, "Fichero recibido.\n\0");escribirLogM(m);
						}//if flog_open

						if (flogE.is_open()) {
							char m[MAX];
							strcpy(m, "Fichero recibido.\n\0");escribirLogE(m);
						}//if flog_open

					}
				}
			}
			break;
		case 2:
			tramaRecibida2.D = car2;
			campo++;
			break;
		case 3:
			tramaRecibida2.C = car2;
			campo++;
			break;
		case 4:
			tramaRecibida2.NT = car2;
			if (tramaRecibida2.C != 02) {	//Si es 02 es trama de datos
				campo = 1;
				switch (tramaRecibida2.C) {
				case 05:
					cout << "R " << tramaRecibida2.D << " ENQ " << tramaRecibida2.NT << endl;

					if (flogM.is_open()) {
						char m[MAX];
						strcpy(m, "E \0");escribirLogM(m);
						m[0]=tramaRecibida2.D;m[1]='\0';escribirLogM(m);
						strcpy(m, " ENQ \0");escribirLogM(m);
						m[0]=tramaRecibida2.NT;m[1]='\0';escribirLogM(m);
						strcpy(m, "\n\0");
						escribirLogM(m);
					}//if flog_open
					if (flogE.is_open()) {
						char m[MAX];
						strcpy(m, "E \0");escribirLogE(m);
						m[0]=tramaRecibida2.D;m[1]='\0';escribirLogE(m);
						strcpy(m, " ENQ \0");escribirLogE(m);
						m[0]=tramaRecibida2.NT;m[1]='\0';escribirLogE(m);
						strcpy(m, "\n\0");
						escribirLogE(m);
					}//if flog_open

					campoDireccion = tramaRecibida2.D;
					return 1;
					break;
				case 04:
					color = 11 + 0 * 16;
					SetConsoleTextAttribute(Pantalla, color);
					cout << "R " << tramaRecibida2.D << " EOT " << tramaRecibida2.NT << endl;

					if (flogM.is_open()) {
						char m[MAX];
						strcpy(m, "E \0");escribirLogM(m);
						m[0]=tramaRecibida2.D;m[1]='\0';escribirLogM(m);
						strcpy(m, " EOT \0");escribirLogM(m);
						m[0]=tramaRecibida2.NT;m[1]='\0';escribirLogM(m);
						strcpy(m, "\n\0");
						escribirLogM(m);
					}//if flog_open
					if (flogE.is_open()) {
						char m[MAX];
						strcpy(m, "E \0");escribirLogE(m);
						m[0]=tramaRecibida2.D;m[1]='\0';escribirLogE(m);
						strcpy(m, " EOT \0");escribirLogE(m);
						m[0]=tramaRecibida2.NT;m[1]='\0';escribirLogE(m);
						strcpy(m, "\n\0");
						escribirLogE(m);
					}//if flog_open

					return 2;
					break;
				case 06:
					cout << "R " << tramaRecibida2.D << " ACK " << tramaRecibida2.NT << endl;
					if (flogM.is_open()) {
						char m[MAX];
						strcpy(m, "E \0");escribirLogM(m);
						m[0]=tramaRecibida2.D;m[1]='\0';escribirLogM(m);
						strcpy(m, " ACK \0");escribirLogM(m);
						m[0]=tramaRecibida2.NT;m[1]='\0';escribirLogM(m);
						strcpy(m, "\n\0");
						escribirLogM(m);

					}//if flog_open
					if (flogE.is_open()) {
						char m[MAX];
						strcpy(m, "E \0");escribirLogE(m);
						m[0]=tramaRecibida2.D;m[1]='\0';escribirLogE(m);
						strcpy(m, " ACK \0");escribirLogE(m);
						m[0]=tramaRecibida2.NT;m[1]='\0';escribirLogE(m);
						strcpy(m, "\n\0");
						escribirLogE(m);

					}//if flog_open
					return 3;
					break;
				case 21:
					cout << "R " << tramaRecibida2.D << " NACK " << tramaRecibida2.NT << endl;
					if (flogM.is_open()) {
						char m[MAX];
						strcpy(m, "E \0");escribirLogM(m);
						m[0]=tramaRecibida2.D;m[1]='\0';escribirLogM(m);
						strcpy(m, " NACK \0");escribirLogM(m);
						m[0]=tramaRecibida2.NT;m[1]='\0';escribirLogM(m);
						strcpy(m, "\n\0");
						escribirLogM(m);

					}//if flog_open
					if (flogE.is_open()) {
						char m[MAX];
						strcpy(m, "E \0");escribirLogE(m);
						m[0]=tramaRecibida2.D;m[1]='\0';escribirLogE(m);
						strcpy(m, " NACK \0");escribirLogE(m);
						m[0]=tramaRecibida2.NT;m[1]='\0';escribirLogE(m);
						strcpy(m, "\n\0");
						escribirLogE(m);

					}//if flog_open
					return 4;
					break;
				}//switch que trama de control es
			} else {
				campo++;
			}
			break;
		case 5:
			tramaRecibida2.L = (unsigned char) car2;
			campo++;
		case 6:
			RecibirCadena(PuertoCOM, tramaRecibida2.Datos, tramaRecibida2.L);
			tramaRecibida2.Datos[tramaRecibida2.L + 1] = '\0';
			campo++;
			break;
		case 7:
			tramaRecibida2.BCE = (unsigned char) car2;
			campo = 1;

			unsigned char BCEControl = CalculoBCE(tramaRecibida2.Datos,tramaRecibida2.L);
			if (BCEControl == tramaRecibida2.BCE) {//Si los bce son correctos
				//AQUI VA ESCRIBIR FICHERO
				if(Finfich2 == true){	//Si estamos en la parte final del fichero
					int color = 7 + 0 * 16;
					SetConsoleTextAttribute(Pantalla, color);
				}
				cout << "R " << tramaRecibida2.D << " STX " << tramaRecibida2.NT<< " " << (int) tramaRecibida2.BCE << " "<< (int) BCEControl << endl;

				if (flogM.is_open()) {
					char m[MAX];
					strcpy(m, "E \0");escribirLogM(m);
					m[0]=tramaRecibida2.D;m[1]='\0';escribirLogM(m);
					strcpy(m, " STX \0");escribirLogM(m);
					m[0]=tramaRecibida2.NT;m[1]='\0';escribirLogM(m);
					m[0]=' ';m[1]='\0';escribirLogM(m);
					sprintf(m,"%d \0",(int)tramaRecibida2.BCE);escribirLogM(m);
					sprintf(m,"%d\0",(int)BCEControl);escribirLogM(m);
					strcpy(m, "\n\0");
					escribirLogM(m);
				}//if flog_open

				if (flogE.is_open()) {
					char m[MAX];
					strcpy(m, "E \0");escribirLogE(m);
					m[0]=tramaRecibida2.D;m[1]='\0';escribirLogE(m);
					strcpy(m, " STX \0");escribirLogE(m);
					m[0]=tramaRecibida2.NT;m[1]='\0';escribirLogE(m);
					m[0]=' ';m[1]='\0';escribirLogE(m);
					sprintf(m,"%d \0",(int)tramaRecibida2.BCE);escribirLogE(m);
					sprintf(m,"%d\0",(int)BCEControl);escribirLogE(m);
					strcpy(m, "\n\0");
					escribirLogE(m);
				}//if flog_open

				if (Finfich2 == true) {	//Si es la parte final del fichero(cuando se recibe el tamaño)
					int color = 6 + 0 * 16;
					SetConsoleTextAttribute(Pantalla, colorFichero2);
					printf("El tamano del fichero es ");
					if (flogM.is_open()) {
						char m[MAX];
						strcpy(m, "El tamano del fichero es \0");escribirLogM(m);
					}//if flog_open

					if (flogE.is_open()) {
						char m[MAX];
						strcpy(m, "El tamano del fichero es \0");escribirLogE(m);
					}//if flog_open

					color = 7 + 0 * 16;
					SetConsoleTextAttribute(Pantalla, colorFichero2);
					for (int i = 0; i < tramaRecibida2.L; i++) {
						printf("%c", tramaRecibida2.Datos[i]);
					}
					printf(" bytes.\n");
					if (flogM.is_open()) {
						char m[MAX];
						escribirLogM(tramaRecibida2.Datos);
						strcpy(m, " bytes.\n\0");escribirLogM(m);
					}//if flog_open

					if (flogE.is_open()) {
						char m[MAX];
						escribirLogE(tramaRecibida2.Datos);
						strcpy(m, " bytes.\n\0");escribirLogE(m);
					}//if flog_open

					SetConsoleTextAttribute(Pantalla, color);
				}// if fich true
				if (Finfich2 == false) {	//Si es la parte inicial del fichero, las 3 priemras tramas de cabecera
					escribirTramaME(contador2, tramaRecibida2.Datos,tramaRecibida2.L);
					contador2++;
				} else {
					Finfich2 = false;
				}
			} else {//Si los bce son incorrectos
				cout << "R " << tramaRecibida2.D << " STX " << tramaRecibida2.NT << " " << (int) tramaRecibida2.BCE << " " << (int) BCEControl << endl;
				if (flogM.is_open()) {
					char m[MAX];
					strcpy(m, "E \0");escribirLogM(m);
					m[0]=tramaRecibida2.D;m[1]='\0';escribirLogM(m);
					strcpy(m, " STX \0");escribirLogM(m);
					m[0]=tramaRecibida2.NT;m[1]='\0';escribirLogM(m);
					m[0]=' ';m[1]='\0';escribirLogM(m);
					sprintf(m,"%d\0",(int)BCEControl);escribirLogM(m);
					strcpy(m, "\n\0");
					escribirLogM(m);
				}//if flog_open

				if (flogE.is_open()) {
					char m[MAX];
					strcpy(m, "E \0");escribirLogE(m);
					m[0]=tramaRecibida2.D;m[1]='\0';escribirLogE(m);
					strcpy(m, " STX \0");escribirLogE(m);
					m[0]=tramaRecibida2.NT;m[1]='\0';escribirLogE(m);
					m[0]=' ';m[1]='\0';escribirLogE(m);
					sprintf(m,"%d\0",(int)BCEControl);escribirLogE(m);
					strcpy(m, "\n\0");
					escribirLogE(m);
				}//if flog_open
				return 6;
			}
			return 0;
			break;
		}
	}
	return 5;
}

void enviarFichME(HANDLE PuertoCOM, unsigned char D, unsigned char NT) {

	char cadena[255];
	int campo = 1;
	ifstream fent;
	fent.open("EProtoc.txt");
	int longi = 0;
	unsigned long int total = 0;
	int valor = -1;
	int color;
	if (fent.is_open()) {
		 color = 12 + 0 * 16;
		SetConsoleTextAttribute(Pantalla, color);

		EnviarCaracter(PuertoCOM, '{');

		NT = '0';
		fent.getline(cadena, 254, '\n');	//1 nombre del  autor
		crearTrama(PuertoCOM, cadena, strlen(cadena), D, NT);
		ComprobarLLegadaACK(PuertoCOM, campo, valor);
		AlternanciaNT(NT);
		cout << "Enviando fichero por ";

		for (int i = 0; i < strlen(cadena); i++) {
			printf("%c", cadena[i]);
		}
		printf("\n");

		if (flogM.is_open()) {
			cadena[strlen(cadena)]='\0';
			char m[MAX];
			strcpy(m, "Enviando fichero por \0");escribirLogM(m);escribirLogM(cadena);
			strcpy(m, "\n\0");
			escribirLogM(m);
		}//if flog_open
		if (flogE.is_open()) {
			cadena[strlen(cadena)]='\0';
			char m[MAX];
			strcpy(m, "Enviando fichero por \0");escribirLogE(m);escribirLogE(cadena);
			strcpy(m, "\n\0");
			escribirLogE(m);
		}//if flog_open

		fent.getline(cadena, 254, '\n');	//2 color
		crearTrama(PuertoCOM, cadena, strlen(cadena), D, NT);
		ComprobarLLegadaACK(PuertoCOM, campo, valor);
		AlternanciaNT(NT);

		fent.getline(cadena, 254, '\n');	//3 nombre fichero
		crearTrama(PuertoCOM, cadena, strlen(cadena), D, NT);
		ComprobarLLegadaACK(PuertoCOM, campo, valor);
		AlternanciaNT(NT);

		color = 2 + 0 * 16;
		SetConsoleTextAttribute(Pantalla, color);
		while (!fent.eof()) {
			fent.read(cadena, 254);
			longi = fent.gcount();
			if (longi > 0) {
				cadena[longi] = '\0';
				total = total + longi;
				crearTrama(PuertoCOM, cadena, longi, D, NT);
				ComprobarLLegadaACK(PuertoCOM, campo, valor);
				AlternanciaNT(NT);
			}
		}//while cuerpo fichero

		fent.close();
		EnviarCaracter(PuertoCOM, '}');

		color = 7 + 0 * 16;
		SetConsoleTextAttribute(Pantalla, color);
		sprintf(cadena, "%lu", total);
		crearTrama(PuertoCOM, cadena, strlen(cadena), D, NT);
		ComprobarLLegadaACK(PuertoCOM, campo, valor);

		//LONGITUD FICHERO
		color = 2 + 0 * 16;
		SetConsoleTextAttribute(Pantalla, color);
		printf("Se ha terminado de enviar el fichero");
		printf("\n");
		SetConsoleTextAttribute(Pantalla, color);
		if (flogM.is_open()) {
			char m[MAX];
			strcpy(m,"Se ha terminado de enviar el fichero. \n\0");
			escribirLogM(m);
		}//if flog_open
		if (flogE.is_open()) {
			char m[MAX];
			strcpy(m,"Se ha terminado de enviar el fichero. \n\0");
			escribirLogE(m);
		}//if flog_open

		color = 11 + 0*16;
		SetConsoleTextAttribute(Pantalla, color);
	} else {
		printf("ERROR: El fichero EProtoc.txt no existe\n");
		if (flogM.is_open()) {
			char m[MAX];
			strcpy(m,"ERROR: El fichero EProtoc.txt no existe. \n\0");
			escribirLogM(m);
		}//if flog_open
		if (flogE.is_open()) {
			char m[MAX];
			strcpy(m,"ERROR: El fichero EProtoc.txt no existe. \n\0");
			escribirLogE(m);
		}//if flog_open
	}//else si fichero no existe
}

void MaestroSeleccion(HANDLE PuertoCOM) {
	PonerColor = false;
	int valor = -1;
	int campo = 1;
	unsigned char NT = '0';
	unsigned char D = 'R';

	int color = 9 + 0 * 16;
	SetConsoleTextAttribute(Pantalla, color);
	EnviarTramaENQ(PuertoCOM, D, NT = '0');
	ComprobarLLegadaACK(PuertoCOM, campo, valor);

	enviarFichME(PuertoCOM, D, NT);

	color = 11 + 0 * 16;
	SetConsoleTextAttribute(Pantalla, color);
	EnviarTramaEOT(PuertoCOM, D, NT = '0');
	ComprobarLLegadaACK(PuertoCOM, campo, valor);

	color = 2 + 0 * 16;
	SetConsoleTextAttribute(Pantalla, color);
	printf("Fin de protocolo");
	printf("\n");
	if (flogM.is_open()) {
		char m[MAX];
		strcpy(m, "Fin de protocolo \n\0");escribirLogM(m);
	}//if flog_open

}

void esclavoProtoc(HANDLE PuertoCOM) {	//opcion es lo que selecciono el maestro
	PonerColor = false;
	int campo = 1;
	unsigned char NT = '0';
	int valor = 99;
	int color = 9 + 0 * 16;
	SetConsoleTextAttribute(Pantalla, color);
	int contadorT = 0;
	bool tipoME = false; //para cambiar colores al color transmiitido del fichero false tipo R true tipo T
	while (valor != 1) {
		valor = recibirME(PuertoCOM, campo);
	}

	if (campoDireccion == 'R') {									//seleccion
		tipoME = false;
		EnviarTramaACK(PuertoCOM, 'R', NT);
		color = 12 + 0 * 16;
		SetConsoleTextAttribute(Pantalla, color);

		while (valor != 2) {
			if(contadorT >= 3){
				color = 2 + 0 * 16;
				SetConsoleTextAttribute(Pantalla, color);
			}
			valor = recibirME(PuertoCOM, campo);
			if (valor == 0) {
				EnviarTramaACK(PuertoCOM, 'R', NT);
				AlternanciaNT(NT);
				contadorT++;
			}
			if (valor == 6) {
				EnviarTramaNACK(PuertoCOM, 'R', NT);
			}
		}//while
		color = 11 + 0 * 16;
		SetConsoleTextAttribute(Pantalla, color);
		EnviarTramaACK(PuertoCOM, 'R', NT = '0');

	} else {													//sondeo
		if (campoDireccion == 'T') {
			tipoME = true;
			EnviarTramaACK(PuertoCOM, 'T', NT);
			enviarFichME(PuertoCOM, 'T', NT = '0');
			valor = 99;
			color = 11 + 0*16;
			EnviarTramaEOT(PuertoCOM, 'T', NT = '0');
			while (valor != 3) {
				valor = recibirME(PuertoCOM, campo);
				if (valor == 4) {
					AlternanciaNT(NT);
					color = 11 + 0*16;
					SetConsoleTextAttribute(Pantalla, color);
					EnviarTramaEOT(PuertoCOM, 'T', NT);
					valor = 99;
				}
			}//while
		}//if campoDireccion == T
	}//else
	color = 2 + 0 * 16;

	if(!tipoME){
	SetConsoleTextAttribute(Pantalla, colorFichero2);
	}else{
	SetConsoleTextAttribute(Pantalla, color);
	}

	printf("Fin de protocolo");
	printf("\n");
	if (flogE.is_open()) {
		char m[MAX];
		strcpy(m, "Fin de protocolo \n\0");escribirLogE(m);
	}//if flog_open
}

void MaestroSondeo(HANDLE PuertoCOM) {
	PonerColor = false;
	int valor = -1;
	int campo = 1;
	unsigned char NT = '0';
	unsigned char D = 'T';
	int contadorT = 0;
	int color = 9 + 0 * 16;
	SetConsoleTextAttribute(Pantalla, color);

	EnviarTramaENQ(PuertoCOM, D, NT = '0');
	ComprobarLLegadaACK(PuertoCOM, campo, valor);

	color = 12 + 0 * 16;
	SetConsoleTextAttribute(Pantalla, color);

	while (valor != 2) {
		valor = recibirME(PuertoCOM, campo);
		if(contadorT >= 3){	//Control de los colores
			if(Finfich2 == true){;
				color = 7 + 0 * 16;
				SetConsoleTextAttribute(Pantalla, color);
			}else{
				color = 2 + 0 * 16;
				SetConsoleTextAttribute(Pantalla, color);
			}
		}
		if (valor == 0) {
			if(PonerColor == true){
			int color = 7 + 0 * 16;
			SetConsoleTextAttribute(Pantalla, color);
			PonerColor = false;
		}
			EnviarTramaACK(PuertoCOM, D, NT);
			AlternanciaNT(NT);
			contadorT++;
		}
		if (valor == 6) {
			EnviarTramaNACK(PuertoCOM, D, NT);
			contadorT++;
		}
	}//while

	color = 11 + 0 * 16;
	SetConsoleTextAttribute(Pantalla, color);
	int opcion2 = 0;
	NT = '0';
	bool fin = false;

	while (!fin) {
		while (valor != 2) {
			valor = recibirME(PuertoCOM, campo);
		}

		int color = 2 + 0 * 16;
		SetConsoleTextAttribute(Pantalla, color);
		printf("Desea finalizar la transmision de datos.\n");
		printf("1: Si.\n");
		printf("2: No.\n");
		if (flogM.is_open()) {
			char m[MAX];
			strcpy(m, "Desea finalizar la transmision de datos. \n1: Si.\n2: No.\n\0");escribirLogM(m);
		}//if flog_open

		cin >> opcion2;
		color = 11 + 0 * 16;
		SetConsoleTextAttribute(Pantalla, color);
		switch (opcion2) {
		case 1:
			fin = true;
			EnviarTramaACK(PuertoCOM, D, NT);
			break;
		case 2:
			EnviarTramaNACK(PuertoCOM, D, NT);
			AlternanciaNT(NT);
			valor = 99;
			break;
		}//switch
	}//while no se acepte cerra la comunicacion
	color = 2 + 0 * 16;
	SetConsoleTextAttribute(Pantalla, colorFichero2);
	printf("Fin de protocolo");
	printf("\n");
	if (flogM.is_open()) {
		char m[MAX];
		strcpy(m, "Fin de protocolo \n\0");escribirLogM(m);
	}//if flog_open
}

void crearTrama(HANDLE PuertoCOM, char Datos[], int longitud, unsigned char D,
		unsigned char NT) {
	unsigned char longitudC = (unsigned char) longitud;
	unsigned char BCEControl = CalculoBCE(Datos, (unsigned char) longitud);
	EnviarCaracter(PuertoCOM, 22);
	EnviarCaracter(PuertoCOM, D);
	EnviarCaracter(PuertoCOM, 02);
	EnviarCaracter(PuertoCOM, NT);
	EnviarCaracter(PuertoCOM, longitudC);
	EnviarCadena(PuertoCOM, Datos, longitud);
	EnviarCaracter(PuertoCOM, BCEControl);
	cout << "E " << D << " STX " << NT << " " << (int) BCEControl << endl;

	if (flogM.is_open()) {
		char m[MAX];
		strcpy(m, "E \0");escribirLogM(m);
		m[0]=D;m[1]='\0';escribirLogM(m);
		strcpy(m, " STX \0");escribirLogM(m);
		m[0]=NT;m[1]='\0';escribirLogM(m);
		m[0]=' ';m[1]='\0';escribirLogM(m);
		sprintf(m,"%d\0",(int)BCEControl);escribirLogM(m);
		strcpy(m, "\n\0");
		escribirLogM(m);
	}//if flog_open
	if (flogE.is_open()) {
		char m[MAX];
		strcpy(m, "E \0");escribirLogE(m);
		m[0]=D;m[1]='\0';escribirLogE(m);
		strcpy(m, " STX \0");escribirLogE(m);
		m[0]=NT;m[1]='\0';escribirLogE(m);
		m[0]=' ';m[1]='\0';escribirLogE(m);
		sprintf(m,"%d\0",(int)BCEControl);escribirLogE(m);
		strcpy(m, "\n\0");
		escribirLogE(m);
	}//if flog_open
}

void EnviarTramaENQ(HANDLE PuertoCOM, unsigned char D, unsigned char NT) {
	EnviarCaracter(PuertoCOM, 22);
	EnviarCaracter(PuertoCOM, D);
	EnviarCaracter(PuertoCOM, 05);
	EnviarCaracter(PuertoCOM, NT);
	cout << "E " << D << " ENQ " << NT << endl;

	if (flogM.is_open()) {
		char m[MAX];
		strcpy(m, "E \0");escribirLogM(m);
		m[0]=D;m[1]='\0';escribirLogM(m);
		strcpy(m, " ENQ \0");escribirLogM(m);
		m[0]=NT;m[1]='\0';escribirLogM(m);
		strcpy(m, "\n\0");
		escribirLogM(m);
	}//if flog_open
	if (flogE.is_open()) {
		char m[MAX];
		strcpy(m, "E \0");escribirLogE(m);
		m[0]=D;m[1]='\0';escribirLogE(m);
		strcpy(m, " ENQ \0");escribirLogE(m);
		m[0]=NT;m[1]='\0';escribirLogE(m);
		strcpy(m, "\n\0");
		escribirLogE(m);
	}//if flog_open
}

void EnviarTramaEOT(HANDLE PuertoCOM, unsigned char D, unsigned char NT) {
	EnviarCaracter(PuertoCOM, 22);
	EnviarCaracter(PuertoCOM, D);
	EnviarCaracter(PuertoCOM, 04);
	EnviarCaracter(PuertoCOM, NT);
	cout << "E " << D << " EOT " << NT << endl;

	if (flogM.is_open()) {
		char m[MAX];
		strcpy(m, "E \0");escribirLogM(m);
		m[0]=D;m[1]='\0';escribirLogM(m);
		strcpy(m, " EOT \0");escribirLogM(m);
		m[0]=NT;m[1]='\0';escribirLogM(m);
		strcpy(m, "\n\0");
		escribirLogM(m);
	}//if flog_open
	if (flogE.is_open()) {
		char m[MAX];
		strcpy(m, "E \0");escribirLogE(m);
		m[0]=D;m[1]='\0';escribirLogE(m);
		strcpy(m, " EOT \0");escribirLogE(m);
		m[0]=NT;m[1]='\0';escribirLogE(m);
		strcpy(m, "\n\0");
		escribirLogE(m);
	}//if flog_open
}

void EnviarTramaACK(HANDLE PuertoCOM, unsigned char D, unsigned char NT) {
	EnviarCaracter(PuertoCOM, 22);
	EnviarCaracter(PuertoCOM, D);
	EnviarCaracter(PuertoCOM, 06);
	EnviarCaracter(PuertoCOM, NT);
	cout << "E " << D << " ACK " << NT << endl;

	if (flogM.is_open()) {
		char m[MAX];
		strcpy(m, "E \0");escribirLogM(m);
		m[0]=D;m[1]='\0';escribirLogM(m);
		strcpy(m, " ACK \0");escribirLogM(m);
		m[0]=NT;m[1]='\0';escribirLogM(m);
		strcpy(m, "\n\0");
		escribirLogM(m);
	}//if flog_open
	if (flogE.is_open()) {
		char m[MAX];
		strcpy(m, "E \0");escribirLogE(m);
		m[0]=D;m[1]='\0';escribirLogE(m);
		strcpy(m, " ACK \0");escribirLogE(m);
		m[0]=NT;m[1]='\0';escribirLogE(m);
		strcpy(m, "\n\0");
		escribirLogE(m);
	}//if flog_open
}

void EnviarTramaNACK(HANDLE PuertoCOM, unsigned char D, unsigned char NT) {
	EnviarCaracter(PuertoCOM, 22);
	EnviarCaracter(PuertoCOM, D);
	EnviarCaracter(PuertoCOM, 21);
	EnviarCaracter(PuertoCOM, NT);
	cout << "E " << D << " NACK " << NT << endl;

	if (flogM.is_open()) {
		char m[MAX];
		strcpy(m, "E \0");escribirLogM(m);
		m[0]=D;m[1]='\0';escribirLogM(m);
		strcpy(m, " NACK \0");escribirLogM(m);
		m[0]=NT;m[1]='\0';escribirLogM(m);
		strcpy(m, "\n\0");
		escribirLogM(m);
	}//if flog_open
	if (flogE.is_open()) {
		char m[MAX];
		strcpy(m, "E \0");escribirLogE(m);
		m[0]=D;m[1]='\0';escribirLogE(m);
		strcpy(m, " NACK \0");escribirLogE(m);
		m[0]=NT;m[1]='\0';escribirLogE(m);
		strcpy(m, "\n\0");
		escribirLogE(m);
	}//if flog_open
}

void ComprobarLLegadaACK(HANDLE PuertoCOM, int campo, int &valor) {
	bool fin = false;
	while (valor != 3 && !fin) {
		valor = recibirME(PuertoCOM, campo);
		if (valor == 4) {
			fin = true;
		}
	}//while
	if (fin) {
		valor = -2;
	} else {
		valor = -1;
	}
}

void AlternanciaNT(unsigned char &NT) {
	if (NT == '0') {
		NT = '1';
	} else {
		NT = '0';
	}
}
//Recepcion de las tramas de cabecera del fichero
void escribirTramaME(int contador, char datos[], unsigned char longi) {
	int l = (int) longi;
	if (contador == 1) {
		strcpy(autores2, datos);
		lAutores2 = l;
	} else {
		if (contador == 2) {
			colorFichero2 = atoi(datos);
			SetConsoleTextAttribute(Pantalla, colorFichero2);
			cout << "Recibiendo fichero por ";
			if (flogM.is_open()) {
				char m[MAX];
				strcpy(m, "Recibiendo fichero por \0");escribirLogM(m);
			}//if flog_open

			if (flogE.is_open()) {
				char m[MAX];
				strcpy(m, "Recibiendo fichero por \0");escribirLogE(m);

			}//if flog_open

			for (int i = 0; i < lAutores2; i++) {
				printf("%c", autores2[i]);
			}
			printf("\n");
			if (flogM.is_open()) {
				char m[MAX];
				escribirLogM(autores2);
				strcpy(m, "\n\0");
				escribirLogM(m);
			}//if flog_open
			if (flogE.is_open()) {
				char m[MAX];
				escribirLogE(autores2);
				strcpy(m, "\n\0");;
				escribirLogE(m);
			}//if flog_open

			int color = 12 + 0 * 16;
			SetConsoleTextAttribute(Pantalla, color);

		} else {
			if (contador == 3) {
				fsal2.open(datos);
				if (fsal2.is_open()) {
					SetConsoleTextAttribute(Pantalla, colorFichero2);
					printf("Se ha conseguido crear el fichero.\n");
					if (flogM.is_open()) {
						char m[MAX];
						strcpy(m, "Se ha conseguido crear el fichero.\n\0");
						escribirLogM(m);
					}//if flog_open
					if (flogE.is_open()) {
						char m[MAX];
						strcpy(m, "Se ha conseguido crear el fichero.\n\0");
						escribirLogE(m);
					}//if flog_open

					int color = 12 + 0 * 16;
					SetConsoleTextAttribute(Pantalla, color);
					return;
				}
			}
			fsal2.write(datos, l);
		}//else
	}//else
}
