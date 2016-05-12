#include "ARamificacionPoda.h"

#include <queue>

#include "Mapa.h"
#include "ACota.h"
#include <iostream>

ARamificacionPoda::ARamificacionPoda(const Mapa& mapa, const ACota& optimista, const ACota& pesimita)
	:_mapa(mapa), _cOptimista(optimista), _cPesimista(pesimita)
{
}


ARamificacionPoda::~ARamificacionPoda()
{
}

ARamificacionPoda::sInfoAlgoritmo ARamificacionPoda::ejecutarAlgoritmo()
{
	sInfoAlgoritmo informacionToReturn(_mapa.getNumeroDeCiudades());

	Nodo Y(_mapa.getNumeroDeCiudades(), _mapa.getCiudadInicial());
	std::priority_queue<Nodo, std::vector<Nodo>, Nodo> C;

	int costeMejor = _cPesimista.calcularCoste(Y); //En nuestro problema siempre hay solucion (si no, esto valdria infinito)
	C.push(Y);
	while (!C.empty() && C.top().distanciaOptimista <= costeMejor)
	{
		Y = C.top(); C.pop();

		//Este nodo va a ser explorado
		Nodo X(Y);
		X.k++;
		informacionToReturn.numNodosExplorados++;
		for (int i = 0; i < _mapa.getNumeroDeCiudades() - 1; i++)
		{
			//Si esta ciudad no ha sido usada con anterioridad
			if (!X.ciudadesUsadas[i])
			{
				int nuevaDistancia = X.distanciaTotal + _mapa.getDistanciaEntreCiudades(X.ciudadesRecorridas[X.k - 1], i);
				X.distanciaTotal = nuevaDistancia;
				X.ciudadesRecorridas[X.k] = i;
				X.ciudadesUsadas[i] = true;

				//Si es solicion
				if (X.k == (_mapa.getNumeroDeCiudades() - 1))
				{
					X.distanciaTotal += _mapa.getDistanciaEntreCiudades((X.ciudadesRecorridas[X.k], X.ciudadesRecorridas[0])); //Distancia de la ultima ciudad a la primera

					if (X.distanciaTotal < informacionToReturn.distanciaOptima) //Al principio, informacionToReturn.distanciaOptima es infinito
					{
						informacionToReturn.copiarSolucion(X);

						//TODO Borrar esto cuando no sea debug
						std::cout << "Solucion encontrada: " << informacionToReturn.distanciaOptima << " Nodos explorados: " << informacionToReturn.numNodosExplorados << std::endl;
					}
				}
				else //Si no es solucion
				{
					//Si es prometedor, seguir explorandolo
					X.distanciaOptimista = _cOptimista.calcularCoste(X);
					if (X.distanciaOptimista <= informacionToReturn.distanciaOptima)
					{
						C.push(X);
					}

					int cP = _cPesimista.calcularCoste(X);
					if (cP < informacionToReturn.distanciaOptima)
					{
						informacionToReturn.distanciaOptima = cP;

						//TODO Borrar esto cuando no sea debug
						std::cout << "Distancia optima por pesimista actualizada: " << informacionToReturn.distanciaOptima << " Nodos explorados: " << informacionToReturn.numNodosExplorados << std::endl;
					}
				}

				X.ciudadesUsadas[i] = false;


			}
		}
	}
}

void ARamificacionPoda::sInfoAlgoritmo::copiarSolucion(Nodo X, const Mapa& mapa)
{
	distanciaOptima = X.distanciaTotal;
	mapa.ciudadesToStringArray(*recorridoCiudades, X.ciudadesRecorridas);
	numNodosExploradosOptima = numNodosExplorados;
}
