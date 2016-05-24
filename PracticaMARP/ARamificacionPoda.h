#pragma once

#include <stdio.h>
#include <string>
#include <assert.h>

class Mapa;
class ACota;

//Algoritmo que dado una matriz con la distancia entre ciudades, una cota optimista y una cota pesimista
//devuelve la distancia minima, el orden de ciudades a recorrer, el tiempo que se ha tardado en total en ejecutarlo
//numero de nodos explorados, tiempo medio por nodo, etc.
class ARamificacionPoda
{

private:
	const Mapa& _mapa;
	const ACota& _cOptimista;
	const ACota& _cPesimista;

	class Nodo
	{
	public:
		int k;
		int distanciaTotal; //Coste real de recorrer las ciudades en el orden de ciudadesRecorridas
		int distanciaOptimista;
		int* ciudadesRecorridas; //Array con el orden en el que se tienen que recorrer las ciudades
		bool* ciudadesUsadas; //True si esa ciudad ya ha sido explorada

		Nodo(int numeroCiudades);
		Nodo(const Nodo& aCopiar);
		~Nodo();

		Nodo& operator=(const Nodo& aCopiar);

		struct comparator
		{
			//Funcion comparadora para crear una cola de minimos.
			bool operator()(const Nodo& l, const Nodo& r)
			{
				return l.distanciaTotal > r.distanciaTotal;
			}
		};

	private:
		int numCiudades;
	};

public:

	struct sInfoAlgoritmo 
	{
		int distanciaOptima; //Distancia optima calculada por el algoritmo
		short int numCiudades; //Numero de ciudades que tenia que recorrer
		std::string recorridoCiudades; //Orden en las que hay que recorrer las ciudades para obtener la distanciaOptima
		int numNodosExplorados; //El numero de nodos que el algoritmo ha explorado
		int numNodosExploradosOptima; //Numero de nodos que habian sido explorados cuando la solucion optima fue encontrada
		float tiempoTotal; //Tiempo total que el algoritmo ha tardado en terminar. En segundos
		float tiempoMedio; //Tiempo medio que dedica el algoritmo en procesar un nodo. (tiempoTotal / numNodosExplorados)

		sInfoAlgoritmo(int n)
		{
			distanciaOptima = INT_MAX;
			numCiudades = n;
			recorridoCiudades = "";
			numNodosExplorados = 0;
			numNodosExploradosOptima = 0;
			tiempoTotal = 0;
			tiempoMedio = 0;
		}

		~sInfoAlgoritmo()
		{
		}

		void copiarSolucion(Nodo X, const Mapa& mapa);

		void print();
		long long int calcularNodos();
	};

	ARamificacionPoda(const Mapa& mapa, const ACota& optimista, const ACota& pesimita);
	~ARamificacionPoda();

	//Ejecuta el algoritmo y devuelve una estructura sInfoAlgoritmo con la informacion obtenida
	sInfoAlgoritmo ejecutarAlgoritmo();


};

