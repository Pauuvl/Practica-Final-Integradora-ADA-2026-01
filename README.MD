# ADA_PF — Práctica Final Integradora

## Integrantes
- Paulina Velásquez 
- Helen Valentina Sanabria
- Yilmar David Murillo
- Nicolas Rodriguez

## Estructura del repositorio

```
Practica-Final-Integradora-ADA-2026-01/
├── .gitignore
├── README.MD
├── data/
│   └── WA_Fn-UseC_-Telco-Customer-Churn.csv
├── results/
│   ├── solicitudes_ordenadas.csv        ← Módulo A
│   ├── busquedas_A.txt                  ← Módulo A
│   ├── mst_red.txt                      ← Módulo B
│   └── asignacion_bw.txt                ← Módulo C (pendiente)
├── src/
│   ├── parser.hpp / parser.cpp          ← Módulo A: parseo CSV
│   ├── mergesort.hpp / mergesort.cpp    ← Módulo A: MergeSort
│   ├── binary_search.hpp / binary_search.cpp ← Módulo A: búsqueda binaria
│   ├── graph.hpp / graph.cpp            ← Módulo B: grafo K_20
│   ├── kruskal.hpp / kruskal.cpp        ← Módulo B: Kruskal + Union-Find
│   ├── knapsack.hpp / knapsack.cpp      ← Módulo C (pendiente)
│   └── main.cpp                         ← orquestador del pipeline
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