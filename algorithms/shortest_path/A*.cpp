//
// Created by samuel benibgui on 28/05/2025.
//


// complexity: O(E log V)
// where V is the number of vertices and E is the number of edges
// limits: weights can be negative, but no negative cycles


#include <iostream>
#include <vector>

#include <unordered_set>


using namespace std;

struct Position {
    int x, y;

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const Position& other) const {
        return tie(x, y) < tie(other.x, other.y);
    }
};

// Pour utiliser Position dans unordered_map/set
namespace std {
    template <>
    struct hash<Position> {
        size_t operator()(const Position& p) const noexcept {
            return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
        }
    };
}

int heuristic(const Position& a, const Position& b) {
    return abs(a.x - b.x) + abs(a.y - b.y); // distance de Manhattan
}

vector<Position> a_star(const vector<vector<int>>& grid, const Position& start, const Position& goal) {
    unordered_map<Position, int> g_score;
    unordered_map<Position, Position> came_from;
    auto cmp = [&](const Position& a, const Position& b) {
        return g_score[a] + heuristic(a, goal) > g_score[b] + heuristic(b, goal);
    };
    priority_queue<Position, vector<Position>, decltype(cmp)> open_set(cmp);

    g_score[start] = 0;
    open_set.push(start);

    vector<Position> directions = {{1,0}, {-1,0}, {0,1}, {0,-1}};

    while (!open_set.empty()) {
        Position current = open_set.top();
        open_set.pop();

        if (current == goal) {
            // reconstruct path
            vector<Position> path;
            for (Position p = goal; p != start; p = came_from[p])
                path.push_back(p);
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        for (const auto& dir : directions) {
            Position neighbor = {current.x + dir.x, current.y + dir.y};
            if (neighbor.x < 0 || neighbor.x >= grid.size() || neighbor.y < 0 || neighbor.y >= grid[0].size())
                continue;
            if (grid[neighbor.x][neighbor.y] == 1) continue; // obstacle

            int tentative_g = g_score[current] + 1;
            if (!g_score.count(neighbor) || tentative_g < g_score[neighbor]) {
                g_score[neighbor] = tentative_g;
                came_from[neighbor] = current;
                open_set.push(neighbor);
            }
        }
    }

    return {}; // pas de chemin
}