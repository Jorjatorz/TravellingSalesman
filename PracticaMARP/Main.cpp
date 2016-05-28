#include <iostream>

#include "Mapa.h"
#include "ACota_Nula_Optimista.h"
#include "ARamificacionPoda.h"
#include "ACota_Nula_Pesimista.h"
#include "ACota_Ingenua_Optimista.h"
#include "ACota_Ingenua_Pesimista.h"
#include "ACota_Buena_Optimista.h"
#include "ACota_Buena_Pesimista.h"

int main(int argc, char* argv[])
{
	Mapa map(17, 25, false);

	///////////////////////////////////////////////////////////////////////////////////////
	ACota_Nula_Optimista cotaMala;
	ACota_Nula_Pesimista pesMala;

	ARamificacionPoda ag(map, cotaMala, pesMala);

	//ARamificacionPoda::sInfoAlgoritmo resultado = ag.ejecutarAlgoritmo();

	//resultado.print();

	std::cout << std::endl;

	/////////////////////////////////////////////////////////////////////////////////////////
	ACota_Ingenua_Pesimista pesIngenua(map);
	ACota_Ingenua_Optimista cotaIngenua(map);

	ARamificacionPoda ag2(map, cotaIngenua, pesIngenua);

	//ARamificacionPoda::sInfoAlgoritmo resultado2 = ag2.ejecutarAlgoritmo();
	//resultado2.print();

	 std::cout << std::endl;
	 ////////////////////////////////////////////////////////////
	 ACota_Buena_Optimista cotaBuena(map);
	 ACota_Buena_Pesimista pesBuena(map);

	 ARamificacionPoda ag3(map, cotaBuena, pesBuena);

	 ARamificacionPoda::sInfoAlgoritmo resultado3 = ag3.ejecutarAlgoritmo();
	 resultado3.print();

	 std::cout << std::endl;

	 ////////////////////////////////////////////////////////////
	 ARamificacionPoda ag4(map, cotaBuena, pesIngenua);

	 ARamificacionPoda::sInfoAlgoritmo resultado4 = ag4.ejecutarAlgoritmo();
	 resultado4.print();

	 std::cout << std::endl;


	system("Pause");
	return 0;
}