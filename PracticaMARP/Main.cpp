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
	std::cout << "Introduce el numero de ciudades a explorar del conjunto de ciudades de Espana: ";
	int ciudades;
	std::cin >> ciudades;
	Mapa map(ciudades, 25, true); //Se empieza en Madrid (ciudad 25) y se eligen ciudades aleatorias para formar el mapa.

	///////////////////////////////////////////////////////////////////////////////////////
	ACota_Nula_Optimista cotaMala;
	ACota_Nula_Pesimista pesMala;

	ARamificacionPoda ag(map, cotaMala, pesMala);

	ARamificacionPoda::sInfoAlgoritmo resultado = ag.ejecutarAlgoritmo();
	std::cout << "--------------Cota Nula--------------" << std::endl;
	resultado.print();

	std::cout << std::endl;

	/////////////////////////////////////////////////////////////////////////////////////////
	ACota_Ingenua_Pesimista pesIngenua(map);
	ACota_Ingenua_Optimista cotaIngenua(map);

	ARamificacionPoda ag2(map, cotaIngenua, pesIngenua);

	std::cout << "--------------Cota Ingenua--------------" << std::endl;
	ARamificacionPoda::sInfoAlgoritmo resultado2 = ag2.ejecutarAlgoritmo();
	resultado2.print();

	 std::cout << std::endl;
	 ////////////////////////////////////////////////////////////
	 ACota_Buena_Optimista cotaBuena(map);
	 ACota_Buena_Pesimista pesBuena(map);

	 ARamificacionPoda ag3(map, cotaBuena, pesBuena);

	 ARamificacionPoda::sInfoAlgoritmo resultado3 = ag3.ejecutarAlgoritmo();
	 std::cout << "--------------Cota Buena--------------" << std::endl;
	 resultado3.print();

	 std::cout << std::endl;



	system("Pause");
	return 0;
}