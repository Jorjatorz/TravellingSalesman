#include "ACota_Ingenua_Pesimista.h"

#include "ARamificacionPoda.h"
#include "Mapa.h"

ACota_Ingenua_Pesimista::ACota_Ingenua_Pesimista(const Mapa& map)
{
	_distanciasMaximas = new int[map.getNumeroDeCiudades()];
	calcularDistanciasMaximas(map);
}


ACota_Ingenua_Pesimista::~ACota_Ingenua_Pesimista()
{
	delete[] _distanciasMaximas;
}

int ACota_Ingenua_Pesimista::calcularCoste(Nodo& X) const
{
	int suma = X.distanciaTotal;
	for (int i = 0; i < X.numCiudades; i++)
	{
		if (!X.ciudadesUsadas[i])
		{
			suma += _distanciasMaximas[i];
		}
	}

	suma += _distanciasMaximas[X.ciudadesRecorridas[X.k]]; //Anadir la distancia maxima de la ultima ciudad elegida

	return suma;
}

void ACota_Ingenua_Pesimista::calcularDistanciasMaximas(const Mapa& map)
{
	for (int i = 0; i < map.getNumeroDeCiudades(); i++)
	{
		int max = 0;
		for (int j = 0; j < map.getNumeroDeCiudades(); j++)
		{
			int dist = map.getDistanciaEntreCiudades(i, j);

			if (dist > max)
			{
				max = dist;
			}
		}

		_distanciasMaximas[i] = max;
	}
}
