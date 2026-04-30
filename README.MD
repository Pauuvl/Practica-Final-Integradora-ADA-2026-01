# ADA_PF — Módulo A: Divide y Vencerás

## Integrantes
- (Apellido1) — Módulo A  
- (Apellido2) — Módulo B  
- (Apellido3) — Módulo C  

## Estructura del repositorio

```
ADA_PF/
├── README.md
├── data/
│   └── WA_Fn-UseC_-Telco-Customer-Churn.csv   ← dataset (incluir aquí)
├── results/                                     ← generado automáticamente
│   ├── solicitudes_ordenadas.csv
│   ├── busquedas_A.txt
│   ├── mst_red.txt
│   └── asignacion_bw.txt
├── src/
│   ├── parser.hpp / parser.cpp                  ← Módulo A: parseo CSV
│   ├── mergesort.hpp / mergesort.cpp            ← Módulo A: MergeSort
│   ├── binary_search.hpp / binary_search.cpp   ← Módulo A: búsqueda binaria
│   ├── graph.hpp / graph.cpp                   ← Módulo B (pendiente)
│   ├── kruskal.hpp / kruskal.cpp               ← Módulo B (pendiente)
│   ├── knapsack.hpp / knapsack.cpp             ← Módulo C (pendiente)
│   └── main.cpp                                ← orquestador del pipeline
└── report/
    └── Informe.pdf
```

## Compilación

```bash
g++ -std=c++17 -O2 -o ada_pf src/main.cpp src/parser.cpp src/mergesort.cpp src/binary_search.cpp
```

> Cuando se agreguen los módulos B y C, añadir `src/graph.cpp src/kruskal.cpp src/knapsack.cpp` al comando.

## Ejecución

```bash
./ada_pf data/WA_Fn-UseC_-Telco-Customer-Churn.csv
```

El programa genera automáticamente todos los archivos en `results/`.

## Requisitos

- Compilador con soporte C++17 (g++ ≥ 7 o clang++ ≥ 5)
- Sistema operativo: Linux / macOS / Windows (con MinGW o WSL)
- Dataset: `WA_Fn-UseC_-Telco-Customer-Churn.csv` en la carpeta `data/`

## Valores de referencia (verificación Módulo A)

| Propiedad | Valor esperado |
|-----------|---------------|
| Total registros cargados | 7,043 |
| Registros TotalCharges nulo | 11 |
| Registros Churn = No | 5,174 |
| tenure máximo | 72 |
| tenure mínimo | 0 |

## Dataset

- Fuente: [Kaggle — Telco Customer Churn](https://www.kaggle.com/datasets/blastchar/telco-customer-churn)
- Licencia: CC0 (dominio público)
- Registros: 7,043 clientes, 21 atributos