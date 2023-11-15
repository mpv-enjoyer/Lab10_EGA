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

Parents parents_inbreeding(std::vector<std::vector<int>> current_population)
{
    int population_size = current_population.size();
    int code_size = current_population[0].size();
    Parents output;
    output.first = random_int(0, population_size - 1);
}