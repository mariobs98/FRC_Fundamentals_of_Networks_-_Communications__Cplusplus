
//AUTORES
//Mario Bermejo Sánchez
//Enrique Moreno Ávila
//CURSO -> Segundo
//Hora Laboratorio -> Martes 8:30

#ifndef TRAMAS_H_
#define TRAMAS_H_

struct TramaControl{
	unsigned char S; //Sincronismo = SYN = 22
	unsigned char D; //Direccion=(En principio fijo a ’T’)
	unsigned char C; //Control = (05 (ENQ), 04 (EOT), 06 (ACK), 21 (NACK))
	unsigned char NT; //Numero de Trama = (En principio fijo a ‘0’)
	unsigned char L;  //Long(Longitud del campo de datos);
	char Datos[255]; //Datos[255];
	unsigned char BCE;//(Siempre debe tomar siempre valores entre 1 y 254);
};


#endif /* TRAMAS_H_ */
