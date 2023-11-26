#include "main.h"

int main()
{
    //begin_all_tests();
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

    std::cout << "\n1) Random\n"
    "2) Inbreeding\n"
    "3) Outbreeding\n"
    "4) Positive associative mating (default)\n"
    "5) Negative associative mating\n"
    "Select parents generation method: ";
    int parents_method;
    std::cin >> parents_method;

    std::cout << "\n1) Consecutive (default)\n"
    "2) Partial\n"
    "3) Cyclic\n"
    "Select crossover method: ";
    int crossover_method;
    std::cin >> crossover_method;

    std::cout << "\n1) Point\n"
    "2) Saltation (default)\n"
    "3) Inversion\n"
    "Select mutation method: ";
    int mutation_method;
    std::cin >> mutation_method;

    bool enable_elite_strategy;
    std::cout << "Enable elite strategy (Y/N): ";
    char elite_input;
    std::cin >> elite_input;
    enable_elite_strategy = elite_input == 'Y' || elite_input == 'y';

    float overlap_coefficient;
    std::cout << "Input overlap coefficient = (0, 1]: ";
    std::cin >> overlap_coefficient;
    
    int selection_method;
    std::cout << "\n1) Proportional (default)\n"
    "2) Rank\n"
    "3) Beta-tourney\n"
    "Select selection method: ";
    std::cin >> selection_method;

    int max_population_count;
    std::cout << "Input max population count: ";
    std::cin >> max_population_count;

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

    std::vector<int> best_code = current_population[0];
    int best_distance = get_distance_unified(best_code, distances);

    for (int population_id = 0; population_id < max_population_count; population_id++)
    {
        std::cout << "Population #" << population_id << " start\n" << to_string(current_population, &distances);
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

        std::cout << "Population #" << population_id << " children\n" << to_string(current_population_children, &distances);

        int mutation_size = random_int(1, population_size);
        std::vector<std::vector<int>> current_population_mutation(mutation_size);

        for (int i = 0; i < mutation_size; i++)
        {
            int current_child = random_int(0, population_size - 1);
            switch (mutation_method)
            {
            case 1:
                current_population_mutation[i] = mutation_point(current_population_children[current_child]);
                break;
            case 2:
                current_population_mutation[i] = mutation_saltation(current_population_children[current_child]);
                break;
            case 3:
                current_population_mutation[i] = mutation_inversion(current_population_children[current_child]);
                break;
            default:
                current_population_mutation[i] = mutation_saltation(current_population_children[current_child]);
                break;
            }
        }

        std::cout << "Population #" << population_id << " mutations\n" << to_string(current_population_mutation, &distances);

        auto current_reproduction_set = current_population_children;
        current_reproduction_set.insert(current_reproduction_set.end(), current_population_mutation.begin(), current_population_mutation.end());
        std::vector<std::vector<int>> next_population = std::vector<std::vector<int>>();

        if (enable_elite_strategy)
        {
            next_population.push_back(exclude_best_unified_code(current_population, current_reproduction_set, distances));
        }

        int original_left = (1 - overlap_coefficient) * population_size - enable_elite_strategy;
        if (original_left < 0)
        {
            original_left = 0;
        }
        int reproduction_left = population_size - original_left - enable_elite_strategy;

        random_shuffle(current_population);
        for (int i = 0; i < original_left; i++)
        {
            next_population.push_back(current_population[i]);
        }

        std::vector<std::vector<int>> from_reproduction;
        switch (selection_method)
        {
        case 1:
            from_reproduction = selection_proportional(current_reproduction_set, distances, reproduction_left);
            break;
        case 2:
            from_reproduction = selection_rank(current_reproduction_set, distances, reproduction_left);
            break;
        case 3:
            from_reproduction = selection_beta_tourney(current_reproduction_set, distances, reproduction_left);
            break;
        default:
            from_reproduction = selection_proportional(current_reproduction_set, distances, reproduction_left);
            break;
        }
        next_population.insert(next_population.end(), from_reproduction.begin(), from_reproduction.end());
        for (int i = 0; i < next_population.size(); i++)
        {
            unify_code(next_population[i]);
            if (best_distance > get_distance_unified(next_population[i], distances))
            {
                best_distance = get_distance_unified(next_population[i], distances);
                best_code = next_population[i];
            }
        }
        std::cout << "Current best: " << to_string(best_code, &distances) << "\n";
        current_population = next_population;
    }
}

//Current best: [ 2 1 6 11 3 12 10 9 13 8 7 4 14 5 ] Distance: 67.790001
//Current best: [ 2 1 6 11 3 10 12 8 13 7 4 14 9 5 ] Distance: 55.810001