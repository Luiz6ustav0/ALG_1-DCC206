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

    airportsGraph.getSCC();
    airportsGraph.calculateInAndOutDegreeForSCCs();
    airportsGraph.calculateNumberOfSinksAndSourcesFromSCCs();
    int result = airportsGraph.getMaxBetweenSinksAndSources();

    cout << result << endl;

    return 0;
}