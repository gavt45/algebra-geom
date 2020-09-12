#include <iostream>
#include <iomanip>
#include <math.h>

#define ABS(x) ((x)>=0 ? (x):(-(x)))

using namespace std;

class Complex { // a + ib
    // for simple representation
    double a;
    double b;
    // for trigonometric representation
    double ro;
    double phi;

public:
    Complex(){
        this->a = 0.0;
        this->b = 0.0;
        convert_simple_to_trig();
    }

//    Complex(double a, double b){
//        this->a = a;
//        this->b = b;
//    }

    Complex(double ro, double phi){
        this->ro = ro;
        this->phi = phi;
        convert_trig_to_simple();
    }

    double real(){
        convert_trig_to_simple();
        return a;
    }

    void set_real(double _a){
        a = _a;
        convert_simple_to_trig();
    }

    double imaginary(){
        convert_trig_to_simple();
        return b;
    }

    void set_imag(double _b){
        b = _b;
        convert_simple_to_trig();
    }

    double get_trig_ro(){
        convert_simple_to_trig();
//            return sqrt(this->a*this->a + this->b*this->b);
//        else
        return ro;
    }

    double get_trig_phi(){
        convert_simple_to_trig();
        return phi;
    }

    void multiply(int real, int imag){
        convert_trig_to_simple();
        a = a*real - b*imag;
        b = a*imag + b*real;
        convert_simple_to_trig();
    }

//    void print_roots(int n){
//        convert_simple_to_trig();
//
//        convert_trig_to_simple();
//    }

    void power_trig(int n){
        convert_simple_to_trig();
        ro = pow(ro, n);
        phi *= n;
        phi -= (int)(phi/(2*M_PI))*2*M_PI;
        convert_trig_to_simple();
    }

    void print_all(){
        cout << "Z{SIMPLE: ";
        print_complex();
        cout << "; TRIG: ";
        print_complex_trig();
        cout << "}";
    }

    void print_complex(){
        convert_trig_to_simple();
        cout << setprecision(12) << this->a << " " << (this->b>=0?"+ ":"- ") << "i*" << setprecision(12) << ABS(this->b);
    }

    void print_complex_trig(){
        convert_simple_to_trig();
        double phi = this->get_trig_phi();
        cout << setprecision(12) << this->get_trig_ro() << " * (cos(" << setprecision(12) << phi << ") + i*sin(" << setprecision(12) << phi << "))";
    }

private:
    void convert_trig_to_simple(){
//        if (trig){
        a = ro * cos(phi);
        b = ro * sin(phi);
//        } else {
//            cout << "Trying to convert converted number or non trig!!!" << endl;
//        }
    }

    void convert_simple_to_trig(){
        ro = sqrt(this->a*this->a + this->b*this->b);
        phi = atan(this->b/this->a);
//        trig = true;
    }
};

//void print_complex(complex z){
//    cout << setprecision(12) << z.a << " " << (z.b>=0?"+ ":"- ") << "i*" << setprecision(12) << ABS(z.b);
//}
//
//void print_complex_trig(complex z){
//    double phi = atan(z.b/z.a);
//    cout << setprecision(12) << sqrt(z.a*z.a + z.b*z.b) << " * (cos(" << setprecision(12) << phi << ") + i*sin(" << setprecision(12) << phi << "))";
//}

int main(int argc, char * argv[]){
    // if (argc < 2)
    Complex z = Complex();
    cout << "Please, input a and b for z = a + ib:" << endl;
    double a,b;
    cin >> a >> b;
    z.set_imag(b); z.set_real(a);
    cout << "Please, input choice(0,1,2 or 3)" << endl;
    int choice = -1;
    cin >> choice;
    switch (choice){
        case 0: { // just print out numbers
            z.print_all();
            cout << endl;
            break;
        }
        case 1: { // print z^-1
            Complex z_inverse = Complex();
            
            z_inverse.set_real(z.real()/(z.real()*z.real()+z.imaginary()*z.imaginary()));
            z_inverse.print_all();cout << endl;
            z_inverse.set_imag(-z.imaginary()/(z.real()*z.real()+z.imaginary()*z.imaginary()));

            z_inverse.print_all();
            cout << endl;
            break;
        }
        case 2: { // print z^n
            Complex z1 = Complex(z.get_trig_ro(), z.get_trig_phi());
            z1.print_all(); cout << endl;
            cout << "Power?: ";
            int power = 1;
            cin >> power;
            z1.power_trig(power);
            cout << endl;
            z1.print_all();
            cout << endl;
            break;
        }
        case 3: { // print all n-th roots of z
            double ro = z.get_trig_ro(), phi = z.get_trig_phi();
            
            break;
        }
        default: {
            cout << "Wrong choice!" << endl;
            return -1;
        }
    }
    return 0;
}