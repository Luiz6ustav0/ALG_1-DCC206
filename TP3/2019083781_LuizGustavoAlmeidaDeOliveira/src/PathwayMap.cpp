#include <PathwayMap.hpp>
#include <vector>

PathwayMap::PathwayMap(int numEdges) {
    this->numOfNodes = numEdges;
    this->graphVertices = vector<vector<int>>(numEdges, vector<int>());
    this->parent = vector<int>(numEdges);
    this->memoizacao = vector<vector<int>>(numEdges, vector<int>(2, -1));
    this->notInTheSolution = vector<bool>(numEdges, true);
}

void PathwayMap::addEdge(int source, int destination) {
    this->graphVertices[source].push_back(destination);
    this->graphVertices[destination].push_back(source);
}

int PathwayMap::firstTask() {
    return PathwayMap::min(this->coberturaMinimaDeClinicasEmGrafoAciclico(0, 0),
                           this->coberturaMinimaDeClinicasEmGrafoAciclico(0, 1));
}

vector<int> PathwayMap::secondTask() {
    vector<int> nodesInTheSolution = vector<int>();
    for (int nodeIndx = 0; nodeIndx < numOfNodes; ++nodeIndx) {
        if (notInTheSolution[nodeIndx]) {
            for (const auto &adjNode : graphVertices[nodeIndx]) {
                if (notInTheSolution[adjNode]) {
                    notInTheSolution[nodeIndx] = false;
                    notInTheSolution[adjNode] = false;
                    nodesInTheSolution.push_back(nodeIndx);
                    nodesInTheSolution.push_back(adjNode);
                    break;
                }
            }
        }
    }
    return nodesInTheSolution;
}

int PathwayMap::coberturaMinimaDeClinicasEmGrafoAciclico(int root, int calculatedValue) {
    if (graphVertices[root].empty())
        return calculatedValue;
    else if (memoizacao[root][calculatedValue] != -1) // ja foi calculado
        return memoizacao[root][calculatedValue];

    int soma = 0;
    for (int edgeIndex = 0; edgeIndex < (int)graphVertices[root].size(); ++edgeIndex) {
        int currentNode = graphVertices[root][edgeIndex];
        if (currentNode != parent[root]) {
            parent[currentNode] = root;
            if (calculatedValue == 0) // nesse caso o no precisa ser inserido pois nenhum dos dois esta na solucao
                soma += coberturaMinimaDeClinicasEmGrafoAciclico(currentNode, 1);
            else // caso o outro ja esteja, verificando se e melhor incluir o atual ou não
                soma += min(coberturaMinimaDeClinicasEmGrafoAciclico(currentNode, 1),
                            coberturaMinimaDeClinicasEmGrafoAciclico(currentNode, 0));
        }
    }
    memoizacao[root][calculatedValue] = soma + calculatedValue;
    return memoizacao[root][calculatedValue];
}

int PathwayMap::min(int a, int b) {
    return a > b ? b : a;
}
