#include "ACota_Ingenua_Optimista.h"

#include "ARamificacionPoda.h"
#include "Mapa.h"

ACota_Ingenua_Optimista::ACota_Ingenua_Optimista(const Mapa& map)
{
	_distanciasMinimas = new int[map.getNumeroDeCiudades()];
	calcularDistanciasMinimas(map);
}


ACota_Ingenua_Optimista::~ACota_Ingenua_Optimista()
{
	delete [] _distanciasMinimas;
}

int ACota_Ingenua_Optimista::calcularCoste(Nodo& X) const
{
	int suma = X.distanciaTotal;
	for (int i = 0; i < X.numCiudades; i++)
	{
		if (!X.ciudadesUsadas[i])
		{
			suma += _distanciasMinimas[i];
		}
	}
	suma += _distanciasMinimas[X.ciudadesRecorridas[X.k]]; //Anadir la distancia minima de la ultima ciudad elegida

	return suma;
}

void ACota_Ingenua_Optimista::calcularDistanciasMinimas(const Mapa& map)
{
	for (int i = 0; i < map.getNumeroDeCiudades(); i++)
	{
		int min = INT_MAX;
		for (int j = 0; j < map.getNumeroDeCiudades(); j++)
		{
			if (j != i)
			{
				int dist = map.getDistanciaEntreCiudades(i, j);

				if (dist < min)
				{
					min = dist;
				}
			}
		}

		_distanciasMinimas[i] = min;
	}
}
