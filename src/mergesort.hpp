#pragma once
#include "parser.hpp"
#include <vector>

// Ordena las solicitudes por tenure DESCENDENTE (mayor prioridad primero).
// Implementación estable O(n log n) en todos los casos.
void mergeSort(std::vector<Solicitud>& arr, int izq, int der);