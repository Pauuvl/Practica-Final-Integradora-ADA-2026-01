#include "graph.hpp"
#include <cmath>

Grafo construirGrafo(const std:: vector<Solicitud> & solicitudes){
    const int NUM_NODOS= 20;

    //Reparte registros en 20 grupos por índice
    std::vector<std::vector<double>> grupos(NUM_NODOS);
    for (int i=0; i< (int)solicitudes.size(); ++i) {
        grupos[i % NUM_NODOS].push_back(solicitudes[i].monthlyCharges);
    }
    //Calcula el promedio para cada grupo y redondea a 2 decimales
    std::vector<double> promedios(NUM_NODOS, 0.0);
    for (int k = 0; k < NUM_NODOS; ++k) {
        double suma = 0.0;
        for (double mc : grupos[k]) suma += mc;
        promedios[k] = std::round((suma / grupos[k].size()) * 100.0) / 100.0;
    }
    Grafo g;
    g.numNodos= NUM_NODOS;
    g.numAristas= 0;

    for (int k= 0; k< NUM_NODOS;++k){
        g.nodos.push_back(solicitudes[k]);
    }
    //Genera 190 aristas entre los 20 nodos, con peso basado en la suma de promedios
    for (int u=0; u< NUM_NODOS; ++u){
        for (int v= u+1; v < NUM_NODOS;++v) {
            double peso= std::floor(promedios[u] + promedios[v]);
            g.aristas.push_back({u, v, peso});
            g.numAristas ++;
        }
    }
    return g;
}