#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Función para verificar si un número es primo
int es_primo(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

void contar_primos(int hijo_num) {
    int limite = 1000;
    printf("Proceso hijo %d (PID: %d) contando números primos hasta %d...\n", hijo_num, getpid(), limite);
    for (int i = 2; i <= limite; i++) {
        if (es_primo(i)) {
            printf("Hijo %d: %d es primo\n", hijo_num, i);
        }
    }
}

int main() {
    pid_t pid1, pid2, pid3;

    // Crear primer proceso hijo
    pid1 = fork();
    if (pid1 == 0) {
        contar_primos(1);  // Hijo 1 cuenta números primos
        return 0;
    }

    // Crear segundo proceso hijo
    pid2 = fork();
    if (pid2 == 0) {
        contar_primos(2);  // Hijo 2 cuenta números primos
        return 0;
    }

    // Crear tercer proceso hijo
    pid3 = fork();
    if (pid3 == 0) {
        contar_primos(3);  // Hijo 3 cuenta números primos
        return 0;
    }

    // Código del proceso padre: esperar a los hijos
    printf("Proceso padre (PID: %d) esperando a los hijos...\n", getpid());
    wait(NULL);  // Esperar a que termine algún hijo
    wait(NULL);  // Esperar a que termine otro hijo
    wait(NULL);  // Esperar al último hijo

    printf("Todos los procesos hijos han terminado.\n");

    return 0;
}
