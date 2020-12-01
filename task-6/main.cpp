//
// Created by Gav on 26/11/2020.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

// Define DEBUG if you want to see verbose output
//#define DEBUG 1

//#ifdef DEBUG
#include <sstream>
//#endif

using namespace std;

const double EPS = 1e-8;

bool abs_comp(const vector<double>& a, const vector<double>& b) {
    for (int i = 0; i < min(a.size(), b.size()); i++){
        if (abs(abs(a[i]) - abs(b[i])) < EPS) continue;
        return abs(a[i]) < abs(b[i]);
    }
    return abs(a[0]) < abs(b[0]);
}

void mult(vector<double> &a, double k) {
    for (double & i : a) {
        i = i * k;
    }
}

vector<double> sum(vector<double> a, vector<double> b, double k) {
    vector<double> s(min(a.size(), b.size()), 0);
    for (int i = 0; i < a.size(); ++i) {
        s[i] = a[i] + k * b[i];
        if (fabs(s[i]) < EPS) s[i] = 0;
    }
    return s;
}

string print_vec(const vector<double> &a) {
    stringstream ss;
    for (double i : a) {
        ss << i << " ";
    }
    return ss.str();
}

#ifdef DEBUG
void print_all(const vector<vector<double>> &arr) {
    for (const vector<double> &a : arr) {
        cout << print_vec(a) << endl;
    }
}
#endif

int main() {
    int n, k;
    cin >> n;
    k = n;
    vector<vector<double>> arr(k, vector<double>(n, 0));
    vector<vector<double>> back_arr(k, vector<double>(n, 0));
//    vector<double> barr(n, 0);

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
//            if (j == n) cin >> barr[i];
//            else {
                if (i == j) back_arr[i][j] = 1;
                cin >> arr[i][j];
//            }
        }
    }

    vector<bool> used_vectors(n, false); // true if we used i-th vector to subtract from all

    int det_digit = 0;

    for (int l = 0; l < n; ++l) { // length of the vector
#ifdef DEBUG
        cout << "L: " << l << endl;
#endif
        bool found_non_empty = false;
        double v = 0;
        int v_idx = 0;
        for (int i = 0; i < k; ++i) {
            // if vector element is non null and this vector is not already used
            if (fabs(arr[i][l]) > EPS && !used_vectors[i]) {
                found_non_empty = true;
                v = arr[i][l];
                v_idx = i;
                break;
            }
        }

        if (found_non_empty) {
            used_vectors[v_idx] = true;
            if (v_idx != l){
                det_digit++;
#ifdef DEBUG
                cout << "Putting row #" << v_idx << " on #" << l << endl;
#endif
            }

            for (int i = 0; i < k; ++i) {
                if (!used_vectors[i]) {
                    double koef = -arr[i][l] / v;
                    arr[i] = sum(arr[i], arr[v_idx], koef);
                    back_arr[i] = sum(back_arr[i], back_arr[v_idx], koef);
//                    barr[i] += koef * barr[v_idx];
#ifdef DEBUG
                    cout << "i: " << i << "; minus: " << print_vec(arr[i]) << endl;
                    print_all(arr);
//                    cout << "barr: " << print_vec(barr) << endl;
#endif
                }
            }
        }
    }

    // det != 0
    // n == k
    assert(n == k);
    for (int c = n-1; c > 0; --c) {
        for (int r = c-1; r >= 0; --r) {
            double koef = -arr[r][c]/arr[c][c];
            arr[r] = sum(arr[r], arr[c], koef);
            back_arr[r] = sum(back_arr[r], back_arr[c], koef);
//            barr[r] += koef * barr[c];
#ifdef DEBUG
            cout << "i: " << r << "; minus: " << print_vec(arr[c]) << endl;
            print_all(arr);
//            cout << "barr: " << print_vec(barr) << endl;
#endif
        }
    }

    for (int m = 0; m < n; ++m) {
        mult(back_arr[m], 1/arr[m][m]);
        arr[m][m] = 1;
    }

#ifdef DEBUG
    int i = 0;
    for (const auto &vec : arr) {
        cout << "vec: " << print_vec(vec) << " | " << print_vec(back_arr[i]) << endl;
        i++;
    }
#endif


    cout << "Back arr:" << endl;
#ifndef DEBUG
    int i = 0;
#else
    i=0
#endif
    for (const auto &vec : back_arr) {
        cout << print_vec(vec) << endl;
        i++;
    }

//    for (int m = 0; m < n; ++m) {
//        cout << "X_" << m << " = " << barr[m]/arr[m][m] << endl;
//    }

    return 0;
}
