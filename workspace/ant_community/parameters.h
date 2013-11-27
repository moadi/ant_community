#ifndef PARAMETERS_H_
#define PARAMETERS_H_

class Parameters
{
	public:
		double decay;
		int maxIterations;
		int maxSteps;

		Parameters(Graph &g)
		{
			maxSteps = (int) ((2.0/3.0) * g.num_vertices);
			decay = 0.5;
		}
};

#endif /* PARAMETERS_H_ */
