#ifndef AIRPORTS_GRAPH_H
#define AIRPORTS_GRAPH_H

#include <vector>

using namespace std;

class AirportsGraph {

    int numOfNodes;

    vector<vector<int>> reversedVertices;
    vector<vector<int>> scc;
    vector<int> inDegreeNodesInSCC;
    vector<int> outDegreeNodesInSCC;
    vector<char> visited;
    int sinks, sources;

public:
    AirportsGraph(int numEdges);

    vector<vector<int>> graphVertices;

    int getNumOfNodes();

    void addConnection(int sourceNode, int sinkNode);

    vector<vector<int>> getSCC();

    void calculateInAndOutDegreeForSCCs();

    void calculateNumberOfSinksAndSourcesFromSCCs();

    int getMaxBetweenSinksAndSources();

    void dfs(int u, vector<vector<int>> &adj, vector<int> &out);
};

#endif