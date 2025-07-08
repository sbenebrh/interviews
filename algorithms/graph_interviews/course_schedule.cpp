//
// Created by samuel benibgui on 26/06/2025.
//

/* Description:
 * You are given numCourses and a list of prerequisites,
 * where each prerequisite is a pair [a, b] meaning to take course a, you must first take course b.
* Return true if it is possible to finish all courses (i.e. the course dependency graph has no cycle), otherwise return false.
*/

#include <iostream>
#include <vector>
using namespace std;

auto dfs(int node, const vector<vector<int> > &adj, vector<int> &state) -> bool {
    if (state[node] == 1) return false; // cycle detected
    if (state[node] == 2) return true; // already visited

    state[node] = 1; // mark as visiting
    for (int neighbor : adj[node]) {
        if (!dfs(neighbor, adj, state)) return false; // cycle found in DFS
    }
    state[node] = 2; // mark as visited
    return true;
}

bool canFinish(int numCourses, const vector<pair<int, int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    for (const auto& [a,b] : prerequisites) {
        adj[b].push_back(a); // b must be taken before a
    }
    vector<int> state(numCourses, 0); // 0: unvisited, 1: visiting, 2: visited
    bool result = true;
    for (int node = 0; node < numCourses; ++node) {
        if (state[node]==0) {
            result &= dfs(node, adj, state);
        }
    }
    return result;
}

void runTest(int numCourses, const vector<pair<int, int>>& prerequisites, bool expected, const string& testName) {
    bool result = canFinish(numCourses, prerequisites);
    cout << testName << " => ";
    if (result == expected) {
        cout << "PASSED ✅" << endl;
    } else {
        cout << "FAILED ❌ (Expected: " << expected << ", Got: " << result << ")" << endl;
    }
}

int main() {
    runTest(2, {{1, 0}}, true, "Test 1 - Simple dependency");
    runTest(2, {{1, 0}, {0, 1}}, false, "Test 2 - Simple cycle");
    runTest(3, {{1, 0}, {2, 1}}, true, "Test 3 - Chain of dependencies");
    runTest(3, {{1, 0}, {2, 1}, {0, 2}}, false, "Test 4 - Cycle in chain");
    runTest(4, {}, true, "Test 5 - No dependencies");
    runTest(5, {{0,1},{1,2},{2,3},{3,4}}, true, "Test 6 - Linear chain");

    return 0;
}