#include <iostream>
#include <vector>
#include "NeuralNets.h"

using namespace std;
template <typename T> void print(vector<vector<T>> vect);

int main(int argc, char const *argv[]) {

  vector<vector<double>> X = {{1, 2},
                              {1, 2},
                              {1, 2},
                              {1, 2},
                              {1, 2},
                              {1, 2}};
  vector<vector<int>> Y(6, vector<int>(1,1));
  double learning_rate = 0.2;
  int    n_h = 4;
  int    num_iterations = 100;
  bool   print_cost = true;

  NeuralNets NN = NeuralNets(
                		X,
                		Y,
                		learning_rate,
                		n_h,
                		num_iterations,
                		print_cost
                	);
  NN.initialize_parameters();
  cout<<"\nW1 = "<<endl;
  print(NN.parameters.W1);
  cout<<"\nb1 = "<<endl;
  print(NN.parameters.b1);


  cout<<"\nW2 = "<<endl;
  print(NN.parameters.W2);
  cout<<"\nb2 = "<<endl;
  print(NN.parameters.b2);

  return 0;
}

template <typename T> void print(vector<vector<T>> vect){
  for (size_t i = 0; i < vect.size(); i++){
    for (size_t j = 0; j < vect[0].size(); j++)
      cout<<vect[i][j]<<"  \t";
    cout<<endl;
  }
}

// g++ -c main.cpp NeuralNets.cpp
// g++ main.o NeuralNets.o -o out
