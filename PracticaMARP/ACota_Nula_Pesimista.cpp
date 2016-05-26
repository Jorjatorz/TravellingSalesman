#include "ACota_Nula_Pesimista.h"

#include <intsafe.h>

ACota_Nula_Pesimista::ACota_Nula_Pesimista()
{
}


ACota_Nula_Pesimista::~ACota_Nula_Pesimista()
{
}

int ACota_Nula_Pesimista::calcularCoste(Nodo& X) const
{
	return INT_MAX;
}
