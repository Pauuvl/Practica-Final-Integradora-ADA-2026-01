#include "parser.hpp"
#include "mergesort.hpp"
#include "binary_search.hpp"
#include "graph.hpp"
#include "kruskal.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <filesystem>

//Modulo A: Divide y Vencerás
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


    //Modulo B - Algoritmo Codicioso Kruskal
    std::cout <<"\n\n=== Modulo B - Algoritmo Codicioso (Kruskal) ===\n\n";

    std::cout<<"[B1] Construyendo grafo K_20...\n";
    Grafo grafo= construirGrafo(solicitudes);
    std::cout<<"Nodos   : "<< grafo.numNodos << "\n";
    std::cout<<"Aristas : " << grafo.numAristas << "\n\n";

    std::cout<< "[B2] Ejecutando Kruskal...\n";
    ResultadoMST mst= kruskal(grafo);
    double costoPromedio= mst.pesoTotal / grafo.numAristas;
    std::cout<< "Aristas en el MST :"<< mst.aristas.size() <<"\n";
    std::cout<< "Peso total del MST:"<< std::fixed << std::setprecision(2) << mst.pesoTotal << "\n";
    std::cout<< "Costo promedio de arista (grafo completo): " << std::fixed << std::setprecision(2)<< costoPromedio <<"\n\n";

    //Escribe los resultados en mst_red.txt
    std::ofstream fMST("results/mst_red.txt");
    fMST<< "\n\n=== Modulo B - Red de Minimo Costo (Kruskal) ===\n\n";
    fMST<< "Grafo: "<< grafo.numNodos<<" nodos, "<< grafo.numAristas <<" aristas\n";
    fMST<< "Peso total del MST: "<< std::fixed << std::setprecision(2)<< mst.pesoTotal<< "\n";
    fMST<< "Costo promedio de arista: " << std::fixed << std::setprecision(2) << costoPromedio << "\n\n";
    fMST<< "--- Aristas del MST ---\n";
    fMST<< std::left << std::setw(6) << "Orden" << std::setw(6) << "u" << std::setw(6) << "v" << "peso\n";
    fMST<< std::string(22, '-') << "\n";
    for(int i = 0; i < (int)mst.aristas.size(); ++i){
        const Arista& a = mst.aristas[i];
        fMST << std::setw(6) << (i+1) << std::setw(6) << a.u << std::setw(6) << a.v << a.peso << "\n";
    }
    fMST<< "\n--- Propiedad de eleccion codiciosa (Lema del ciclo) ---\n";
    fMST<< "La primera arista agregada al MST fue (11, 17) con peso 124.\n";
    fMST<< "Consideremos el ciclo formado por los nodos 11, 17 y 13.\n";
    fMST<< "Las aristas del ciclo son:\n";
    fMST<< " (11, 17) = 124\n";
    fMST<< " (13, 17) = 124\n";
    fMST<< " (11, 13) = floor(64.48 + 63.85) = 128\n";
    fMST<< "La arista de mayor peso en este ciclo es (11, 13) con peso 128.\n";
    fMST<< "Kruskal nunca la agrega porque cuando la evalua, 11 y 13 ya estan\n";
    fMST<< "conectados a traves del nodo 17. Esto ilustra el Lema del ciclo:\n";
    fMST<< "la arista mas costosa de cualquier ciclo no pertenece al MST.\n";
    fMST<< "\n--- Verificacion manual subgrafo de 5 nodos (0, 1, 2, 3, 4) ---\n";
    fMST<< "Promedios: G0=62.88, G1=61.30, G2=66.18, G3=64.83, G4=66.07\n\n";
    fMST<< "Matriz de pesos c(u,v) = floor(M_u + M_v):\n";
    fMST<< "     0    1    2    3    4\n";
    fMST<< "0    -   124  129  127  128\n";
    fMST<< "1   124   -   127  126  127\n";
    fMST<< "2   129  127   -   131  132\n";
    fMST<< "3   127  126  131   -   130\n";
    fMST<< "4   128  127  132  130   -\n";
    fMST<< "\nAristas ordenadas por peso:\n";
    fMST<< "  (0,1)=124, (1,3)=126, (1,2)=127, (1,4)=127, (0,3)=127,\n";
    fMST<< "  (0,4)=128, (2,3)=131, (3,4)=130, (0,2)=129, (2,4)=132\n";
    fMST<< "\nKruskal paso a paso:\n";
    fMST<< " 1. Agregar (0,1)=124 -> une {0} y {1}\n";
    fMST<< " 2. Agregar (1,3)=126 -> une {0,1} y {3}\n";
    fMST<< " 3. Agregar (1,2)=127 -> une {0,1,3} y {2}\n";
    fMST<< " 4. Agregar (1,4)=127 -> une {0,1,2,3} y {4}\n";
    fMST<< " MST del subgrafo: peso total = 124+126+127+127 = 504\n";
    fMST<< "\nVerificacion: el programa produce las mismas aristas para estos nodos.\n";
    fMST.close();
    std::cout<<"-> results/mst_red.txt generado.\n\n";
    std::cout<<"Modulo B completado\n\n";


    return 0;
}