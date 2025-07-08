//
// Created by samuel benibgui on 26/06/2025.
//

/* Description: Problem Statement (EN):
Given n nodes labeled from 0 to n - 1 and a list of undirected edges.
determine if these edges make up a valid tree.

A tree is an acyclic, connected undirected graph. */
#include <iostream>
#include <vector>
using namespace std;

int find(int x, vector<int> &parent) {
    if (parent[x] != x)
        parent[x] = find(parent[x], parent);
    return parent[x];
}

bool unionSets(int x, int y, vector<int>& parent) {
    int px = find(x, parent);
    int py = find(y, parent);
    if (px == py) return false; // cycle
    parent[px] = py;
    return true;
}

bool validTree(int n, const vector<pair<int, int>>& edges) {
    if (n == 0) return true;
    if (edges.size() != n - 1) return false;

    vector<int> parent(n);
    for (int i = 0; i < n; ++i) parent[i] = i;

    int components = n;
    for (const auto& [u, v] : edges) {
        if (unionSets(u, v, parent)) {
            components--;
        } else {
            return false;
        }
    }

    return components == 1;
}

void runTest(int n, const vector<pair<int, int>>& edges, bool expected, const string& name) {
    bool res = validTree(n, edges);
    cout << name << " => " << (res == expected ? "PASSED ✅" : "FAILED ❌") << endl;
}

int main() {
    runTest(5, {{0,1},{0,2},{0,3},{1,4}}, true, "Tree test - valid tree");
    runTest(5, {{0,1},{1,2},{2,3},{1,3},{1,4}}, false, "Tree test - cycle");
    runTest(4, {{0,1},{2,3}}, false, "Tree test - disconnected");
    runTest(1, {}, true, "Tree test - single node");
    runTest(0, {}, true, "Tree test - empty graph");
    runTest(4, {{1, 2}, {2, 3}}, false, "Test 7 - Isolated node (0 is disconnected)");
    return 0;
}