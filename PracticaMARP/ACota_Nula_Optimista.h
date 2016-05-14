#pragma once

#include "ACota.h"

//Cota que no poda (devuelve siempre Infinito)
class ACota_Nula_Optimista: public ACota
{
public:
	ACota_Nula_Optimista();
	~ACota_Nula_Optimista();

	virtual int calcularCoste(int distanciaActual, int numCiudades, bool ciudadUsada[]) const;

};

