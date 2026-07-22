# 🛣️ Road Repair Prioritization System using Kruskal's Algorithm 🚗🚧👷‍♂️

[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Algorithm](https://img.shields.io/badge/Algorithm-Kruskal%27s%20MST-orange.svg)](https://en.wikipedia.org/wiki/Kruskal%27s_algorithm)
[![Data Structure](https://img.shields.io/badge/Data%20Structure-Adjacency%20List%20%2B%20DSU-green.svg)](https://en.wikipedia.org/wiki/Disjoint-set_data_structure)

A C-based graph data structure implementation that models a city road network and calculates the optimal priority sequence for repairing degraded roads using **Kruskal's Minimum Spanning Tree (MST) Algorithm**.

---

## 📌 Overview

A graph-based decision system that prioritizes road maintenance using **Kruskal's Algorithm**. It ranks repair urgency by evaluating pothole counts, road condition, and traffic density to output an optimal repair schedule.

---

## 🧮 Priority Weight Calculation Formula

Each road segment (edge) connecting two checkpoints (vertices) is assigned a priority weight using weighted metrics:

$$\text{Priority Weight} = (-10 \times \text{Pothole Count}) + (-7 \times \text{Road Condition}) + (-5 \times \text{Traffic Density})$$

| Parameter | Scale / Input | Weight Multiplier | Significance |
| :--- | :--- | :--- | :--- |
| **Potholes Count** | Number of potholes | `-10` | Higher pothole counts yield lower negative weights (higher urgency) |
| **Road Condition** | `1` (Good) to `10` (Worst) | `-7` | Worse conditions increase repair priority |
| **Traffic Density** | `1` (Low) to `10` (High) | `-5` | Heavily traversed roads receive higher maintenance priority |

> 💡 **Note**: Because Kruskal's Algorithm selects edges with minimum weight first, larger negative numbers indicate higher repair urgency and are selected earlier.

---

## 🔬 Key Data Structures & Algorithms

- **Adjacency List Graph (`struct graph` & `struct listNode`)**: Efficiently represents checkpoints (nodes) and road segments (edges).
- **Disjoint-Set Union (DSU)**: Uses `findParent()` and `uni()` helper functions to detect and avoid cycles during tree construction.
- **Kruskal's Minimum Spanning Tree (MST)**: Iteratively selects candidate roads with the highest urgency (minimum weight) until all checkpoints are connected.

---

## 📁 Project Structure

```
Road-repair-prioritization-system/
├── priority.h         # Priority weight multipliers and structure definition
├── main.c             # Graph construction, priority evaluation & Kruskal's algorithm
└── README.md          # Project documentation
```

---

## 🚀 Getting Started

### Prerequisites
- GCC Compiler or any C99-compliant C compiler (Clang, MSVC, MinGW).

### Compilation & Execution

1. Clone the repository:
   ```bash
   git clone https://github.com/SamarthBagde/Road-repair-prioritization-system.git
   cd Road-repair-prioritization-system
   ```

2. Compile the source code:
   ```bash
   gcc main.c -o main
   ```

3. Run the compiled executable:
   - **Linux / macOS**:
     ```bash
     ./main
     ```
   - **Windows**:
     ```cmd
     main.exe
     ```

---

## 💻 Sample Interaction

```text
Enter number of check points : 
3
Enter name of check point 0 : Station
Enter name of check point 1 : Market
Enter name of check point 2 : Hospital

Enter number of Paths (Roads) want to repair : 
2
Enter paths details : 

Enter road 0 (startpoint - endpoint) : 
0 1
Enter pothole count : 
15
Enter traffic dencity [1 (low) - 10 (high)] : 
8
Enter road condition [1 (Good) - 10 (Worst)] : 
9

Enter road 1 (startpoint - endpoint) : 
1 2
Enter pothole count : 
5
Enter traffic dencity [1 (low) - 10 (high)] : 
4
Enter road condition [1 (Good) - 10 (Worst)] : 
3

The priority order of the road repair operations suggested by the system is : 

Road : Station - Market
Pothole Count : 15	Traffic Density : 8	Road Condition : 9
```

---

## 📄 License

Distributed under the MIT License. See `LICENSE` for more information.
