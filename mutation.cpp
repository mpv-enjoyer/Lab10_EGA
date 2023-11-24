#include "main.h"

std::vector<int> mutation_point(std::vector<int> code)
{
    int left_point = random_int(0, code.size() - 1);
    std::swap(code[left_point], code[left_point + 1]);
    return code;
}

std::vector<int> mutation_saltation(std::vector<int> code)
{
    std::vector<int> numbers = std::vector<int>(code.size());
    for (int i = 0; i < code.size(); i++)
    {
        numbers[i] = i;
    }
    random_shuffle(numbers);
    int left_point = numbers[0];
    int right_point = numbers[1];
    std::swap(code[left_point], code[right_point]);
    return code;
}

std::vector<int> mutation_inversion(std::vector<int> code)
{
    int parent_size = code.size();
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
    int left_included = numbers[0];
    int right_included = numbers[1];
    int halfsize = (right_included - left_included + 1) / 2;
    for (int i = 0; i < halfsize; i++)
    {
        std::swap(code[left_included + i], code[right_included - i]);
    }
    return code;
}