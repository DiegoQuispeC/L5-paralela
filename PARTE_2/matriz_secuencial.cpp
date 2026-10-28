#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <iomanip>

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {

    int N = atoi(argv[1]);
    vector<double> A((size_t)N * N);
    vector<double> x(N);
    vector<double> y(N, 0.0);

    for (int i = 0; i < N; i++) {
        x[i] = 1.0;
        for (int j = 0; j < N; j++) {
            A[(size_t)i * N + j] = 2.0;
        }
    }

    auto inicio = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            y[i] += A[(size_t)i * N + j] * x[j];
        }
    }
    auto fin = high_resolution_clock::now();
    duration<double> tiempo = fin - inicio;
 
    cout << fixed << setprecision(12);
    cout << "Tamano de matriz: " << N << " x " << N << endl;
    cout << "Resultado de comprobacion: " << y[N - 1] << endl;
    cout << "Tiempo: " << tiempo.count() << " segundos" << endl;
    
    return 0;
}