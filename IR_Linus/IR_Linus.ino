#include <PETEletrica.h>

// Infravermelho
const unsigned char pin_sensor[] = {A0, A1, A2, A3, A4};
SensorInfravermelhoRC qtr(pin_sensor, 5, 2000, QTR_NO_EMITTER_PIN); // declaração do sensor IR
unsigned int sensores[5]; 

void setup() {
  Serial.begin(9600); // estabelece a comunicação
  // calibra o IR
  for(int i = 0; i < 100; i++){ 
      qtr.calibrate();
      delay(10);
  }
}

void loop() {
  unsigned int position = qtr.readLine(sensores); // leitura dos sensores infravermelhos para saber a posicao do carrinho em relação a fita
  Serial.println(position); // a partir do sensor IR, printa posição do carrinho em relação a fita
}