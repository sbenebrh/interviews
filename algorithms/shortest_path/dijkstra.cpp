//
// Created by samuel benibgui on 28/05/2025.
//

// complexity: O((V + E) log V)
// where V is the number of vertices and E is the number of edges
// limits: weights are non-negative integers




#include <vector>
#include <queue>
#include <iostream>

using Graph = std::vector<std::vector<std::pair<int, int>>>;

std::vector<int> dijkstra(const Graph& graph, int start, std::vector<int>& parent) {
    constexpr int INF = std::numeric_limits<int>::max();
    std::vector dist(graph.size(), INF);
    parent.assign(graph.size(), -1);
    dist[start] = 0;

    using P = std::pair<int, int>; // (distance, node)
    std::priority_queue<P, std::vector<P>, std::greater<>> pq; // min-heap
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : graph[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
                parent[v] = u;
            }
        }
    }
    return dist;
}



void print_path(int target, const std::vector<int>& parent) {
    std::stack<int> path;
    int current = target;

    while (current != -1) {
        path.push(current);
        current = parent[current];
    }

    std::cout << "Chemin : ";
    while (!path.empty()) {
        std::cout << path.top();
        path.pop();
        if (!path.empty()) std::cout << " -> ";
    }
    std::cout << std::endl;
}
int main() {
    // Création du graphe
    // Exemple : 0 -> { (1,4), (2,1) }, etc.
    Graph g(4);
    g[0] = {{1, 4}, {2, 1}};
    g[1] = {{3, 1}};
    g[2] = {{1, 2}, {3, 5}};
    g[3] = {}; // Pas de voisins

    int start = 0;
    std::vector<int> parent;
    std::vector<int> distances = dijkstra(g, start, parent);

    // Affichage des distances depuis le noeud 0
    std::cout << "Distances depuis le sommet " << start << " :" << std::endl;
    for (size_t i = 0; i < distances.size(); ++i) {
        if (distances[i] == std::numeric_limits<int>::max()) {
            std::cout << "Sommet " << i << " : infini (inatteignable)" << std::endl;
        } else {
            std::cout << "Sommet " << i << " : " << distances[i] << std::endl;
            print_path(i, parent);
        }
    }

    return 0;
}