/*
 * Enviar.cpp
 *
 *  Created on: 1 mar. 2020
 *      Author: Enrique
 */
/*
 * Mario Bermejo Sánchez --- DNI: 76063621-E --- GRUPO 3
 * Enrique Moreno Ávila  --- DNI: 76047833-N --- GRUPO 3
 */
//CURSO -> Segundo
//Hora Laboratorio -> Martes 8:30
#include "Enviar.h"

using namespace std;
char mensaje[MAX]; //Mensaje para enviar, el tamano viene dado por la variable MAX
unsigned short int indiceMensaje = 0;//Indice que lleva la posicion en mensaje;
bool f5 = false;	//recoger f5
extern bool ME;
extern ofstream flog;//Variable global flog para escirbir la salida en el fichero.
extern ofstream flogM;
extern ofstream flogE;
extern HANDLE Pantalla;
extern bool MostrarTramaExclusion;
void EnviarTramaENQ(HANDLE PuertoCOM) {
	EnviarCaracter(PuertoCOM, 22);
	EnviarCaracter(PuertoCOM, 'T');
	EnviarCaracter(PuertoCOM, 05);
	EnviarCaracter(PuertoCOM, '0');
	printf("Se ha enviado una trama ENQ.\n");
	if (flog.is_open()) {
		char m[MAX];
		strcpy(m, "Se ha enviado una trama ENQ.\n\0");
		escribirLog(m);
	}
}

void EnviarTramaEOT(HANDLE PuertoCOM) {
	EnviarCaracter(PuertoCOM, 22);
	EnviarCaracter(PuertoCOM, 'T');
	EnviarCaracter(PuertoCOM, 04);
	EnviarCaracter(PuertoCOM, '0');
	printf("Se ha enviado una trama EOT.\n");
	if (flog.is_open()) {
		char m[MAX];
		strcpy(m, "Se ha enviado una trama EOT.\n\0");
		escribirLog(m);
	}
}

void EnviarTramaACK(HANDLE PuertoCOM) {
	EnviarCaracter(PuertoCOM, 22);
	EnviarCaracter(PuertoCOM, 'T');
	EnviarCaracter(PuertoCOM, 06);
	EnviarCaracter(PuertoCOM, '0');
	printf("Se ha enviado una trama ACK.\n");
	if (flog.is_open()) {
		char m[MAX];
		strcpy(m, "Se ha enviado una trama ACK.\n\0");
		escribirLog(m);
	}
}

void EnviarTramaNACK(HANDLE PuertoCOM) {
	EnviarCaracter(PuertoCOM, 22);
	EnviarCaracter(PuertoCOM, 'T');
	EnviarCaracter(PuertoCOM, 21);
	EnviarCaracter(PuertoCOM, '0');
	printf("Se ha enviado una trama NACK.\n");
	if (flog.is_open()) {
		char m[MAX];
		strcpy(m, "Se ha enviado una trama NACK.\n\0");
		escribirLog(m);
	}
}

unsigned char CalculoBCE(char Datos[], unsigned char longitud) {
	unsigned char BCE = Datos[0];
	for (int i = 1; i < longitud; i++) {
		BCE = BCE ^ Datos[i];
	}
	if (BCE == 0 || BCE == 255) {
		BCE = 1;
	}
	return BCE;
}

void TratamientoEnviarCaracter(char car, HANDLE PuertoCOM) {
	int color = 0 + 3 * 16;
	SetConsoleTextAttribute(Pantalla, color);
	switch (car) {
	case 0:			//pulsar FN
		car = getch();
		if (car == 59) {				//si F1
			EnviarTramaMensaje(PuertoCOM, mensaje, indiceMensaje);
			printf("\n");

			indiceMensaje = 0;
		}
		if (car == 60) {			//si F2
			int opcion = 0;
			color = 12 + 15*16;
			SetConsoleTextAttribute(Pantalla, color);
			printf("Selecciona la trama de control a enviar: \n");//mostramos opciones de tramas a elegir
			printf("1 --Trama ENQ \n");
			printf("2 --Trama EOT \n");
			printf("3 --Trama ACK \n");
			printf("4 --Trama NACK \n");
			if (flog.is_open()) {
				char m[MAX];
				strcpy(m,"Selecciona la trama de control a enviar: \n1 --Trama ENQ \n2 --Trama EOT \n3 --Trama ACK \n4 --Trama NACK \n\0");
				escribirLog(m);
			}
			cin >> opcion;
			switch (opcion) {
			case 1:
				EnviarTramaENQ(PuertoCOM);			//trama enq
				break;
			case 2:
				EnviarTramaEOT(PuertoCOM);			//trama eot
				break;
			case 3:
				EnviarTramaACK(PuertoCOM);			//trama ack
				break;
			case 4:
				EnviarTramaNACK(PuertoCOM);			//trama nack
				break;
			default://mensaje de error, se ha seleccionado una trama incorrecta
				printf("Selecciona una opcion adecuada. \n");

				if (flog.is_open()) {
					char m[MAX];
					strcpy(m, "Selecciona una opcion adecuada. \n\0");
					escribirLog(m);
				}//if flog_open

			}//switch
		}
		if (car == 61) { // si f3
			leerFichero(PuertoCOM);
		}
		if (car == 63 && !f5) { //si f5 log
			if(!ME){
			f5 = true;
			flog.open("log.txt");
			}
		}
		if (car == 64) {
			ME = true;
			if (flog.is_open()) {
				flog.close();
				f5 = false;
			}//Si al estrar en maestro-esclavo flog de F5 esta abierto, se cierra.

			int color = 11 + 0 * 16;
			SetConsoleTextAttribute(Pantalla, color);
		    printf("============================================================================\n");
		    printf("---------------------- PROTOCOLO MAESTRO-ESCLAVO ---------------------------\n");
		    printf("============================================================================\n");

			color = 12 + 0 * 16;
			SetConsoleTextAttribute(Pantalla, color);
			int opcion = 0;
			printf("Selecciona una opcion: \n");
			printf("1: Maestro.\n");
			printf("2: Esclavo.\n");
			cin >> opcion;
			if (opcion == 1) {
				flogM.open("Prolog-m.txt");
				if (flogM.is_open()) {
					char m[MAX];
					strcpy(m, "============================================================================\n\0");
					escribirLogM(m);
					strcpy(m, "---------------------- PROTOCOLO MAESTRO-ESCLAVO ---------------------------\n\0");
					escribirLogM(m);
					strcpy(m, "============================================================================\n\0");
					escribirLogM(m);
					strcpy(m, "Selecciona una opcion: \n1: Maestro.\n2: Esclavo.\n\0");
					escribirLogM(m);
				}//if log_open

				EnviarCaracter(PuertoCOM, 'E'); //La otra estacion sera esclava
				procedimientoMaestroProtocolo(PuertoCOM);
			} else {//el esclavo se queda esperando si a o b para ejecutar el procedimiento de sondeo o seleccion
				flogE.open("Prolog-e.txt");
				if (flogE.is_open()) {
					char m[MAX];
					strcpy(m, "============================================================================\n\0");
					escribirLogE(m);
					strcpy(m, "---------------------- PROTOCOLO MAESTRO-ESCLAVO ---------------------------\n\0");
					escribirLogE(m);
					strcpy(m, "============================================================================\n\0");
					escribirLogE(m);
					strcpy(m, "Selecciona una opcion: \n1: Maestro.\n2: Esclavo\nHa seleccionado ESCLAVO.\n\0");
					escribirLogE(m);
				}//if log_open
				printf("Ha seleccionado ESCLAVO.\n\0");
				EnviarCaracter(PuertoCOM, 'M');
				esclavoProtoc(PuertoCOM);
			}
			opcion = 0;

			if(flogM.is_open()){
			flogM.close();
			}

			if(flogE.is_open()){
			flogE.close();
			}
			ME = false;
		}
		break;
	case 8:		//retroceso
		if (indiceMensaje > 0) {
			indiceMensaje--;
			printf("%c", '\b'); //este hace que el cursor vaya uno hacia la izquierda
			printf("%c", ' '); //pone la posición que queremos borrar(este vuelve a la posición anterior de la derecha)
			printf("%c", '\b'); //este hace que el cursor vaya uno hacia la izquierda para escribir
		}
		break;
	case 13: //Intro
		printf("\n"); // hacemos un salto de linea
		mensaje[indiceMensaje] = '\n';
		indiceMensaje++;
		break;
	case 27:
		break;//No hacemos nada, registramos la tecla esc y salimos de la aplicacion
	default:
		if (indiceMensaje < MAX - 2) {
			int color = 0 + 6 * 16;
			SetConsoleTextAttribute(Pantalla, color);
			printf("%c", car);
			mensaje[indiceMensaje] = car;//almacenamos el caracter en el vector
			indiceMensaje++;
		}
		break;
	}//switch
}	//tratamientoEnviarCaracter

void EnviarTramaMensaje(HANDLE PuertoCOM, const char mensaje[], int longitud) {
	char Datos[255];
	int campo = 1;
	int resta = 0;
	int longTrama = 0;
	int contadorGlobal = 0;
	bool dentro = true;
	//Realizamos la resta de 254(la longitud de la trama a enviar) a la longitud del mensaje total. Si el resultado es negativo o igual a 0,
	//enviamos una trama con la longitud de caracteres que contenga el mensaje, en caso de ser mayor, enviamos una trama de 254 caracteres y luego realizamos la misma
	// resta, y volvemos a comprobar en que caso nos situamos.
	resta = longitud - 254;
	while (dentro) {

		if (resta < 0) {
			resta = 254 + resta;
			for (int i = 0; i < resta; i++) {
				Datos[i] = mensaje[contadorGlobal];
				contadorGlobal++;
				longTrama++;
			}//for
			Datos[longTrama] = '\n';
			Datos[longTrama + 1] = '\0';
			EnviarMensaje(PuertoCOM, Datos, longTrama + 1);


			if (flog.is_open()) {
				char m[MAX];
				escribirLog(Datos);
			}// if flog_open

			if(MostrarTramaExclusion){
			TratamientoRecibirCaracter(PuertoCOM, campo);	//Exclusion, enviamos y vemos si recibimos
			}
			dentro = false;
		} else {
			for (int i = 0; i < 254; i++) {
				Datos[i] = mensaje[contadorGlobal];
				contadorGlobal++;
				longTrama++;
			}//for
			EnviarMensaje(PuertoCOM, Datos, longTrama);


			if (flog.is_open()) {
				char m[MAX];
				escribirLog(Datos);
			}// if flog_open

			if(MostrarTramaExclusion){
			TratamientoRecibirCaracter(PuertoCOM, campo);	//Exclusion, enviamos y vemos si recibimos
			}
		}//else
		longTrama = 0;
		resta = resta - 254;

	}//while
}	//EnviarTramaMensaje

void EnviarMensaje(HANDLE PuertoCOM, char Datos[], int longitud) {
	unsigned char longitudC = (unsigned char) longitud;
	EnviarCaracter(PuertoCOM, 22);
	EnviarCaracter(PuertoCOM, 'T');	//En este punto fijo a T siempre
	EnviarCaracter(PuertoCOM, 02);
	EnviarCaracter(PuertoCOM, '0');  //En este punto fijo a 0 siempre
	EnviarCaracter(PuertoCOM, longitudC);
	EnviarCadena(PuertoCOM, Datos, longitud);
	EnviarCaracter(PuertoCOM, CalculoBCE(Datos, (unsigned char) longitud));
}

void leerFichero(HANDLE PuertoCOM) {
	char cadena[255];
	int campo = 1;
	ifstream fent;
	fent.open("fichero-e.txt");
	int longi = 0;
	int total = 0;
	int esc = -1;

	if (fent.is_open()) {
		EnviarCaracter(PuertoCOM, '{');	//Abrimos conexion con la otra estacion para enviar fichero con {

		fent.getline(cadena, 254, '\n');	//1 Nombre del emisor
		longi = fent.gcount(); //esto es lo que vale la longitud de esa linea
		EnviarMensaje(PuertoCOM, cadena, longi - 1);
		cout << "Enviando fichero por ";

		if (flog.is_open()) {
			char m[MAX];
			strcpy(m, "Enviando fichero por \0");
			escribirLog(m);
		}

		for (int i = 0; i < longi; i++) {	//Escribimos en pantalla quien envia el fichero
			printf("%c", cadena[i]);
		}
		printf("\n");

		if (flog.is_open()) {
			escribirLog(cadena);
			escribirLog("\n\0");
		}

		fent.getline(cadena, 254, '\n');	//2 Color a mostrar en pantalla
		longi = fent.gcount();
		EnviarMensaje(PuertoCOM, cadena, longi - 1);

		fent.getline(cadena, 254, '\n');	//3 Nombre que tendra el fichero receptor
		longi = fent.gcount();
		EnviarMensaje(PuertoCOM, cadena, longi - 1);

		esc = RecogerESC();	//Comrpobamos si se pulsa escape para cancelar la accion

		while (!fent.eof() && esc != 1) {	//si final de fichero o esc == 1 salimos (si esc == 1 es que se ha pulsado escape)
			fent.read(cadena, 254);
			longi = fent.gcount();
			esc = RecogerESC();
			if (longi > 0) {
				cadena[longi] = '\0';
				total = total + longi;
				EnviarMensaje(PuertoCOM, cadena, longi);
				TratamientoRecibirCaracter(PuertoCOM, campo);	//Exclusion, enviamos y vemos si recibimos
			}
		}//while
		fent.close();	//Cerramos flujo de fichero

		EnviarCaracter(PuertoCOM, '}'); //Notificamos a estacion receptora  de fin de envio de fichero con }

		sprintf(cadena, "%d", total);
		int total2 = strlen(cadena);
		EnviarMensaje(PuertoCOM, cadena, total2);	//Enviamos longitud total del cuerpo del fichero

		//LONGITUD FICHERO
		int color = 0 + 3 * 16;
		SetConsoleTextAttribute(Pantalla, color);
		printf("Fichero Enviado");
		printf("\n");

		if (flog.is_open()) {
			char m[MAX];
			strcpy(m, "Fichero Enviado\n\0");
			escribirLog(m);
		}

	} else {
		printf("ERROR: El fichero fichero-e.txt no existe\n");
		if (flog.is_open()) {
			char m[MAX];
			strcpy(m, "ERROR: El fichero fichero-e.txt no existe\n\0");
			escribirLog(m);
		}
	}//else si no existe el fichero a abrir
}

int RecogerESC() {
	if (kbhit())	//Detecta una pulsacion
	{
		char car = getch();		//Recogemos la tecla pulsada
		if (car == 27) {	// si la tecla es escape devolvemos 1 si no, -1
			return 1;
		}
	}
	return -1;
}

//Se le pasa un vector char con un mensaje el cual se escribira en el fichero log
void escribirLog(char mensaje[]) {
	flog.write(mensaje, strlen(mensaje));
	flog.flush();
}

void escribirLogM(char mensaje[]) {
	flogM.write(mensaje, strlen(mensaje));
	flogM.flush();
}

void escribirLogE(char mensaje[]) {
	flogE.write(mensaje, strlen(mensaje));
	flogE.flush();
}

void procedimientoMaestroProtocolo(HANDLE PuertoCOM) {
	int opcion = 0;
	int color = 2 + 0 * 16;

	SetConsoleTextAttribute(Pantalla, color);
	printf("Ha seleccionado MAESTRO.Selecciona el tipo de operacion.\n");
	printf("1: Operacion de seleccion.\n");
	printf("2: Operacion de sondeo.\n");//Tipo de operacion que deseamos hacer, se introduce R si seleccion y T si sondeo,
										//se enviara una trama de establecimiento a la estacion esclava indicando lo seleccionado
	if (flogM.is_open()) {
		char m[MAX];
		strcpy(m, "Ha seleccionado MAESTRO.Selecciona el tipo de operacion.\n1: Operacion de seleccion.\n2: Operacion de sondeo.\n\0");
		escribirLogM(m);
	}//if log_open

	cin >> opcion;
	if (opcion == 1) {
		MaestroSeleccion(PuertoCOM);
	} else {
		if (opcion == 2) {
			MaestroSondeo(PuertoCOM);
		}
	}//else
}

