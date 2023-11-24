#include "main.h"

void begin_all_tests()
{
    std::vector<int> expected;
    std::vector<int> actual;
    
    std::cout << "TESTS: \n";

    expected = { 2, 7, 3, 4, 1, 5, 6 };
    actual = crossover_consecutive({ 5, 7, 3, 4, 1, 2, 6 }, { 4, 6, 2, 1, 7, 3, 5 }, 2, 4);
    std::cout << "1) [consecutive] Expected: " << to_string(expected) << " Actual: " << to_string(actual) << "\n";

    expected = { 7, 6, 3, 4, 1, 2, 5 };
    actual = crossover_partial({ 5, 7, 3, 4, 1, 2, 6 }, { 4, 6, 2, 1, 7, 3, 5 }, 2, 4);
    std::cout << "2) [partial] Expected: " << to_string(expected) << " Actual: " << to_string(actual) << "\n";

    expected = { 5, 7, 3, 4, 1, 2, 8, 9, 6 };
    actual = crossover_cyclic({ 5, 7, 3, 4, 1, 2, 9, 8, 6 }, { 4, 7, 2, 1, 6, 3, 8, 9, 5 }, true);
    std::cout << "3) [cyclic] Expected: " << to_string(expected) << " Actual: " << to_string(actual) << "\n";

    std::cout << "4) [point mutation] Actual: " << to_string(mutation_point({ 1, 2, 3, 4, 5, 6, 7, 8 })) << "\n";

    std::cout << "5) [saltation mutation] Actual: " << to_string(mutation_saltation({ 1, 2, 3, 4, 5, 6, 7, 8 })) << "\n";

    std::cout << "6) [inversion mutation] Actual: " << to_string(mutation_inversion({ 1, 2, 3, 4, 5, 6, 7, 8 })) << "\n";

    std::cout << "TESTS END.\n";
}