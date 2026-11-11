#include <stdio.h>
#include "validaciones.h"

// Función privada y auxiliar para limpiar la basura del teclado
void limpiarBuffer() {
    int c;
    // Lee y descarta caracteres hasta encontrar el salto de línea (Enter) o el fin de archivo
    while ((c = getchar()) != '\n' && c != EOF);
}

// 1. Lectura a prueba de fallos para Menús (Enteros)
int leerEnteroSeguro(int min, int max) {
    int valor;
    int estado_lectura;

    while (1) { // Bucle infinito hasta que el usuario ingrese algo válido
        estado_lectura = scanf("%d", &valor);

        // Verificamos que scanf haya leído 1 número válido y esté en el rango
        if (estado_lectura == 1 && valor >= min && valor <= max) {
            limpiarBuffer();
            return valor;
        } else {
            limpiarBuffer();
            printf("> Error: Entrada invalida. Ingrese un entero entre %d y %d: ", min, max);
        }
    }
}

// 2. Lectura a prueba de fallos para Magnitudes Físicas (Flotantes)
float leerFlotanteSeguro(float min, float max) {
    float valor;
    int estado_lectura;

    while (1) {
        estado_lectura = scanf("%f", &valor);

        if (estado_lectura == 1 && valor >= min && valor <= max) {
            limpiarBuffer();
            return valor;
        } else {
            limpiarBuffer();
            printf("> Error: Valor fuera de limites físicos. Ingrese un numero entre %.2f y %.2f: ", min, max);
        }
    }
}

// 3. Pausa controlada del sistema
void esperarEnter() {
    // Como las funciones anteriores ya limpian el buffer, solo esperamos un [Enter] limpio
    getchar();
}
