  // calculos dos intervalos feitos para 150bpm

  int buzzer = 3;

  // define a frequencia de cada nota musical
  #define D1   148   // 147,5 Hz 1°
  #define D1b  139   // 139,1 Hz 1°
  #define C1   132   // 131,5 Hz 1° 
  #define G1   392   // 392,4 Hz 1° batman
  #define C2  527   // 527,15 Hz 2° batman
  #define G2  196   // 196,5 Hz
  #define G2b  186   // 185,6 Hz
  #define F  175   // 175,3 Hz
  #define D2 590   // 590,3 Hz

  // melodia e intervalos de tempo da primeira parte
  int melodia_1[] = {
    D1, D1, D1b, D1b, C1, C1, D1b, D1b, // (na na na na na na na na)
    D1, D1, D1b, D1b, C1, C1, D1b, D1b, // (na na na na na na na na)
    D1, D1, D1b, D1b, C1, C1, D1b, D1b, // (na na na na na na na na)
    D1, D1, D1b, D1b, C1, C1, D1b, D1b, // (na na na na na na na na)
    G1, G1, // (batman)
    C1, C1, D1b, D1b // (na na na na)
  };

  int duracoes_1[] = {
    200, 200, 200, 200, 200, 200, 200, 200,
    200, 200, 200, 200, 200, 200, 200, 200,
    200, 200, 200, 200, 200, 200, 200, 200,
    200, 200, 200, 200, 200, 200, 200, 200,
    400, 400,
    200, 200, 200, 200
  };

  // melodia e intervalos de tempo da segunda parte
  int melodia_2[] = {
    D1, D1, D1b, D1b, C1, C1, D1b, D1b,  // (na na na na na na na na)
    G1, G1,  // (batman)
    C1, C1, D1b, D1b // (na na na na)
  };

  int duracoes_2[] = {
    200, 200, 200, 200, 200, 200, 200, 200,
    400, 400,
    200, 200, 200, 200
  };

  // melodia e intervalos de tempo da terceira parte
  int melodia_3[] = {
    D1, D1, D1b, D1b, C1, C1, D1b, D1,  // (na na na na na na na na)
    C2, C2,  // (batman)
    F, F, G2b, G2b // (na na na na)
  };

  int duracoes_3[] = {
    200, 200, 200, 200, 200, 200, 200, 200,
    400, 400,
    200, 200, 200, 200
  };

  // melodia e intervalos de tempo da quarta parte
  int melodia_4[] = {
    G2, G2, G2b, G2b, F, F, G2b, G2,  // (na na na na na na na na)
    G1, G1,  // (batman)
    C1, C1, D1b, D1b // (na na na na)
  };

  int duracoes_4[] = {
    200, 200, 200, 200, 200, 200, 200, 200,
    400, 400,
    200, 200, 200, 200
  };

  // melodia e intervalos de tempo da quinta parte
  int melodia_5[] = {
    D1, D1, D1b, D1b, C1, C1, D1b, D1,  // (na na na na na na na na)
    D2, D2  // (batman)
  };

  int duracoes_5[] = {
    200, 200, 200, 200, 200, 200, 200, 200,
    400, 400
  };

  // melodia e intervalos de tempo da sexta parte
  int melodia_6[] = {
    0, D2, D2, D2, C2, C2, 0, C2, C2, C2,
    G1, G1,  // (batman)
    C1, C1, D1b, D1b // (na na na na)
  };

  int duracoes_6[] = {
    200, 200, 200, 200, 400, 400, 200, 200, 200, 200,
    400, 400,
    200, 200, 200, 200
  };

  void setup(){}

  void loop(){
    // tocar cada nota das notas com seus respectivos intervalos da primeira parte
    for (int i = 0; i < sizeof(melodia_1) / sizeof(int); i++){
      tone(buzzer, melodia_1[i], duracoes_1[i]);
      delay(duracoes_1[i] + 10);
      noTone(buzzer);
    }

    // o acrescimo de 10 no delay pode ser alterado
    // tocar cada nota das notas com seus respectivos intervalos da segunda parte
    for (int i = 0; i < sizeof(melodia_2) / sizeof(int); i++){
      tone(buzzer, melodia_2[i], duracoes_2[i]);
      delay(duracoes_2[i] + 10);
      noTone(buzzer);
    }
    // tocar cada nota das notas com seus respectivos intervalos da terceira parte
    for (int i = 0; i < sizeof(melodia_3) / sizeof(int); i++){
      tone(buzzer, melodia_3[i], duracoes_3[i]);
      delay(duracoes_3[i] + 10);
      noTone(buzzer);
    }
    // tocar cada nota das notas com seus respectivos intervalos da quarta parte
    for (int i = 0; i < sizeof(melodia_4) / sizeof(int); i++){
      tone(buzzer, melodia_4[i], duracoes_4[i]);
      delay(duracoes_4[i] + 10);
      noTone(buzzer);
    }
    // tocar cada nota das notas com seus respectivos intervalos da quinta parte
    for (int i = 0; i < sizeof(melodia_5) / sizeof(int); i++){
      tone(buzzer, melodia_5[i], duracoes_5[i]);
      delay(duracoes_5[i] + 10);
      noTone(buzzer);
    }
    // tocar cada nota das notas com seus respectivos intervalos da sexta parte
    for (int i = 0; i < sizeof(melodia_6) / sizeof(int); i++){
      tone(buzzer, melodia_6[i], duracoes_6[i]);
      delay(duracoes_6[i] + 10);
      noTone(buzzer);
    }

    // ...
  }