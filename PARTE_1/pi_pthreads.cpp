#include <iostream>
#include <pthread.h>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <iomanip>

using namespace std;
using namespace chrono;

const long long N = 10000000000;

struct Datos {
    long long inicio;
    long long fin;
    double suma;
};

void* calcularPi(void* argumento) {
    Datos* datos = (Datos*) argumento;

    double sumaLocal = 0.0;
    double factor = (datos->inicio % 2 == 0) ? 1.0 : -1.0;

    for (long long i = datos->inicio; i < datos->fin; i++) {
        sumaLocal += factor / (2 * i + 1);
        factor = -factor;
    }

    datos->suma = sumaLocal;

    return nullptr;
}

int main(int argc, char* argv[]) {

    int num_hilos = atoi(argv[1]);

    vector<pthread_t> hilos(num_hilos);
    vector<Datos> datos(num_hilos);

    auto inicio = high_resolution_clock::now();

    for (int i = 0; i < num_hilos; i++) {
        datos[i].inicio = i * N / num_hilos;
        datos[i].fin = (i + 1) * N / num_hilos;
        datos[i].suma = 0.0;
        pthread_create(&hilos[i], nullptr, calcularPi, &datos[i]);
    }

    for (int i = 0; i < num_hilos; i++) {
        pthread_join(hilos[i], nullptr);
    }

    double sumaTotal = 0.0;

    for (int i = 0; i < num_hilos; i++) {
        sumaTotal += datos[i].suma;
    }
    double pi = 4.0 * sumaTotal;
    auto fin = high_resolution_clock::now();
    duration<double> tiempo = fin - inicio;

    cout << fixed << setprecision(12);
    cout << "Valor de PI: " << pi << endl;
    cout << "Iteraciones: " << N << endl;
    cout << "Hilos: " << num_hilos << endl;
    cout << "Tiempo: " << tiempo.count() << " segundos" << endl;

    return 0;
}