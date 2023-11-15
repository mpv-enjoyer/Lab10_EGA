#include "main.h"

std::vector<int> method_neighbour(int N, const std::vector<std::vector<float>>& distance, int start_from)
{
    std::vector<bool> X = std::vector<bool>(N, false); // Если мы уже входили в город, пишем 1
    std::vector<int> trace;
    float overall_distance = 0;
    int x = start_from;
    X[x] = true;
    trace.push_back(x);
    //std::cout << 1 << ") Trace " << to_string(trace) << " Select " << x << "\n";
    for (int i = 1; i < N; i++)
    {
        int current_town = x;
        float sum = 0;
        for (int j = 0; j < N; j++)
        {
            if (X[j]) continue;
            sum += 1/distance[current_town][j];
        }
        for (int j = 0; j < N; j++)
        {
            if (X[j]) continue;
            //std::cout << " [" << j << " - " <<  100 / sum / distance[current_town][j]<< "%]";
        }
        //std::cout << "\n";
        float rnd = random_float(0, sum);
        int randomresult = 0;
        for (int j = 0; j < N; j++)
        {
            if (X[j]) continue;
            rnd -= 1/distance[current_town][j];
            if (rnd <= 0) 
            {
                randomresult = j;
                break;
            }
        }
        x = randomresult;
        X[x] = true;
        overall_distance += distance[current_town][randomresult];
        trace.push_back(x);
        //std::cout << "Chose " << randomresult << " with chance " << 100 / distance[current_town][randomresult] / sum << "%\n";
        //print_step(i + 1, trace, x, distance[current_town][randomresult], overall_distance);
    }
    overall_distance += distance[trace[0]][trace[N-1]];
    std::cout << "Final: Trace " << to_string(trace) << " Distance " << overall_distance << "\n";
    return trace;
}