#include "main.h"

int main()
{
    std::vector<std::vector<float>> distances = read_matrix("matrix_input.txt");
    int city_count = distances.size();
    /* Чтобы избежать повторяющихся кодировок, введем правила:
    - Начинаем с 0 города
    Таким образом, длина кодировки это (city_count - 1) */
    int population_size; 
    std::cout << "Введите величину популяции: ";
    std::cin >> population_size;
    int code_size = city_count - 1;
    std::vector<std::vector<int>> current_population;
    std::cout << "\n1) Случайный без контроля\n"
    "2) Случайный контролируемый (по умолчанию)\n"
    "3) Жадный алгоритм ближайшего города\n"
    "4) Жадный алгоритм ближайшего соседа\n"
    "Введите способ задания начальной популяции: ";
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
    std::cout << to_string(current_population);
    std::cout << "\n1) Случайный\n";
    int parents_method;
    std::cin >> parents_method;
}