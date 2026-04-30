#include "mergesort.hpp"
#include <vector>


static void merge(std::vector<Solicitud>& arr, int izq, int mid, int der) {
    int n1 = mid - izq + 1;
    int n2 = der - mid;

    
    std::vector<Solicitud> L(arr.begin() + izq, arr.begin() + izq + n1);
    std::vector<Solicitud> R(arr.begin() + mid + 1, arr.begin() + mid + 1 + n2);

    int i = 0, j = 0, k = izq;

    // Mezclar usando > para orden descendente; >= garantiza estabilidad
    while (i < n1 && j < n2) {
        if (L[i].tenure >= R[j].tenure) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}


void mergeSort(std::vector<Solicitud>& arr, int izq, int der) {
    if (izq >= der) return;          // caso base: subarray de 1 elemento
    int mid = izq + (der - izq) / 2; // evita desbordamiento de enteros
    mergeSort(arr, izq, mid);
    mergeSort(arr, mid + 1, der);
    merge(arr, izq, mid, der);
}