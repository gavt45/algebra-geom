#include <iostream>
#include <iomanip>
#include <math.h>

#define ABS(x) ((x)>=0 ? (x):(-(x)))

using namespace std;

struct complex { // a + ib
    double a;
    double b;
};

void print_complex(complex z){
    cout << setprecision(12) << z.a << " " << (z.b>=0?"+ ":"- ") << "i*" << setprecision(12) << ABS(z.b);
}

void print_complex_trig(complex z){
    double phi = atan(z.b/z.a);
    cout << setprecision(12) << sqrt(z.a*z.a + z.b*z.b) << " * (cos(" << setprecision(12) << phi << ") + i*sin(" << setprecision(12) << phi << "))";
}

int main(int argc, char * argv[]){
    // if (argc < 2)
    complex z = complex{};
    cout << "Please, input a and b for z = a + ib:" << endl;
    cin >> z.a >> z.b;
    cout << "Please, input choice(0,1,2 or 3)" << endl;
    int choice = -1;
    cin >> choice;
    switch (choice){
        case 0: { // just print out numbers
            print_complex_trig(z);
            cout << endl;
            break;
        }
        case 1: { // print z^-1
            complex z_inverse = complex{};
            
            z_inverse.a = z.a/(z.a*z.a+z.b*z.b);
            z_inverse.b = -z.b/(z.a*z.a+z.b*z.b);

            cout << "z^-1: " ;
            print_complex(z_inverse);
            cout << endl;
            cout << "Trig: ";
            print_complex_trig(z_inverse);
            cout << endl;
            break;
        }
        case 2: { // print z^n
            cout << "Unimplemented!" << endl;
            break;
        }
        case 3: {
            cout << "Unimplemented!" << endl;
            break;
        }
        default: {
            cout << "Wrong choice!" << endl;
            return -1;
        }
    }
    return 0;
}