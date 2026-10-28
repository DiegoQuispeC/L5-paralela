
#include <iostream>
#include <pthread.h>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace chrono;

int contador = 0;
int num_hilos;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condicion = PTHREAD_COND_INITIALIZER;

void barrera() {

    pthread_mutex_lock(&mutex);
    contador++;

    if (contador == num_hilos) {
        pthread_cond_broadcast(&condicion);
    } else {
        while (contador < num_hilos) {
            pthread_cond_wait(&condicion, &mutex);
        }
    }
    pthread_mutex_unlock(&mutex);
}

void* trabajo(void* argumento) {

    int id = *(int*) argumento;
    volatile long long resultado = 0;

    for (long long i = 0; i < (id + 1) * 1000000LL; i++) {
        resultado += i % 10;
    }

    pthread_mutex_lock(&mutex);
    cout << "Hilo " << id << " llego a la barrera" << endl;
    pthread_mutex_unlock(&mutex);

    barrera();

    pthread_mutex_lock(&mutex);
    cout << "Hilo " << id << " paso la barrera" << endl;
    pthread_mutex_unlock(&mutex);

    return nullptr;
}

int main(int argc, char* argv[]) {

    num_hilos = atoi(argv[1]);

    vector<pthread_t> hilos(num_hilos);
    vector<int> ids(num_hilos);

    auto inicio = high_resolution_clock::now();
    for (int i = 0; i < num_hilos; i++) {
        ids[i] = i;
        pthread_create(&hilos[i], nullptr, trabajo, &ids[i]);
    }

    for (int i = 0; i < num_hilos; i++) {
        pthread_join(hilos[i], nullptr);
    }
    auto fin = high_resolution_clock::now();
    duration<double> tiempo = fin - inicio;

    cout << "Hilos: " << num_hilos << endl;
    cout << "Tiempo total: " << tiempo.count() << " segundos" << endl;

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condicion);

    return 0;
}
