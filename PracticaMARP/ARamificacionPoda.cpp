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

	informacionToReturn.distanciaOptima = _cPesimista.calcularCoste(Y.distanciaTotal, _mapa.getNumeroDeCiudades(), Y.ciudadesUsadas); //En nuestro problema siempre hay solucion (si no, esto valdria infinito)
	informacionToReturn.tiempoTotal = clock();

	C.push(Y);
	while (!C.empty() && C.top().distanciaOptimista <= informacionToReturn.distanciaOptima)
	{
		Y = C.top(); 
		//Este nodo va a ser explorado
		Nodo X(_mapa.getNumeroDeCiudades());
		X = Y;

		C.pop();

		X.k++;
		informacionToReturn.numNodosExplorados++;
		for (int i = 1; i < _mapa.getNumeroDeCiudades(); i++)
		{
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
					X.distanciaOptimista = _cOptimista.calcularCoste(X.distanciaTotal, _mapa.getNumeroDeCiudades(), X.ciudadesUsadas);
					if (X.distanciaOptimista <= informacionToReturn.distanciaOptima)
					{
						C.push(X);
					}

					int cP = _cPesimista.calcularCoste(X.distanciaTotal, _mapa.getNumeroDeCiudades(), X.ciudadesUsadas);
					if (cP < informacionToReturn.distanciaOptima)
					{
						informacionToReturn.distanciaOptima = cP;
					}
				}

				X.ciudadesUsadas[i] = false;


			}
		}
	}

	informacionToReturn.tiempoTotal = (clock() - informacionToReturn.tiempoTotal) / CLOCKS_PER_SEC;
	informacionToReturn.tiempoMedio = informacionToReturn.tiempoTotal / informacionToReturn.numNodosExplorados;

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
	std::cout << "Numero de ciudades recorridas: " << numCiudades << std::endl;
	std::cout << "Distancia optima: " << distanciaOptima << std::endl;
	std::cout << "Ciclo de ciudades: " << recorridoCiudades << std::endl;
	std::cout << "Numero de nodos teoricos a explorar: " << calcularNodos() << std::endl;
	std::cout << "Numero nodos explorados: " << numNodosExplorados << std::endl;
	std::cout << "Numero nodos explorados al encontrar el optimo: " << numNodosExploradosOptima << std::endl;
	std::cout << "Tiempo total del algoritmo: " << tiempoTotal << " segundos." << std::endl;
	std::cout << "Tiempo medio por nodo explorado: " << tiempoMedio << " segundos." << std::endl;
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

ARamificacionPoda::Nodo::Nodo(int numeroCiudades)
{
	numCiudades = numeroCiudades;
	k = 0;
	distanciaTotal = 0; //Coste real de recorrer las ciudades en el orden de ciudadesRecorridas
	distanciaOptimista = 0;
	ciudadesRecorridas = new int[numeroCiudades]; //Array con el orden en el que se tienen que recorrer las ciudades
	ciudadesUsadas = new bool[numeroCiudades]; //True si esa ciudad ya ha sido explorada
	memset(ciudadesUsadas, false, numeroCiudades * sizeof(bool));
}

ARamificacionPoda::Nodo::Nodo(const Nodo& aCopiar)
{

	numCiudades = aCopiar.numCiudades;
	k = aCopiar.k;
	distanciaTotal = aCopiar.distanciaTotal;
	distanciaOptimista = aCopiar.distanciaOptimista;
	ciudadesRecorridas = new int[numCiudades];
	ciudadesUsadas = new bool[numCiudades];

	if ((aCopiar.ciudadesRecorridas != nullptr) && (aCopiar.ciudadesUsadas != nullptr))
	{
		memcpy(ciudadesRecorridas, aCopiar.ciudadesRecorridas, numCiudades * sizeof(int));
		memcpy(ciudadesUsadas, aCopiar.ciudadesUsadas, numCiudades * sizeof(bool));
	}
}

ARamificacionPoda::Nodo::~Nodo()
{
	delete[] ciudadesRecorridas;
	ciudadesRecorridas = nullptr;
	delete[] ciudadesUsadas;
	ciudadesUsadas = nullptr;
}

ARamificacionPoda::Nodo& ARamificacionPoda::Nodo::operator=(const Nodo& aCopiar)
{
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

	return *this;
}
