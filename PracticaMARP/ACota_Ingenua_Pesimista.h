#pragma once

#include "ACota.h"

class Mapa;

class ACota_Ingenua_Pesimista : public ACota
{
public:
	ACota_Ingenua_Pesimista(const Mapa& map);
	~ACota_Ingenua_Pesimista();

	//Suma la distancia maximas de las ciudades aun sin elegir.
	//Esta distancia maxima ha sido calculada anteriormente
	//O(n)
	virtual int calcularCoste(Nodo& X) const;

private:
	//Dado un mapa, calcula la distancia mayor de una ciudad a las demas.
	//Es decir, mira todas las distancia desde Madrid a las demas ciudades y guarda la maxima
	//O(n^2)
	void calcularDistanciasMaximas(const Mapa& map);
	int *_distanciasMaximas;

};

