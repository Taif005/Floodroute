# 🚦 Safe Route Finder using Graph Algorithms (C++)

## 📖 Overview

Safe Route Finder is a C++ project that finds the shortest and safest route between two locations in a road network. The project models a city as a weighted graph, where intersections are represented as vertices and roads are represented as edges. Roads marked as flooded are ignored to ensure that only safe routes are considered.

The project implements three well-known pathfinding algorithms:

* **Dijkstra's Algorithm**
* **Bellman-Ford Algorithm**
* **A* (A-Star) Search Algorithm**

This project was developed to compare different shortest-path algorithms and demonstrate their behavior on the same graph.

---

## ✨ Features

* Read graph data from an input file.
* Represent the road network using an adjacency list.
* Ignore flooded or blocked roads.
* Find the shortest safe path between two locations.
* Display:

  * Source location
  * Destination location
  * Shortest distance
  * Shortest path
* Compare the performance of three graph algorithms.

---

## 🧠 Algorithms Used

### 1. Dijkstra's Algorithm

* Finds the shortest path in graphs with non-negative edge weights.
* Uses a **min-priority queue (Min Heap)**.
* Efficient for road networks without negative weights.

**Time Complexity:** `O((V + E) log V)`

---

### 2. Bellman-Ford Algorithm

* Finds the shortest path even when negative edge weights exist.
* Detects **negative-weight cycles**.
* Slower than Dijkstra but more flexible.

**Time Complexity:** `O(V × E)`

---

### 3. A* Search Algorithm

* Uses a heuristic (Euclidean distance) to estimate the remaining distance to the destination.
* Usually explores fewer nodes than Dijkstra.
* Suitable for navigation and pathfinding applications.

**Time Complexity:** `O((V + E) log V)` (depends on the heuristic)

---

## 📂 Project Structure

```text
Safe-Route-Finder/
│
├── Dijkstra.cpp
├── BellmanFord.cpp
├── AStar.cpp
├── input.txt
├── README.md
└── docs/
    ├── Dijkstra_Line_by_Line_Explanation.docx
    ├── BellmanFord_Line_by_Line_Explanation.docx
    └── AStar_Line_by_Line_Explanation.docx
```

---

## 📥 Input Format

```text
Number_of_Vertices Number_of_Edges

Location Names

u v weight flooded

...

Source Destination
```

### Example

```text
5 7

Dhaka
Mirpur
Uttara
Gazipur
Tongi

0 1 4 0
0 2 2 0
1 3 5 0
2 3 2 0
3 4 3 0
2 4 10 1
1 4 8 0

0 4
```

Where:

* **u** = Source vertex
* **v** = Destination vertex
* **weight** = Distance or travel cost
* **flooded**

  * `0` = Safe road
  * `1` = Flooded road (ignored)

---

## 📤 Output

```text
Source: Dhaka
Destination: Tongi

Shortest Distance: 9

Shortest Path:
Dhaka -> Uttara -> Gazipur -> Tongi
```

---

## 💻 Technologies Used

* C++
* Standard Template Library (STL)
* Priority Queue
* Vectors
* File Handling
* Graph Data Structure

---

## 🎯 Learning Objectives

This project demonstrates:

* Graph representation using adjacency lists
* Shortest path algorithms
* Priority queues
* Heuristic search
* File handling in C++
* Path reconstruction using parent arrays
* Algorithm comparison and analysis

---

## 🚀 Future Improvements

* Interactive graphical user interface (GUI)
* Real-time traffic information
* Dynamic obstacle detection
* Support for undirected and directed graphs
* Visual graph representation
* Performance benchmarking of algorithms
* Map integration using real geographic data

---

## 👨‍💻 Author

**Taif Chowdhury**

Computer Science & Engineering Student

---

## 📜 License

This project is intended for educational and learning purposes.
