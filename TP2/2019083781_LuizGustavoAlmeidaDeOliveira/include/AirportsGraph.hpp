#ifndef AIRPORTS_GRAPH_H
#define AIRPORTS_GRAPH_H

#include <unordered_map>
#include <vector>

using namespace std;

class AirportsGraph {

    int numOfNodes;

    vector<vector<int>> reversedVertices;
    vector<unordered_map<int, int>> scc;
    vector<int> inDegreeNodesInSCC;
    vector<int> outDegreeNodesInSCC;
    vector<char> visited;
    int sinks, sources;

public:
    AirportsGraph(int numEdges);

    vector<vector<int>> graphVertices;

    int getNumOfNodes();

    void addConnection(int sourceNode, int sinkNode);

    vector<unordered_map<int, int>> getSCC();

    void calculateInAndOutDegreeForSCCs();

    void calculateNumberOfSinksAndSourcesFromSCCs();

    int getMaxBetweenSinksAndSources();

    void dfs(int u, vector<vector<int>> &adj, vector<int> &out);

    void dfsToBuildComponents(int node, vector<vector<int>> &adjNodes, unordered_map<int, int> &order);
};

#endif