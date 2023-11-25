#include "main.h"

std::vector<std::vector<int>> selection_proportional(std::vector<std::vector<int>> reproduction_set, const std::vector<std::vector<float>>& distance, int output_size)
{
    std::vector<std::vector<int>> output;
    float sum = 0;
    for (int i = 0; i < reproduction_set.size(); i++)
    {
        sum += 1.0f / get_distance_unified(reproduction_set[i], distance);
    }
    while (output.size() != output_size)
    {
        float random_result = random_float(0, sum);
        for (int i = 0; i < reproduction_set.size(); i++)
        {
            random_result -= 1.0f / get_distance_unified(reproduction_set[i], distance);
            if (random_result <= 0)
            {
                //sum -= 1.0f / get_distance_unified(reproduction_set[i], distance);
                output.push_back(reproduction_set[i]);
                //reproduction_set.erase(reproduction_set.begin() + i);
                break;
            }
        }
    }
    return output;
}

std::vector<std::vector<int>> selection_rank(std::vector<std::vector<int>> reproduction_set, const std::vector<std::vector<float>>& distance, int output_size)
{
    std::vector<float> possibilities;
    sort_by_distance_descending(reproduction_set, distance);
    float nplus = 3.0f;
    float nminus = 1.0f;
    int size = reproduction_set.size();
    int sum = 0;
    for (int rank = 0; rank < size; rank++)
    {
        possibilities.push_back(nminus - (nplus - nminus) * rank / (size - 1)); 
        sum += nminus - (nplus - nminus) * rank / (size - 1);
    }
    std::vector<std::vector<int>> output;
    while (output.size() != output_size)
    {
        float random_result = random_float(0, sum);
        for (int i = 0; i < reproduction_set.size(); i++)
        {
            random_result -= possibilities[i];
            if (random_result <= 0)
            {
                output.push_back(reproduction_set[i]);
                break;
            }
        }
    }
    return output;
}

std::vector<std::vector<int>> selection_beta_tourney(std::vector<std::vector<int>> reproduction_set, const std::vector<std::vector<float>>& distance, int output_size)
{
    std::vector<std::vector<int>> output;
    int beta = 3;
    for (int i = 0; i < output_size; i++)
    {
        random_shuffle(reproduction_set);
        float min = get_distance_unified(reproduction_set[0], distance);
        int mini = 0;
        for (int j = 1; j < beta; j++)
        {
            float current = get_distance_unified(reproduction_set[j], distance);
            if (current < min)
            {
                mini = j;
                min = current;
            }
        }
        output.push_back(reproduction_set[mini]);
    }
    return output;
}