#include "pch.h"
#include <iostream>
#include <omp.h>

// valores para diferentes pruebas
#define mostrar 10

#define N 1000
#define chunk 10
//
//#define N 100000
//#define chunk 1000
//
//#define N 1000000
//#define chunk 10000
//
//#define N 10000000
//#define chunk 50000

//#define N 100000000
//#define chunk 100000


void imprimirArreglo(float* d);

int main()
{
    std::cout << "=== Prueba de Suma de Arreglos ===" << std::endl;
    std::cout << "N = " << N << ", chunk = " << chunk << std::endl;
    std::cout << "Threads disponibles: " << omp_get_max_threads() << std::endl;

    float* a = new float[N];
    float* b = new float[N];
    float* c = new float[N];

    // Inicialización
    for (int i = 0; i < N; i++) {
        a[i] = i * 1.0f;
        b[i] = (i + 10) * 2.0f;
    }

    // VERSION PARALELA
    double start_paralelo = omp_get_wtime();
#pragma omp parallel for shared(a,b,c) schedule(static, chunk)
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }
    double end_paralelo = omp_get_wtime();
    double tiempo_paralelo = end_paralelo - start_paralelo;

    // VERSION SECUENCIAL (para comparar)
    float* c_seq = new float[N];
    double start_secuencial = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        c_seq[i] = a[i] + b[i];
    }
    double end_secuencial = omp_get_wtime();
    double tiempo_secuencial = end_secuencial - start_secuencial;

    // Resultados
	std::cout << "\nLos primeros " << mostrar << " elementos del arreglo a: " << std::endl;
	imprimirArreglo(a);
	std::cout << "Los primeros " << mostrar << " elementos del arreglo b: " << std::endl;
	imprimirArreglo(b);
	std::cout << "Los primeros " << mostrar << " elementos del arreglo c: " << std::endl;
	imprimirArreglo(c);


    std::cout << "\n--- RESULTADOS ---" << std::endl;
    std::cout << "Tiempo secuencial:  " << tiempo_secuencial << " seg" << std::endl;
    std::cout << "Tiempo paralelo:    " << tiempo_paralelo << " seg" << std::endl;
    std::cout << "Speedup:            " << tiempo_secuencial / tiempo_paralelo << "x" << std::endl;
    std::cout << "Eficiencia:         " << (tiempo_secuencial / tiempo_paralelo) / omp_get_max_threads() * 100 << "%" << std::endl;

    delete[] a;
    delete[] b;
    delete[] c;
    delete[] c_seq;

    return 0;
}

void imprimirArreglo(float* d) {
    for (int i = 0; i < mostrar; i++) {
        std::cout << d[i] << " ";
    }
    std::cout << std::endl;
}

