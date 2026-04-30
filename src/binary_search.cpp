#include "binary_search.hpp"


int busquedaBinaria(const std::vector<Solicitud>& arr, int izq, int der, int k) {
    
    if (izq > der) return -1;

    int mid = izq + (der - izq) / 2;

    if (arr[mid].tenure >= k) {
        
        int resultado = busquedaBinaria(arr, izq, mid - 1, k);
        return (resultado == -1) ? mid : resultado;
    } else {
    
        return busquedaBinaria(arr, izq, mid - 1, k);
    }
}