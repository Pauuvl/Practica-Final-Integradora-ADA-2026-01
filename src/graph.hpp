
#pragma once
#include "parser.hpp"
#include <vector>
#include <string>

struct Arista {
    int u; //nodo origen
    int v; //nodo destino
    double peso;
};
struct Grafo {
    int numNodos; //Los nodos de los 20 clientes
    int numAristas; //Las 190 aristas del grafo, cada una con su peso
    std::vector<Solicitud> nodos; 
    std::vector<Arista>aristas; 
};
Grafo construirGrafo(const std::vector <Solicitud> & ordenados);