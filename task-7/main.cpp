//
// Created by Gav on 07/12/2020.
//
#include <iostream>
#include <vector>
#include <cmath>

// Define DEBUG if you want to see verbose output
//#define DEBUG 1

#include <sstream>

using namespace std;

const double EPS = 1e-8;

class VariableValue {
private:
    bool parameter = false, set = false;
public:
    int var_cnt=0;
    vector<bool> param_mask;
    vector<double> paramter_k;

    VariableValue(){}

    VariableValue(int idx){
        this->var_cnt = idx;
        parameter = true;
        set = true;
    }
    VariableValue(int var_cnt, vector<double> &parameter_k, vector<bool> &param_mask){
        this->var_cnt = var_cnt;
        this->paramter_k = move(parameter_k);
        this->param_mask = param_mask;
        parameter = false;
        set = true;
    }

    bool is_parameter() { return parameter; }
    bool is_set() { return set; }

    void sum(vector<double> b, double k) {
//        vector<double> s(min(paramter_k.size(), b.size()), 0);
        for (int i = 0; i < paramter_k.size(); ++i) {
            paramter_k[i] = paramter_k[i] + k * b[i];
        }
    }

    void sum(VariableValue b, double k) {
//        vector<double> s(min(paramter_k.size(), b.paramter_k.size()), 0);
        for (int i = 0; i < paramter_k.size(); ++i) {
            paramter_k[i] = paramter_k[i] + k * b.paramter_k[i];
        }
    }

    void mult(double k) {
        for (double & i : paramter_k) {
            i = i * k;
        }
    }

    string str() {
        stringstream ss;
        if (!set){
            ss << "nil";
            return ss.str();
        }
        if (parameter) ss << "x_" << var_cnt;
        else {
            int j = 0;
            for (int i = 0; i < param_mask.size(); ++i) {
                if (param_mask[i]){
                    if (paramter_k[j] != 0)
                        ss << paramter_k[j] << " * x_" << i+1 << " ";
                    j++;
                }
            }
//            int param_cnt = paramter_k.size();
//            for (int i = 0; i < param_cnt; ++i) {
//                if (paramter_k[i] != 0)
//                    ss << paramter_k[i] << " * x_" << i+var_cnt-param_cnt+1 << " ";
//            }
        }
        return ss.str();
    }
};

vector<double> sum(vector<double> a, vector<double> b, double k) {
    vector<double> s(min(a.size(), b.size()), 0);
    for (int i = 0; i < a.size(); ++i) {
        s[i] = a[i] + k * b[i];
    }
    return s;
}

pair<double, int> get_first_on_row(vector<double> &row){
    int j = 0;
    for (double i : row) {
        if (i != 0) return {i, j};
        j++;
    }
    return {0, row.size()-1};
}

#ifdef DEBUG

string print_vec(const vector<double> &a) {
    stringstream ss;
    for (double i : a) {
        ss << i << " ";
    }
    return ss.str();
}

string print_vec(const vector<bool> &a) {
    stringstream ss;
    for (bool i : a) {
        ss << i;
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


    int rank = k - null_cnt;
//    cout << "Rank of this system is " << rank << endl;
//    cout << "This system is " << (null_cnt == 0 ? "not " : "") << "linear dependent" << endl;
//    cout << "System:" << endl;
//    print_all(arr);

    // find full solution
    int parameter_count = n;
    vector<bool> param_mask(n, true);
    int i = 0, j = 0;
    while (i < n && j < k) {
//        cout << "arr[" << j << "][" << i << "] = " << arr[j][i] << endl;
        if (arr[j][i] != 0) {
//            cout << "X_" << i+1 << " is not param" << endl;
            param_mask[i] = false;
            j++;
            parameter_count--;
        } else i++;
    }
//    cout << "Mask: " << print_vec(param_mask) << endl;
//    cout << "Param cnt: " << parameter_count << endl;

    vector<VariableValue> full_solution(n);

    for (int i1 = 0; i1 < n; i1++) {
        if (param_mask[i1])
            full_solution[i1] = VariableValue(i1+1); // parameters
    }

    for (int k1 = rank-1; k1 >= 0; --k1) {
        vector<double> param_k(parameter_count);
        j = 0;
        for (i = 0; i < n; i++){
            if (param_mask[i]){
                param_k[j] = - arr[k1][i];
                j++;
            }
        }
        VariableValue var_val = VariableValue(n, param_k, param_mask);
        pair<double, int> first_on_row = get_first_on_row(arr[k1]);
        assert(first_on_row.first != 0);
        var_val.mult(- 1);
//        cout << "Params for x_" << k1+1 << " = " << var_val.str() << endl;
        // minus other values
        for (int l = first_on_row.second+1; l < n; ++l) {
            if (!full_solution[l].is_parameter()){
//                cout << var_val.str() << " + " << full_solution[l].str() << ";" << endl;
                var_val.sum(full_solution[l], arr[k1][l]);
            }
        }
        //todo don't forget to mult by -1
        var_val.mult(-1/first_on_row.first);
//        cout << "Params for x_" << first_on_row.second+1 << " = " << var_val.str() << endl;
        full_solution[first_on_row.second] = var_val;
    }


    cout << "solution: " << endl;
    for (int row = 0; row < n; ++row) {
        string str = full_solution[row].str();
        cout << "X_" << row+1 << " = " << (str.empty() ? "0" : str) << endl;
    }

    cout << endl << "FSS: (ФСР):" << endl;

    j = 0;
    for (int p = 0; p < n; p++){
        if (param_mask[p]) {
            cout << "a_" << j+1 << " = (";
            for (int l = 0; l < n; ++l) {
                if (! full_solution[l].is_parameter())
                    cout << full_solution[l].paramter_k[j] << ", ";
                else
                    cout << (p == full_solution[l].var_cnt-1) << ", ";
            }
            cout << ");" << endl;
            j++;
        }
    }

//    for (int row = rank-2; row >= 0; --row) {
//
//    }

    return 0;
}

