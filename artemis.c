#include <stdio.h>
#include <math.h> // Necesario para la función sqrt() (raíz cuadrada)
#include "artemis.h"

// 1. Inicialización de la nave en la plataforma
void inicializarNave(EstadoNave *nave) {
    nave->tiempo = 0.0;
    nave->altitud = Y_INICIAL;
    nave->velocidad = V_INICIAL;
    nave->aceleracion = 0.0;
    nave->fase_vuelo = 0;
}

// 2. Fase 1: MRUV con aceleración constante guiada por el tiempo (Desacople SRB)
void calcularFase1(EstadoNave *nave, float tiempo_objetivo, float aceleracion) {
    // Ecuación de Posición: y = y0 + v0*t + 0.5*a*t^2
    nave->altitud = nave->altitud + (nave->velocidad * tiempo_objetivo) + (0.5 * aceleracion * tiempo_objetivo * tiempo_objetivo);

    // Ecuación de Velocidad: v = v0 + a*t
    nave->velocidad = nave->velocidad + (aceleracion * tiempo_objetivo);

    // Actualizamos el estado general de la telemetría
    nave->tiempo = nave->tiempo + tiempo_objetivo;
    nave->aceleracion = aceleracion;
    nave->fase_vuelo = 1;
}

// 2. Fase 2: MRUV guiada por la altitud (usando ecuación de Torricelli)
void calcularFase2(EstadoNave *nave, float altitud_objetivo, float aceleracion) {
    float distancia_a_recorrer = altitud_objetivo - nave->altitud;

    // Torricelli: vf^2 = v0^2 + 2*a*d -> vf = raiz(v0^2 + 2*a*d)
    float velocidad_final = sqrt((nave->velocidad * nave->velocidad) + (2 * aceleracion * distancia_a_recorrer));

    // Despejamos el tiempo de la ecuación de velocidad: t = (vf - v0) / a
    float tiempo_fase = (velocidad_final - nave->velocidad) / aceleracion;

    // Actualizamos el estado de la nave
    nave->altitud = altitud_objetivo;
    nave->velocidad = velocidad_final;
    nave->tiempo = nave->tiempo + tiempo_fase;
    nave->aceleracion = aceleracion;
    nave->fase_vuelo = 2;
}

// 3. Fase 3: Cálculo de falla y caída libre
float calcularAltitudMaximaCaidaLibre(EstadoNave *nave) {
    // En el punto de altura máxima, la velocidad final es 0 m/s.
    // Torricelli: 0 = v0^2 + 2*g*d -> d = -(v0^2) / (2*g)
    // La gravedad actúa en contra (frena la nave), por lo que usamos -GRAVEDAD.
    float distancia_extra = -(nave->velocidad * nave->velocidad) / (2 * (-GRAVEDAD));

    // Retornamos la altitud total (la altitud de la falla + lo que subió por inercia)
    return nave->altitud + distancia_extra;
}

// 4. Cálculo auxiliar para Fuerzas G
float calcularAceleracionEnG(float aceleracion_m_s2) {
    return aceleracion_m_s2 / GRAVEDAD;
}

// 5. Interfaz limpia de reporte
void imprimirReporteTelemetria(const EstadoNave *nave) {
    printf("\n==========================================\n");
    printf("   TELEMETRIA SLS ORION - FASE %d\n", nave->fase_vuelo);
    printf("==========================================\n");
    printf(" Tiempo de vuelo: %12.2f s\n", nave->tiempo);
    printf(" Altitud actual:  %12.2f m\n", nave->altitud);
    printf(" Rapidez (v):     %12.2f m/s\n", nave->velocidad);
    printf(" Aceleracion:     %12.2f m/s^2 (%.2f G)\n", nave->aceleracion, calcularAceleracionEnG(nave->aceleracion));
    printf("------------------------------------------\n");
}
