
#include <iostream>
#include <vector>
#include <pthread.h>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace chrono;

struct Datos {
    int inicio;
    int fin;
    int N;
    double* A;
    double* x;
    double* y;
};

void* multiplicar(void* argumento) {
    Datos* datos = (Datos*) argumento;

    int N = datos->N;

    for (int i = datos->inicio; i < datos->fin; i++) {
        double suma = 0.0;

        for (int j = 0; j < N; j++) {
            suma += datos->A[(size_t)i * N + j] * datos->x[j];
        }

        datos->y[i] = suma;
    }

    return nullptr;
}

int main(int argc, char* argv[]) {

    int N = atoi(argv[1]);
    int num_hilos = atoi(argv[2]);

    vector<double> A((size_t)N * N);
    vector<double> x(N);
    vector<double> y(N, 0.0);

    for (int i = 0; i < N; i++) {
        x[i] = 1.0;

        for (int j = 0; j < N; j++) {
            A[(size_t)i * N + j] = 2.0;
        }
    }

    vector<pthread_t> hilos(num_hilos);
    vector<Datos> datos(num_hilos);

    auto inicio = high_resolution_clock::now();
    for (int i = 0; i < num_hilos; i++) {
        datos[i].inicio = (long long)i * N / num_hilos;
        datos[i].fin = (long long)(i + 1) * N / num_hilos;
        datos[i].N = N;
        datos[i].A = A.data();
        datos[i].x = x.data();
        datos[i].y = y.data();

        pthread_create(&hilos[i], nullptr, multiplicar, &datos[i]);
    }

    for (int i = 0; i < num_hilos; i++) {
        pthread_join(hilos[i], nullptr);
    }
    auto fin = high_resolution_clock::now();
    duration<double> tiempo = fin - inicio;

    cout << "Tamano de matriz: " << N << " x " << N << endl;
    cout << "Hilos: " << num_hilos << endl;
    cout << "Resultado de comprobacion: " << y[N - 1] << endl;
    cout << "Tiempo: " << tiempo.count() << " segundos" << endl;

    return 0;
}
