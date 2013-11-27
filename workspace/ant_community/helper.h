#include <random>

#ifndef HELPER_H_
#define HELPER_H_

class Helper
{
	public:
		std::random_device rd;
		std::mt19937 gen;
		int num_vertices;

		Helper(Graph &graph)
		{
			gen.seed(rd());
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
