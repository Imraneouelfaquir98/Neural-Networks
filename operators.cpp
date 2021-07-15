#include "operators.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace std;

long long int x0 = 765502822;

template <typename T, typename D>
double operator*(const vector<T>& U, const vector<D>& V){
    try{
        if(U.size() != V.size()){
            throw string("ERREUR : Dimension incompatible !");
        }
        else{
            double produit = 0;
            for(int i = 0 ; i < U.size() ; i++)
                produit += (double)U[i] * V[i];
            return produit;
        }
    }
    catch(string const& chaine){
       cerr << chaine << endl;
       return 0;
    }
}

template <typename T, typename D>
vector<double> operator*(const T &alpha, const vector<D>& U){
    vector<double> W(U.size() , 0);
    for(int i = 0 ; i < U.size() ; i++)
        W[i] = (double)alpha*U[i];
    return W;
}

template <typename T, typename D>
vector<double> operator*(const vector<T>& U, const D &alpha){
    vector<double> W(U.size() , 0);
    for(int i = 0 ; i < U.size() ; i++)
                W[i] = (double)alpha*U[i];
    return W;
}

template <typename T, typename D>
vector <vector<double>> operator*(const vector<vector<T>>& U, const vector<vector<D>>& V){
    vector <vector<double>> W(U.size() , vector<double>(V[0].size(),0));
    try{
        if(U[0].size() != V.size()){
            throw string("ERREUR : Dimension incompatible !");
        }
        else{
            for(int i = 0 ; i < U.size() ; i++){
                for(int j = 0 ; j < V[0].size() ; j++){
                    double pivot;
                    for(int k = 0 ; k < U[0].size() ; k++)
                        W[i][j] += (double)U[i][k] * V[k][j];
                }
            }
            return W;
        }
    }
    catch(string const& chaine){
       cerr << chaine << endl;
       return W;
    }
}

template <typename T, typename D>
vector <vector<double>> operator*(const T &alpha, const vector<vector<D>>& U){
    vector <vector<double>> W(U.size() , vector<double>(U[0].size(),0));
    for(int i = 0 ; i < U.size() ; i++)
        for(int j = 0 ; j < U[0].size() ; j++)
                W[i][j] = (double)alpha*U[i][j];
    return W;
}

template <typename T, typename D>
vector <vector<double>> operator*(const vector<vector<T>>& U, const D &alpha){
    return alpha*U;
}

template <typename T, typename D>
vector<double> operator/(const vector<T> & U, const D &m){
    try{
        if( m == 0){
            throw string("ERREUR : can not devise with zero !");
        }
        else{
            vector<double> W(U.size() , 0);
            for(int i = 0 ; i < U.size() ; i++)
                        W[i] = (double)U[i]/m;
            return W;
        }
    }
    catch(string const& chaine){
        cerr << chaine << endl;
        vector<double> W (U.size(), 0);
        return W;
    }
}

template <typename T, typename D>
vector <vector<double>> operator/(const vector<vector<T>>& U, const D &m){
    vector <vector<double>> W(U.size() , vector<double>(U[0].size(),0));
    try{
        if( m == 0){
            throw string("ERREUR : can not devise with zero !");
        }
        else{
            for(int i = 0 ; i < U.size() ; i++)
                for(int j = 0 ; j < U[0].size() ; j++)
                        W[i][j] = (double)U[i][j]/m;
            return W;
        }
    }
    catch(string const& chaine){
       cerr << chaine << endl;
       return W;
    }
}

template <typename T, typename D>
vector <vector<double>> operator/(const vector<vector<T>>& U, const vector<vector<D>>& m){
    vector <vector<double>> W(U.size() , vector<double>(U[0].size(),0));
    try{
        if(m[0].size() > 1 || m.size() > 1){
            throw string("ERREUR : can not devise with vector !");
        }
        else if( m[0][0] == 0){
            throw string("ERREUR : can not devise with zero !");
        }
        else{
            for(int i = 0 ; i < U.size() ; i++)
                for(int j = 0 ; j < U[0].size() ; j++)
                        W[i][j] = (double)U[i][j]/m[0][0];
            return W;
        }
    }
    catch(string const& chaine){
       cerr << chaine << endl;
       return W;
    }
}

template <typename T, typename D>
vector<double> operator-(const vector<T> & U, const vector<D> & V){
    try{
        if(U.size() != V.size()){
            throw string("ERREUR : Dimension incompatible !1");
        }
        else{
            vector<double> W(U.size() , 0);
            for(int i = 0 ; i < U.size() ; i++){
                    W[i] = (double)(U[i] - V[i]);
            }
            return W;
        }
    }
    catch(string const& chaine){
        cerr << chaine << endl;
        vector<double> W (U.size(), 0);
        return W;
    }
}

template <typename T, typename D>
vector <vector<double>> operator-(const vector<vector<T>>& U, const vector<vector<D>>& V){
    vector <vector<double>> W(U.size() , vector<double>(U[0].size(),0));
    try{
        if(U.size() != V.size() || U[0].size() != V[0].size() ){
            throw string("ERREUR : Dimension incompatible !");
        }
        else{
            for(int i = 0 ; i < U.size() ; i++){
                for(int j = 0 ; j < U[0].size() ; j++){
                    W[i][j] = (double)(U[i][j] - V[i][j]);
                }
            }
            return W;
        }
    }
    catch(string const& chaine){
       cerr << chaine << endl;
       return W;
    }
}

template <typename T, typename D>
vector<double> operator+(const vector<T> & U, const vector<D> & V){
    try{
        if(U.size() != V.size()){
            throw string("ERREUR : Dimension incompatible !2");
        }
        else{
            vector<double> W(U.size() , 0);
            for(int i = 0 ; i < U.size() ; i++){
                    W[i] = (double)(U[i] + V[i]);
            }
            return W;
        }
    }
    catch(string const& chaine){
        cerr << chaine << endl;
        vector<double> W (U.size(), 0);
        return W;
    }
}

template <typename T, typename D>
vector <vector<double>> operator+(const vector<vector<T>>& U, const vector<vector<D>>& V){
    vector <vector<double>> W(U.size() , vector<double>(U[0].size(),0));
    try{
        if(U.size() != V.size() || U[0].size() != V[0].size() ){
            throw string("ERREUR : Dimension incompatible !");
        }
        else{
            for(int i = 0 ; i < U.size() ; i++){
                for(int j = 0 ; j < U[0].size() ; j++){
                    W[i][j] = (double)(U[i][j] + V[i][j]);
                }
            }
            return W;
        }
    }
    catch(string const& chaine){
       cerr << chaine << endl;
       return W;
    }
}

// Transposé
template<typename T>
vector <vector<T>> T(const vector<vector<T>>& U){
    vector <vector<T>> W(U[0].size() , vector<T>(U.size(),0));
    for(int i = 0 ; i < U.size() ; i++){
        for(int j = 0 ; j < U[0].size() ; j++){
            W[j][i] = U[i][j];
        }
    }
    return W;
}

template<typename T>
vector<vector<T>> zeros(int x, int y){
  return vector<vector<T>>(x, vector<T>(y, 0));
}

template<typename T>
vector<vector<T>> ones(int x, int y){
  return vector<vector<T>>(x, vector<T>(y, 1));
}

vector<vector<double>> random_uniform(int x, int y){
  vector<vector<double>> V(x, vector<double>(y, 0));
  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++){
      x0 = (65539*x0)%2147483648;
      V[i][j] = ((double)x0/2147483648) * 0.01;
    }
	return V;
}
