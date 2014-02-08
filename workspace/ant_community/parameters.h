#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include "graph.h"

class Parameters
{
	public:
		double decay; //pheromone decay factor
		int maxIterations;
		int maxSteps;
		int maxTries; //max number of times ant tries to move
		int updatePeriod; //number of cycle after which to update pheromone
		double threshold; //sets how well connected a cluster is

		Parameters(Graph &g)
		{
			if(g.num_vertices > 113)
			{
				maxSteps = 75;
				updatePeriod = maxSteps / 3;
			}
			else
			{
				maxSteps = (int) ((2.0/3.0) * g.num_vertices);
				updatePeriod = maxSteps / 3;
			}

			decay = 0.95;
			maxIterations = 25;
			maxTries = 2;

			long int max_edges = ((g.num_vertices)*(g.num_vertices - 1))/2;
			double p =  ((double) g.num_edges / max_edges) * 100;
			cout << "Percentage of links = " << p << "\n\n";
			if (p <= 0.100)
			{
				threshold = 0.80;
			}
			else
			{
				threshold = 0.35;
			}
		}
};

#endif /* PARAMETERS_H_ */
