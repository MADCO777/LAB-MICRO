#include <iostream>
#include <unistd.h>     // Para fork(), getpid(), getppid(), sleep()
#include <sys/wait.h>   // Para wait(), waitpid()
#include <cstdlib>      // Para rand(), srand()
#include <ctime>        // Para time()

using namespace std;

// Función para mostrar separadores en la salida
void mostrarSeparador(const string& actividad) {
    cout << "\n" << string(50, '=') << endl;
    cout << "    " << actividad << endl;
    cout << string(50, '=') << endl;
}

// ACTIVIDAD I: Primer Hijo (15 puntos)
void actividad1() {
    mostrarSeparador("ACTIVIDAD I: Primer Hijo");
    
    pid_t pid = fork();
    
    if (pid == -1) {
        cerr << "Error al crear proceso hijo" << endl;
        return;
    }
    else if (pid == 0) {
        // Proceso hijo
        cout << "HIJO: Mi PID es " << getpid() 
             << ", PID de mi padre es " << getppid() << endl;
        cout << "HIJO: Durmiendo por 3 segundos..." << endl;
        sleep(3);
        cout << "HIJO: Terminando..." << endl;
        exit(0);
    }
    else {
        // Proceso padre
        cout << "PADRE: Esperando que termine el hijo..." << endl;
        wait(NULL);
        cout << "PADRE: El hijo ha terminado correctamente" << endl;
    }
}

// ACTIVIDAD II: Dos hijos, dos tareas (15 puntos)
void actividad2() {
    mostrarSeparador("ACTIVIDAD II: Dos hijos, dos tareas");
    
    pid_t pid1, pid2;
    
    // Crear primer hijo
    pid1 = fork();
    if (pid1 == -1) {
        cerr << "Error al crear primer hijo" << endl;
        return;
    }
    else if (pid1 == 0) {
        // Primer hijo - cuenta del 1 al 5
        cout << "HIJO 1 (PID " << getpid() << "): Contando del 1 al 5:" << endl;
        for (int i = 1; i <= 5; i++) {
            cout << "HIJO 1: " << i << endl;
            sleep(1);
        }
        exit(0);
    }
    
    // Crear segundo hijo
    pid2 = fork();
    if (pid2 == -1) {
        cerr << "Error al crear segundo hijo" << endl;
        return;
    }
    else if (pid2 == 0) {
        // Segundo hijo - imprime letras A-E
        cout << "HIJO 2 (PID " << getpid() << "): Imprimiendo letras A-E:" << endl;
        for (char c = 'A'; c <= 'E'; c++) {
            cout << "HIJO 2: " << c << endl;
            sleep(1);
        }
        exit(0);
    }
    
    // Proceso padre espera a ambos hijos
    cout << "PADRE: Esperando que terminen ambos hijos..." << endl;
    wait(NULL); // Esperar primer hijo
    wait(NULL); // Esperar segundo hijo
    cout << "PADRE: Ambos hijos han terminado" << endl;
}

// ACTIVIDAD III: Jerarquía de procesos {nieto} (15 puntos)
void actividad3() {
    mostrarSeparador("ACTIVIDAD III: Jerarquía de procesos (nieto)");
    
    pid_t pid_hijo = fork();
    
    if (pid_hijo == -1) {
        cerr << "Error al crear proceso hijo" << endl;
        return;
    }
    else if (pid_hijo == 0) {
        // Proceso hijo
        cout << "HIJO: Mi PID es " << getpid() 
             << ", PID de mi padre es " << getppid() << endl;
        
        // El hijo crea un nieto
        pid_t pid_nieto = fork();
        
        if (pid_nieto == -1) {
            cerr << "Error al crear proceso nieto" << endl;
            exit(1);
        }
        else if (pid_nieto == 0) {
            // Proceso nieto
            cout << "NIETO: Mi PID es " << getpid() 
                 << ", PID de mi padre es " << getppid() << endl;
            cout << "NIETO: Durmiendo por 2 segundos..." << endl;
            sleep(2);
            cout << "NIETO: Terminando..." << endl;
            exit(0);
        }
        else {
            // El hijo espera al nieto
            cout << "HIJO: Esperando que termine el nieto..." << endl;
            wait(NULL);
            cout << "HIJO: El nieto ha terminado, ahora termino yo" << endl;
            exit(0);
        }
    }
    else {
        // Proceso padre
        cout << "PADRE: Mi PID es " << getpid() << endl;
        cout << "PADRE: Esperando que termine el hijo..." << endl;
        wait(NULL);
        cout << "PADRE: El hijo ha terminado, proceso completado" << endl;
    }
}

// ACTIVIDAD IV: Multiprocesamiento y reloj (15 puntos)
void actividad4() {
    mostrarSeparador("ACTIVIDAD IV: Multiprocesamiento y reloj");
    
    cout << "PADRE (PID " << getpid() << "): Creando 3 hijos..." << endl;
    
    // Crear tres hijos
    for (int i = 1; i <= 3; i++) {
        pid_t pid = fork();
        
        if (pid == -1) {
            cerr << "Error al crear hijo " << i << endl;
            continue;
        }
        else if (pid == 0) {
            // Proceso hijo
            for (int j = 1; j <= 3; j++) {
                cout << "HIJO " << i << " (PID " << getpid() 
                     << "): Mensaje " << j << "/3" << endl;
                sleep(1);
            }
            cout << "HIJO " << i << ": Terminando" << endl;
            exit(0);
        }
    }
    
    // El padre NO espera a los hijos
    cout << "PADRE: No esperaré a los hijos, termino inmediatamente" << endl;
    cout << "PADRE: Los hijos continuarán ejecutándose como huérfanos" << endl;
    
    // Pequeña pausa para ver algunos mensajes antes de terminar
    sleep(1);
}

// ACTIVIDAD V: Control de procesos zombies (15 puntos)
void actividad5() {
    mostrarSeparador("ACTIVIDAD V: Control de procesos zombies");
    
    cout << "=== PRIMERA PARTE: SIN wait() - Creando zombie ===" << endl;
    
    pid_t pid = fork();
    
    if (pid == -1) {
        cerr << "Error al crear proceso hijo" << endl;
        return;
    }
    else if (pid == 0) {
        // Proceso hijo - termina rápidamente
        cout << "HIJO (PID " << getpid() << "): Terminando rápidamente..." << endl;
        exit(0);
    }
    else {
        // Proceso padre - NO llama wait() inmediatamente
        cout << "PADRE: Hijo creado con PID " << pid << endl;
        cout << "PADRE: Durmiendo 5 segundos SIN llamar wait()..." << endl;
        cout << "PADRE: Ejecuta 'ps aux | grep Z' en otra terminal para ver zombie" << endl;
        
        sleep(5);
        
        cout << "\n=== SEGUNDA PARTE: CON wait() - Limpiando zombie ===" << endl;
        cout << "PADRE: Ahora llamando wait() para limpiar zombie..." << endl;
        
        int status;
        pid_t terminated_pid = wait(&status);
        
        if (terminated_pid > 0) {
            cout << "PADRE: Hijo con PID " << terminated_pid 
                 << " terminó con status " << status << endl;
        }
        
        cout << "PADRE: Zombie eliminado correctamente" << endl;
    }
}

// ACTIVIDAD VI: Creación de múltiples procesos hijos (25 puntos)
void actividad6() {
    mostrarSeparador("ACTIVIDAD VI: Múltiples procesos hijos");
    
    int n;
    cout << "Ingrese la cantidad de hijos a crear (máximo 10): ";
    cin >> n;
    
    if (n <= 0 || n > 10) {
        cout << "Número inválido. Debe ser entre 1 y 10." << endl;
        return;
    }
    
    // Inicializar generador de números aleatorios
    srand(time(NULL));
    
    cout << "PADRE (PID " << getpid() << "): Creando " << n << " hijos..." << endl;
    
    // Crear N hijos
    for (int i = 1; i <= n; i++) {
        pid_t pid = fork();
        
        if (pid == -1) {
            cerr << "Error al crear hijo " << i << endl;
            continue;
        }
        else if (pid == 0) {
            // Proceso hijo
            int tiempo_sleep = (rand() % 5) + 1; // Entre 1 y 5 segundos
            
            cout << "Soy el hijo " << i << " con PID " << getpid() << endl;
            cout << "HIJO " << i << ": Dormiré por " << tiempo_sleep << " segundos" << endl;
            
            sleep(tiempo_sleep);
            
            cout << "HIJO " << i << ": Terminando después de " << tiempo_sleep << " segundos" << endl;
            exit(0);
        }
    }
    
    // El padre espera a todos los hijos
    cout << "PADRE: Esperando que terminen todos los " << n << " hijos..." << endl;
    
    int hijos_terminados = 0;
    int status;
    pid_t pid_terminado;
    
    while ((pid_terminado = wait(&status)) > 0) {
        hijos_terminados++;
        cout << "PADRE: Hijo con PID " << pid_terminado 
             << " terminó (" << hijos_terminados << "/" << n << ")" << endl;
    }
    
    cout << "PADRE: Todos los hijos han terminado." << endl;
}

// Función para mostrar el menú
void mostrarMenu() {
    cout << "\n" << string(60, '*') << endl;
    cout << "    LABORATORIO 04 - PROGRAMACIÓN CON FORK()" << endl;
    cout << "    Universidad del Valle de Guatemala" << endl;
    cout << string(60, '*') << endl;
    cout << "1. Actividad I: Primer Hijo" << endl;
    cout << "2. Actividad II: Dos hijos, dos tareas" << endl;
    cout << "3. Actividad III: Jerarquía de procesos (nieto)" << endl;
    cout << "4. Actividad IV: Multiprocesamiento y reloj" << endl;
    cout << "5. Actividad V: Control de procesos zombies" << endl;
    cout << "6. Actividad VI: Múltiples procesos hijos" << endl;
    cout << "7. Ejecutar todas las actividades" << endl;
    cout << "0. Salir" << endl;
    cout << string(60, '*') << endl;
    cout << "Seleccione una opción: ";
}

int main() {
    int opcion;
    
    do {
        mostrarMenu();
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                actividad1();
                break;
            case 2:
                actividad2();
                break;
            case 3:
                actividad3();
                break;
            case 4:
                actividad4();
                cout << "\nNOTA: Los hijos pueden seguir ejecutándose." << endl;
                cout << "Usa 'ps -lf | grep <usuario>' para verificar procesos." << endl;
                break;
            case 5:
                actividad5();
                break;
            case 6:
                actividad6();
                break;
            case 7:
                cout << "\nEjecutando todas las actividades...\n" << endl;
                actividad1();
                sleep(2);
                actividad2();
                sleep(2);
                actividad3();
                sleep(2);
                actividad4();
                sleep(5); // Dar tiempo a que los hijos huérfanos terminen
                actividad5();
                sleep(2);
                actividad6();
                break;
            case 0:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
        }
        
        if (opcion != 0) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        
    } while (opcion != 0);
    
    return 0;
}