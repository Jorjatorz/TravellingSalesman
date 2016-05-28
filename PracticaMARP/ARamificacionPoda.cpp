#include "ARamificacionPoda.h"

#include <queue>

#include "Mapa.h"
#include "ACota.h"
#include <iostream>
#include <time.h>
#include <functional>

ARamificacionPoda::ARamificacionPoda(const Mapa& mapa, const ACota& optimista, const ACota& pesimita)
	:_mapa(mapa), _cOptimista(optimista), _cPesimista(pesimita)
{
}


ARamificacionPoda::~ARamificacionPoda()
{
}

ARamificacionPoda::sInfoAlgoritmo ARamificacionPoda::ejecutarAlgoritmo()
{
	sInfoAlgoritmo informacionToReturn(_mapa.getNumeroDeCiudades());

	Nodo Y(_mapa.getNumeroDeCiudades());
	std::priority_queue<Nodo, std::vector<Nodo>, Nodo::comparator> C;

	Y.ciudadesRecorridas[0] = 0;
	Y.ciudadesUsadas[0] = true;
	Y.distanciaOptimista = _cOptimista.calcularCoste(Y);

	informacionToReturn.distanciaOptima = _cPesimista.calcularCoste(Y); //En nuestro problema siempre hay solucion (si no, esto valdria infinito)
	std::cout << "CP: " << informacionToReturn.distanciaOptima << std::endl;
	informacionToReturn.tiempoTotal = clock();

	C.push(Y);
	while (!C.empty() && C.top().distanciaOptimista <= informacionToReturn.distanciaOptima)
	{
		Y = C.top(); 
		C.pop();

		Nodo X(_mapa.getNumeroDeCiudades());
		informacionToReturn.numNodosExplorados++;
		for (int i = 1; i < _mapa.getNumeroDeCiudades(); i++)
		{
			//Este nodo va a ser explorado
		
			X = Y;
			X.k++;
			//Si esta ciudad no ha sido usada con anterioridad
			if (!X.ciudadesUsadas[i])
			{
				int nuevaDistancia = Y.distanciaTotal + _mapa.getDistanciaEntreCiudades(X.ciudadesRecorridas[X.k - 1], i);
				X.distanciaTotal = nuevaDistancia;
				X.ciudadesRecorridas[X.k] = i;
				X.ciudadesUsadas[i] = true;

				//Si es solicion
				if (X.k == (_mapa.getNumeroDeCiudades() - 1))
				{
					X.distanciaTotal += _mapa.getDistanciaEntreCiudades(X.ciudadesRecorridas[X.k], X.ciudadesRecorridas[0]); //Distancia de la ultima ciudad a la primera

					if (X.distanciaTotal < informacionToReturn.distanciaOptima) //Al principio, informacionToReturn.distanciaOptima es infinito
					{
						informacionToReturn.copiarSolucion(X, _mapa);
					}
				}
				else //Si no es solucion
				{
					//Si es prometedor, seguir explorandolo
					X.distanciaOptimista = _cOptimista.calcularCoste(X);
					if (X.distanciaOptimista <= informacionToReturn.distanciaOptima)
					{
						C.push(X);
					}

					int cP = _cPesimista.calcularCoste(X);
					if (cP < informacionToReturn.distanciaOptima)
					{
						std::cout << "CP: " << cP << std::endl;
						informacionToReturn.distanciaOptima = cP;
					}
				}

				X.ciudadesUsadas[i] = false;


			}
		}
	}

	informacionToReturn.tiempoTotal = (clock() - informacionToReturn.tiempoTotal) / CLOCKS_PER_SEC;
	informacionToReturn.tiempoMedioNodo = informacionToReturn.tiempoTotal / informacionToReturn.numNodosExplorados;

	return informacionToReturn;
}

void ARamificacionPoda::sInfoAlgoritmo::copiarSolucion(Nodo X, const Mapa& mapa)
{
	distanciaOptima = X.distanciaTotal;
	mapa.ciudadesToStringArray(recorridoCiudades, X.ciudadesRecorridas);
	numNodosExploradosOptima = numNodosExplorados;
}

void ARamificacionPoda::sInfoAlgoritmo::print()
{
	long long int nodosTeoricos = calcularNodos();
	std::cout << "Numero de ciudades recorridas: " << numCiudades << std::endl;
	std::cout << "Distancia optima: " << distanciaOptima << std::endl;
	std::cout << "Ciclo de ciudades: " << recorridoCiudades << std::endl;
	std::cout << "Numero de nodos teoricos a explorar: " << nodosTeoricos << std::endl;
	std::cout << "Numero nodos explorados: " << numNodosExplorados << std::endl;
	std::cout << "Numero nodos explorados al encontrar el optimo: " << numNodosExploradosOptima << std::endl;
	std::cout << "Tiempo total del algoritmo: " << tiempoTotal << " segundos." << std::endl;
	std::cout << "Tiempo medio por nodo explorado: " << tiempoMedioNodo << " segundos." << std::endl;
	std::cout << "Tiempo total teorico del algoritmo: " << tiempoMedioNodo * nodosTeoricos << " segundos." << std::endl; //El tiempo medio que ha tardado un nodo por el numero de nodos totales (teoricos) a explorar.
	std::cout << "Porcentaje mejora en tiempo del algoritmo: " << (1 - (tiempoTotal / (tiempoMedioNodo * nodosTeoricos))) * 100 << " %" << std::endl;
}

long long int ARamificacionPoda::sInfoAlgoritmo::calcularNodos()
{
	std::function<int(int)> factorial = [&](int n)
	{
		return n < 2 ? 1 : n * factorial(n - 1);
	};

	double sum = 0;
	for (int i = 1; i < numCiudades; i++)
	{
		sum += 1.0 / factorial(i);
	}

	return factorial(numCiudades - 1) * sum;
}

Nodo::Nodo(int numeroCiudades)
{
	numCiudades = numeroCiudades;
	k = 0;
	distanciaTotal = 0; //Coste real de recorrer las ciudades en el orden de ciudadesRecorridas
	distanciaOptimista = 0;
	ciudadesRecorridas = new int[numeroCiudades]; //Array con el orden en el que se tienen que recorrer las ciudades
	ciudadesUsadas = new bool[numeroCiudades]; //True si esa ciudad ya ha sido explorada
	memset(ciudadesUsadas, false, numeroCiudades * sizeof(bool));

	datosExtra = nullptr;
	lengthDatosExtra = 0;
}

Nodo::Nodo(const Nodo& aCopiar)
{

	numCiudades = aCopiar.numCiudades;
	k = aCopiar.k;
	distanciaTotal = aCopiar.distanciaTotal;
	distanciaOptimista = aCopiar.distanciaOptimista;
	ciudadesRecorridas = new int[numCiudades];
	ciudadesUsadas = new bool[numCiudades];

	datosExtra = nullptr;
	lengthDatosExtra = 0;

	if ((aCopiar.ciudadesRecorridas != nullptr) && (aCopiar.ciudadesUsadas != nullptr))
	{
		memcpy(ciudadesRecorridas, aCopiar.ciudadesRecorridas, numCiudades * sizeof(int));
		memcpy(ciudadesUsadas, aCopiar.ciudadesUsadas, numCiudades * sizeof(bool));
	}

	if (aCopiar.datosExtra != nullptr)
	{
		if (datosExtra != nullptr)
		{
			memcpy(datosExtra, aCopiar.datosExtra, aCopiar.lengthDatosExtra * sizeof(int));
			lengthDatosExtra = aCopiar.lengthDatosExtra;
		}
		else
		{
			datosExtra = new int[aCopiar.lengthDatosExtra];
			memcpy(datosExtra, aCopiar.datosExtra, aCopiar.lengthDatosExtra * sizeof(int));
			lengthDatosExtra = aCopiar.lengthDatosExtra;
		}
	}
	else
	{
		datosExtra = nullptr;
		lengthDatosExtra = 0;
	}
}

Nodo::~Nodo()
{
	delete[] ciudadesRecorridas;
	ciudadesRecorridas = nullptr;
	delete[] ciudadesUsadas;
	ciudadesUsadas = nullptr;
	
	if (datosExtra != nullptr)
	{
		delete[] datosExtra;
		datosExtra = nullptr;
		lengthDatosExtra = 0;
	}
}

Nodo& Nodo::operator=(const Nodo& aCopiar)
{
	//Si la direccion del array es el mismo eso quiere decir que son el mismo nodo.
	if (this->ciudadesRecorridas == aCopiar.ciudadesRecorridas) return *this;

	numCiudades = aCopiar.numCiudades;
	k = aCopiar.k;
	distanciaTotal = aCopiar.distanciaTotal;
	distanciaOptimista = aCopiar.distanciaOptimista;

	if ((aCopiar.ciudadesRecorridas != nullptr) && (aCopiar.ciudadesUsadas != nullptr))
	{		
		memcpy(ciudadesRecorridas, aCopiar.ciudadesRecorridas, numCiudades * sizeof(int));
		memcpy(ciudadesUsadas, aCopiar.ciudadesUsadas, numCiudades * sizeof(bool));
	}

	if (aCopiar.datosExtra != nullptr)
	{
		if (datosExtra != nullptr)
		{
			memcpy(datosExtra, aCopiar.datosExtra, aCopiar.lengthDatosExtra * sizeof(int));
			lengthDatosExtra = aCopiar.lengthDatosExtra;
		}
		else
		{
			datosExtra = new int[aCopiar.lengthDatosExtra];
			memcpy(datosExtra, aCopiar.datosExtra, aCopiar.lengthDatosExtra * sizeof(int));
			lengthDatosExtra = aCopiar.lengthDatosExtra;
		}
	}
	else
	{
		datosExtra = nullptr;
		lengthDatosExtra = 0;
	}

	return *this;
}
