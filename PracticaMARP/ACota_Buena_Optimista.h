#pragma once

#include "ACota.h"

class Mapa;

//Cota que es calculada a traves de una Matriz de Coste Reducida almacenada como informacion adicional en cada nodo
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

