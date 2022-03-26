/*
 * Recibir.cpp
 *
 *  Created on: 1 mar. 2020
 *      Author: Enrique y Mario
 */
/*
 * Mario Bermejo Sánchez --- DNI: 76063621-E --- GRUPO 3
 * Enrique Moreno Ávila  --- DNI: 76047833-N --- GRUPO 3
 */
//CURSO -> Segundo
//Hora Laboratorio -> Martes 8:30
#include "Recibir.h"

ofstream fsal;
bool Finfich = false;
bool escribir = false;	//variable que se pone a true cuando se va a escribir el cuerpo del fichero que se recibe
int contador = 1;		//Contador de las tramas de cabecera
char carR;	//caracter que se recibe
TramaControl tramaRecibida;		//Trama que se va a recibir
int colorFichero = 0;	//Color leido del fichero
char autores[254];		//Autores leidos del fichero
int lAutores = 0;		//Longitud del campo autores

extern bool ME;
extern bool f5;	//Control de apertura de flog
extern ofstream flog;//Variable global flog para escirbir la salida en el fichero.
extern ofstream flogM;
extern ofstream flogE;
extern HANDLE Pantalla;
bool MostrarTramaExclusion = true;// desactiva el control para poder mostrar un mensaje mediante exclusion mutua durante el envio de un fichero
void TratamientoRecibirCaracter(HANDLE PuertoCOM, int &campo) {

	carR = RecibirCaracter(PuertoCOM);
	int color = 13 + 11 * 16;
	SetConsoleTextAttribute(Pantalla, color);
	if (carR != 0) {	//Recibimos datos
		switch (campo) {
		case 1:
			if (carR == 22) {
				//añadir caracter 22 sincronismo a trama auxiliar tramarecibida
				tramaRecibida.S = carR;
				campo++;
			} else {
				if (carR == '{') {
					escribir = true;
					MostrarTramaExclusion = false;
				} else {
					if (carR == '}') {
						Finfich = true;
						escribir = false;

						contador = 1;
						fsal.close();
						SetConsoleTextAttribute(Pantalla, colorFichero);
						printf("Fichero recibido.\n");

						if (flog.is_open()) {
							char m[MAX];
							strcpy(m, "Fichero recibido.\n\0");
							escribirLog(m);
						}//if log_open

					}	//if car } fin recibir fichero
				}	//else

				if(escribir == false){	//Mientras se esta recibiendo el cuerpo del fichero no entra aqui, para evitar errores con recibir del cuerpo del fichero una M o E y
											//activar el protocolo
				if (carR == 'E') {	//Si recibe E, sera esclava
					ME = true;
					int color = 11 + 0 * 16;
					SetConsoleTextAttribute(Pantalla, color);

					if(flog.is_open()){
						flog.close();
						f5 = false;
					}

					flogE.open("Prolog-e.txt");
				    printf("============================================================================\n");
				    printf("---------------------- PROTOCOLO MAESTRO-ESCLAVO ---------------------------\n");
				    printf("============================================================================\n");

					if (flogE.is_open()) {
						char m[MAX];
						strcpy(m, "============================================================================\n\0");
						escribirLogE(m);
						strcpy(m, "---------------------- PROTOCOLO MAESTRO-ESCLAVO ---------------------------\n\0");
						escribirLogE(m);
						strcpy(m, "============================================================================\n\0");
						escribirLogE(m);
						strcpy(m, "Has seleccionado ESCLAVO\n\0");
						escribirLogE(m);
					}
				    color = 2 + 0 * 16;
					SetConsoleTextAttribute(Pantalla, color);

					printf("Has seleccionado ESCLAVO\n");
					esclavoProtoc(PuertoCOM);

					if(flogE.is_open()){
					flogE.close();
					}

				}					//ifMaestro(esta es esclava)


				if (carR == 'M') {
					if (flog.is_open()) {
							flog.close();
							f5 = false;
					}
					ME = true;
					flogM.open("Prolog-m.txt");

					int color = 11 + 0 * 16;
					SetConsoleTextAttribute(Pantalla, color);

				    printf("============================================================================\n");
				    printf("---------------------- PROTOCOLO MAESTRO-ESCLAVO ---------------------------\n");
				    printf("============================================================================\n");

					if (flogM.is_open()) {
						char m[MAX];
						strcpy(m, "============================================================================\n\0");
						escribirLogM(m);
						strcpy(m, "---------------------- PROTOCOLO MAESTRO-ESCLAVO ---------------------------\n\0");
						escribirLogM(m);
						strcpy(m, "============================================================================\n\0");
						escribirLogM(m);
						strcpy(m, "Has seleccionado MAESTRO\n\0");
						escribirLogM(m);
					}//if log_open

				    color = 2 + 0 * 16;
					SetConsoleTextAttribute(Pantalla, color);

					printf("Has seleccionado MAESTRO\n");
					procedimientoMaestroProtocolo(PuertoCOM);

					if(flogM.is_open()){
					flogM.close();
					}
					ME = false;
				}					//elseMaestro(esta es maestra)
				}// if de la variable escribir == false
			}//else si recibe otro caracter distinto de 22

			break;
		case 2:
			//añadir caracter direccion a trama auxiliar tramarecibida
			tramaRecibida.D = carR;
			campo++;
			break;
		case 3:
			//añadir caracter Control a trama auxiliar tramarecibida
			tramaRecibida.C = carR;
			campo++;
			break;
		case 4:
			//añadir caracter numtrama a trama auxiliar tramarecibida
			tramaRecibida.NT = carR;
			if (tramaRecibida.C != 02) {//Si recibimos un  02 en campo control es trama de datos, por lo tanto no entramos aqui en el switch
				campo = 1;				//En otro caso, comprobamos que trama de control hemos recibido, entrando en el switch

				switch (tramaRecibida.C) {
				case 05:
					printf("Se ha recibido una trama ENQ.");
					printf("\r\n");

					if (flog.is_open()) {
						char m[MAX];
						strcpy(m, "Se ha recibido una trama ENQ.\n\0");
						escribirLog(m);
					}//if flog_open
					break;
				case 04:
					printf("Se ha recibido una trama EOT.");
					printf("\r\n");

					if (flog.is_open()) {
						char m[MAX];
						strcpy(m, "Se ha recibido una trama EOT.\n\0");
						escribirLog(m);
					}
					break;
				case 06:
					printf("Se ha recibido una trama ACK.");
					printf("\r\n");

					if (flog.is_open()) {
						char m[MAX];
						strcpy(m, "Se ha recibido una trama ACK.\n\0");
						escribirLog(m);
					}
					break;
				case 21:
					printf("Se ha recibido una trama NACK.");
					printf("\r\n");

					if (flog.is_open()) {
						char m[MAX];
						strcpy(m, "Se ha recibido una trama NACK.\n\0");
						escribirLog(m);
					}
					break;
				}//switch
			} else {
				campo++;
			}
			break;
		case 5:
			tramaRecibida.L = (unsigned char) carR;
			campo++;
		case 6:
			RecibirCadena(PuertoCOM, tramaRecibida.Datos, tramaRecibida.L);
			tramaRecibida.Datos[tramaRecibida.L] = '\0';
			campo++;
			break;
		case 7:
			tramaRecibida.BCE = (unsigned char) carR;
			campo = 1;
			unsigned char BCEControl = CalculoBCE(tramaRecibida.Datos,tramaRecibida.L);	//se calcula el bce de la trama recibida
			if (BCEControl == tramaRecibida.BCE) {//se comprueba que los bce correspondan
				//AQUI VA ESCRIBIR FICHERO
				if (Finfich == true) {
					SetConsoleTextAttribute(Pantalla, colorFichero);
					printf("El tamano del fichero es ");

					if (flog.is_open()) {
						escribirLog("El tamano del fichero es \0");
					}

					for (int i = 0; i < tramaRecibida.L; i++) {
						printf("%c", tramaRecibida.Datos[i]);
					}
					printf(" bytes.\n");

					if (flog.is_open()) {
						escribirLog(tramaRecibida.Datos);
						escribirLog(" bytes.\n\0");
					}
					MostrarTramaExclusion = true;
				}// if fich == true fichero recibido y se comienza a recibir la parte final, tamaño total etc...
				if (escribir == false && Finfich == false) {	// Si no estoy recibiendo fichero, ni estoy en su caso ultimo. Es decir, recibo normal.
					MostrarMensaje(tramaRecibida);
				} else {
					if (Finfich == false) {	//Recepcion cuerpo del fichero
						escribirTrama(contador, tramaRecibida.Datos,tramaRecibida.L);
						contador++;
					} else {
						Finfich = false;
					}
				}//else
			} else {	//If si no corresponden los BCE
				printf("Error al recibir la trama. BCE incorrecto.\n");

				if (flog.is_open()) {
					char m[MAX];
					strcpy(m, "Error al recibir la trama. BCE incorrecto.\n\0");
					escribirLog(m);
				}
			}//else
			break;
		}//switch campo
	}//if car!=0
}

void escribirTrama(int contador, char datos[], unsigned char longi) {
	int l = (int) longi;	//longitud del campo datos
	if (contador == 1) {
		strcpy(autores, datos);
		lAutores = l;	//longitud del nombre de autores
	} else {
		if (contador == 2) {
			colorFichero = atoi(datos);
			SetConsoleTextAttribute(Pantalla, colorFichero);
			cout << "Recibiendo fichero por ";

			if (flog.is_open()) {
				char m[MAX];
				strcpy(m, "Recibiendo fichero por.\n\0");
				escribirLog(m);
			}
			for (int i = 0; i < lAutores; i++) {
				printf("%c", autores[i]);
			}
			printf("\n");

			if (flog.is_open()) {
				escribirLog(autores);
				escribirLog("\n\0");
			}

		} else {
			if (contador == 3) {
				fsal.open(datos);
				if (fsal.is_open()) {
					SetConsoleTextAttribute(Pantalla, colorFichero);
					printf("Se ha conseguido crear el fichero.\n");

					if (flog.is_open()) {
						char m[MAX];
						strcpy(m, "Se ha conseguido crear el fichero.\n\0");
						escribirLog(m);
					}
					return;
				}//if fsal_open
			}
			fsal.write(datos, l);	// escribe cuerpo del fichero
		}//else
	}//else
}

//Le pasas una trama y la escribe en pantalla, el campo datos
void MostrarMensaje(TramaControl tramaRecibida) {
	int color = 9 + 10 * 16;
	SetConsoleTextAttribute(Pantalla, color);
	int i = 0;
	int tam = (int) tramaRecibida.L;
	char m[MAX];

	while (i < tam) {
		printf("%c", tramaRecibida.Datos[i]);
		m[i] = tramaRecibida.Datos[i];
		i++;
	}
	m[tam] = '\0';
	if (flog.is_open()) {
		escribirLog(m);
	}
}

