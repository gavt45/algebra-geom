//
// Created by Gav on 30/10/2020.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

// Define DEBUG if you want to see verbose output
//#define DEBUG 1

#ifdef DEBUG
#include <sstream>
#endif

using namespace std;

const double EPS = 1e-8;

bool abs_comp(const vector<double>& a, const vector<double>& b) {
    for (int i = 0; i < min(a.size(), b.size()); i++){
        if (abs(abs(a[i]) - abs(b[i])) < EPS) continue;
        return abs(a[i]) < abs(b[i]);
    }
    return abs(a[0]) < abs(b[0]);
}

vector<double> sum(vector<double> a, vector<double> b, double k) {
    vector<double> s(min(a.size(), b.size()), 0);
    for (int i = 0; i < a.size(); ++i) {
        s[i] = a[i] + k * b[i];
        if (fabs(s[i]) < EPS) s[i] = 0;
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
    cin >> n;
    k = n;
    vector<vector<double>> arr(k, vector<double>(n, 0));

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> arr[i][j];
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

    sort(arr.rbegin(), arr.rend(), abs_comp);
//    int swap_cnt = bubble_sort(arr);

    long double det = 1.0;
    for (int m = 0; m < n; ++m) {
        det *= arr[m][m];
#ifdef DEBUG
        cout << m << " " << n-m-1 << endl;
#endif
    }

    det *= pow(-1,det_digit/2);

#ifdef DEBUG
    for (const auto &vec : arr) {
        cout << "vec: " << print_vec(vec) << endl;
    }
#endif

    cout << "det = " << setprecision(30) << det << endl;
    return 0;
}
