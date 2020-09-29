//
// Created by Gav on 28/09/2020.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <math.h>

#define EPS 1e-6
#define DIMENSION 3

using namespace std;

bool is_complanar(vector<vector<double>> m) {
    if (m.size() != DIMENSION || m[0].size() != DIMENSION) {
        cout << "invalid size! Should be 3x3" << endl;
        exit(-1);
    }
    // [строка][столбец]
    double det = (m[0][0] * m[1][1] * m[2][2]) + (m[2][0] * m[0][1] * m[1][2]) + (m[0][2] * m[1][0] * m[2][1])
              - ((m[0][2] * m[1][1] * m[2][0]) + (m[0][1] * m[1][0] * m[2][2]) + (m[0][0] * m[2][1] * m[1][2]));
    return det == 0;
}

double scalar(vector<double> a, vector<double> b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

vector<double> vec_mult(vector<double> a, vector<double> b){
    vector<double> c(DIMENSION,-1);
    c[0] = a[1]*b[2] - a[2]*b[1];
    c[1] = - (a[0]*b[2] - a[2]*b[0]);
    c[2] = a[0]*b[1] - a[1]*b[0];
    return c;
}

bool is_null(vector<double> a){
    return abs(a[0])<EPS&&abs(a[1])<EPS&&abs(a[2])<EPS;
}

double mod(vector<double> a){
    return sqrt(a[0]*a[0] + a[1]*a[1] + a[2]*a[2]);
}


string print_vec(vector<double> &a){
    stringstream ss;
    ss << "{";
    for (double i : a) {
        ss << i << ",";
    }
    ss << "}";
    return ss.str();
}

int main() {
    vector<vector<double>> a = {{2, 2, 2},
                             {1, 1,  1},
                             {-1, -1,  -1}};

    cout << "Please, enter vectors: " << endl;
    for (int l = 0; l < DIMENSION; ++l) {
        cin >> a[l][0] >> a[l][1] >> a[l][2];
    }

    cout << (is_complanar(a)?"Vectors are complanar":"Vectors are not complanar") << endl;
    for (vector<double> v1 : a) {
        for (vector<double> v2 : a) {
            vector<double> res = vec_mult(v1,v2);
//            cout << "Collinear: " << print_vec(v1) << " and " << print_vec(v2) << " v1 x v2 = " << print_vec(res) << endl;
            if (v1 != v2 && is_null(vec_mult(v1, v2)))
                cout << "Collinear: " << print_vec(v1) << " and " << print_vec(v2) << endl;
        }
    }

    sort(a.begin(), a.end());

//    for(vector<double> v : a){
//        cout << "Vec: " << print_vec(v) << endl;
//    }

    for (int i = 0; i < DIMENSION; ++i) {
        for (int j = i+1; j < DIMENSION; ++j) {
//            cout << "Vectors: " << endl;
//            for(vector<double> v : a){
//                cout << "Vec: " << print_vec(v) << endl;
//            }
            if (a[i][i] == 0) break;
            double coef = a[j][i]/a[i][i];
//            cout << "Coef: " << coef << "; j: " << j << endl;
            for (int k = i; k < DIMENSION; ++k) {
                a[j][k] -= coef*a[i][k];
            }
        }
//        sort(a.begin(), a.end());
    }
//    cout << "Vectors: " << endl;
    int rank = 0;
    for(vector<double> v : a){
        rank += !is_null(v);
    }
    cout << "Rank: " << rank << endl;

    return 0;
}