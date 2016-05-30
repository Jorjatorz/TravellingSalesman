#pragma once

#include "ACota.h"

class Mapa;

//Cota que es calculada en el constructor usando el algoritmo del Vecino mas Proximo
class ACota_Buena_Pesimista : public ACota
{
public:
	ACota_Buena_Pesimista(const Mapa& map);
	~ACota_Buena_Pesimista();

	virtual int calcularCoste(Nodo& X) const;

private:
	const Mapa& _map;

	//Funcion que ejecuta el algoritmo del Vecino mas Proximo
	int buscarMinimo(int ciudad, bool* recorridas) const;
	int _cota;

};

