#include "main.h"

void begin_all_tests()
{
    std::vector<int> expected;
    std::vector<int> actual;
    std::vector<std::vector<float>> distances = 
    {
        {0, 1, 4, 5, 6},
        {1, 0, 7, 8, 2},
        {4, 7, 0, 9, 1},
        {5, 8, 9, 0, 3},
        {6, 2, 1, 3, 0}
    };

    std::vector<std::vector<int>> reproduction_set =
    {
        { 1, 4, 2, 3 },
        { 2, 3, 4, 1 },
        { 1, 2, 3, 4 },
        { 4, 3, 2, 1 }
    };

    std::cout << "TESTS: \n";

    expected = { 2, 7, 3, 4, 1, 5, 6 };
    actual = crossover_consecutive({ 5, 7, 3, 4, 1, 2, 6 }, { 4, 6, 2, 1, 7, 3, 5 }, 2, 4);
    std::cout << "1) [consecutive crossover] Expected: " << to_string(expected) << " Actual: " << to_string(actual) << "\n";

    expected = { 7, 6, 3, 4, 1, 2, 5 };
    actual = crossover_partial({ 5, 7, 3, 4, 1, 2, 6 }, { 4, 6, 2, 1, 7, 3, 5 }, 2, 4);
    std::cout << "2) [partial crossover] Expected: " << to_string(expected) << " Actual: " << to_string(actual) << "\n";

    expected = { 5, 7, 3, 4, 1, 2, 8, 9, 6 };
    actual = crossover_cyclic({ 5, 7, 3, 4, 1, 2, 9, 8, 6 }, { 4, 7, 2, 1, 6, 3, 8, 9, 5 }, true);
    std::cout << "3) [cyclic crossover] Expected: " << to_string(expected) << " Actual: " << to_string(actual) << "\n";

    std::cout << "4) [point mutation] Actual: " << to_string(mutation_point({ 1, 2, 3, 4, 5, 6, 7, 8 })) << "\n";

    std::cout << "5) [saltation mutation] Actual: " << to_string(mutation_saltation({ 1, 2, 3, 4, 5, 6, 7, 8 })) << "\n";

    std::cout << "6) [inversion mutation] Actual: " << to_string(mutation_inversion({ 1, 2, 3, 4, 5, 6, 7, 8 })) << "\n";

    std::cout << "7) [proportional selection] Actual: \n" << to_string(selection_proportional(reproduction_set, distances, 2));

    std::cout << "8) [beta selection] Actual: \n" << to_string(selection_beta_tourney(reproduction_set, distances, 2));

    std::cout << "9) [rank selection] Actual: \n" << to_string(selection_rank(reproduction_set, distances, 2));

    expected = { 4, 1, 14, 9, 2, 10, 7, 12, 8, 3, 6, 13, 11, 5 };
    actual = crossover_partial({ 4, 1, 14, 9, 2, 10, 7, 12, 8, 3, 6, 13, 11, 5 }, { 6, 5, 10, 2, 4, 1, 3, 9, 13, 11, 12, 14, 7, 8 }, 1, 12);
    std::cout << "10) [partial crossover] Expected: " << to_string(expected) << " Actual: " << to_string(actual) << "\n";

    std::cout << "TESTS END.\n";
}