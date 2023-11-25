#include "main.h"

std::string to_string(const std::vector<int>& input)
{
    std::string output = "[ ";
    for (int i = 0; i < input.size(); i++)
    {
        output.append(std::to_string(input[i]) + " ");    
    }
    output.append("]");
    return output;
}
std::string to_string(const std::vector<std::vector<int>>& input)
{
    std::string output;
    for (int i = 0; i < input.size(); i++)
    {
        output.append(to_string(input[i]) + '\n');
    }
    return output;
}
int random_int(int included_min, int included_max)
{
    static std::default_random_engine rng(time(NULL));
    std::uniform_int_distribution<int> dist(included_min, included_max); 
    dist(rng);
    return dist(rng); 
}
float random_float(float included_min, float included_max)
{
    static std::default_random_engine rng(time(NULL));
    std::uniform_real_distribution<float> dist(included_min, included_max); 
    dist(rng);
    return dist(rng); 
}
void random_shuffle(std::vector<int>& input)
{
    static unsigned seed = time(NULL);
    static std::default_random_engine random = std::default_random_engine(seed);
    std::shuffle(input.begin(), input.end(), random);
}
void random_shuffle(std::vector<std::vector<int>>& input)
{
    static unsigned seed = time(NULL);
    static std::default_random_engine random = std::default_random_engine(seed);
    std::shuffle(input.begin(), input.end(), random);
}
std::vector<std::vector<float>> read_matrix(std::string file_name)
{
    std::ifstream matrix_input(file_name);
    int size = 0;
    matrix_input >> size; //first we want a size of the matrix in our file
    std::cout << size << "\n";
    std::vector<std::vector<float>> matrix = std::vector<std::vector<float>>(size, std::vector<float>(size, 0));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix_input >> matrix[i][j];
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    return matrix;
}
bool equal(const std::vector<int>& lbeing, const std::vector<int>& rbeing)
{
    if (lbeing.size() != rbeing.size())
    {
        return false;
    }
    if (lbeing[0] == rbeing[rbeing.size() - 1]) // Предполагаем, что кодировка развернута
    {
        for (int i = 1; i < lbeing.size(); i++)
        {
            if (lbeing[i] != rbeing[rbeing.size() - 1 - i])
            {
                return false;
            }
        }
    }
    else // Предполагаем, что кодировка не развернута и тогда должна полностью совпадать
    {
        for (int i = 0; i < lbeing.size(); i++)
        {
            if (lbeing[i] != rbeing[i])
            {
                return false;
            }
        }
    }
    return true;
}
void fix_code_offset(std::vector<int>& being)
{
    bool met_zero = false;
    int offset;
    for (int i = 0; i < being.size(); i++)
    {
        if (being[i] == 0)
        {
            being.erase(being.begin() + i);
            met_zero = true;
            offset = i;
            i--;
            continue;
        }
        if (met_zero)
        {
            being.insert(being.begin() + i - offset, being[i]);
            being.erase(being.begin() + i + 1);
        }
    }
}
std::vector<bool> find_unfixed(std::vector<std::vector<int>>& population)
{
    std::vector<bool> regenerate = std::vector<bool>(population.size(), false);
    for (int i = 0; i < population.size(); i++)
    {
        std::vector<bool> was_in = std::vector<bool>(population[i].size(), false);
        for (int j = 0; j < population[i].size(); j++) // Проверка на повторяющиеся города
        {
            int current = population[i][j];
            if (was_in[current])
            {
                regenerate[i] = true;
                break;
            }
            was_in[current] = true;
        }
        if (!regenerate[i])
        {
            for (int j = 0; j < i; j++) // Проверка на совпадающие кодировки
            {
                if (equal(population[j], population[i]) && !regenerate[j])
                {
                    regenerate[i] = true;
                    break;
                }
            }
        }
    }
    return regenerate;
}
void fix_uncontrolled(std::vector<std::vector<int>>& population)
{
    std::vector<bool> regenerate = find_unfixed(population);
    bool regenerated;
    do
    {
        regenerated = false;
        for (int i = 0; i < population.size(); i++)
        {
            if (regenerate[i])
            {
                for (int j = 0; j < population[i].size(); j++)
                {
                    population[i][j] = random_int(1, population[i].size());
                }
                regenerated = true;
            }
        }
        regenerate = find_unfixed(population);
    } while (regenerated);
}
void unify_code(std::vector<int>& being)
{
    if (being[0] < being[being.size() - 1])
    {
        return;
    }
    for (int i = 0; i < being.size() / 2; i++)
    {
        std::iter_swap(being.begin() + i, being.end() - i - 1);
    }
}
int hamming_distance(const std::vector<int>& unified_left, const std::vector<int>& unified_right)
{
    int output = 0;
    for (int i = 0; i < unified_left.size(); i++)
    {
        output += unified_left[i] == unified_right[i] ? 0 : 1;
    }
    return output;
}
float get_distance_unified(const std::vector<int>& trace, const std::vector<std::vector<float>>& distance)
{
    float output = distance[0][trace[0]] + distance[trace[trace.size() - 1]][0];
    for (int i = 0; i < trace.size() - 1; i++)
    {
        output += distance[trace[i]][trace[i+1]];
    }
    return output;
}
std::vector<int> exclude_best_unified_code(std::vector<std::vector<std::vector<int>>>& codes, std::vector<std::vector<float>> distance)
{
    std::vector<int> output;
    float min = __FLT_MAX__;
    int mini = 0;
    int minj = 0;
    for (int i = 0; i < codes.size(); i++)
    {
        for (int j = 0; j < codes[i].size(); j++)
        {
            float current = get_distance_unified(codes[i][j], distance);
            if (current < min)
            {
                output = codes[i][j];
                min = current;
                mini = i;
                minj = j;
            }
        }
    }
    codes[mini].erase(codes[mini].begin() + minj);
    return output;
}
void sort_by_distance_descending(std::vector<std::vector<int>>& code, const std::vector<std::vector<float>>& distance)
{
    for (int i = 0; i < code.size() - 1; i++)
    {
        float current_max = get_distance_unified(code[i], distance);
        int current_max_index = i;
        for (int j = i + 1; j < code.size(); j++)
        {
            float current_distance = get_distance_unified(code[j], distance);
            if (current_distance > current_max)
            {
                current_max_index = j;
                current_max = current_distance;
            }
        }
        std::swap(code[i], code[current_max_index]);
    }
}