#ifndef NEURALNETS_H
#define NEURALNETS_H

#include <iostream>
#include <vector>
#include <map>


class NeuralNets
{
public:

	vector<vector<double>> 	X;
	vector<double>			Y;
	int 		n_h, n_x, n_y;
	int 		num_iterations 	= 10000;
	double 	learning_rate 	= 0.2;
	bool 		print_cost;

	NeuralNets();
	Parameters  initialize_parameters();
	Cache       forward_propagation (vector<vector<double>>  X, Parameters parameters);
	double      compute_cost        (vector       <double>  A2, Parameters parameters);
	double      sigmoid             (vector       <double>   X);
	double      sigmoid             (double	 X);
	double      predict             (Parameters parameters, vector<double> X);
	Grads       backward_propagation(Parameters parameters, Cache  cache);
	Parameters  update_parameters   (Parameters parameters, Grads  grads);
	void        fit                 ();

};

typedef struct Parameters {
	vector<vector<double>> W1, W2;
	vector<double> b1, b2;
} Parameters;

typedef struct Cache {
	vector<double> A1, Z1, A2, Z2;
} Cache;

typedef struct Grads {
	vector<vector<double>> dW1, dW2;
	vector<double> db1, db2;
}

#endif // NERALNETS_H
