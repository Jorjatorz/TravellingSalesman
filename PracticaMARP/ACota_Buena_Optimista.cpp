#include "ACota_Buena_Optimista.h"

#include "ARamificacionPoda.h"
#include "Mapa.h"

ACota_Buena_Optimista::ACota_Buena_Optimista(const Mapa& map)
	:_map(map)
{
}


ACota_Buena_Optimista::~ACota_Buena_Optimista()
{
}

int ACota_Buena_Optimista::calcularCoste(Nodo& X) const
{
	int cota = 0;
	if (X.datosExtra == nullptr && X.k == 0)
	{
		generarMatrizDistancias(X.datosExtra, X.lengthDatosExtra);

		//Calcular la cota y susbstraer minimos. En este caso no cancelamos la fila y la columna por ser la ciudad inicial
		cota = calcularMinimos(X.datosExtra);
	}
	else if (X.datosExtra == nullptr)
	{
		generarMatrizDistancias(X.datosExtra, X.lengthDatosExtra);

		//Hacer infinita la fila ciudadesRecorridas[k - 1] y la columna ciudadesRecorridas[k]
		cancelarFilaColumna(X);
		//Calcular la cota y susbstraer minimos
		cota = X.distanciaOptimista + calcularMinimos(X.datosExtra) + _map.getDistanciaEntreCiudades(X.ciudadesRecorridas[X.k - 1], X.ciudadesRecorridas[X.k]);
	}
	else
	{
		//Hacer infinita la fila ciudadesRecorridas[k - 1] y la columna ciudadesRecorridas[k]
		cancelarFilaColumna(X);
		//Calcular la cota y susbstraer minimos
		cota = X.distanciaOptimista + calcularMinimos(X.datosExtra) + _map.getDistanciaEntreCiudades(X.ciudadesRecorridas[X.k - 1], X.ciudadesRecorridas[X.k]);
	}

	return cota;
}

void ACota_Buena_Optimista::generarMatrizDistancias(int*& matriz, int& sizeMatriz) const
{
	//Genera una matriz con las distancias de cada ciudad a las demas
	//(i, j) siendo la distancia desde la ciudad i a la j
	//La matrix es cuadrada y simetrica (para facilitar los calculos)
	sizeMatriz = _map.getNumeroDeCiudades() * _map.getNumeroDeCiudades();
	matriz = new int[sizeMatriz];

	for (int i = 0; i < _map.getNumeroDeCiudades(); i++)
	{
		for (int j = 0; j < _map.getNumeroDeCiudades(); j++)
		{
			int distancia = _map.getDistanciaEntreCiudades(i, j);
			distancia = distancia == 0 ? INT_MAX : distancia; //Hacer infinitas las distancia de una ciudad a si misma (i, i) = INF

			matriz[i * _map.getNumeroDeCiudades() + j] = distancia; //Equivalente a [i][j]
		}
	}
}

int ACota_Buena_Optimista::calcularMinimos(int* matriz) const
{
	auto minimoFila = [&](int i)
	{
		//Obtener minimo
		int min = INT_MAX;
		for (int j = 0; j < _map.getNumeroDeCiudades(); j++)
		{
			int dist = matriz[i * _map.getNumeroDeCiudades() + j];

			if (dist < min)
			{
				min = dist;
			}
		}

		//Restar el minimo a la fila
		if (min > 0)
		{
			for (int j = 0; j < _map.getNumeroDeCiudades(); j++)
			{
				int dist = matriz[i * _map.getNumeroDeCiudades() + j];
				if (dist != INT_MAX) //No restarselo a infinito
				{
					matriz[i * _map.getNumeroDeCiudades() + j] -= min;
				}
			}
		}

		return min;
	};

	auto minimoColumna = [&](int j)
	{
		//Obtener minimo
		int min = INT_MAX;
		for (int i = 0; i < _map.getNumeroDeCiudades(); i++)
		{
			int dist = matriz[i * _map.getNumeroDeCiudades() + j];

			if (dist < min)
			{
				min = dist;
			}
		}

		//Restar el minimo a la columna
		if (min > 0)
		{
			for (int i = 0; i < _map.getNumeroDeCiudades(); i++)
			{
				int dist = matriz[i * _map.getNumeroDeCiudades() + j];
				if (dist != INT_MAX) //No restarselo a infinito
				{
					matriz[i * _map.getNumeroDeCiudades() + j] -= min;
				}
			}
		}

		return min;
	};

	int coste = 0;
	//Filas-----------	
	//Obtener los minimos y restarlos
	for (int i = 0; i < _map.getNumeroDeCiudades(); i++)
	{
		coste = minimoFila(i);
	}
	//Columnas
	//Obtener los minimos y restarlos
	for (int j = 0; j < _map.getNumeroDeCiudades(); j++)
	{
		coste = minimoColumna(j);
	}


	return coste;
}

void ACota_Buena_Optimista::cancelarFilaColumna(Nodo& X) const
{
	int row = X.ciudadesRecorridas[X.k - 1];
	int col = X.ciudadesRecorridas[X.k];

	for (int i = 0; i < _map.getNumeroDeCiudades(); i++)
	{
		X.datosExtra[i * _map.getNumeroDeCiudades() + col] = INT_MAX;
	}

	for (int j = 0; j < _map.getNumeroDeCiudades(); j++)
	{
		X.datosExtra[row * _map.getNumeroDeCiudades() + j] = INT_MAX;
	}
}

