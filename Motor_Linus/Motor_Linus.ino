#include <PETEletrica.h>

// Infravermelho
const unsigned char pin_sensor[] = { A0, A1, A2, A3, A4 };
SensorInfravermelhoRC qtr(pin_sensor, 5, 2000, QTR_NO_EMITTER_PIN);  // declaração do sensor IR
unsigned int sensores[5];

// Motores
Motores motor(10, 11, 6, 5);

void setup() {
  Serial.begin(9600);  // estabelece a comunicação
}

void loop() {
  motor.set_motors(100, 100);  // embica para esquerda
  delay(500);
  motor.set_motors(0, 0);
  delay(1000);

  motor.set_motors(200, -200);  // vai reto
  delay(400);
  motor.set_motors(0, 0);
  delay(1000);

  motor.set_motors(-100, -100);  // alinha na curva
  delay(400);
  motor.set_motors(0, 0);
  delay(1000);

  motor.set_motors(100, -100);  // vai reto
  delay(800);
  motor.set_motors(0, 0);
  delay(1000);

  motor.set_motors(-100, -100);  // embica para direita
  delay(500);
  motor.set_motors(0, 0);
  delay(1000);

  motor.set_motors(100, -100);  // vai reto
  delay(600);
}