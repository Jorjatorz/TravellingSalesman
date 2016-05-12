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
	//Ciudades elegidas. _Contiene las verdaderas ids de las ciudad. Por ejemplo, [12, 3 ,1]. la ciudad elegida 0 es, en realidad, la ciudad 12 
	int *_ciudadesElegidasArray;

	int getDistanciaEntreCiudadesAUX(int ciudad1, int ciudad2) const;
public:
	Mapa(int n, int ciudadInicial, bool permutar);
	~Mapa();

	/*inline const int const getCiudadElegidas(int i) const
	{
		return _ciudadesElegidarArray[i];
	}*/

	inline int getNumeroDeCiudades() const
	{
		return _n;
	}

	inline int getCiudadInicial() const
	{
		return _cInicial;
	}

	//Devuelve el nombre de una ciudad (id original)
	inline std::string getNombreCiudad(int ciudad) const
	{
		return _CIUDADES[ciudad];
	}

	//Devuelve la distancia entre dos ciudades
	int getDistanciaEntreCiudades(int ciudad1, int ciudad2) const;

	//Convierte un array de ciudades recorridas a string (ciudadesRecorridas tiene que usar las ids de las ciudades elegidas, no las ids verdaderas de la ciudad)
	void ciudadesToStringArray(std::string& recorridoCiudades, int* ciudadesRecorridas) const;
};

