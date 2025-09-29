#include <PETEletrica.h>

// Infravermelho
const unsigned char pin_sensor[] = {A0, A1, A2, A3, A4};
SensorInfravermelhoRC qtr(pin_sensor, 5, 2000, QTR_NO_EMITTER_PIN); // declaração do sensor IR
unsigned int sensores[5]; 
float a0, a1, a2, a3, a4;


void setup() {
  Serial.begin(9600); // estabelece a comunicação
  // calibra o IR
  for(int i = 0; i < 200; i++){ 
      qtr.calibrate();
      delay(10);
  }
}

void loop() {
  a0 = analogRead(A0);
  a1 = analogRead(A1);
  a2 = analogRead(A2);
  a3 = analogRead(A3);
  a4 = analogRead(A4);

  float mediaSensores = ((a0 + a1 + a2 + a3 + a4) / 5);  // calculo da media para indetificação da tag

  unsigned int position = qtr.readLine(sensores); // leitura dos sensores infravermelhos para saber a posicao do carrinho em relação a fita
  Serial.println(mediaSensores); // a partir do sensor IR, printa posição do carrinho em relação a fita
}