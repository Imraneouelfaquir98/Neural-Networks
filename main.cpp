#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include "NeuralNets.h"
#include "operators.h"

using namespace std;

typedef struct Dataset{
  vector<vector<double>> X_train, X_test;
  vector<vector<int   >> Y_train, Y_test;
}Dataset;

Dataset load_dataset(string filename, Dataset dataset);
vector<vector<double>> read_csv(string filename);

int main(int argc, char const *argv[]) {

  Dataset dataset;
  for (int i = 1; i <= 50; i++)
    dataset = load_dataset("./SolutionDatasetRC101/solution_data_"+to_string(i)+".txt", dataset);

  double learning_rate = 0.001;
  int    n_h = 10;
  int    num_iterations = 5000;
  bool   print_cost = true;

  NeuralNets NN = NeuralNets(
    dataset.X_train,
    dataset.Y_train,
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

  vector<vector<int>> preds = T(NN.predict(dataset.X_test));
  double accuracy = 0;
  for (size_t i = 0; i < dataset.Y_test.size(); i++) {
    accuracy += (dataset.Y_test[i][0] == preds[i][0])? 1 : 0;
  }

  cout<<"\nAccuracy = "<<(double)accuracy/dataset.Y_test.size()<<endl;

  return 0;
}
// g++ -c main.cpp NeuralNets.cpp && g++ main.o NeuralNets.o -o out && ./out



Dataset load_dataset(string filename, Dataset dataset){
  ifstream myFile(filename);

  string line;
  double val;
  stringstream ss;
  int counter = 0;


  if(!myFile.is_open()) throw runtime_error("Could not open \""+filename+"\" file");
  for (size_t i = 0; i < 4; i++) getline(myFile, line);

  if(myFile.good()){
      vector<double> X_line;
      while (getline(myFile, line)) {
        ss = stringstream(line);
        for (size_t i = 0; i < 3; i++) {
          ss>>val;
          X_line.push_back(val);
        }
        ss>>val;
        if(counter%5 != 0){
          ss>>val;
          dataset.X_train.push_back(X_line);
          dataset.Y_train.push_back({(int)val});
        }
        else{
          ss>>val;
          dataset.X_test.push_back(X_line);
          dataset.Y_test.push_back({(int)val});
        }
        X_line.clear();
        counter++;
      }
      myFile.close();
  }
  return dataset;
}

// vector<vector<double>> load_dataset(string filename){
//   vector<vector<double>> X;
//   ifstream myFile(filename);
//
//   if(!myFile.is_open()) throw runtime_error("Could not open \""+filename+"\" file");
//   string line;
//   double val;
//   stringstream ss;
//
//   for (size_t i = 0; i < 4; i++) getline(myFile, line);
//
//   if(myFile.good()){
//       vector<double> X_line;
//       while (getline(myFile, line)) {
//         ss = stringstream(line);
//         for (size_t i = 0; i < 4; i++) {
//           ss>>val;
//           X_line.push_back(val);
//         }
//         X.push_back(X_line);
//         X_line.clear();
//       }
//       myFile.close();
//   }
//   return X;
// }


vector<vector<double>> read_csv(string filename){
    vector<vector<double>> result;
    ifstream myFile(filename);
    if(!myFile.is_open()) throw runtime_error("Could not open \""+filename+"\" file");
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
