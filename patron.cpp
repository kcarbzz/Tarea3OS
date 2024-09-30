#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Ingrese el valor de n: ";
    cin >> n;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            cout << "0";
        }
        cout << "1" << endl;
    }
    return 0;
}
