#include "main.h"

std::vector<int> crossover_consecutive(std::vector<int> parent_left, std::vector<int> parent_right, int left_cut_included, int right_cut_included)
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
    left_cut_included = left_cut_included == -1 ? numbers[0] : left_cut_included;
    right_cut_included = right_cut_included == -1 ? numbers[1] : right_cut_included;
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
    for (int i = (start_from + 1) % parent_size; i != start_from; i = (i + 1) % parent_size)
    {
        if (parent_right[i] != -1)
        {
            output[current_index] = parent_right[i];
            current_index = (current_index + 1) % parent_size;
        }
    }
    return output;
}

std::vector<int> crossover_partial(std::vector<int> parent_left, std::vector<int> parent_right, int left_cut_included, int right_cut_included)
{
    int parent_size = parent_left.size();
    std::vector<int> transposition = std::vector<int>(parent_size, -1);
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
    left_cut_included = left_cut_included == -1 ? numbers[0] : left_cut_included;
    right_cut_included = right_cut_included == -1 ? numbers[1] : right_cut_included;
    //Элементы вектора transposition имеют значение:
    //i: i + 1 переходит в transposition[i]
    //Делаем так потому что в самой кодировке всегда отсутствует 0.
    for (int i = left_cut_included; i <= right_cut_included; i++)
    {
        output[i] = parent_left[i];
        transposition[parent_left[i] - 1] = parent_right[i];
    }
    for (int i = 0; i < left_cut_included; i++)
    {
        int value = parent_right[i];
        for (;;)
        {
            if (transposition[value - 1] == -1)
            {
                break;
            }
            value = transposition[value - 1];
        }
        output[i] = value;
    }
    for (int i = right_cut_included + 1; i < parent_size; i++)
    {
        int value = parent_right[i];
        for (;;)
        {
            if (transposition[value - 1] == -1)
            {
                break;
            }
            value = transposition[value - 1];
        }
        output[i] = value;
    }
    return output;
}

std::vector<int> crossover_cyclic(std::vector<int> parent_left, std::vector<int> parent_right, bool testing)
{
    int parent_size = parent_left.size();
    std::vector<std::vector<int>> cycles = std::vector<std::vector<int>>();
    std::vector<bool> inserted = std::vector<bool>(parent_size, false);
    for (int i = 0; i < parent_size; i++)
    {
        if (inserted[i])
        {
            continue;
        }
        int cycle_begin = parent_left[i];
        std::vector<int> current_cycle = { parent_left[i] };
        std::vector<int> current_cycle_ids = { i };
        if (parent_left[i] != parent_right[i])
        {
            current_cycle.push_back(parent_right[i]);
        }
        else
        {
            cycles.push_back({ i });
            continue;
        }
        inserted[i] = true;
        int current_index = i + 1;
        for (;; current_index = (current_index + 1) % parent_size)
        {
            if (current_cycle[current_cycle.size() - 1] == parent_left[current_index])
            {
                inserted[current_index] = true;
                current_cycle_ids.push_back(current_index);
                if (parent_right[current_index] == cycle_begin)
                {
                    break;
                }
                current_cycle.push_back(parent_right[current_index]);
            }
        }
        cycles.push_back(current_cycle_ids);
    }
    std::vector<int> output = std::vector<int>(parent_size);
    for (int i = 0; i < cycles.size(); i++)
    {
        bool pick_from_left = testing ? (i + 1) % 2 : random_int(0, 1);
        for (int j = 0; j < cycles[i].size(); j++)
        {
            int index = cycles[i][j];
            output[index] = pick_from_left ? parent_left[index] : parent_right[index];
        }
    }
    return output;
}