# Advanced-Algorithm-Project

## Background
This project is part of the Advanced Algorithms course in PES University. 
The aim of the project is to compare different routing algorithms, observe their efficiency and understand the principles behind them.

## Steps to Run
### Central Routing Algorithms
To compile all the central routing algorithms
```
g++ ./Code/main.cpp ./Code/Dijkstra.cpp  ./Code/Bellman.cpp ./Code/Floyds.cpp -o cen.out
```
To run with different inputs
``` 
./cen.out < /Input/500nodes.txt
```

### Distance Vector Algorithms
To compile sequential distance vector
```
g++ ./Code/dist-vect-seq.cpp -o seq.out
```
To run sequential disance vector with input
```
./seq.out ./Input/500nodes.txt
```
To compile threaded distance vector
```
g++ ./Code/dist-vect-thread.cpp -pthread -o -th.out
```
To run threaded distance vector with inputs
```
./th.out ./Input/500nodes.txt
```

## Built with
* C++

##Authors
* **Rohan Rajesh Talesara** - **01FB16ECS309**
* **Saahitya E** - **01FB16ECS322**
* **Shalini Sai Prasad** - **01FB16ECS350**

