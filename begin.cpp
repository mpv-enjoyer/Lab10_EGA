#include "main.h"

std::vector<std::vector<int>> begin_uncontrolled(int code_size, int population_size)
{
    std::vector<std::vector<int>> output = std::vector<std::vector<int>>(population_size, std::vector<int>(code_size));
    for (int i = 0; i < population_size; i++)
    {
        for (int j = 0; j < code_size; j++)
        {
            output[i][j] = random_int(1, code_size);
        }
    }
    return output;
}

std::vector<std::vector<int>> begin_controlled(int code_size, int population_size)
{
    static unsigned seed = time(NULL);
    static std::default_random_engine random = std::default_random_engine(seed);
    std::vector<std::vector<int>> output = std::vector<std::vector<int>>(population_size, std::vector<int>(code_size));
    bool repeat;
    for (int i = 0; i < population_size; i++)
    {
        repeat = false;
        for (int j = 0; j < code_size; j++)
        {
            output[i][j] = j + 1;
        }
        do
        {
            std::shuffle(output[i].begin(), output[i].end(), random);
            for (int j = 0; j < i; j++)
            {
                repeat = repeat || equal(output[i], output[j]);
                if (repeat)
                {
                    break;
                }
            }
        } while (repeat);
    }
    return output;
}

std::vector<std::vector<int>> begin_method_city(const std::vector<std::vector<float>>& distances, int population_size)
{
    static unsigned seed = time(NULL);
    static std::default_random_engine random = std::default_random_engine(seed);
    int code_size = distances.size() - 1;
    std::vector<std::vector<int>> output = std::vector<std::vector<int>>(population_size, std::vector<int>(code_size));
    bool repeat;
    for (int i = 0; i < population_size; i++)
    {
        std::vector<int> trace = method_city(distances.size(), distances, random_int(0, code_size));
        fix_code_offset(trace);   
        do
        {
            repeat = false;
            for (int j = 0; j < i; j++)
            {
                if (equal(trace, output[j]))
                {
                    repeat = true;
                    break;
                }
            }
            if (repeat)
            {
                std::shuffle(trace.begin(), trace.end(), random);
            }
        } while (repeat);
        for (int j = 0; j < code_size; j++)
        {
            output[i][j] = trace[j];
        }
    }
    return output;
}

std::vector<std::vector<int>> begin_method_neighbour(const std::vector<std::vector<float>>& distances, int population_size)
{
    static unsigned seed = time(NULL);
    static std::default_random_engine random = std::default_random_engine(seed);
    int code_size = distances.size() - 1;
    std::vector<std::vector<int>> output = std::vector<std::vector<int>>(population_size, std::vector<int>(code_size));
    bool repeat;
    for (int i = 0; i < population_size; i++)
    {
        std::vector<int> trace = method_neighbour(distances.size(), distances, random_int(0, code_size));
        fix_code_offset(trace);
        do
        {
            repeat = false;
            for (int j = 0; j < i; j++)
            {
                if (equal(trace, output[j]))
                {
                    repeat = true;
                    break;
                }
            }
            if (repeat)
            {
                std::shuffle(trace.begin(), trace.end(), random);
            }
        } while (repeat);
        for (int j = 0; j < code_size; j++)
        {
            output[i][j] = trace[j];
        }
    }
    return output;
}