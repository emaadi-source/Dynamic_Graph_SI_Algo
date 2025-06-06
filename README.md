# Dynamic_Graph_SI_Algo
# Overview
DynamicGraphSI is a C++ implementation of a subgraph isomorphism (SI) algorithm tailored for dynamic graphs. The project integrates concepts from discrete mathematics and data training, enabling the detection of temporally ordered patterns in evolving networks. It extends the VF3 algorithm to efficiently identify isomorphic subgraphs across sequential snapshots, preserving both structure and chronology.

![image alt](https://github.com/emaadi-source/Dynamic_Graph_SI_Algo/blob/main/_Create%20a%20clean%2C%20modern%20illustration%20%2C%20showing%20a%20dynamic%20graph%20of%20a%20basketball%20passing%20network.%20Depict%20nodes%20(players)%20and%20directed%20edges%20(passes)%20across%20layered%20time%20snapshots%20with%20a%20blue-to-green%20gradient.%20I.jpg)

# Key Features
Dynamic Graph Processing – Supports snapshot-based representation for tracking evolving structures.
Subgraph Isomorphism Detection – Matches patterns while maintaining temporal order.
Optimized Algorithm – Extends VF3 for dynamic contexts, ensuring efficiency.
Application in Sports Analytics – Analyzes basketball passing networks to evaluate team adaptability using entropy measures.
# Technical Details
Graph Representation: Uses an adjacency-based snapshot model to capture evolving connections.
Pattern Matching: Detects subgraph occurrences while considering node correspondence and sequential interactions.
Entropy Analysis: Quantifies network complexity to assess strategic adaptability in basketball games.
Implementation: Developed in C++, ensuring performance optimization and scalability.
# Usage
This project is suitable for researchers, analysts, and developers working on:

Dynamic graph analysis in social networks, biology, and sports.
Graph pattern recognition with chronological constraints.
Performance evaluation in adaptive network systems.
# Installation & Setup
Clone the Repository

git clone https://github.com/emaadi-source/DynamicGraphSI.git
cd DynamicGraphSI
# Compile the Code

g++ -o DynamicGraphSI main.cpp -std=c++11  
# Run the Program

./DynamicGraphSI  
