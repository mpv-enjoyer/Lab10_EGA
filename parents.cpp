#include "main.h"

Parents parents_random(int population_size)
{
    std::vector<int> numbers = std::vector<int>(population_size);
    for (int i = 0; i < population_size; i++)
    {
        numbers[i] = i;
    }
    random_shuffle(numbers);
    return {numbers[0], numbers[1]};
}

Parents parents_inbreeding(std::vector<std::vector<int>> population)
{
    int population_size = population.size();
    int code_size = population[0].size();
    Parents output;
    output.first = random_int(0, population_size - 1);
    float sum = 0;
    for (int i = 0; i < population_size; i++)
    {
        if (i == output.first)
        {
            continue;
        }
        sum += 1 / hamming_distance(population[output.first], population[i]);
    }
    float random_result = random_float(0, sum);
    for (int i = 0; i < population_size; i++)
    {
        if (i == output.first)
        {
            continue;
        }
        random_result -= 1 / hamming_distance(population[output.first], population[i]);
        if (random_result <= 0)
        {
            output.second = i;
            return output;
        }
    }
    return { -1, -1 };
}

Parents parents_outbreeding(std::vector<std::vector<int>> population)
{
    int population_size = population.size();
    int code_size = population[0].size();
    Parents output;
    output.first = random_int(0, population_size - 1);
    int sum = 0;
    for (int i = 0; i < population_size; i++)
    {
        if (i == output.first)
        {
            continue;
        }
        sum += hamming_distance(population[output.first], population[i]);
    }
    int random_result = random_float(0, sum);
    for (int i = 0; i < population_size; i++)
    {
        if (i == output.first)
        {
            continue;
        }
        random_result -= hamming_distance(population[output.first], population[i]);
        if (random_result <= 0)
        {
            output.second = i;
            return output;
        }
    }
    return { -1, -1 };
}

Parents parents_positive_mating