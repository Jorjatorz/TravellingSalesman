#include <iostream>

#include "Mapa.h"
#include "ACota_Nula_Optimista.h"
#include "ARamificacionPoda.h"
#include "ACota_Nula_Pesimista.h"
#include "ACota_Ingenua_Optimista.h"
#include "ACota_Ingenua_Pesimista.h"

int main(int argc, char* argv[])
{
	Mapa map(10, 25, true);
	ACota_Nula_Optimista cotaMala;
	ACota_Nula_Pesimista pesMala;

	ACota_Ingenua_Pesimista pesBuena(map);
	ACota_Ingenua_Optimista cotaBuena(map);

	ARamificacionPoda ag(map, cotaMala, pesMala);

	//ARamificacionPoda::sInfoAlgoritmo resultado = ag.ejecutarAlgoritmo();

	//resultado.print();

	ARamificacionPoda ag2(map, cotaBuena, pesBuena);

	ARamificacionPoda::sInfoAlgoritmo resultado2 = ag2.ejecutarAlgoritmo();
	 resultado2.print();

	system("Pause");
	return 0;
}