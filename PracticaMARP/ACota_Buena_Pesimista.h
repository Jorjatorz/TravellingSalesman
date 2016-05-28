#pragma once

#include "ACota.h"

class Mapa;

class ACota_Buena_Pesimista : public ACota
{
public:
	ACota_Buena_Pesimista(const Mapa& map);
	~ACota_Buena_Pesimista();

	virtual int calcularCoste(Nodo& X) const;

private:
	const Mapa& _map;

	int buscarMinimo(int ciudad, bool* recorridas) const;
	int _cota;

};

