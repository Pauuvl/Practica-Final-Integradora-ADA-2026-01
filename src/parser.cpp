#include "parser.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

// ---------------------------------------------------------------------------
// Utilidad: quita espacios al inicio y al final de un string
// ---------------------------------------------------------------------------
static std::string trim(const std::string& s) {
    size_t inicio = s.find_first_not_of(" \t\r\n");
    if (inicio == std::string::npos) return "";
    size_t fin = s.find_last_not_of(" \t\r\n");
    return s.substr(inicio, fin - inicio + 1);
}

// ---------------------------------------------------------------------------
// parsearCSV
// ---------------------------------------------------------------------------
// Formato del CSV (21 columnas):
//   Col 0  : customerID
//   Col 1  : gender
//   Col 2  : SeniorCitizen
//   Col 3  : Partner
//   Col 4  : Dependents
//   Col 5  : tenure          <-- necesitamos
//   Col 6  : PhoneService
//   Col 7  : MultipleLines
//   Col 8  : InternetService
//   Col 9  : OnlineSecurity
//   Col 10 : OnlineBackup
//   Col 11 : DeviceProtection
//   Col 12 : TechSupport
//   Col 13 : StreamingTV
//   Col 14 : StreamingMovies
//   Col 15 : Contract
//   Col 16 : PaperlessBilling
//   Col 17 : PaymentMethod
//   Col 18 : MonthlyCharges  <-- necesitamos
//   Col 19 : TotalCharges    <-- necesitamos (puede ser " ")
//   Col 20 : Churn            <-- necesitamos
// ---------------------------------------------------------------------------
ParseResult parsearCSV(const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + rutaArchivo);
    }

    ParseResult resultado;
    resultado.totalRegistros    = 0;
    resultado.totalChargesNulos = 0;

    std::string linea;

    // Saltar cabecera
    std::getline(archivo, linea);

    while (std::getline(archivo, linea)) {
        if (trim(linea).empty()) continue;

        // Separar por comas
        std::vector<std::string> campos;
        std::istringstream ss(linea);
        std::string campo;
        while (std::getline(ss, campo, ',')) {
            campos.push_back(campo);
        }

        // El CSV tiene exactamente 21 columnas; ignorar filas malformadas
        if (campos.size() < 21) continue;

        Solicitud s;

        s.customerID     = trim(campos[0]);
        s.tenure         = std::stoi(trim(campos[5]));
        s.monthlyCharges = std::stod(trim(campos[18]));

        // TotalCharges puede ser un espacio en blanco cuando tenure == 0
        std::string tcStr = trim(campos[19]);
        if (tcStr.empty()) {
            s.totalCharges = 0.0;
            resultado.totalChargesNulos++;
        } else {
            s.totalCharges = std::stod(tcStr);
        }

        std::string churnStr = trim(campos[20]);
        s.churn = (churnStr == "Yes");

        resultado.solicitudes.push_back(s);
        resultado.totalRegistros++;
    }

    return resultado;
}