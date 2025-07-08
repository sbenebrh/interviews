//
// Created by samuel benibgui on 26/06/2025.
//
/* Description:
You are given a 2D grid map of '1's (land) and '0's (water). An island is formed by connecting adjacent lands horizontally or vertically (not diagonally).

Return the number of distinct islands in the grid.

Each cell in the grid is either '1' (land) or '0' (water). All four edges of the grid are surrounded by water.
*/


#include <vector>

int numIslands(std::vector<std::vector<char>>& grid);


#include <iostream>
#include <vector>
using namespace std;

auto DFS(std::vector<std::vector<char> > &grid, int rowIndex, int colIndex) -> void {
    if (rowIndex>= grid.size() || rowIndex < 0 || colIndex >= grid[0].size() || colIndex < 0 || grid[rowIndex][colIndex] == '0') {
        return; // out of bounds or water
    }

    grid[rowIndex][colIndex] = '0';


    DFS(grid, rowIndex + 1, colIndex); // down
    DFS(grid, rowIndex - 1, colIndex);
    DFS(grid, rowIndex, colIndex + 1); // right
    DFS(grid, rowIndex, colIndex - 1); // left
}

int numIslands(vector<vector<char>>& grid) {
    int islandCount = 0;
    for (int rowIndex = 0; rowIndex < grid.size(); rowIndex++) {
        for (int colIndex = 0 ; colIndex < grid[rowIndex].size(); colIndex++) {
            if (grid[rowIndex][colIndex] == '1') {
                islandCount++;
                DFS(grid, rowIndex, colIndex);
            }
        }
    }
    return islandCount;
}



void runTest(vector<vector<char>> grid, int expected, const string& testName) {
    int result = numIslands(grid);
    cout << testName << " => ";
    if (result == expected) {
        cout << "PASSED ✅ (Output: " << result << ")" << endl;
    } else {
        cout << "FAILED ❌ (Expected: " << expected << ", Got: " << result << ")" << endl;
    }
}

int main() {
    // Test 1: Classic multiple islands
    vector<vector<char>> grid1 = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    runTest(grid1, 3, "Test 1 - Multiple Islands");

    // Test 2: All land
    vector<vector<char>> grid2 = {
        {'1','1','1'},
        {'1','1','1'},
        {'1','1','1'}
    };
    runTest(grid2, 1, "Test 2 - One Big Island");

    // Test 3: Empty grid
    vector<vector<char>> grid3 = {};
    runTest(grid3, 0, "Test 3 - Empty Grid");

    // Test 4: All water
    vector<vector<char>> grid4 = {
        {'0','0','0'},
        {'0','0','0'},
        {'0','0','0'}
    };
    runTest(grid4, 0, "Test 4 - All Water");

    // Test 5: Alternating isolated land
    vector<vector<char>> grid5 = {
        {'1','0','1','0'},
        {'0','1','0','1'},
        {'1','0','1','0'},
        {'0','1','0','1'}
    };
    runTest(grid5, 8, "Test 5 - Disconnected Land");

    return 0;
}