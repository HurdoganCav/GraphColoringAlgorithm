#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) : V(V) {
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int>& getNeighbors(int v) {
        return adj[v];
    }

    int getV() const {
        return V;
    }
};

void colorGraph(Graph& graph, const string& outputFileName) {
    int V = graph.getV();
    vector<int> colors(V, -1);

    for (int v = 0; v < V; ++v) {
        unordered_set<int> usedColors;
        for (int neighbor : graph.getNeighbors(v)) {
            if (colors[neighbor] != -1) {
                usedColors.insert(colors[neighbor]);
            }
        }

        int color = 0;
        while (usedColors.find(color) != usedColors.end()) {
            ++color;
        }

        colors[v] = color;
    }

    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cout << "Output file failed " << outputFileName << endl;
        return;
    }

    outputFile << "Colored " << outputFileName << endl;
    for (int i = 0; i < V; ++i) {
        string color;
        switch (colors[i]) {
            case 0:
                color = "Red";
                break;
            case 1:
                color = "Blue";
                break;
            case 2:
                color = "Green";
                break;

            default:
                color = "Black";
                break;
        }
        outputFile << "Node " << i << " ---> Color " << color << endl;
    }
}

int main() {
    string datasetPaths[] = {
            //Insert paths here
            R"(gc_20_1.txt)",
            R"(gc_50_7.txt)",
            R"(gc_70_1.txt)",
            R"(gc_500_3.txt)",
            R"(gc_1000_9.txt)"
    };

    for (const auto& datasetPath : datasetPaths) {
        ifstream inputFile(datasetPath);
        if (!inputFile.is_open()) {
            cout << "Cannot reach dateset " << datasetPath << endl;
            continue;
        }

        int V, E;
        inputFile >> V >> E;

        Graph graph(V);
        int u, v;
        while (inputFile >> u >> v) {
            graph.addEdge(u, v);
        }

        string outputFileName = "output_" + datasetPath.substr(datasetPath.find_last_of("/\\") + 1);
        colorGraph(graph, outputFileName);

        cout << "Output folder complete " << outputFileName << endl;

        inputFile.close();
    }

    return 0;
}
