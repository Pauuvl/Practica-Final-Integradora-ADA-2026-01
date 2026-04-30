#pragma once
#include <string>
#include <vector>

struct Solicitud {
    std::string customerID;
    int         tenure;          // Prioridad de servicio
    double      monthlyCharges;  // Valor mensual (USD)
    double      totalCharges;    // Peso en la mochila
    bool        churn;           // true = en riesgo (Yes), false = activa (No)
};

struct ParseResult {
    std::vector<Solicitud> solicitudes;
    int totalRegistros;
    int totalChargesNulos;  // registros con TotalCharges vacío (tenure == 0)
};

// Lee el CSV y devuelve las solicitudes junto con estadísticas de parseo.
// Lanza std::runtime_error si el archivo no se puede abrir.
ParseResult parsearCSV(const std::string& rutaArchivo);