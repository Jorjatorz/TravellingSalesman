#pragma once

struct Nodo;

//Interfaz para representar una cota (optimista o pesimista)
class ACota
{
public:
	ACota();
	~ACota();
	virtual int calcularCoste(Nodo& X) const = 0;
};

