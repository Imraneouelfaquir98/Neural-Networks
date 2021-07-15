#ifndef OPERATORS_H
#define OPERATORS_H

#include <vector>

using namespace std;

template <typename T, typename D> double                 operator*(const vector<T>        & U, const vector<D>        & V    );
template <typename T, typename D> vector<double>         operator*(const vector<T>        & U, const D                & alpha);
template <typename T, typename D> vector<double>         operator*(const T           & alpha , const vector<D>        & U    );
template <typename T, typename D> vector<vector<double>> operator*(const T           & alpha , const vector<vector<D>>& U    );
template <typename T, typename D> vector<vector<double>> operator*(const vector<vector<T>>& U, const vector<vector<D>>& V    );
template <typename T, typename D> vector<vector<double>> operator*(const vector<vector<T>>& U, const D                & alpha);
template <typename T, typename D> vector<double>         operator/(const vector<T>        & U, const D                & m    );
template <typename T, typename D> vector<vector<double>> operator/(const vector<vector<T>>& U, const D                & m    );
template <typename T, typename D> vector<vector<double>> operator/(const vector<vector<T>>& U, const vector<vector<D>>& m    );
template <typename T, typename D> vector<double>         operator-(const vector<T>        & U, const vector<D>        & V    );
template <typename T, typename D> vector<vector<double>> operator-(const vector<vector<T>>& U, const vector<vector<D>>& V    );
template <typename T, typename D> vector<double>         operator+(const vector<T>        & U, const vector<D>        & V    );
template <typename T, typename D> vector<vector<double>> operator+(const vector<vector<T>>& U, const vector<vector<D>>& V    );
template <typename T> vector<vector<T>> T     (const vector<vector<T>>& U);
template <typename T> vector<vector<T>> zeros (int x, int y);
template <typename T> vector<vector<T>> ones  (int x, int y);
vector<vector<double>> random_uniform(int x, int y);

#endif // OPERATORS_H
