#include <iostream>
#include <iomanip>
#include <math.h>

#define ABS(x) ((x)>=0 ? (x):(-(x)))

#define MIN_DOUBLE_VAL 1e-6

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
//        print_all();
    }

    double imaginary(){
        convert_trig_to_simple();
        return b;
    }

    void set_imag(double _b){
        b = _b;
        convert_simple_to_trig();
//        print_all();
    }

    double get_ro(){
        convert_simple_to_trig();
//            return sqrt(this->a*this->a + this->b*this->b);
//        else
        return ro;
    }

    void set_ro(double _ro){
        ro = _ro;
        convert_trig_to_simple();
    }

    double get_phi(){
        convert_simple_to_trig();
        return phi;
    }

    void set_phi(double _phi){
        phi = _phi;
        convert_trig_to_simple();
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
        double phi = this->get_phi();
        cout << setprecision(12) << this->get_ro() << " * (cos(" << setprecision(12) << phi << ") + i*sin(" << setprecision(12) << phi << "))";
    }

private:
    void convert_trig_to_simple(){
//        if (trig){
        a = ro * cos(phi);
//        cout << "a:" << a << endl;
        if (abs(a) < MIN_DOUBLE_VAL) a = 0;
        b = ro * sin(phi);
//        cout << "b:" << b << endl;
        if (abs(b) < MIN_DOUBLE_VAL) b = 0;
//        } else {
//            cout << "Trying to convert converted number or non trig!!!" << endl;
//        }
    }

    void convert_simple_to_trig(){
        if (a == 0 && b == 0)
            ro = 0;
        else
            ro = sqrt(a*a + b*b);
        if (b != 0 && ro != 0) {
            phi = asin(b / ro);
            if (a < 0)
                phi = M_PI - phi;
        } else if (a != 0 && ro != 0) {
            phi = acos(a / ro);
            if (b < 0)
                phi = 2*M_PI - phi;
        } /*else if (a != 0 && b != 0) {
            phi = atan(a / b);
        }*/ else
            phi = 0;
//            phi = atan(b/a);
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
    if ((abs(a) < MIN_DOUBLE_VAL && b != 0) || (abs(b) < MIN_DOUBLE_VAL && b != 0)) {
        cout << "Coefficient is to smaller than " << MIN_DOUBLE_VAL << "! Please, recompile with another value."
             << endl;
        return 0;
    }
    z.set_imag(b); z.set_real(a);
    int choice = -1;
    bool stop = false;
    while (!stop) {
        cout << "Please, input choice(0,1,2 or 3)" << endl << "> ";
        cin >> choice;
        switch (choice) {
            case 0: { // just print out numbers
                z.print_all();
                cout << endl;
                break;
            }
            case 1: { // print z^-1
                Complex z_inverse = Complex();
                if (z.real() * z.real() + z.imaginary() * z.imaginary() != 0)
                    z_inverse.set_real(z.real() / (z.real() * z.real() + z.imaginary() * z.imaginary()));
                if (z.real() * z.real() + z.imaginary() * z.imaginary() != 0)
                    z_inverse.set_imag(-z.imaginary() / (z.real() * z.real() + z.imaginary() * z.imaginary()));

                z_inverse.print_all();
                cout << endl;
                break;
            }
            case 2: { // print z^n
                Complex z1 = Complex(z.get_ro(), z.get_phi());
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
                Complex z1 = Complex(z.get_ro(), z.get_phi());
                cout << "Root?: ";
                double power = 1.0;
                cin >> power;
                z1.set_ro(pow(z1.get_ro(), 1 / power));
                z1.set_phi(z1.get_phi() / power);
                cout << "TRIG: " << setprecision(12) << z1.get_ro() << " * (cos(" << setprecision(12) << z1.get_phi()
                     << " + 2pi*k/" << power << ") + i*sin(" << setprecision(12) << z1.get_phi() << " + 2pi*k/" << power
                     << ")) where k in [0; " << power - 1 << "]";
                break;
            }
            default: {
                cout << "Wrong choice!" << endl;
                stop = true;
            }
        }
    }
    return 0;
}