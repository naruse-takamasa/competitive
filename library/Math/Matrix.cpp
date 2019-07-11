#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

typedef vector<vector<ll>> Matrix;

void init(int n, Matrix &matrix)
{
    matrix = vector<vector<ll>>(static_cast<unsigned long>(n), vector<ll>(static_cast<unsigned long>(n)));
    /*for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> matrix[i][j];
        }
    }*/
}

Matrix &operator*(Matrix &matrix, Matrix &matrix1)
{
    int height = static_cast<int>(matrix.size());
    int width = static_cast<int>(matrix[0].size());
    int height2 = static_cast<int>(matrix1.size());
    int width2 = static_cast<int>(matrix1[0].size());
    assert(width == height2);
    Matrix res;
    res = vector<vector<ll>>(static_cast<unsigned long>(height), vector<ll>(width2, 0));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width2; j++)
        {
            for (int k = 0; k < width; k++)
            {
                res[i][j] = add(res[i][j], mul(matrix[i][k], matrix1[k][j]));
                // res[i][j] += matrix[i][k] * matrix1[k][j];
            }
        }
    }
    matrix.swap(res);
    return matrix;
}

Matrix pow(Matrix matrix, ll x)
{
    Matrix res = vector<vector<ll>>(matrix.size(), vector<ll>(matrix.size(), 0));
    for (int i = 0; i < (int)matrix.size(); i++)
    {
        res[i][i] = 1;
    }
    while (x)
    {
        show(x);
        if (x & 1)
        {
            res = res * matrix;
        }
        matrix = matrix * matrix;
        x >>= 1;
    }
    return res;
}
