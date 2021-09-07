#ifndef PATHWAY_GRAPH_H
#define PATHWAY_GRAPH_H

#include <vector>

using namespace std;

class PathwayMap {

    int numOfNodes;

    vector<int> parent;

    vector<vector<int>> memoizacao;

    static inline int min(int a, int b);

    vector<bool> notInTheSolution;

public:

    explicit PathwayMap(int numEdges);

    vector<vector<int>> graphVertices;

    void addEdge(int sourceNode, int sinkNode);

    int firstTask();

   vector<int> secondTask();

    int coberturaMinimaDeClinicasEmGrafoAciclico(int root, int inTheSolution);
};

#endif