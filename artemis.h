#ifndef ARTEMIS_H
#define ARTEMIS_H

// Constantes físicas y del escenario base
#define GRAVEDAD 9.80
#define V_INICIAL 0.0
#define Y_INICIAL 0.0
#define A1_BASE 20.0
#define T_DESACOPLE_BASE 120.0
#define A2_BASE 12.5
#define ALTITUD_CORTE_BASE 160000.0

// Estructura que representa la telemetría de la nave en un instante dado
typedef struct {
    float tiempo;       // Instante de tiempo (s)
    float altitud;      // Posición vertical 'y' (m)
    float velocidad;    // Rapidez 'v' (m/s)
    float aceleracion;  // Aceleración actual (m/s^2)
    int fase_vuelo;     // 1: MRUV SRB, 2: MRUV Núcleo, 3: Caída Libre
} EstadoNave;

// Prototipos de funciones lógicas y de cálculo (a implementar en artemis.c)
void inicializarNave(EstadoNave *nave);
void calcularFase1(EstadoNave *nave, float tiempo_objetivo, float aceleracion);
void calcularFase2(EstadoNave *nave, float altitud_objetivo, float aceleracion);
float calcularAltitudMaximaCaidaLibre(EstadoNave *nave);
float calcularAceleracionEnG(float aceleracion_m_s2);
void imprimirReporteTelemetria(const EstadoNave *nave);

#endif

