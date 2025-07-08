//
// Created by samuel benibgui on 28/05/2025.
//
// complexity: O(V * E)
// where V is the number of vertices and E is the number of edges
// limits: weights can be negative, but no negative cycles

#include <vector>
#include <iostream>
#include <limits>


struct Edge {
    int from;
    int to;
    int weight;
};

const int INF = std::numeric_limits<int>::max();

bool bellman_ford(int n, int start, const std::vector<Edge>& edges, std::vector<int>& dist, std::vector<int>& parent) {
    dist.assign(n, INF);
    parent.assign(n, -1);
    dist[start] = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (const auto& edge : edges) {
            if (dist[edge.from] != INF && dist[edge.from] + edge.weight < dist[edge.to]) {
                dist[edge.to] = dist[edge.from] + edge.weight;
                parent[edge.to] = edge.from;
            }
        }
    }

    // Check for negative weight cycles
    for (const auto& edge : edges) {
        if (dist[edge.from] != INF && dist[edge.from] + edge.weight < dist[edge.to]) {
            return false; // Negative cycle detected
        }
    }
    return true; // No negative cycle
}

void print_path(int node, const std::vector<int>& parent) {
    if (node == -1) return;
    print_path(parent[node], parent);
    std::cout << node << " ";
}


int main() {
    int n = 5; // nombre de sommets
    std::vector<Edge> edges = {
        {0, 1, 6},
        {0, 2, 7},
        {1, 2, 8},
        {1, 3, 5},
        {1, 4, -4},
        {2, 3, -3},
        {2, 4, 9},
        {3, 1, -2},
        {4, 0, 2},
        {4, 3, 7}
    };

    std::vector<int> dist, parent;
    int start = 0;

    if (bellman_ford(n, start, edges, dist, parent)) {
        for (int i = 0; i < n; ++i) {
            std::cout << "Distance vers " << i << " = ";
            if (dist[i] == INF)
                std::cout << "infini";
            else
                std::cout << dist[i];

            std::cout << " — Chemin : ";
            print_path(i, parent);
            std::cout << "\n";
        }
    } else {
        std::cout << "Cycle négatif détecté !\n";
    }

    return 0;
}