#include "parser.hpp"
#include "mergesort.hpp"
#include "binary_search.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <filesystem>


using Clock = std::chrono::high_resolution_clock;
using Ms    = std::chrono::duration<double, std::milli>;


double medirTiempoSort(const std::vector<Solicitud>& base, int n) {
    std::vector<Solicitud> copia(base.begin(), base.begin() + n);
    auto t0 = Clock::now();
    mergeSort(copia, 0, (int)copia.size() - 1);
    auto t1 = Clock::now();
    return Ms(t1 - t0).count();
}


void escribirOrdenadas(const std::vector<Solicitud>& arr, const std::string& ruta) {
    std::ofstream f(ruta);
    f << "customerID,tenure,MonthlyCharges,TotalCharges,Churn\n";
    for (const auto& s : arr) {
        f << s.customerID      << ","
          << s.tenure          << ","
          << std::fixed << std::setprecision(2)
          << s.monthlyCharges  << ","
          << s.totalCharges    << ","
          << (s.churn ? "Yes" : "No") << "\n";
    }
}



int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0]
                  << " data/WA_Fn-UseC_-Telco-Customer-Churn.csv\n";
        return 1;
    }

    const std::string rutaCSV = argv[1];


    std::filesystem::create_directories("results");

  
    std::cout << "=== Módulo A — Divide y Vencerás ===\n\n";
    std::cout << "[A1] Parseando CSV: " << rutaCSV << " ...\n";

    ParseResult pr;
    try {
        pr = parsearCSV(rutaCSV);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    std::cout << "  Total de registros cargados      : " << pr.totalRegistros    << "\n";
    std::cout << "  Registros con TotalCharges nulo  : " << pr.totalChargesNulos << "\n";

    int activos = 0, enRiesgo = 0;
    for (const auto& s : pr.solicitudes) {
        if (s.churn) enRiesgo++; else activos++;
    }
    std::cout << "  Registros con Churn = No (activos): " << activos  << "\n";
    std::cout << "  Registros con Churn = Yes (riesgo): " << enRiesgo << "\n\n";

    
    std::cout << "[A2] Ordenando por tenure descendente con MergeSort...\n";

    auto& solicitudes = pr.solicitudes;
    auto t0 = Clock::now();
    mergeSort(solicitudes, 0, (int)solicitudes.size() - 1);
    auto t1 = Clock::now();
    double tiempoCompleto = Ms(t1 - t0).count();

    std::cout << "  Ordenamiento completo (7043 registros): "
              << std::fixed << std::setprecision(2) << tiempoCompleto << " ms\n";
    std::cout << "  tenure[0]    (mayor) = " << solicitudes.front().tenure << "\n";
    std::cout << "  tenure[last] (menor) = " << solicitudes.back().tenure  << "\n\n";

    
    escribirOrdenadas(solicitudes, "results/solicitudes_ordenadas.csv");
    std::cout << "  -> results/solicitudes_ordenadas.csv generado.\n\n";

    
    std::cout << "[A4] Analisis empirico de tiempos:\n";

    int tamanios[] = {1000, 3500, 7043};
    double tiempos[3];

    for (int i = 0; i < 3; i++) {
      
        double suma = 0.0;
        for (int rep = 0; rep < 5; rep++) {
            suma += medirTiempoSort(solicitudes, tamanios[i]);
        }
        tiempos[i] = suma / 5.0;
    }

    std::cout << "  +----------+------------+------------------+\n";
    std::cout << "  |    n     | Tiempo(ms) | n*log2(n) (norm) |\n";
    std::cout << "  +----------+------------+------------------+\n";

    double base_nlogn = tamanios[0] * std::log2(tamanios[0]);
    for (int i = 0; i < 3; i++) {
        double nlogn = tamanios[i] * std::log2(tamanios[i]);
        double ratio = nlogn / base_nlogn;
        std::cout << "  | " << std::setw(8) << tamanios[i]
                  << " | " << std::setw(10) << std::fixed << std::setprecision(2) << tiempos[i]
                  << " | " << std::setw(16) << std::setprecision(4) << ratio << " |\n";
    }
    std::cout << "  +----------+------------+------------------+\n\n";

   
    std::cout << "[A3] Busqueda binaria recursiva — 5 consultas:\n";

    struct Consulta { std::string id; int k; };
    std::vector<Consulta> consultas = {
        {"Q_A01", 72},
        {"Q_A02", 60},
        {"Q_A03", 45},
        {"Q_A04", 30},
        {"Q_A05", 12}
    };

    std::ofstream fBusq("results/busquedas_A.txt");
    fBusq << "Resultados de busqueda binaria recursiva\n";
    fBusq << "Arreglo ordenado por tenure DESCENDENTE\n";
    fBusq << "Consulta: primera solicitud con tenure >= k\n\n";
    fBusq << std::left
          << std::setw(10) << "Consulta"
          << std::setw(6)  << "k"
          << std::setw(16) << "customerID"
          << std::setw(8)  << "tenure"
          << "Churn\n";
    fBusq << std::string(50, '-') << "\n";

    std::cout << "  " << std::left
              << std::setw(10) << "Consulta"
              << std::setw(6)  << "k"
              << std::setw(16) << "customerID"
              << std::setw(8)  << "tenure"
              << "Churn\n";
    std::cout << "  " << std::string(48, '-') << "\n";

    int n = (int)solicitudes.size();
    for (const auto& c : consultas) {
        int idx = busquedaBinaria(solicitudes, 0, n - 1, c.k);

        std::string custID  = (idx == -1) ? "NO FUE ENCONTRADO" : solicitudes[idx].customerID;
        std::string tenureS = (idx == -1) ? "-"             : std::to_string(solicitudes[idx].tenure);
        std::string churnS  = (idx == -1) ? "-"             : (solicitudes[idx].churn ? "Yes" : "No");

        std::cout << "  " << std::setw(10) << c.id
                  << std::setw(6)  << c.k
                  << std::setw(16) << custID
                  << std::setw(8)  << tenureS
                  << churnS << "\n";

        fBusq << std::setw(10) << c.id
              << std::setw(6)  << c.k
              << std::setw(16) << custID
              << std::setw(8)  << tenureS
              << churnS << "\n";
    }

    fBusq.close();
    std::cout << "\n  -> results/busquedas_A.txt generado.\n\n";
    std::cout << " Modulo A completado \n";

    return 0;
}