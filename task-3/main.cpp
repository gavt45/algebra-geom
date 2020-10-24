//
// Created by Gav on 23/10/2020.
//
#include <iostream>
#include <vector>
#include <cmath>

// Define DEBUG if you want to see verbose output
//#define DEBUG 1

#ifdef DEBUG
#include <sstream>
#endif

using namespace std;

const double EPS = 1e-8;

vector<double> sum(vector<double> a, vector<double> b, double k) {
    vector<double> s(min(a.size(), b.size()), 0);
    for (int i = 0; i < a.size(); ++i) {
        s[i] = a[i] + k * b[i];
    }
    return s;
}

#ifdef DEBUG
string print_vec(const vector<double> &a) {
    stringstream ss;
    for (double i : a) {
        ss << i << " ";
    }
    return ss.str();
}

void print_all(const vector<vector<double>> &arr) {
    for (const vector<double> &a : arr) {
        cout << print_vec(a) << endl;
    }
}
#endif

int main() {
    int n, k;
    cin >> n >> k;
    vector<vector<double>> arr(k, vector<double>(n, 0));

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> arr[i][j];
        }
    }

    vector<bool> used_vectors(n, false); // true if we used i-th vector to subtract from all

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

            for (int i = 0; i < k; ++i) {
                if (!used_vectors[i]) {
                    arr[i] = sum(arr[i], arr[v_idx], -arr[i][l] / v);
#ifdef DEBUG
                    cout << "i: " << i << "; minus: " << print_vec(arr[i]) << endl;
                    print_all(arr);
#endif
                }
            }
        }
    }

    int null_cnt = 0;

    // Count non null vectors
    for (const auto &vec : arr) {
        bool is_null = true;
        for (double element : vec) {
            if (fabs(element) > EPS) {
                is_null = false;
                break;
            }
        }
#ifdef DEBUG
        if (is_null) cout << "Null vec: " << print_vec(vec) << endl;
#endif
        null_cnt += is_null;
    }

    cout << "Rank of this system is " << k - null_cnt << endl;
    cout << "This system is " << (null_cnt == 0 ? "not " : "") << "linear dependent" << endl;
    return 0;
}
