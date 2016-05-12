#pragma once


#include <string>
class Mapa
{
private:
	//Distancias y nombre de 28 ciudades de españa
	//Sacadas de la asignatura Programacion Evolutiva
	static const int _DIST[28][28];
	static const std::string _CIUDADES[28];

	//Numero de ciudades que se han elegido
	int _n;
	//ciudad del mapa inicial
	int _cInicial;
	//Ciudades elegidas
	int *_ciudadesElegidarArray;
public:
	Mapa(int n, int ciudadInicial, bool permutar);
	~Mapa();

	inline const int* const getCiudadesElegidasArray() const
	{
		return _ciudadesElegidarArray;
	}

	inline int getNumeroDeCiudades() const
	{
		return _n;
	}

	//Devuelve el nombre de una ciudad
	inline std::string getNombreCiudad(int ciudad) const
	{
		return _CIUDADES[ciudad];
	}

	//Devuelve la distancia entre dos ciudades
	static int getDistanciaEntreCiudades(int ciudad1, int ciudad2);
};

