#include "Mapa.h"
#include <assert.h>
#include <iostream>

const int Mapa::_DIST[28][28] = {
	{},
	{ 171 },
	{ 369, 294 },
	{ 366, 537, 633 },
	{ 525, 696, 604, 318 },
	{ 540, 515, 809, 717, 1022 },
	{ 646, 817, 958, 401, 694, 620 },
	{ 488, 659, 800, 243, 536, 583, 158 },
	{ 504, 675, 651, 229, 89, 918, 605, 447 },
	{ 617, 688, 484, 618, 342, 1284, 1058, 900, 369 },
	{ 256, 231, 525, 532, 805, 284, 607, 524, 701, 873 },
	{ 207, 378, 407, 256, 318, 811, 585, 427, 324, 464, 463 },
	{ 354, 525, 332, 457, 272, 908, 795, 637, 319, 263, 610, 201 },
	{ 860, 1031, 1172, 538, 772, 1118, 644, 535, 683, 1072, 1026, 799, 995 },
	{ 142, 313, 511, 282, 555, 562, 562, 404, 451, 708, 305, 244, 445, 776 },
	{ 640, 615, 909, 817, 1122, 100, 720, 683, 1018, 1384, 384, 911, 1008, 1218, 662 },
	{ 363, 353, 166, 534, 438, 868, 829, 671, 485, 335, 584, 278, 166, 1043, 479, 968 },
	{ 309, 480, 621, 173, 459, 563, 396, 238, 355, 721, 396, 248, 458, 667, 486, 663, 492 },
	{ 506, 703, 516, 552, 251, 1140, 939, 781, 323, 219, 856, 433, 232, 1006, 677, 1240, 350, 690 },
	{ 495, 570, 830, 490, 798, 274, 322, 359, 694, 1060, 355, 587, 797, 905, 406, 374, 831, 339, 1029 },
	{ 264, 415, 228, 435, 376, 804, 730, 572, 423, 367, 520, 179, 104, 944, 380, 904, 99, 393, 336, 732 },
	{ 584, 855, 896, 255, 496, 784, 359, 201, 407, 796, 725, 511, 733, 334, 500, 884, 761, 391, 730, 560, 668 },
	{ 515, 490, 802, 558, 866, 156, 464, 427, 762, 1128, 259, 655, 865, 973, 472, 256, 861, 407, 1097, 118, 779, 628 },
	{ 578, 653, 899, 358, 676, 468, 152, 115, 595, 999, 455, 526, 736, 650, 464, 568, 770, 278, 968, 244, 671, 316, 312 },
	{ 762, 933, 1074, 440, 674, 1020, 546, 437, 585, 974, 928, 696, 897, 98, 678, 1120, 945, 569, 908, 807, 846, 236, 875, 352 },
	{ 251, 422, 563, 115, 401, 621, 395, 237, 297, 663, 417, 190, 400, 609, 167, 721, 434, 58, 632, 397, 335, 333, 465, 336, 551 },
	{ 473, 482, 219, 644, 436, 997, 939, 781, 506, 265, 713, 388, 187, 1153, 615, 1097, 129, 602, 313, 941, 209, 877, 1009, 880, 1055, 544 },
	{ 150, 75, 219, 516, 675, 590, 796, 638, 654, 613, 306, 357, 444, 1010, 292, 690, 278, 459, 628, 611, 340, 734, 583, 694, 912, 401, 407 }
};

const std::string Mapa::_CIUDADES[28] = { "Albacete", "Alicante", "Almeria", "Avila", "Badajoz",
"Barcelona", "Bilbao", "Burgos", "Caceres", "Cadiz", "Castellon", "Ciudad_Real", "Cordoba",
"A_Coruna", "Cuenca", "Gerona", "Granada", "Guadalajara", "Huelva", "Huesca",
"Jaen", "Leon", "Lerida", "Logrono", "Lugo", "Madrid", "Malaga", "Murcia" };

Mapa::Mapa(int n, int ciudadInicial, bool permutar)
	:_n(n), _cInicial(ciudadInicial)
{
	//Si no se permuta, elegir las n primero ciudades
	if (!permutar)
	{
		if (n >= ciudadInicial)
		{
			std::cout << "ERROR: La ciudad inicial tiene que estar entre las n primeras ciudades" << std::endl;
			assert(false); //La ciudad inicial tiene que estar entre las n primeras ciudades
		}

		_ciudadesElegidarArray = new int[n];
		for (int i = 0; i < n; i++)
		{
			if (i != ciudadInicial)
			{
				_ciudadesElegidarArray[i + 1] = i;
			}
		}
		_ciudadesElegidarArray[0] = ciudadInicial;
	}
	else
	{
		//Elegimos ciudades aleatoriamente (que no hayan sido elegidas ya)
		bool elegida[28];
		memset(elegida, false, 28);

		_ciudadesElegidarArray[0] = ciudadInicial;
		elegida[ciudadInicial] = true;
		for (int i = 1; i < n; i++)
		{
			int c = rand() % 28;
			while (elegida[n])
			{
				c = rand() % 28;
			}

			_ciudadesElegidarArray[i] = c;
			elegida[c] = true;
		}
	}
}


Mapa::~Mapa()
{
}

int Mapa::getDistanciaEntreCiudades(int ciudad1, int ciudad2)
{
	int distancia;
	//Si las ciudades son iguales, devolver 0
	if (ciudad1 == ciudad2)
	{
		return 0;
	}
	else if (ciudad1 > ciudad2)
	{
		distancia = _DIST[ciudad1][ciudad2];
	}
	else
	{
		distancia = _DIST[ciudad2][ciudad1];
	}

	return distancia;
}