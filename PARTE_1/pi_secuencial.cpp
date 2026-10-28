#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

int main() {
    long long N = 10000000000;
    double suma = 0.0;
    double factor = 1.0;

    auto inicio = high_resolution_clock::now();

    for (long long i = 0; i < N; i++) {
        suma += factor / (2 * i + 1);
        factor = -factor;
    }

    double pi = 4.0 * suma;

    auto fin = high_resolution_clock::now();
    duration<double> tiempo = fin - inicio;

    cout << fixed << setprecision(12);
    cout << "Valor de PI: " << pi << endl;
    cout << "Iteraciones: " << N << endl;
    cout << "Tiempo: " << tiempo.count() << " segundos" << endl;

    return 0;
}