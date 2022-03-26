/*
 * MaestroEsclavo.h
 *
 *  Created on: 13 abr. 2020
 *      Author: Kike
 */

#ifndef MAESTROESCLAVO_H_
#define MAESTROESCLAVO_H_

#include "Recibir.h"

using namespace std;

int recibirME(HANDLE PuertoCOM, int &campo);
void enviarFichME(HANDLE PuertoCOM);

//void escribirTramaME(int contador, char datos[], unsigned char longi);

void MaestroSeleccion(HANDLE PuertoCOM);
void esclavoProtoc(HANDLE PuertoCOM);

void MaestroSondeo(HANDLE PuertoCOM);

void ComprobarLLegadaACK(HANDLE PuertoCOM, int campo, int &valor);
void AlternanciaNT(unsigned char &NT);



void crearTrama(HANDLE PuertoCOM, char datos[], int longi, unsigned char D, unsigned char NT);
void EnviarTramaENQ(HANDLE PuertoCOM, unsigned char D, unsigned char NT);
void EnviarTramaEOT(HANDLE PuertoCOM, unsigned char D, unsigned char NT);
void EnviarTramaACK(HANDLE PuertoCOM, unsigned char D, unsigned char NT);
void EnviarTramaNACK(HANDLE PuertoCOM, unsigned char D, unsigned char NT);

void escribirTramaME(int contador, char datos[], unsigned char longi);

#endif /* MAESTROESCLAVO_H_ */
