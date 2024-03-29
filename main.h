#pragma once
#define _GLIBCXX_DEBUG
#include <random>
#include <vector>
#include <iostream>
#include <ctime>
#include <fstream>
#include <algorithm>

struct Parents
{
    int first;
    int second;
};

//misc.cpp
std::string to_string(const std::vector<int>& input, const std::vector<std::vector<float>>* distance = nullptr);
std::string to_string(const std::vector<std::vector<int>>& input, const std::vector<std::vector<float>>* distance = nullptr);
int random_int(int included_min, int included_max);
float random_float(float included_min, float included_max);
void random_shuffle(std::vector<int>& input);
void random_shuffle(std::vector<std::vector<int>>& input);
std::vector<std::vector<float>> read_matrix(std::string file_name);
bool equal(const std::vector<int>& lbeing, const std::vector<int>& rbeing);
void fix_code_offset(std::vector<int>& being);
void fix_uncontrolled(std::vector<std::vector<int>>& population);
void unify_code(std::vector<int>& being);
int hamming_distance(const std::vector<int>& unified_left, const std::vector<int>& unified_right);
float get_distance_unified(const std::vector<int>& trace, const std::vector<std::vector<float>>& distance);
float get_distance_unified(const std::vector<int>& trace, const std::vector<std::vector<float>>* distance);
std::vector<int> exclude_best_unified_code(std::vector<std::vector<int>>& codes_left, std::vector<std::vector<int>>& codes_right, std::vector<std::vector<float>> distance);
void sort_by_distance_descending(std::vector<std::vector<int>>& code, const std::vector<std::vector<float>>& distance);

//begin.cpp
std::vector<std::vector<int>> begin_uncontrolled(int code_size, int population_size);
std::vector<std::vector<int>> begin_controlled(int code_size, int population_size);
std::vector<std::vector<int>> begin_method_city(const std::vector<std::vector<float>>& distances, int population_size);
std::vector<std::vector<int>> begin_method_neighbour(const std::vector<std::vector<float>>& distances, int population_size);

//method_*.cpp
std::vector<int> method_city(int N, const std::vector<std::vector<float>>& distance, int start_from);
std::vector<int> method_neighbour(int N, const std::vector<std::vector<float>>& distance, int start_from);

//parents.cpp
Parents parents_random(int population_size);
Parents parents_inbreeding(const std::vector<std::vector<int>>& population);
Parents parents_outbreeding(const std::vector<std::vector<int>>& population);
Parents parents_positive_mating(const std::vector<std::vector<int>>& population, const std::vector<std::vector<float>>& distance);
Parents parents_negative_mating(const std::vector<std::vector<int>>& population, const std::vector<std::vector<float>>& distance);

//crossover.cpp
std::vector<int> crossover_consecutive(std::vector<int> parent_left, std::vector<int> parent_right, int left_cut_included = -1, int right_cut_included = -1);
std::vector<int> crossover_partial(std::vector<int> parent_left, std::vector<int> parent_right, int left_cut_included = -1, int right_cut_included = -1);
std::vector<int> crossover_cyclic(std::vector<int> parent_left, std::vector<int> parent_right, bool testing = false);

//mutation.cpp
std::vector<int> mutation_inversion(std::vector<int> code);
std::vector<int> mutation_saltation(std::vector<int> code);
std::vector<int> mutation_point(std::vector<int> code);

//selection.cpp
std::vector<std::vector<int>> selection_proportional(std::vector<std::vector<int>> reproduction_set, const std::vector<std::vector<float>>& distance, int output_size);
std::vector<std::vector<int>> selection_rank(std::vector<std::vector<int>> reproduction_set, const std::vector<std::vector<float>>& distance, int output_size);
std::vector<std::vector<int>> selection_beta_tourney(std::vector<std::vector<int>> reproduction_set, const std::vector<std::vector<float>>& distance, int output_size);

//tests.cpp
void begin_all_tests();