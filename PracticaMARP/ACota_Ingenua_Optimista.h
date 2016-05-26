#pragma once

#include "ACota.h"

class Mapa;

class ACota_Ingenua_Optimista : public ACota
{
public:
	ACota_Ingenua_Optimista(const Mapa& map);
	~ACota_Ingenua_Optimista();

	//Suma la distancia minima de las ciudades aun sin elegir.
	//Esta distancia minima ha sido calculada anteriormente
	//O(n)
	virtual int calcularCoste(Nodo& X) const;

private:
	//Dado un mapa, calcula la distancia menor de una ciudad a las demas.
	//Es decir, mira todas las distancia desde Madrid a las demas ciudades y guarda la minima
	//O(n^2)
	void calcularDistanciasMinimas(const Mapa& map);
	int *_distanciasMinimas;

};

