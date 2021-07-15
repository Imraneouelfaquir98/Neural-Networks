#include <cmath>
#include "NeuralNets.h"
#include "operators.h"


NeuralNets::NeuralNets(
  vector<vector<double>> X,
  vector<vector<int   >> Y,
  double learning_rate,
  int    n_h,
  int    num_iterations,
  bool   print_cost
){
  this->X              = X;
  this->Y              = Y;
  this->learning_rate  = learning_rate;
  this->n_h            = n_h;
  this->num_iterations = num_iterations;
  this->print_cost     = print_cost;

  n_x = (int)this->X[0].size();
  n_y = 1;//(int)this->Y   .size();
}

void NeuralNets::initialize_parameters(){
  this->parameters.W1 = random_uniform(this->n_h, this->n_x);
  this->parameters.W2 = random_uniform(this->n_y, this->n_h);
  this->parameters.b1 = zeros(this->n_h, 1);
  this->parameters.b2 = zeros(this->n_y, 1);
};

void NeuralNets::update_parameters(Grads  grads){
  parameters.W1 = parameters.W1 - learning_rate*grads.dW1;
  parameters.b1 = parameters.b1 - learning_rate*grads.db1;
  parameters.W2 = parameters.W2 - learning_rate*grads.dW2;
  parameters.b2 = parameters.b2 - learning_rate*grads.db2;
}

pair<vector<vector<double>>,Cache>
NeuralNets::forward_propagation (vector<vector<double>>  X){
  Cache cache;
  cache.Z1 = parameters.W1 * T(X) + parameters.b1;
  cache.A1 = tanh_v(cache.Z1);
  cache.Z2 = parameters.W2 * cache.A1 + parameters.b2;
  cache.A2 = sigmoid(cache.Z2);
  return pair<vector<vector<double>>,Cache>(cache.A2, cache);
}



double NeuralNets::compute_cost(vector<vector<double>> A2){
  double m = (double)this->Y.size();
  double logprobs = 1/m*(
    log_v(A2) * (double)this->Y +
    (ones(A2.size(), A2[0].size()) - log_v(A2)) * (ones(A2.size(), A2[0].size()) - (double)this->Y)
  )
}


vector<vector<double>> NeuralNets::tanh_v(vector<vector<double>> Z){
  vector<vector<double>> tanh_Z (Z.size(), vector<double>(Z[0].size(), 0));
  for (size_t i = 0; i < Z.size(); i++) {
    for (size_t j = 0; j < Z[0].size(); j++) {
      tanh_Z[i][j] = tanh(Z[i][j]);
    }
  }
  return tanh_Z;
}

vector<vector<double>> NeuralNets::log_v(vector<vector<double>> Z){
  vector<vector<double>> log_Z (Z.size(), vector<double>(Z[0].size(), 0));
  for (size_t i = 0; i < Z.size(); i++) {
    for (size_t j = 0; j < Z[0].size(); j++) {
      log_Z[i][j] = log(Z[i][j]);
    }
  }
  return log_Z;
}

vector<vector<double>> NeuralNets::sigmoid(vector<vector<double>> Z){
  vector<vector<double>> sigmoid_Z (Z.size(), vector<double>(Z[0].size(), 0));
  for (size_t i = 0; i < Z.size(); i++) {
    for (size_t j = 0; j < Z[0].size(); j++) {
      sigmoid_Z[i][j] = 1/(1 + exp(-Z[i][j]));
    }
  }
  return sigmoid_Z;
}

// double NeuralNets::random_uniform(){
//   x0 = (65539*x0)%2147483648;
//   return (double)x0/2147483648;
// }
