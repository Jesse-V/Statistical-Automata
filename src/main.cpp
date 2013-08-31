
#include <array>
#include <iostream>


const int N = 3;
typedef std::array<std::array<int, N>, N> Array2D;


Array2D getLiveNeighborCounts(const Array2D& adjacencyMatrix)
{
    Array2D liveNeighborCount;
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



void print(const std::string& title, const Array2D& array)
{
    std::cout << title << std::endl;
    for (std::size_t i = 0; i < N; i++)
    {
        for (std::size_t j = 0; j < N; j++)
            std::cout << array[i][j] << " ";

        std::cout << std::endl;
    }
}



int main(int argc, char **argv)
{
    Array2D adjacencyMatrix{{
        {{ 0, 1, 1 }},
        {{ 1, 0, 1 }},
        {{ 1, 1, 0 }}
    }};

    print("Current Adjacency Matrix:", adjacencyMatrix);
    
    auto counts = getLiveNeighborCounts(adjacencyMatrix);

    print("Live Neighbor Counts:", counts);
}
