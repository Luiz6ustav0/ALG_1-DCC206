#include <AirportsGraph.hpp>
#include <stack>
#include <vector>

AirportsGraph::AirportsGraph(int numEdges) {
    this->numOfNodes = numEdges;
    this->graphVertices = vector<vector<int>>(numEdges, vector<int>());
    this->reversedVertices = vector<vector<int>>(numEdges, vector<int>());
    this->visited = vector<char>(numEdges, 0);
    this->sinks = this->sources = 0;
}

int AirportsGraph::getNumOfNodes() {
    return this->numOfNodes;
}

void AirportsGraph::addConnection(int source, int destination) {
    this->graphVertices[source - 1].push_back(destination - 1);
    this->reversedVertices[destination - 1].push_back(source - 1);
}

void AirportsGraph::dfs(int node, vector<vector<int>> &adjNodes, vector<int> &order) {
    this->visited[node] = 1;
    for (int vertex : adjNodes[node])
        if (this->visited[vertex] == 0)
            dfs(vertex, adjNodes, order);
    order.push_back(node);
}

vector<vector<int>> AirportsGraph::getSCC() {
    vector<int> ord;
    for (int nodeIndx = 0; nodeIndx < this->getNumOfNodes(); ++nodeIndx)
        if (visited[nodeIndx] == 0)
            dfs(nodeIndx, this->graphVertices, ord);

    this->visited = vector<char>(this->getNumOfNodes(), 0);
    for (int nodeIndx = this->getNumOfNodes() - 1; nodeIndx >= 0; --nodeIndx)
        if (!visited[ord[nodeIndx]]) {
            this->scc.push_back({});
            dfs(ord[nodeIndx], this->reversedVertices, this->scc.back());
        }
    return this->scc;
}

void AirportsGraph::calculateInAndOutDegreeForSCCs() {
    this->inDegreeNodesInSCC = vector<int>(this->numOfNodes, 0);
    this->outDegreeNodesInSCC = vector<int>(this->numOfNodes, 0);

    for (auto &component : this->scc) {
        for (int &element : component) {
            for (int &adjElement : this->graphVertices[element]) {
                bool isIn = false;
                for (int &inTest : component)
                    if (inTest == adjElement)
                        isIn = true;
                if (!isIn) {
                    this->inDegreeNodesInSCC[adjElement] += 1;
                    this->outDegreeNodesInSCC[element] += 1;
                }
            }
        }
    }
}

void AirportsGraph::calculateNumberOfSinksAndSourcesFromSCCs() {
    for (auto &component : this->scc) {
        int componentIn = 0, componentOut = 0;
        for (auto &element : component) {
            componentIn += this->inDegreeNodesInSCC[element];
            componentOut += this->outDegreeNodesInSCC[element];
        }
        if (componentIn == 0)
            this->sources++;
        if (componentOut == 0)
            this->sinks++;
    }
}

int AirportsGraph::getMaxBetweenSinksAndSources() {
    return max(this->sinks, this->sources);
}