#ifndef HELPER_H_
#define HELPER_H_

#include <random>
#include <cmath>
//#include <chrono>

class Helper
{
	public:
		std::random_device rd;
		std::mt19937 gen;
		int num_vertices;
		unsigned long seed;

		Helper(Graph& graph)
		{
			seed = rd();
			//seed = 1486048213;//2365693151;
			gen.seed(seed);
			num_vertices = graph.num_vertices;
		}

		inline double randomNumber()
		{
			std::uniform_real_distribution<> random(0, 1);
			double decision = random(gen);
			return decision;
		}

		inline double probability()
		{
			std::uniform_real_distribution<> reset(0,1);
			double val = reset(gen);
			return val;
		}

		inline int newVertex()
		{
			std::uniform_int_distribution<> vertex(0, num_vertices - 1);
			int vert = vertex(gen);
			return vert;
		}
};

#endif /* HELPER_H_ */
