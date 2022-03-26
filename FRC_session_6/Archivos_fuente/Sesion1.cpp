//============================================================================
// ----------- PRÁCTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES -----------
// ---------------------------- CURSO 2019/20 --------------------------------
// ----------------------------- SESION1.CPP ---------------------------------
//============================================================================

/*
 * Mario Bermejo Sánchez --- DNI: 76063621-E --- GRUPO 3
 * Enrique Moreno Ávila  --- DNI: 76047833-N --- GRUPO 3
 */
//CURSO -> Segundo
//Hora Laboratorio -> Martes 8:30

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <string.h>
#include "PuertoSerie.h"
#include "Tramas.h"
#include "Enviar.h"
#include "Recibir.h"
#include "inicio.h"

using namespace std;

HANDLE PuertoCOM;
HANDLE Pantalla;

ofstream flog;
ofstream flogM;
ofstream flogE;

int main()
{
    char carE;
    int puerto;//Numero del puerto a elegir.
    char PSerie[5];//Puerto a utilizar.
    int nVel;//Numero de la velocidad a elegir
    int vel = 0; //Velocidad del puerto.
    int campo = 1;
    int color;
    //Encabezado
    printf("============================================================================\n");
    printf("----------- PRACTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES ------------\n");
    printf("---------------------------- CURSO 2019/20 ---------------------------------\n");
    printf("----------------------------- SESION1.CPP ----------------------------------\n");
    printf("============================================================================\n\n");

    //Abrimos el puerto. Para ello necesitamos indicar los siguientes parámetros:
    // - Nombre del puerto a abrir: ("COM1", "COM2", "COM3", ...).
    // - Velocidad: (1200, 1400, 4800, 9600, 19200, 38400, 57600, 115200).
    // - Número de bits en cada byte enviado o recibido: (4, 5, 6, 7, 8).
    // - Paridad: (0=sin paridad, 1=impar, 2=par, 3=marca, 4=espacio).
    // - Bits de stop: (0=1 bit, 1=1.5 bits, 2=2 bits).

    //ELECCION PUERTO
    Pantalla = GetStdHandle(STD_OUTPUT_HANDLE);
    color = 9 + 15*16;
    SetConsoleTextAttribute(Pantalla, color);

    if(1 == eleccionPuerto(PSerie,puerto)){		//eleccionPuerto devuelve 1 si se selecciona un puerto no valido, terminando la ejecucion del codigo debido al error.
    	return 1;	//Cierre de practica
    }

    printf("\n");

    //ELECCION VELOCIDAD
    if(1 == eleccionVelocidad(vel, nVel)){		//eleccionVelocidad devuelve 1 si se selecciona un puerto no valido, terminando la ejecucion del codigo debido al error.
    	    printf("Error al abrir el puerto, has seleccionado opciones incorrectas.\n");
    	    getch();
    	    return 1;
    }

    printf("\n");

    //ABRIR PUERTO
    PuertoCOM = AbrirPuerto(PSerie, vel, 8, 0, 0); //Abrimos el puerto (en la sala siempre abrimos el COM1)

    if(PuertoCOM == NULL)		//Si ha dado error la apertura del puerto, terminamos la ejecucion debido al error
    {
        printf("Error al abrir el puerto %s\n",PSerie);
        getch();
        return (1);
    }
    else{
        printf("Se ha abierto el puerto ");
        printf(PSerie);
        printf(" a una velocidad de ");
        printf("%i\n",vel);
    }

    // Lectura y escritura simultánea de caracteres:
    while(carE != 27)
    {
    	TratamientoRecibirCaracter(PuertoCOM,campo);
        if (kbhit())
        {
            carE = getch();
            TratamientoEnviarCaracter(carE, PuertoCOM);
        }
    }//while
	flog.close();
// Cerramos el puerto:
   CerrarPuerto(PuertoCOM);

   return 0;
}
