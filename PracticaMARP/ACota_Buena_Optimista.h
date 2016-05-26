#pragma once

#include "ACota.h"

//Reduced cost matrix
class ACota_Buena_Optimista: public ACota
{
public:
	ACota_Buena_Optimista();
	~ACota_Buena_Optimista();

	virtual int calcularCoste(Nodo& X) const;

};

