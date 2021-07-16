#ifndef NEURALNETS_H
#define NEURALNETS_H

#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef struct Parameters {
	vector<vector<double>> W1, W2, b1, b2;
} Parameters;

typedef struct Cache {
	vector<vector<double>> A1, Z1, A2, Z2;
} Cache;

typedef struct Grads {
	vector<vector<double>> dW1, dW2, db1, db2;
} Grads;

class NeuralNets
{
public:

	vector<vector<double>> X;
	vector<vector<int   >> Y;
	int 		               n_h, n_x, n_y;
	int 		               num_iterations;
	double 	               learning_rate;
	bool 		               print_cost;

	Parameters parameters;

	NeuralNets(
		vector<vector<double>> X,
		vector<vector<int   >> Y,
		double learning_rate,
		int    n_h,
		int    num_iterations,
		bool   print_cost
	);

	void     initialize_parameters();
	double   compute_cost        (vector<vector<double>> A2);
	double   predict             (vector<double> X );
	Grads    backward_propagation(Cache  cache);
	void     update_parameters   (Grads  grads);
	void     fit                 ();

	pair<vector<vector<double>>,Cache> forward_propagation (vector<vector<double>> X);

	vector<vector<double>> sigmoid (vector<vector<double>> Z);
	vector<vector<double>> tanh_v  (vector<vector<double>> Z);
	vector<vector<double>> log_v   (vector<vector<double>> Z);

	long long int x0 = 765502822;
	vector<vector<double>> random_uniform(int x, int y);
};



#endif // NEURALNETS_H
