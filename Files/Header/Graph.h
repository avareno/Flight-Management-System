#ifndef PROJETO_AED_GRAPH_H
#define PROJETO_AED_GRAPH_H

#include <string>
#include <vector>
#include <list>

using namespace std;

class Graph {
    struct Edge{
        string src; //Source node -> Will be the Source Airport Code
        string dest; //Destination node -> Will be the Target Airport Code
        string al_code; //A string al_code -> Will be the Airline Code
        double dist; //An double dist -> Will be the distance between the Source Airport and the Target Airport (Haversine Distance Function)
        // TODO: Calcular distância entre dois locais com a 'Haversine Distance Function'
    };
    struct Node{
        list<Edge> adj; //The list of outgoing edges (to adjacent nodes)
        bool visited; // To track if the node has been visited
    };
    int n; //Graph size(vertices are number ed from 1 ton)
    bool hasDir; // false:undirect; true:directed
    vector<Node> nodes; //The list of nodes being represented

public:
    //Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir=false);
    //Add edge from source to destination with a certain al_code
    void addEdge(const string& src, const string& dest, const string& al_code, double dist);
    int getNodeIndex(const string& label);
    void dfs(const string& startNode);
    void bfs(const string& startNode);
    int connectedComponents();
    double Haversine_d(double &lat1, double& lon1, double &lat2, double& lon2);
};

#endif //PROJETO_AED_GRAPH_H
