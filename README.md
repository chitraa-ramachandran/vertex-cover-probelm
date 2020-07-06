# vertex-cover-probelm
Implemented vertex cover probelm for optimal placement of traffic cameras

This work belongs to the coursework done by me for, ECE650: Methods and Tools for software Engineering, University of Waterloo.  
**Languages used:**  
- Python 2
- C++  
## Overview
The project is to help the local police department with their installation of security cameras at traffic intersections.
You will solve a particular kind of optimization problem, called the Vertex Cover problem, in this
context. The idea is for the police to be able to minimize the number of cameras they need to
install, and still be as effective as possible with their monitoring.  

Module 1 (A1) 
Take as input a series of commands that describe streets. Use that input to construct a particular kind of undirected graph. So, we Developed a python script that can parse vertices of given streets and localize the intersections, representing the given vertices and edges as an undirected graph.
Module 2 (A2) 
Developed a C++ script that finds the shortest path for a given undirected graph using Breadth-First Search algorithm.  
Module 3 (A3)
Developed two C++ scripts namely rgen and driver. Rgen generates random streets for any given user specification, Driver is the control program that helps to couple Module 1 , Module 2 and Rgen. Inter-Process communication concepts and methodologies are implemented.Inter-Process Communication (IPC) is used to link the output of the random input generator to the input of the Python script, and the output of the Python script to the input of the C++ program that finds the shortest path
Module 4 (A4) 
Developed a C++ script that reduces a VERTEX COVER to CNF-SAT and incorporates MiniSAT solver  to compute the minimum sized Vertex cover for any given undirected graph.  
Final Analysis: Developed two more Vertex cover algorithms (Approx-VC1 and Approx-VC2) and did analysis on the following criterions : vertex cover obtained, running time and the mean approximation ratio. 


