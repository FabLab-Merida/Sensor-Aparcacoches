/*
* CONFIGURACION DE LA DISTRIBUCION DE PINES
*/
#include <Adafruit_NeoPixel.h>
#define pin_trig_sensor 3
#define pin_echo_sensor 2
#define pin_neo 8
#define pin_buzzer 6
/*
* CONFIGURACION DE LAS VARIABLES
*/
#define limite_rojo 25
#define limite_verde 40
#define numero_pixeles 8
/*
* PROGRAMA
*/
int contadorVerde = 0;    //Variable utiizada para temporizar el tiempo que lleva consecutivo en estado verde
int contadorNaranja = 0;  //Variable utiizada para temporizar el tiempo que lleva consecutivo en estado naranja
int contadorRojo = 0;     //Variable utiizada para temporizar el tiempo que lleva consecutivo en estado rojo
int distancia = 0;
Adafruit_NeoPixel tira = Adafruit_NeoPixel(numero_pixeles, pin_neo, NEO_GRB + NEO_KHZ800);
void setup() {
  Serial.begin(9600);
  pinMode(pin_trig_sensor, OUTPUT);
  pinMode(pin_echo_sensor, INPUT);
  pinMode(pin_buzzer, OUTPUT);
  tira.begin();
}
void loop() {
  // Ponemos el Triiger en estado bajo y esperamos 2 ms
  digitalWrite(pin_trig_sensor, LOW);
  delayMicroseconds(2);
  // Ponemos el pin Trigger a estado alto y esperamos 10 ms
  digitalWrite(pin_trig_sensor, HIGH);
  delayMicroseconds(10);
  // Comenzamos poniendo el pin Trigger en estado bajo
  digitalWrite(pin_trig_sensor, LOW);
  unsigned long tiempo = pulseIn(pin_echo_sensor, HIGH);
  distancia = tiempo * 0.000001 * 34000 / 2.0;
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();
  delay(250);
  if (distancia > limite_verde) {
    //Ponemos a 0 los ocntadores de las otras distancias y contamos en la distancia verde
    contadorVerde = contadorVerde + 1;
    contadorNaranja = 0;
    contadorRojo = 0;
    //Si aun no ha contado 20 veces consecutivas activa el led y mantiene el buzzer descativado
    if (contadorVerde < 20) {
      tira.fill(tira.Color(0, 255, 0), 0, 8);
      tira.show();
      noTone(pin_buzzer);
      delay(100);
      //Si ya ha contado más de 20 veces consecutivas desactiva el LED
    } else {
      tira.fill(tira.Color(0, 0, 0), 0, 8);
      tira.show();
      noTone(pin_buzzer);
      delay(100);
    }
  } else if (distancia < limite_verde && distancia > limite_rojo) {
    //Ponemos a 0 los ocntadores de las otras distancias y contamos en la distancia naranja
    contadorVerde = 0;
    contadorNaranja = contadorNaranja + 1;
    contadorRojo = 0;
    //Si aun no ha contado 20 veces consecutivas activa el led y activa el buzzer a la frecuencia deseada
    if (contadorNaranja < 20) {
      tira.fill(tira.Color(255, 100, 0), 0, 8);
      tira.show();
      tone(pin_buzzer, 200, 100);
      delay(100);
      //Si ya ha contado más de 20 veces consecutivas desactiva el LED y el buzzer
    } else {
      tira.fill(tira.Color(0, 0, 0), 0, 8);
      tira.show();
      noTone(pin_buzzer);
      delay(100);
    }
  } else if (distancia < limite_rojo) {
    //Ponemos a 0 los ocntadores de las otras distancias y contamos en la distancia roja
    contadorVerde = 0;
    contadorNaranja = 0;
    contadorRojo = contadorRojo + 1;
    //Si aun no ha contado 20 veces consecutivas activa el led y activa el buzzer a la frecuencia deseada
    if (contadorRojo < 20) {
      tira.fill(tira.Color(255, 0, 0), 0, 8);
      tira.show();
      tone(pin_buzzer, 200);
      delay(100);
      //Si ya ha contado más de 20 veces consecutivas desactiva el LED y el buzzer
    } else {
      tira.fill(tira.Color(0, 0, 0), 0, 8);
      tira.show();
      noTone(pin_buzzer);
      delay(100);
    }
  }
}
