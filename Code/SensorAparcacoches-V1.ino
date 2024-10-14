/*
* CONFIGURACION DE LA DISTRIBUCION DE PINES
*/
#define pin_trig_sensor 3
#define pin_echo_sensor 2
#define pin_led_roja 9
#define pin_led_amarilla 10
#define pin_led_verde 11
#define pin_buzzer 6

/*
* CONFIGURACION DE LAS VARIABLES
*/

#define limite_rojo 20
#define limite_verde 50

/*
* PROGRAMA
*/


int distancia = 0;

void setup() {
  Serial.begin(9600);

  pinMode(pin_trig_sensor, OUTPUT);
  pinMode(pin_echo_sensor, INPUT);
  pinMode(pin_led_roja, OUTPUT);
  pinMode(pin_led_amarilla, OUTPUT);
  pinMode(pin_led_verde, OUTPUT);
  pinMode(pin_buzzer, OUTPUT);
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
  int contador = 0; // Sirve para evitar que siga pitando tras 5 segudos estacionado el vehiculo
  if (distancia > limite_verde) {
    digitalWrite(pin_led_roja, LOW);
    digitalWrite(pin_led_amarilla, LOW);
    digitalWrite(pin_led_verde, HIGH);
    noTone(pin_buzzer);
    contador = 0;
    }
  else if (distancia<limite_verde && distancia>limite_rojo) {
    digitalWrite(pin_led_roja, LOW);
    digitalWrite(pin_led_amarilla, HIGH);
    digitalWrite(pin_led_verde, LOW);
    tone(pin_buzzer, 200,100);
    delay(100);
    contador = 0;
    }
  else if (distancia < limite_rojo) {
    digitalWrite(pin_led_roja, HIGH);
    digitalWrite(pin_led_amarilla, LOW);
    digitalWrite(pin_led_verde, LOW);
    if(contador < 50) // controla el tiempo que sigue pitando tras entrar en esta distancia, cada 10 es 1 segundo
      tone(pin_buzzer, 200);
      delay(100);
      contador = contador+1;
    }
  }