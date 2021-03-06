
#include "main.hpp"
#include <thread>
#include <iostream>

int main(int argc, char **argv)
{
    Matrix2D adjacencyMatrix{{
        {{ 0, 1, 1 }},
        {{ 1, 0, 1 }},
        {{ 1, 1, 0 }}
    }};

    int iterationCount = 0;

    while (true)
    {
        std::cout << "Iteration: " << iterationCount << std::endl;
        print("Current Adjacency Matrix:", adjacencyMatrix);

        auto counts = getLiveNeighborCounts(adjacencyMatrix);

        print("Live Neighbor Counts:", counts);

        auto ruleMatrix = getRuleMatrix(counts, adjacencyMatrix);

        print("Rule Matrix:", ruleMatrix);

        adjacencyMatrix = applyRuleMatrix(adjacencyMatrix, ruleMatrix);
        iterationCount++;

        std::cout << "---------------------------------" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}



Matrix2D getRuleMatrix(const Matrix2D& neighborCounts, const Matrix2D& adjMatrix)
{
    static std::unordered_map<int, int> rules({ //maps neighbor count to rule
        { 0, -1 },
        { 1, -1 },
        { 2,  0 },
        { 3,  1 },
        { 4, -1 },
        { 5, -1 },
        { 6, -1 },
        { 7, -1 },
        { 8, -1 },
    });

    Matrix2D ruleMatrix;
    for (std::size_t i = 0; i < N; i++)
    {
        for (std::size_t j = 0; j < N; j++)
        {
            if (adjMatrix[i][j] == 0)
                ruleMatrix[i][j] = rules[neighborCounts[i][j]];
            else
                ruleMatrix[i][j] = 0;
        }
    }

    return ruleMatrix;
}



Matrix2D getLiveNeighborCounts(const Matrix2D& adjacencyMatrix)
{
    Matrix2D liveNeighborCount;
    for (std::size_t i = 0; i < N; i++)
    {
        for (std::size_t j = 0; j < N; j++)
        {
            int count = 0;

            if (i != 0 && j != 0)
                count += adjacencyMatrix[i - 1][j - 1];

            if (j != 0)
                count += adjacencyMatrix[i    ][j - 1];

            if (i != N - 1 && j != 0)
                count += adjacencyMatrix[i + 1][j - 1];

            if (i != 0)
                count += adjacencyMatrix[i - 1][j    ];

            if (i != N - 1)
                count += adjacencyMatrix[i + 1][j    ];

            if (i != 0 && j != N - 1)
                count += adjacencyMatrix[i - 1][j + 1];

            if (j != N - 1)
                count += adjacencyMatrix[i    ][j + 1];

            if (i != N - 1 && j != N - 1)
                count += adjacencyMatrix[i + 1][j + 1];

            liveNeighborCount[i][j] = count;
        }
    }

    return liveNeighborCount;
}



Matrix2D applyRuleMatrix(const Matrix2D& adjacencyMatrix, const Matrix2D& ruleMatrix)
{
    Matrix2D result;
    for (std::size_t i = 0; i < N; i++)
    {
        for (std::size_t j = 0; j < N; j++)
        {
            result[i][j] = adjacencyMatrix[i][j];

            if (adjacencyMatrix[i][j] == 1 && ruleMatrix[i][j] == -1)
                result[i][j] -= 1;
            
            if (adjacencyMatrix[i][j] == 0 && ruleMatrix[i][j] == 1)
                result[i][j] += 1;
        }
    }

    return result;
}



void print(const std::string& title, const Matrix2D& array)
{
    std::cout << title << std::endl;
    for (std::size_t i = 0; i < N; i++)
    {
        for (std::size_t j = 0; j < N; j++)
            std::cout << array[i][j] << "   ";

        std::cout << std::endl;
    }
}
