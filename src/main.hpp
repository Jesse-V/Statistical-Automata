
#ifndef MAIN
#define MAIN

#include <array>
#include <unordered_map>

const int N = 3;
typedef std::array<std::array<int, N>, N> Matrix2D;

Matrix2D getLiveNeighborCounts(const Matrix2D& adjacencyMatrix);
void print(const std::string& title, const Matrix2D& array);
Matrix2D getRuleMatrix(const Matrix2D& neighborCounts, const Matrix2D& adjMatrix);
Matrix2D applyRuleMatrix(const Matrix2D& adjacencyMatrix, const Matrix2D& ruleMatrix);

#endif
