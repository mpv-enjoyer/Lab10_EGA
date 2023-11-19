#include "main.h"

std::vector<int> crossover_consecutive(std::vector<int> parent_left, std::vector<int> parent_right)
{
    int parent_size = parent_left.size();
    std::vector<int> output = std::vector<int>(parent_size);
    std::vector<int> numbers = std::vector<int>(parent_size - 2);
    //По бокам оставляем хотя бы 1 изначальный элемент
    for (int i = 1; i < parent_size - 1; i++)
    {
        numbers[i - 1] = i;
    }
    random_shuffle(numbers);
    if (numbers[0] > numbers[1])
    {
        std::iter_swap(numbers.begin(), numbers.begin() + 1);
    }
    int left_cut_included = numbers[0];
    int right_cut_included = numbers[1];
    int start_from = -1;
    for (int i = left_cut_included; i <= right_cut_included; i++)
    {
        output[i] = parent_left[i];
        auto found = std::find(parent_right.begin(), parent_right.end(), parent_left[i]);
        int index = std::distance(parent_right.begin(), found);
        if (index > start_from)
        {
            start_from = index;
        }
        parent_right[index] = -1;
    }
    int current_index = right_cut_included + 1;
    for (int i = start_from + 1; i != start_from; i = (i + 1) % parent_size)
    {
        if (parent_right[i] != -1)
        {
            output[current_index] = parent_right[i];
            current_index = (current_index + 1) % parent_size;
        }
    }
    return output;
}

