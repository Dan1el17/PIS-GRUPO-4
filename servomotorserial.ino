#include <Servo.h>

Servo servo1; // Servo 1
Servo servo2; // Servo 2

int servo1Pin = 9;  // Pin al que está conectado el servo 1
int servo2Pin = 10; // Pin al que está conectado el servo 2

int angleServo1 = 90; // Ángulo inicial del servo 1
int angleServo2 = 0;  // Ángulo inicial del servo 2

void setup() {
  servo1.attach(servo1Pin); // Conectar el servo 1 al pin especificado
  servo2.attach(servo2Pin); // Conectar el servo 2 al pin especificado
  servo1.write(angleServo1); // Inicializar servo 1 en 90 grados
  servo2.write(angleServo2); // Inicializar servo 2 en 0 grados
  
  Serial.begin(9600); // Inicializar la comunicación serial a 9600 bps
  Serial.setTimeout(100); // Configurar el tiempo de espera para la lectura serial
}

void loop() {
  if (Serial.available() > 0) { // Verificar si hay datos disponibles en el puerto serial
    // Leer los datos desde el puerto serial
    String data = Serial.readStringUntil('\n'); // Leer una línea completa hasta el salto de línea
    
    // Separar los valores
    int spaceIndex = data.indexOf(' ');
    if (spaceIndex != -1) {
      String val1Str = data.substring(0, spaceIndex);
      String val2Str = data.substring(spaceIndex + 1);

      // Convertir los valores a enteros
      angleServo1 = val1Str.toInt();
      angleServo2 = val2Str.toInt();

      // Mostrar los valores recibidos para depuración
      Serial.print("Recibido: ");
      Serial.print(angleServo1);
      Serial.print(" ");
      Serial.println(angleServo2);

      // Asegurarse de que los ángulos estén dentro del rango válido (0-180)
      angleServo1 = constrain(angleServo1, 0, 180);
      angleServo2 = constrain(angleServo2, 0, 180);

      // Actualizar los ángulos de los servos
      servo1.write(angleServo1);
      servo2.write(angleServo2);
    } else {
      // Mensaje de error si no se pudo separar correctamente
      Serial.println("Error: Datos recibidos no válidos");
    }
  }

  // Pequeña demora para evitar lecturas seriales rápidas
  delay(100);
}
