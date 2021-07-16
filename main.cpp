#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include "NeuralNets.h"
#include "operators.h"

using namespace std;

vector<vector<double>> read_csv(string filename);

int main(int argc, char const *argv[]) {
  vector<vector<double>> X;
  vector<vector<int>> Y;

  vector<vector<double>> result = read_csv("dataset.csv");
  for (size_t i = 0; i < result.size(); i++) {
    X.push_back({result[i][0], result[i][1]});
    Y.push_back({(int)result[i][2]});
  }

  double learning_rate = 1.2;
  int    n_h = 4;
  int    num_iterations = 100000;
  bool   print_cost = true;

  NeuralNets NN = NeuralNets(
                		X,
                		Y,
                		learning_rate,
                		n_h,
                		num_iterations,
                		print_cost
                	);
  NN.fit();
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
// g++ -c main.cpp NeuralNets.cpp && g++ main.o NeuralNets.o -o out && ./out

vector<vector<double>> read_csv(string filename){
    vector<vector<double>> result;
    ifstream myFile(filename);
    if(!myFile.is_open()) throw runtime_error("Could not open file");
    string line, colname;
    double val;

    if(myFile.good()){
        getline(myFile, line);
        vector<double> X_line;
        while(getline(myFile, line)){
            stringstream ss(line);
            int colIdx = 0;
            while(ss >> val){
                X_line.push_back(val);
                if(ss.peek() == ',') ss.ignore();
            }
            result.push_back(X_line);
            X_line.clear();
        }
        myFile.close();
    }
    return result;
}
