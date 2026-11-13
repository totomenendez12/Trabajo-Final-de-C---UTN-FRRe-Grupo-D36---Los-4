Trabajo Práctico Integrador Final: Simulador de Misiones Artemis

Este repositorio contiene el código fuente del simulador cinemático de la misión Artemis (Ascenso del SLS y nave Orion), desarrollado como Trabajo Práctico Integrador Final para la cátedra de Algoritmos y Estructuras de Datos.

Integrantes y Comisión
*   **Comisión / Grupo:** K1.4 / Grupo D36 - "Los 4"
*   **Integrantes:**
    *   Gonzalez, Valentina - 30085
    *   Menendez, Ignacio Manuel - 30157
    *   Monzon, Lourdes - 30399
    *   Pareja Bruno, Maria del Pilar - 30720

Link al video: https://youtu.be/qqWofU1UWlw

Descripción del Escenario Asignado y Reglas de Simulación
**Escenario:** Ascenso y Propulsión con el SLS (MRUV y Desprendimiento).

El programa simula el despegue del cohete Space Launch System (SLS) desde el Centro Espacial Kennedy (partiendo del reposo $y_0 = 0.0$ m). La física de la misión se divide en tres fases:
1.  **Fase 1:** MRUV con aceleración constante ($a_1 = 20.0 \text{ m/s}^2$) impulsado por los SRB hasta los 120 segundos de vuelo.
2.  **Fase 2:** Desacople de los SRB y continuación con el núcleo principal ($a_2 = 12.5 \text{ m/s}^2$) hasta alcanzar una altitud de 160.000 metros.
3.  **Fase 3 (Falla):** Apagado abrupto de motores, iniciando una caída libre inercial bajo la aceleración de la gravedad terrestre ($g = -9.80 \text{ m/s}^2$).

**Reglas de Interacción:** 
El simulador permite al usuario consultar el escenario base programado, extraer la telemetría exacta en un instante de tiempo $t$ personalizado durante la primera fase, o inyectar deliberadamente una falla de motores a una altitud específica (restringida al dominio físico de 10.000 a 200.000 metros) para evaluar el comportamiento inercial del cohete.

Breve Detalle de Funcionamiento
El sistema fue diseñado en lenguaje C bajo un **paradigma modular estricto**, separando las responsabilidades lógicas y visuales para evitar el acoplamiento:
*   `artemis.h` / `artemis.c`: Definen el "Ambiente" encapsulando las magnitudes físicas en el registro `EstadoNave` (tiempo, altitud, velocidad, aceleración). Implementa el motor de cálculo aplicando ecuaciones dependientes del tiempo (Fase 1) y la **Ecuación de Torricelli** independiente del tiempo (Fase 2 y 3). Se hace uso de **punteros** (paso por referencia) para que los cálculos actualicen el estado de la nave directamente en memoria.
*   `validaciones.h` / `validaciones.c`: Módulo de seguridad que aísla los ingresos del usuario mediante ciclos `while(1)`. Implementa rutinas de vaciado de buffer (`getchar() != '\n'`) para prevenir bucles infinitos ante ingresos alfanuméricos accidentales.
*   `main.c`: Orquesta el sistema mediante un menú Pre-Test interactivo. Fuerza la página de códigos UTF-8 mediante la API de Windows para asegurar un correcto renderizado de los caracteres hispanos.

Instrucciones Claras de Compilación y Ejecución (en caso que no funcione el ejecutable)
Para garantizar el correcto funcionamiento del motor matemático y de validaciones, el proyecto debe ser compilado utilizando **GCC**. 

**1. Compilación:**
Abra su terminal (ya sea en Linux/Mac o MSYS2/MinGW en Windows), posiciónese en la raíz del proyecto y ejecute el siguiente comando. Note que la bandera `-lm` es obligatoria para enlazar la librería matemática `math.h`:
```bash
gcc main.c artemis.c validaciones.c -o SimuladorArtemis -lm
```

**2. Ejecución:**
*   En **Windows** (CMD o PowerShell):
    ```bash
    .\SimuladorArtemis.exe
    ```
*   En **Linux / macOS**:
    ```bash
    ./SimuladorArtemis
    ```

Registro Detallado del Uso de Inteligencia Artificial
Durante el ciclo de vida del desarrollo, se empleó Inteligencia Artificial Generativa (Gemini Pro) como un *asistente de programación par*, focalizándose en los siguientes aspectos:
*   **Arquitectura y Modularización:** Se utilizó *Prompt Engineering* para debatir y estructurar la separación del código en archivos `.c` y `.h`, comprendiendo las mejores prácticas para definir el registro global (`struct`) en la cabecera e importar dependencias correctamente sin generar conflictos.
*   **Implementación Matemática:** La IA asistió en la traslación de fórmulas físicas al lenguaje algorítmico. Resultó clave para aplicar la *Ecuación de Torricelli* despejada para tiempo y distancia utilizando la función `sqrt()` de `<math.h>`, evitando depender de variables de tiempo desconocidas en la Fase 2 y 3.
*   **Manejo de Errores y Entorno (Debugging):** La herramienta fue fundamental para aislar problemas nativos de C. Por un lado, se utilizó para diseñar el algoritmo de *limpieza de buffer* del teclado que neutralizó una vulnerabilidad crítica donde la función `scanf` entraba en un bucle infinito al recibir caracteres no numéricos. Por otro lado, aportó la solución a un conflicto de *encoding* visual (tildes rotas) en la terminal integrando rutinas de `<windows.h>` (`SetConsoleOutputCP`). 
*   Esta dinámica iterativa no reemplazó la lógica humana, sino que agilizó el paso de las definiciones del modelado y álgebra a un código robusto, blindado y profesional.
