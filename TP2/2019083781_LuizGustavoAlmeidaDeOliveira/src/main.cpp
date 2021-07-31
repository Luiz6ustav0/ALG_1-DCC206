#include <AirportsGraph.hpp>
#include <iostream>

using namespace std;

int main() {
    int n = 0, m = 0, x = 0, y = 0;
    cin >> n >> m;
    AirportsGraph airportsGraph(n);
    while (m--) {
        cin >> x >> y;
        airportsGraph.addConnection(x, y);
    }

    vector<vector<int>> components = airportsGraph.getSCC();
    // cout << "***************" << endl;
    // for (int i = 0; i < (int)components.size(); ++i) {
    //     if (!components[i].empty()) {
    //         for (int j = 0; j < (int)components[i].size(); ++j) {
    //             cout << components[i][j]+1 << " ";
    //         }
    //         cout << endl;
    //     }
    // }

    cout << "RESULTADO" << endl;
    vector<int> inDegree(n, 0), outDegree(n, 0);
    for (auto &component : components) {
        if (!component.empty()) {
            for (int &element : component) {
                for (int adjElement : airportsGraph.graphVertices[element]) {
                    bool isIn = false;
                    for (int inTest : component)
                        if (inTest == adjElement)
                            isIn = true;
                    if (!isIn) {
                        inDegree[adjElement] += 1;
                        outDegree[element] += 1;
                    }
                }
            }
        }
    }

    int sinks = 0, sources = 0;
    for (auto &component : components) {
        if (!component.empty()) {
            int componentIn = 0, componentOut = 0;
            for (auto &element : component) {
                componentIn += inDegree[element];
                componentOut += outDegree[element];
            }
            // cout << "Component " << count << " in: " << componentIn << " | out: " << componentOut << endl;
            if (componentIn == 0)
                sources++;
            if (componentOut == 0)
                sinks++;
        }
    }

    cout << max(sinks, sources) << endl;

    return 0;
}