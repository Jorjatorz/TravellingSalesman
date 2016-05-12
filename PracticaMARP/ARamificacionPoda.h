#pragma once

#include <string>

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

	struct Nodo
	{
		int k;
		int distanciaTotal; //Coste real de recorrer las ciudades en el orden de ciudadesRecorridas
		int distanciaOptimista;
		int* ciudadesRecorridas; //Array con el orden en el que se tienen que recorrer las ciudades
		bool* ciudadesUsadas; //True si esa ciudad ya ha sido explorada

		const int numCiudades; //Numero de ciudades que contienen las arrays

		Nodo(int nCiudades, int ciudadOriginal)
			:numCiudades(nCiudades)
		{

			ciudadesRecorridas = new int[numCiudades];
			ciudadesUsadas = new bool[numCiudades];
			memset(ciudadesUsadas, false, numCiudades);

			//Guardar la primera ciudad
			ciudadesRecorridas[0] = ciudadOriginal;
			ciudadesUsadas[ciudadOriginal] = true;

			k = 1;
			distanciaTotal = 0;
			distanciaOptimista = 0;
		}

		//Constructor copia
		Nodo(const Nodo& aCopiar)
			:numCiudades(aCopiar.numCiudades)
		{
			k = aCopiar.k;
			distanciaTotal = aCopiar.distanciaTotal;
			distanciaOptimista = aCopiar.distanciaOptimista;

			ciudadesRecorridas = new int[numCiudades];
			ciudadesUsadas = new bool[numCiudades];
			memcpy(ciudadesRecorridas, aCopiar.ciudadesRecorridas, numCiudades);
			memcpy(ciudadesUsadas, aCopiar.ciudadesUsadas, numCiudades);
		}

		~Nodo()
		{
			delete[] ciudadesRecorridas;
			delete[] ciudadesUsadas;
		}

		//Metodo para que la cola de minimos ordene
		bool operator()(const Nodo& l, const Nodo& r)
		{
			return l.distanciaTotal > r.distanciaTotal;
		}
	};

public:

	struct sInfoAlgoritmo 
	{
		int distanciaOptima; //Distancia optima calculada por el algoritmo
		short int numCiudades; //Numero de ciudades que tenia que recorrer
		std::string *recorridoCiudades; //Orden en las que hay que recorrer las ciudades para obtener la distanciaOptima
		int numNodosExplorados; //El numero de nodos que el algoritmo ha explorado
		int numNodosExploradosOptima; //Numero de nodos que habian sido explorados cuando la solucion optima fue encontrada
		float tiempoTotal; //Tiempo total que el algoritmo ha tardado en terminar. En segundos
		float tiempoMedio; //Tiempo medio que dedica el algoritmo en procesar un nodo. (tiempoTotal / numNodosExplorados)

		sInfoAlgoritmo(int n)
		{
			distanciaOptima = INT_MAX;
			numCiudades = n;
			recorridoCiudades = new std::string[n];
			numNodosExplorados = 0;
			numNodosExploradosOptima = 0;
			tiempoTotal = 0;
			tiempoMedio = 0;
		}

		~sInfoAlgoritmo()
		{
			delete[] recorridoCiudades;
		}

		void copiarSolucion(Nodo X, const Mapa& mapa);
	};

	ARamificacionPoda(const Mapa& mapa, const ACota& optimista, const ACota& pesimita);
	~ARamificacionPoda();

	//Ejecuta el algoritmo y devuelve una estructura sInfoAlgoritmo con la informacion obtenida
	sInfoAlgoritmo ejecutarAlgoritmo();


};

