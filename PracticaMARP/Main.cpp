#include <iostream>

#include "Mapa.h"
#include "ACota_Nula_Optimista.h"
#include "ARamificacionPoda.h"
#include "ACota_Nula_Pesimista.h"

int main(int argc, char* argv[])
{
	Mapa map(10, 25, false);
	ACota_Nula_Optimista cota;
	ACota_Nula_Pesimista pes;

	ARamificacionPoda ag(map, cota, pes);

	ARamificacionPoda::sInfoAlgoritmo resultado = ag.ejecutarAlgoritmo();

	resultado.print();

	system("Pause");
	return 0;
}