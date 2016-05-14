#pragma once

//Interfaz para representar una cota (optimista o pesimista)
class ACota
{
public:
	ACota();
	~ACota();
	virtual int calcularCoste(int distanciaActual, int numCiudades, bool ciudadUsada[]) const = 0;
};

