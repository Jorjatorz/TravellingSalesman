#pragma once

#include "ACota.h"

class Mapa;

class ACota_Ingenua_Pesimista : public ACota
{
public:
	ACota_Ingenua_Pesimista(const Mapa& map);
	~ACota_Ingenua_Pesimista();

	virtual int calcularCoste(int distanciaActual, int numCiudades, bool ciudadUsada[]) const;

private:
private:
	//Dado un mapa, calcula la distancia mayor de una ciudad a las demas.
	//Es decir, mira todas las distancia desde Madrid a las demas ciudades y guarda la maxima
	//O(n^2)
	void calcularDistanciasMaximas(const Mapa& map);
	int *_distanciasMaximas;

};

