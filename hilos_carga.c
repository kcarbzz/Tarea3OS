#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/sysinfo.h>

// Función que ejecutará cada hilo
void* cargar_procesador(void* arg) {
    int thread_id = *((int*) arg);
    printf("Hilo %d iniciado. ID de hilo: %lu\n", thread_id, pthread_self());
    
    // Simular carga del procesador por 120 segundos
    for (int i = 0; i < 1000000000; i++) {
        // Operación para consumir CPU (simulación)
        double x = 0.0001;
        x *= x;
    }

    printf("Hilo %d terminado.\n", thread_id);
    return NULL;
}

int main() {
    // Obtener la cantidad de núcleos del sistema
    int num_nucleos = get_nprocs();
    printf("Número de núcleos disponibles: %d\n", num_nucleos);

    pthread_t hilos[num_nucleos];
    int ids[num_nucleos];

    // Crear hilos según la cantidad de núcleos
    for (int i = 0; i < num_nucleos; i++) {
        ids[i] = i + 1;
        if (pthread_create(&hilos[i], NULL, cargar_procesador, &ids[i]) != 0) {
            perror("Error al crear el hilo");
            return 1;
        }
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < num_nucleos; i++) {
        pthread_join(hilos[i], NULL);
    }

    printf("Todos los hilos han terminado.\n");

    return 0;
}
