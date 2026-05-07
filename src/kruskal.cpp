
#include "kruskal.hpp"
#include <algorithm>

UnionFind::UnionFind(int n): padre(n), rango(n, 0){
    for (int i = 0; i < n; ++i) padre[i] = i; //Cada nodo empieza siendo su propio padre
}
//Aca implemento la función del Union-Find para detectar ciclos en el algoritmo de Kruskal
int UnionFind::encontrar(int x){
    if (padre[x]!= x) {
        padre[x]= encontrar(padre[x]); //compresión de caminos
    }
    return padre[x];
}
//Aca se unen los conjuntos para evitar ciclos
bool UnionFind::unir(int x,int y){
    int rx= encontrar(x);
    int ry= encontrar(y);

    if (rx == ry) return false; //ya conectados formarian ciclo
    if (rango[rx]< rango[ry]){
        padre[rx]= ry;
    } else if (rango[rx]> rango[ry]){
        padre[ry]= rx;
    } else {
        padre[ry]= rx;
        rango[rx] ++;
    }
    return true;
}
//Implementación del algoritmo de Kruskal
ResultadoMST kruskal(const Grafo& g){
    //Copia y ordena las aristas por peso ascendente
    std::vector<Arista> aristasOrdenadas= g.aristas;
    std::sort(aristasOrdenadas.begin(), aristasOrdenadas.end(),
              [](const Arista& a, const Arista& b){
                  return a.peso< b.peso;
              });
    //Inicializa Union-Find con V componentes disjuntos
    UnionFind uf(g.numNodos);
    ResultadoMST resultado;
    resultado.pesoTotal= 0.0;

    //Recorre las aristas en orden; agregar si no forma ciclo
    for (const Arista& a: aristasOrdenadas){
        if (uf.unir(a.u, a.v)){
            resultado.aristas.push_back(a);
            resultado.pesoTotal+= a.peso;

            if ((int)resultado.aristas.size()== g.numNodos - 1) break;
        }
    }
    return resultado;
}