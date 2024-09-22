#include <Arduino.h>
#include "driver/adc.h"
#define pot 33
#define led1 5
#define led2 16
#define led3 17

void encenderLed(int led, int tiempo);
void pedirTiempo(int led);
void lecturaADC();
void pedirLed();

void setup() {
  Serial.begin(115200);
  pinMode(pot, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  Serial.println("Elija una de las dos opciones:");
  Serial.println("1. Encender LED");
  Serial.println("2. Lectura ADC");
  
  while (Serial.available() == 0) {
    // Esperar a que el usuario ingrese una opción
  }

  int opcion = Serial.parseInt(); // Leer la opción seleccionada

  switch (opcion) {
    case 1:
      pedirLed();
      break;
    case 2:
      lecturaADC();
      break;
    default:
      Serial.println("Opción no válida.");
      break;
  }

  delay(500); // Pequeño retraso para evitar spam en la comunicación serial
}

void pedirLed() {
  Serial.println("Seleccione el LED a encender (1, 2 o 3):");

  // Esperar la entrada del usuario para el LED
  while (Serial.available() == 0) {
    // Esperar hasta que haya algo en el buffer serial
  }

  int led = Serial.parseInt();  // Leer la selección de LED

  if (led < 1 || led > 3) {
    Serial.println("Selección de LED no válida.");
    return;
  }

  pedirTiempo(led);
}

void pedirTiempo(int led) {
  Serial.println("Ingrese el tiempo que desea que el LED esté encendido (en milisegundos):");

  // Esperar la entrada del usuario para el tiempo
  while (Serial.available() == 0) {
    // Esperar hasta que haya algo en el buffer serial
  }

  int tiempo = Serial.parseInt();  // Leer el tiempo de encendido

  if (tiempo <= 0) {
    Serial.println("El tiempo debe ser mayor a 0.");
    return;
  }

  // Encender el LED seleccionado durante el tiempo especificado
  encenderLed(led, tiempo);
}

void encenderLed(int led, int tiempo) {
  switch (led) {
    case 1:
      digitalWrite(led1, HIGH);
      delay(tiempo);
      digitalWrite(led1, LOW);
      Serial.print("LED1 encendido por ");
      Serial.print(tiempo);
      Serial.println(" ms");
      break;
    case 2:
      digitalWrite(led2, HIGH);
      delay(tiempo);
      digitalWrite(led2, LOW);
      Serial.print("LED2 encendido por ");
      Serial.print(tiempo);
      Serial.println(" ms");
      break;
    case 3:
      digitalWrite(led3, HIGH);
      delay(tiempo);
      digitalWrite(led3, LOW);
      Serial.print("LED3 encendido por ");
      Serial.print(tiempo);
      Serial.println(" ms");
      break;
    default:
      Serial.println("No se eligió una opción válida.");
      break;
  }
}

void lecturaADC() {
  int potVal = analogRead(pot);  // Leer el valor del potenciómetro
  Serial.print("Lectura ADC del potenciómetro: ");
  Serial.println(potVal);
}