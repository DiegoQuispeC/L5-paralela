 PARTE_1

en pi_secuencial.cpp se compila con 
g++ -O2 pi_secuencial.cpp -o pi_secuencial.exe  y luego 
./pi_secuencial.exe 

en pi_pthreads.cpp se compila con
g++ -O2 pi_pthreads.cpp -o pi_pthreads.exe -pthread y luego 
./pi_pthreads.exe N  (N puede ser 1,2.4.8 son los hilos a usar)

 PARTE_2

en matriz_secuencial.cpp se compila con 
g++ -O2 matriz_secuencial.cpp -o matriz_secuencial.exe  y luego 
./matriz_secuencial.exe X (X es el tamaño de matriz como 40000)

en matriz_pthreads.cpp se compila con
g++ -O2 matriz_pthreads.cpp -o matriz_pthreads.exe -pthread y luego 
./matriz_pthreads.exe X N  (X es el tamaño de matriz como 40000 ,N puede ser 1,2.4.8 son los hilos a usar).


PARTE_3 

en lista_sin_mutex.cpp se compila con
g++ -O2 lista_sin_mutex.cpp -o lista_sin_mutex.exe -pthread y luego 
./lista_sin_mutex.exe  N X (N puede ser 1,2.4.8 son los hilos a usar, X es el tamaño de elementos a insertar como 10000 ,).

en lista_con_mutex.cpp se compila con
g++ -O2 lista_con_mutex.cpp -o lista_con_mutex.exe -pthread y luego
./lista_con_mutex.exe N X (N puede ser 1,2.4.8 son los hilos a usar, X es el tamaño de elementos a insertar como 10000 ,).

PARTE_4 

en barrera_espera_activa.cpp se compila con
g++ -O2 barrera_espera_activa.cpp -o barrera_espera_activa.exe -pthread y luego 
./barrera_espera_activa.exe 4 

en barrera_semaforos.cpp se compila con 
g++ -O2 barrera_semaforos.cpp -o barrera_semaforos.exe -pthread y luego 
./barrera_semaforos.exe 4

en barrera_condicion.pp se compila con 
g++ -O2 barrera_condicion.cpp -o barrera_condicion.exe -pthread y luego 
./barrera_condicion.exe 4