/*
 * inicio.cpp
 *
 *  Created on: 25 mar. 2020
 *      Author: Mario Bermejo
 */

#include "inicio.h"
using namespace std;
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string.h>

/**
 * Modulo utilizado para la eleccion de puerto.
 * char PSerie[]: Cadena que guarda el puerto a utilizar.
 * int puerto: Entero utilizado para elegir el puerto.
 */
int eleccionPuerto(char PSerie[], int &puerto){

    printf("Seleccionar el puerto a utilizar:\n");
    printf("1. COM1\n");
    printf("2. COM2\n");
    printf("3. COM3\n");
    printf("4. COM4\n");
    bool salir = false;
    while(!salir){
	cin>>puerto;
	switch(puerto){
	case 1:
		strcpy(PSerie,"COM1");
		salir = true;
		break;
	case 2:
		strcpy(PSerie,"COM2");
		salir = true;
		break;
	case 3:
		strcpy(PSerie,"COM3");
		salir = true;
		break;
	case 4:
		strcpy(PSerie,"COM4");
		salir = true;
		break;
	default:
		printf("Has seleccionado un puerto no valido\n");
		}
    }
	return 0;
}

/**
 * Modulo utilizado para la eleccion de velocidad.
 * int vel: Entero que guarda la velocidad a utilizar en el puerto.
 * int nVel: Numero utilizado para elegir la velocidad.
 */
int eleccionVelocidad(int &vel, int &nVel){

    printf("Seleccionar la velocidad de transmision:\n");
    printf("1. 1200 \n");
    printf("2. 2400 \n");
    printf("3. 4800 \n");
    printf("4. 9600 \n");
    printf("5. 19200 \n");
    bool salir = false;
    while(!salir){
    cin>>nVel;
    switch(nVel){
    case 1:
    	vel = 1200;
    	salir = true;
    	break;
    case 2:
    	vel = 2400;
    	salir = true;
    	break;
    case 3:
    	vel = 4800;
    	salir = true;
    	break;
    case 4:
    	vel = 9600;
    	salir = true;
    	break;
    case 5:
    	vel = 19200;
    	salir = true;
    	break;
	default:
		printf("Has seleccionado una velocidad no valida\n");
    	}
    }
    return 0;
}
