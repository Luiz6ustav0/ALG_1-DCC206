#include <iostream>
#include <list>
#include <stack>
#include <vector>
#define NIL -1
using namespace std;

class Graph {
    int V; // No. of vertices

    void SCCUtil(int &u, vector<int> &disc, vector<int> &low, stack<int> &st,
                 vector<bool> &stackMember, vector<vector<int>> &components, int &k);

public:
    list<int> *adj;                                    // A dynamic array of adjacency lists
    Graph(int V);                                      // Constructor
    void addEdge(int v, int w);                        // function to add an edge to graph
    void SCC(vector<vector<int>> &components, int &k); // prints strongly connected components
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V + 1];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}

void Graph::SCCUtil(int &u, vector<int> &disc, vector<int> &low, stack<int> &st,
                    vector<bool> &stackMember, vector<vector<int>> &components, int &k) {
    static int time = 0;

    disc[u] = low[u] = ++time;
    st.push(u);
    stackMember[u] = true;

    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
        int v = *i; // v is current adjacent of 'u'

        if (disc[v] == -1) {
            SCCUtil(v, disc, low, st, stackMember, components, k);

            low[u] = min(low[u], low[v]);
        }

        else if (stackMember[v] == true)
            low[u] = min(low[u], disc[v]);
    }

    int w = 0; // To store stack extracted vertices
    if (low[u] == disc[u]) {
        while (st.top() != u) {
            w = (int)st.top();
            components[k].push_back(w);
            stackMember[w] = false;
            st.pop();
        }
        w = (int)st.top();
        components[k].push_back(w);
        k++;
        stackMember[w] = false;
        st.pop();
    }
}

// The function to do DFS traversal. It uses SCCUtil()
void Graph::SCC(vector<vector<int>> &components, int &k) {
    vector<int> disc(V, NIL);
    vector<int> low(V, NIL);
    vector<bool> stackMember(V, false);
    stack<int> st;
    for (int i = 1; i <= V; i++)
        if (disc[i] == NIL)
            SCCUtil(i, disc, low, st, stackMember, components, k);
}

// Driver program to test above function
int main() {
    int n = 0, m = 0, k = 0, x, y;
    cin >> n >> m;
    Graph g1(n + 1);
    vector<int> inDegree(n + 1, 0), outDegree(n + 1, 0);
    vector<vector<int>> components(n + 1, vector<int>());
    while (m--) {
        cin >> x >> y;
        g1.addEdge(x, y);
    }
    g1.SCC(components, k);

    // cout << "***************" << endl;
    // for (int i = 0; i < components.size(); ++i) {
    //     if (!components[i].empty()) {
    //         for (int j = 0; j < components[i].size(); ++j) {
    //             cout << components[i][j] << " ";
    //         }
    //         cout << endl;
    //     }
    // }
    cout << "RESULTADO" << endl;
    for (auto &component : components) {
        if (!component.empty()) {
            for (int &element : component) {
                for (int adjElement : g1.adj[element]) {
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

    int sinks = 0, sources = 0, count = 0;
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
            count++;
        }
    }

    cout << max(sinks, sources) << endl;

    return 0;
}