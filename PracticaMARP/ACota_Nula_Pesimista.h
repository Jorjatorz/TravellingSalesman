#pragma once
#include "ACota.h"

class ACota_Nula_Pesimista : public ACota
{
public:
	ACota_Nula_Pesimista();
	~ACota_Nula_Pesimista();

	virtual int calcularCoste(int distanciaActual, int numCiudades, bool ciudadUsada[]) const;

};

