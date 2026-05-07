# ADA_PF — Práctica Final Integradora

## Integrantes
- Paulina Velásquez 
- Helen Valentina Sanabria
- Yilmar David Murillo
- Nicolas Rodriguez

## Estructura del repositorio

```
ADA_PF_Velasquez_Sanabria_Murillo_Rodriguez/
├── README.md
├── data/
│   └── WA_Fn-UseC_-Telco-Customer-Churn.csv
├── results/
│   ├── solicitudes_ordenadas.csv        Módulo A: registros ordenados por tenure
│   ├── busquedas_A.txt                  Módulo A: resultados de las 5 consultas
│   ├── mst_red.txt                      Módulo B: aristas del MST y peso total
│   └── asignacion_bw.txt                Módulo C: solución óptima y contraejemplo
├── src/
│   ├── parser.cpp / parser.hpp          Lectura y parseo del CSV
│   ├── mergesort.cpp / mergesort.hpp
│   ├── binary_search.cpp / binary_search.hpp
│   ├── graph.cpp / graph.hpp            Grafo ponderado y Union-Find
│   ├── kruskal.cpp / kruskal.hpp
│   ├── knapsack.cpp / knapsack.hpp
│   └── main.cpp                         Orquestador del pipeline completo
└── report/
    └── Informe.pdf
```

## Compilación

```bash
g++ -std=c++17 -O2 -o ada_pf src/main.cpp src/parser.cpp src/mergesort.cpp src/binary_search.cpp src/graph.cpp src/kruskal.cpp
```

> Cuando se agregue el Módulo C, añadir `src/knapsack.cpp` al comando.

## Ejecución

**Linux / macOS:**
```bash
./ada_pf data/WA_Fn-UseC_-Telco-Customer-Churn.csv
```

**Windows:**
```bash
ada_pf.exe data/WA_Fn-UseC_-Telco-Customer-Churn.csv
```

El programa genera automáticamente todos los archivos en `results/`.

## Requisitos

- Compilador con soporte C++17 (g++ ≥ 7 o clang++ ≥ 5)
- Sistema operativo: Linux / macOS / Windows (con MinGW o WSL)
- Dataset: `WA_Fn-UseC_-Telco-Customer-Churn.csv` en la carpeta `data/`

## Valores de referencia

| Propiedad | Valor esperado |
|-----------|---------------|
| Total registros cargados | 7,043 |
| Registros TotalCharges nulo | 11 |
| Registros Churn = No | 5,174 |
| tenure máximo | 72 |
| tenure mínimo | 0 |
| Aristas MST | 19 |
| Peso total MST | 2,393.00 |

## Dataset

- Fuente: [Kaggle — Telco Customer Churn](https://www.kaggle.com/datasets/blastchar/telco-customer-churn)
- Licencia: CC0 (dominio público)
- Registros: 7,043 clientes, 21 atributos