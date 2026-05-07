
#pragma once
#include "graph.hpp"
#include <vector>

struct UnionFind {
    std::vector<int> padre;
    std::vector<int> rango;
    explicit UnionFind(int n);

    //Esto retorna el representante del conjunto al que pertenece x
    int encontrar (int x);

    //Une los conjuntos de "x" y "y", retorna true si estaban en distintos conjuntos
    bool unir (int x, int y);
};
//Resultados del kruskal
struct ResultadoMST {
    std::vector <Arista> aristas;// las 19 aristas
    double pesoTotal;
};
// Ejecuta Kruskal sobre el grafo dado y retorna el MST.
ResultadoMST kruskal(const Grafo& g);