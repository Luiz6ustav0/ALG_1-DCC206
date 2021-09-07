#include <PathwayMap.hpp>
#include <iostream>
#include <unordered_map>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {

    if (!argv[1] || !argv[2]) {
        cout << "Argumentos invalidos" << std::endl;
        exit(-1);
    }

    int n = 0, m = 0, x = 0, y = 0;
    string tarefa, caminhoParaEntrada;

    tarefa = string(argv[1]);
    caminhoParaEntrada = string(argv[2]);
    fstream arqLeitura(caminhoParaEntrada);

    arqLeitura >> n >> m;

    PathwayMap pathwaysGraph(n);

    while (m--) {
        arqLeitura >> x >> y;
        pathwaysGraph.addEdge(x, y);
    }

    if (tarefa == "tarefa1") {
        cout << pathwaysGraph.firstTask() << endl;
    } else if (tarefa == "tarefa2") {
        auto secondTaskResult = pathwaysGraph.secondTask();
        for (const auto &node : secondTaskResult) cout << node << endl;
        cout << secondTaskResult.size() << endl;
    }

    return 0;
}