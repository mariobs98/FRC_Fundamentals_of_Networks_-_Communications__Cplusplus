/*
 * Recibir.h
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

#ifndef RECIBIR_H_
#define RECIBIR_H_
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <string.h>
#include "PuertoSerie.h"
#include "Tramas.h"
#include "Enviar.h"
using namespace std;

	void TratamientoRecibirCaracter(HANDLE PuertoCOM, int &campo);

	void MostrarMensaje(TramaControl tramaRecibida);

	void escribirTrama(int contador, char datos[], unsigned char longi);

	#endif /* RECIBIR_H_ */
