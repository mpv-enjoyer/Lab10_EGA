#include "main.h"

int main()
{
    begin_all_tests();
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
    "4) Positive associative mating (default)\n"
    "5) Negative associative mating\n"
    "Select parents generation method: ";
    int parents_method;
    std::cin >> parents_method;

    std::cout << "\n1) Consecutive\n"
    "2) Partial\n"
    "3) Cyclic\n"
    "Select crossover method: ";
    int crossover_method;
    std::cin >> crossover_method;

    std::vector<std::vector<int>> current_population_children;
    for (int i = 0; i < population_size; i++)
    {
        Parents current_parents;
        switch (parents_method)
        {
        case 1:
            current_parents = parents_random(population_size);
            break;
        case 2:
            current_parents = parents_inbreeding(current_population);
            break;
        case 3:
            current_parents = parents_outbreeding(current_population);
            break;
        case 4:
            current_parents = parents_positive_mating(current_population, distances);
            break;
        case 5:
            current_parents = parents_negative_mating(current_population, distances);
            break;
        default:
            current_parents = parents_positive_mating(current_population, distances);
            break;
        }
        std::vector<int> parent_left = current_population[current_parents.first];
        std::vector<int> parent_right = current_population[current_parents.second];
        std::cout << to_string(parent_left) + " + " + to_string(parent_right) << " = ";
        switch (crossover_method)
        {
        case 1:
            current_population_children.push_back(crossover_consecutive(parent_left, parent_right));
            break;
        case 2:
            current_population_children.push_back(crossover_partial(parent_left, parent_right));
            break;
        case 3:
            current_population_children.push_back(crossover_cyclic(parent_left, parent_right));
            break;
        default:
            current_population_children.push_back(crossover_consecutive(parent_left, parent_right));
            break;
        }
        std::cout << to_string(current_population_children[current_population_children.size() - 1]) << "\n";
    }
    
}