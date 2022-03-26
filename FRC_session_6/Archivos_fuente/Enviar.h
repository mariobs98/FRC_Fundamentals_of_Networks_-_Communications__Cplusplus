/*
 * Enviar.h
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

#ifndef ENVIAR_H_
#define ENVIAR_H_
#include "Recibir.h"
#include "MaestroEsclavo.h"
#include <iostream>
#include <fstream>
using namespace std;
const unsigned int MAX = 802;	//Variable para el tamano del mensaje, ahora 800 + 2 para el \0 fin de cadena y \n salto de linea (\n\0)

	void TratamientoEnviarCaracter(char car, HANDLE PuertoCOM);
	void EnviarTramaENQ(HANDLE PuertoCOM);
	void EnviarTramaEOT(HANDLE PuertoCOM);
	void EnviarTramaACK(HANDLE PuertoCOM);
	void EnviarTramaNACK(HANDLE PuertoCOM);

	void EnviarTramaMensaje(HANDLE PuertoCOM,const char mensaje[], int longitud);
	void EnviarMensaje(HANDLE PuertoCOM, char Datos[], int longitud);

	unsigned char CalculoBCE(char Datos[], unsigned char longitud);

	void leerFichero(HANDLE PuertoCOM);

	int RecogerESC();
 	void escribirLog(char mensaje[]);
 	void escribirLogM(char mensaje[]);
 	void escribirLogE(char mensaje[]);
 	void procedimientoMaestroProtocolo(HANDLE PuertoCOM);
#endif /* ENVIAR_H_ */
