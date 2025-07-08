//
// Created by samuel benibgui on 28/05/2025.
//


//complexity: O(V^3)
//where V is the number of vertices
//limits: weights can be negative, but no negative cycles

#include <iomanip>
#include <vector>
#include <iostream>

using Graph = std::vector<std::vector<int>>;
constexpr int INF = std::numeric_limits<int>::max();

void floydWarshall(Graph& G, Graph& next) {
    const auto n = G.size();

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (G[i][j] != INF)
                next[i][j] = j;

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (G[i][k] != INF && G[k][j] != INF) {
                    G[i][j] = std::min(G[i][j], G[i][k] + G[k][j]);
                    next[i][j] = std::min(next[i][j], next[i][k] + next[k][j]);
                }
            }
        }
    }
}

void print_path(int i, int j, const Graph& next) {
    if (next[i][j] == -1) {
        std::cout << "aucun chemin";
        return;
    }

    std::vector<int> path = {i};
    while (i != j) {
        i = next[i][j];
        path.push_back(i);
    }

    for (int k = 0; k < path.size(); ++k) {
        std::cout << path[k];
        if (k + 1 < path.size()) std::cout << " -> ";
    }
}

int main() {
    constexpr int n = 4;
    Graph dist(n, std::vector<int>(n, INF));
    Graph next(n, std::vector<int>(n, -1));

    for (int i = 0; i < n; ++i)
        dist[i][i] = 0;

    dist[0][1] = 5;
    dist[0][3] = 10;
    dist[1][2] = 3;
    dist[2][3] = 1;

    floydWarshall(dist, next);

    std::cout << "Distances minimales :\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << std::setw(5);
            if (dist[i][j] == INF) std::cout << "INF";
            else std::cout << dist[i][j];
        }
        std::cout << std::endl;
    }

    std::cout << "\nChemins :\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j) {
                std::cout << "Chemin de " << i << " à " << j << " : ";
                print_path(i, j, next);
                std::cout << " (distance = ";
                if (dist[i][j] == INF) std::cout << "INF";
                else std::cout << dist[i][j];
                std::cout << ")\n";
            }
}