#include "ACota_Buena_Pesimista.h"

#include "ARamificacionPoda.h"
#include "Mapa.h"

ACota_Buena_Pesimista::ACota_Buena_Pesimista(const Mapa& map)
	:_map(map)
{
	int coste = 0;
	bool* recorridas = new bool[_map.getNumeroDeCiudades()];
	//memcpy(recorridas, X.ciudadesUsadas, sizeof(bool) * _map.getNumeroDeCiudades());
	memset(recorridas, false, sizeof(bool) * _map.getNumeroDeCiudades());
	coste = buscarMinimo(0, recorridas);



	delete[] recorridas;
	_cota = coste;
}


ACota_Buena_Pesimista::~ACota_Buena_Pesimista()
{
}

int ACota_Buena_Pesimista::calcularCoste(Nodo& X) const
{
	return X.distanciaTotal + _cota;
}


int ACota_Buena_Pesimista::buscarMinimo(int ciudad, bool* recorridas) const
{
	if (ciudad == -1)
	{
		return 0;
	}

	//Buscar el minimo de la fila
	int min = INT_MAX;
	int indx = -1;
	for (int j = 0; j < _map.getNumeroDeCiudades(); j++)
	{
		if (!recorridas[j])
		{
			int dist = _map.getDistanciaEntreCiudades(ciudad, j);

			if (dist < min)
			{
				min = dist;
				indx = j;
			}
		}
	}
	
	if (min == INT_MAX)
	{
		min = _map.getDistanciaEntreCiudades(ciudad, 0);
	}
	else
	{
		recorridas[indx] = true;
	}

	return min + buscarMinimo(indx, recorridas);
}
