#pragma once

#include "ACota.h"

class Mapa;

//Reduced cost matrix
class ACota_Buena_Optimista: public ACota
{
public:
	ACota_Buena_Optimista(const Mapa& map);
	~ACota_Buena_Optimista();

	virtual int calcularCoste(Nodo& X) const;

private:
	void generarMatrizDistancias(int*& matriz, int& sizeMatriz) const;
	int calcularMinimos(int* matriz) const;
	void cancelarFilaColumna(Nodo& X) const;
	const Mapa& _map;
};

