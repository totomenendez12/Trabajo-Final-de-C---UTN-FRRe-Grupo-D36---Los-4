#include <stdio.h>
#include <stdlib.h> // Necesario para la función exit() y limpieza de pantalla
#include "artemis.h"
#ifdef _WIN32
    #include <windows.h> 
#endif
#include "validaciones.h" // Incluimos el módulo de entradas seguras 

// Prototipo local para limpiar pantalla según el SO
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    // 1. Declaración e inicialización del Ambiente
    EstadoNave orion;
    int opcion_menu = 0;
    
    // Variables para parámetros personalizados (opción 3)
    float t_pers_fase1;
    float h_pers_falla;

    // Inicialización de la nave al estado cero (reposo)
    inicializarNave(&orion);

    // 2. Ciclo principal del programa
    while (opcion_menu != 4) {
        limpiarPantalla();
        printf("\n======================================================\n");
        printf("    SIMULADOR DE MISIONES ARTEMIS - NAVE ORION (SLS)\n");
        printf("======================================================\n");
        printf("1. Ejecutar Simulacion Completa (Parametros Base)\n");
        printf("2. Consultar Telemetria Parcial (Punto a Punto)\n");
        printf("3. Simular Falla de Motores y Caida Libre\n");
        printf("4. Salir del Simulador\n");
        printf("------------------------------------------------------\n");
        
        printf("Seleccione una operacion (1-4): ");
        opcion_menu = leerEnteroSeguro(1, 4); 

        switch (opcion_menu) {
            case 1:
                // SIMULACIÓN COMPLETA (ESCENARIO BASE) 
                printf("\n[ INICIANDO DESPEGUE - ESCENARIO BASE ]\n");
                
                // Reiniciamos la nave por si se corrió otra simulación antes
                inicializarNave(&orion); 
                
                // Cálculo Fase 1: SRB hasta los 120s
                calcularFase1(&orion, T_DESACOPLE_BASE, A1_BASE);
                printf("\n> Desacople de cohetes SRB (120s):");
                imprimirReporteTelemetria(&orion);
                
                // Cálculo Fase 2: Núcleo hasta los 160.000m
                calcularFase2(&orion, ALTITUD_CORTE_BASE, A2_BASE);
                printf("\n> Corte de motores (160km):");
                imprimirReporteTelemetria(&orion);
                
                // Cálculo Fase 3: Falla y caída libre inercial
                float h_max_base = calcularAltitudMaximaCaidaLibre(&orion);
                printf("\n> Alerta: Falla de Motores.\n");
                printf("> La nave sigue ascendiendo por inercia.\n");
                printf("> Altitud MAXIMA alcanzada antes de caer: %.2f m\n", h_max_base);
                
                printf("\nPresione Enter para continuar...");
                esperarEnter(); // Función del módulo validaciones
                break;

            case 2:
                // CONSULTA INTERACTIVA DE FASE 1 (EJ. PARA GRAFICAR) 
                printf("\n[ CONSULTA DE TELEMETRIA - FASE 1 ]\n");
                printf("Ingrese el instante de tiempo a consultar (ej: 60.0): ");
                t_pers_fase1 = leerFlotanteSeguro(1.0, 120.0); // Rango de validación
                
                inicializarNave(&orion);
                calcularFase1(&orion, t_pers_fase1, A1_BASE);
                imprimirReporteTelemetria(&orion);
                
                printf("\nPresione Enter para continuar...");
                esperarEnter();
                break;

            case 3:
                // SIMULADOR DE FALLAS PERSONALIZADO 
                printf("\n[ SIMULADOR DE FALLAS CATASTROFICAS ]\n");
                printf("Ingrese la altitud (m) donde ocurre la falla de motores (Ej: 100000): ");
                h_pers_falla = leerFlotanteSeguro(10000.0, 200000.0); // Validación de rango
                
                inicializarNave(&orion);
                // Calculamos hasta los 120s normales
                calcularFase1(&orion, T_DESACOPLE_BASE, A1_BASE);
                
                // Calculamos la segunda fase hasta la altitud de falla elegida por el usuario
                calcularFase2(&orion, h_pers_falla, A2_BASE);
                imprimirReporteTelemetria(&orion);
                
                // Calculamos la altura máxima
                float h_max_falla = calcularAltitudMaximaCaidaLibre(&orion);
                printf("\n> Falla iniciada a los %.2f m.\n", h_pers_falla);
                printf("> Altitud MAXIMA alcanzada antes de caer: %.2f m\n", h_max_falla);
                
                printf("\nPresione Enter para continuar...");
                esperarEnter();
                break;

            case 4:
                printf("\nApagando sistemas del simulador. ¡Buen vuelo!\n");
                break;
        }
    }
    return 0;
} 
