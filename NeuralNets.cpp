#include <cmath>
#include <numeric>
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
  n_y = 1;//(int)this->Y[0].size();

  initialize_parameters();
  set_threshold();
}

void NeuralNets::initialize_parameters(){
  this->parameters.W1 = random_uniform(this->n_h, this->n_x);
  this->parameters.W2 = random_uniform(this->n_y, this->n_h);
  this->parameters.b1 = zeros<double> (this->n_h, 1);
  this->parameters.b2 = zeros<double> (this->n_y, 1);
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
  vector<vector<double>> V;
  for (size_t i = 0; i < this->n_h; i++)
    V.push_back(vector<double>(X.size(), parameters.b1[i][0]));

  cache.Z1 = parameters.W1 * T(X) + V;

  cache.A1 = tanh_v(cache.Z1);
  V = vector<vector<double>>(1, vector<double>(X.size(), parameters.b2[0][0]));

  cache.Z2 = parameters.W2 * cache.A1 + V;
  cache.A2 = sigmoid(cache.Z2);
  return pair<vector<vector<double>>,Cache>(cache.A2, cache);
}

double NeuralNets::compute_cost(vector<vector<double>> A2){
  vector<vector<double>>
  logprobs = 1/((double)this->Y.size())*(
    matiply(  log_v(A2), T(  this->Y)) +
    matiply(1-log_v(A2), T(1-this->Y))
  );
  return -sum(logprobs);
}

Grads NeuralNets::backward_propagation(Cache  cache){
  double m = (double)this->X.size();
  Grads grads;
  vector<vector<double>> dZ1, dZ2;
  dZ2 = cache.A2 - T(this->Y);
  grads.dW2 = 1/m * dZ2 * T(cache.A1);
  grads.db2 = {{1/m * sum(dZ2)}};
  dZ1 = 1/m * matiply(T(parameters.W2)*dZ2, ones<double>(cache.A1.size(), cache.A1[0].size()) - power(cache.A1, 2));
  grads.dW1 = 1/m * dZ1 * this->X;
  grads.db1 = vector<vector<double>>(this->n_h, vector<double>(1, 0));
  for (size_t i = 0; i < this->n_h; i++)
    grads.db1[i][0] = sum(dZ1[i]);
  return grads;
}

void NeuralNets::fit(){
  pair<vector<vector<double>>,Cache> forward;
  double cost;
  Grads grads;

  for (size_t i = 0; i < this->num_iterations; i++) {
    forward = forward_propagation(this->X);
    cost    = compute_cost(forward.first);
    grads   = backward_propagation(forward.second);
    update_parameters(grads);
    if (this->print_cost and i%100 == 0)
      cout<<"Cost after iteration "<<i<<" :"<<cost<<endl;
  }
}


vector<vector<int>> NeuralNets::predict(vector<vector<double>> X){
  pair<vector<vector<double>>,Cache> forward = forward_propagation(X);
  vector<vector<double>> probabilities = sigmoid(forward.first);
  vector<vector<int   >> predictions (probabilities.size(), vector<int>(probabilities[0].size(), 0));
  for (size_t i = 0; i < probabilities.size(); i++)
    for (size_t j = 0; j < probabilities[0].size(); j++)
      if(probabilities[i][j] >= threshold){
        predictions[i][j] = 1;
      }
  return predictions;
}

vector<vector<double>> NeuralNets::tanh_v(vector<vector<double>> Z){
  vector<vector<double>> tanh_Z (Z.size(), vector<double>(Z[0].size(), 0));
  for (size_t i = 0; i < Z.size(); i++) {
    for (size_t j = 0; j < Z[0].size();  j++) {
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

vector<vector<double>> NeuralNets::random_uniform(int x, int y){
  vector<vector<double>> V(x, vector<double>(y, 0));
  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++){
      x0 = (65539*x0)%2147483648;
      V[i][j] = ((double)x0/2147483648) * 0.01;
    }
	return V;
}

void NeuralNets::set_threshold(){
  double count_label_1 = 0;
  for (size_t i = 0; i < this->Y.size(); i++)
    if(this->Y[i][0] == 1)
      count_label_1++;
  threshold = (double)count_label_1/this->Y.size();
}

// double NeuralNets::random_uniform(){
//   x0 = (65539*x0)%2147483648;
//   return (double)x0/2147483648;
// }
