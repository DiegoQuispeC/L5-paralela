
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace chrono;

int contador = 0;
int num_hilos;

sem_t count_sem;
sem_t barrier_sem;

void barrera() {

    sem_wait(&count_sem);

    if (contador == num_hilos - 1) {
        contador = 0;
        sem_post(&count_sem);
        for (int i = 0; i < num_hilos - 1; i++) {
            sem_post(&barrier_sem);
        }

    } else {
        contador++;
        sem_post(&count_sem);
        sem_wait(&barrier_sem);
    }
}

void* trabajo(void* argumento) {

    int id = *(int*) argumento;

    volatile long long resultado = 0;

    for (long long i = 0; i < (id + 1) * 1000000LL; i++) {
        resultado += i % 10;
    }

    cout << "Hilo " << id << " llego a la barrera" << endl;
    barrera();
    cout << "Hilo " << id << " paso la barrera" << endl;

    return nullptr;
}

int main(int argc, char* argv[]) {

    num_hilos = atoi(argv[1]);

    if (sem_init(&count_sem, 0, 1) != 0 ||
        sem_init(&barrier_sem, 0, 0) != 0) {
        cout << "Error al inicializar semaforos" << endl;
        return 1;
    }

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
    cout << "Tiempo total: " << tiempo.count() << " segundos" << endl<< endl;

    sem_destroy(&count_sem);
    sem_destroy(&barrier_sem);

    return 0;
}
