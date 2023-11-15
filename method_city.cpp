#include "main.h"

std::vector<int> method_city(int N, const std::vector<std::vector<float>>& distance, int start_from)
{
    if (distance.size() == 0) return {};
    std::vector<bool> X = std::vector<bool>(N, false); // Если мы уже входили в город, пишем 1
    std::vector<int> trace;
    float overall_distance = 0;
    int x = start_from;
    X[x] = true;
    trace.push_back(x);
	//std::cout << "1) Trace " << to_string(trace) << " Select " << x << "\n";

    for (int i = 1; i < N; i++) //общий шаг
    {
        int current_town = x;
        std::vector<int> current_min_pairs;
        for (int j = 0; j < i; j++) //Вычисление минимумов для каждого внутреннего элемента
        {
            float sum = 0;
            for (int k = 0; k < N; k++)
            {
                if (X[k]) continue;
                sum += 1/distance[trace[j]][k];
            }
            
            float rnd = random_float(0, sum);

            int randomresult = 0;
            for (int k = 0; k < N; k++)
            {
                if (X[k]) continue;
                rnd -= 1/distance[trace[j]][k];
                if (rnd <= 0) 
                {
                    randomresult = k;
                    break;
                }
            }
			std::vector<int> output_neighbors_distance;
            for (int k = 0; k < N; k++)
            {
				if (!X[k]) output_neighbors_distance.push_back(distance[trace[j]][k]);
				else output_neighbors_distance.push_back(-1);
            }
			//std::cout << trace[j] << " neighbors distance: " << to_string(output_neighbors_distance) << "\n";
            //std::cout << "Chose " << randomresult << " with chance " << 100 / sum / distance[trace[j]][randomresult] << "%\n";
            current_min_pairs.push_back(randomresult);
        }
        //std::cout << "neighbors winners (from | to == distance):\n";
        float sum = 0;
        for (int j = 0; j < i; j++)
        {
            //std::cout << trace[j] << " | " << current_min_pairs[j] << " == " << distance[trace[j]][current_min_pairs[j]] <<"\n";
            sum += 1/distance[trace[j]][current_min_pairs[j]];
        }
        for (int j = 0; j < i; j++)
        {
            //std::cout << " [" << trace[j] << " - " <<  100 / sum / distance[trace[j]][current_min_pairs[j]]<< "%]";
        }
        //std::cout << "\n";
        float rnd = random_float(0, sum);
        int current_min_to = -1;
        int current_min_from = -1;
        for (int j = 0; j < i; j++)
            {
                rnd -= 1/distance[trace[j]][current_min_pairs[j]];
                if (rnd <= 0) 
                {
                    current_min_from = j;
                    current_min_to = current_min_pairs[j];
                    break;
                }
            }
        int current_min_distance_in_pairs = distance[trace[current_min_from]][current_min_to];
        //std::cout << "Chose " << current_min_from << " with chance " << 100 / sum / current_min_distance_in_pairs << "%\n";
		int show_current_min_from = trace[current_min_from];
        trace.insert(trace.begin() + current_min_from + 1, current_min_to);
        X[current_min_to] = true;
		overall_distance = 0;
		for (int j = 0; j < trace.size()-1; j++)
		{
			overall_distance += distance[trace[j]][trace[j+1]];
		}
		//print_step(i + 1, trace, show_current_min_from, current_min_to, overall_distance, current_min_distance_in_pairs);
    }
    overall_distance += distance[trace[0]][trace[N-1]];

    std::cout << "Final: Trace " << to_string(trace) << " Distance " << overall_distance << "\n";
    return trace;
}