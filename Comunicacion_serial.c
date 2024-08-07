#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void delay(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

int main() {
    int angleServo1 = 90;  // Ángulo inicial para servo 1
    int angleServo2 = 0;   // Ángulo inicial para servo 2
    int increment1 = 1;    // Incremento para servo 1
    int increment2 = 1;    // Incremento para servo 2
    int detenerbucle = 1;       // Variable de control para el bucle

    // Abrir el puerto serial
    FILE *serial = fopen("COM3", "w"); // Cambiar por tu puerto serial en Windows o "/dev/ttyUSB0" en Linux
    if (serial == NULL) {
        printf("No se pudo abrir el puerto serial\n");
        return 1;
    }

    while (detenerbucle) {  /* Cuando angleServo1 sea igual a 90 y angleServo2 sea igual a 0, 
     detenerbucle se establecerá en 0, lo que detendrá el bucle*/
        // Enviar los ángulos de los servos a Arduino
        printf("%d %d\n", angleServo1, angleServo2);
        fprintf(serial, "%d %d\n", angleServo1, angleServo2);
        fflush(serial);  // Forzar la escritura de los datos inmediatamente

        // Actualizar la variable1
        angleServo1 += increment1;
        if (angleServo1 >= 180 || angleServo1 <= 0) {
            increment1 = -increment1;  // Cambiar la dirección del incremento para variable1
        }

        // Actualizar la variable2
        angleServo2 += increment2;
        if (angleServo2 >= 180 || angleServo2 <= 0) {
            increment2 = -increment2;  // Cambiar la dirección del incremento para variable2
        }

        // Espera el delay que se encuentra especificado
        delay(250);
        
        // Verificar la condición para detener el bucle
        if (angleServo1 == 90 && angleServo2 == 0) {
            detenerbucle = 0;  // Cambiar la variable de control para salir del bucle
        }
    }

    fclose(serial); // Cerrar el puerto serial

    return 0;
}
