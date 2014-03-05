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
		int updatePeriod; //number of cycles after which to update pheromone
		double threshold; //sets how well connected a cluster is
		int max_decrease; // maximum number of times the modularity drops

		Parameters(Graph& g)
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
			if (p < 0.100)
			{
				threshold = 0.80;
			}
			else if(p >= 1)
			{
				threshold = 0.25;
			}
			else if(p >= 0.100 && p < 1)
			{
				threshold = 0.35;
			}

			// if graph is really small
			if(g.num_vertices <= 128)
			{
				threshold = 0.5;
			}
			max_decrease = 5;
		}
};

#endif /* PARAMETERS_H_ */
