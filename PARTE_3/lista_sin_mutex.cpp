
#include <iostream>
#include <pthread.h>
#include <vector>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace chrono;

struct Nodo {
    int valor;
    Nodo* siguiente;
};

Nodo* cabeza = nullptr;

void insertar(int valor) {
    Nodo* nuevo = new Nodo;
    nuevo->valor = valor;
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

bool buscar(int valor) {
    Nodo* actual = cabeza;

    while (actual != nullptr) {
        if (actual->valor == valor) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

bool eliminar(int valor) {
    Nodo* actual = cabeza;
    Nodo* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->valor == valor) {
            if (anterior == nullptr) {
                cabeza = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            delete actual;
            return true;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    return false;
}

int contar() {
    int cantidad = 0;
    Nodo* actual = cabeza;

    while (actual != nullptr) {
        cantidad++;
        actual = actual->siguiente;
    }
    return cantidad;
}

struct Datos {
    int id;
    int inserciones;
};

void* trabajo(void* argumento) {
    Datos* datos = (Datos*) argumento;

    for (int i = 0; i < datos->inserciones; i++) {
        int valor = datos->id * datos->inserciones + i;
        insertar(valor);
    }

    return nullptr;
}

int main(int argc, char* argv[]) {

    int num_hilos = atoi(argv[1]);
    int inserciones = atoi(argv[2]);

    vector<pthread_t> hilos(num_hilos);
    vector<Datos> datos(num_hilos);

    auto inicio = high_resolution_clock::now();
    for (int i = 0; i < num_hilos; i++) {
        datos[i].id = i;
        datos[i].inserciones = inserciones;
        pthread_create(&hilos[i], nullptr, trabajo, &datos[i]);
    }

    for (int i = 0; i < num_hilos; i++) {
        pthread_join(hilos[i], nullptr);
    }
    auto fin = high_resolution_clock::now();
    duration<double> tiempo = fin - inicio;

    int esperados = num_hilos * inserciones;
    int obtenidos = contar();

    cout << "Hilos: " << num_hilos << endl;
    cout << "Elementos esperados: " << esperados << endl;
    cout << "Elementos obtenidos: " << obtenidos << endl;
    cout << "Elementos perdidos: " << esperados - obtenidos << endl;
    cout << "Tiempo: " << tiempo.count() << " segundos" << endl;

    cout << "Buscar 0: "
         << (buscar(0) ? "Encontrado" : "No encontrado") << endl;

    cout << "Eliminar 0: "
         << (eliminar(0) ? "Eliminado" : "No encontrado") << endl;

    while (cabeza != nullptr) {
        Nodo* temporal = cabeza;
        cabeza = cabeza->siguiente;
        delete temporal;
    }
    return 0;
}
