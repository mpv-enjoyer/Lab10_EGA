#include "main.h"

int main()
{
    std::vector<std::vector<float>> distances = read_matrix("matrix_input.txt");
    int city_count = distances.size();
    /* Чтобы избежать повторяющихся кодировок, введем правила:
    - Начинаем с 0 города
    - Первый город в перестановках по номеру меньше последнего
    Таким образом, длина кодировки это (city_count - 1) */
    int population_size; 
    std::cout << "Input initial population size: ";
    std::cin >> population_size;
    int code_size = city_count - 1;
    std::vector<std::vector<int>> current_population;
    std::cout << "\n1) Uncontrolled random\n"
    "2) Controlled random (default)\n"
    "3) Nearest city algorithm\n"
    "4) Nearest neighbour algorithm\n"
    "Select initial population generation method: ";
    int start_method;
    std::cin >> start_method;
    switch (start_method)
    {
    case 1:
        current_population = begin_uncontrolled(code_size, population_size);
        fix_uncontrolled(current_population);
        break;
    case 2:
        current_population = begin_controlled(code_size, population_size);
        break;
    case 3:
        current_population = begin_method_city(distances, population_size);
        break;
    case 4:
        current_population = begin_method_neighbour(distances, population_size);
        break;
    default:
        current_population = begin_controlled(code_size, population_size);
        break;
    }
    for (int i = 0; i < population_size; i++)
    {
        unify_code(current_population[i]);
    }
    std::cout << to_string(current_population);
    std::cout << "\n1) Random\n"
    "2) Inbreeding\n"
    "3) Outbreeding\n"
    "4) Positive associative mating\n"
    "5) Negative associative mating\n"
    "Select parents generation method: ";
    int parents_method;
    std::cin >> parents_method;
}