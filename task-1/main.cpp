#include <iostream>
#define ABS(x) ((x)>=0 ? (x):(-(x)))

using namespace std;

struct complex { // a + ib
    int a;
    int b;
};

int main(){
    complex z = complex{};
    cout << "Please, input a and b for z = a + ib:" << endl;
    cin >> z.a >> z.b;
    cout << "Please, input choice(0,1,2 or 3)" << endl;
    int choice = -1;
    cin >> choice;
    switch (choice){
        case 0:
            cout << "Trigonometric number notation: " << z.a << " " << (z.b>=0?"+ ":"- ") << "i" << ABS(z.b) << endl;
            break;
        case 1:
            cout << "Unimplemented!" << endl;
            break;
        case 2:
            cout << "Unimplemented!" << endl;
            break;
        case 3:
            cout << "Unimplemented!" << endl;
            break;
        default:
            cout << "Wrong choice!" << endl;
            return -1;
    }
    return 0;
}