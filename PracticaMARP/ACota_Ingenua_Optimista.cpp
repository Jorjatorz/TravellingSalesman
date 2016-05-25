#include "ACota_Ingenua_Optimista.h"

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

int ACota_Ingenua_Optimista::calcularCoste(int distanciaActual, int numCiudades, bool ciudadUsada[], int* datosExtra, int& lengthDatosExtra) const
{
	int suma = distanciaActual;
	for (int i = 0; i < numCiudades; i++)
	{
		if (!ciudadUsada[i])
		{
			suma += _distanciasMinimas[i];
		}
	}

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
