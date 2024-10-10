#define pin_echo_sensor 8 //Sensor ultrasonido pin 8
#define pin_trigger_sensor 9 //Sensor ultrasonido pin 9
void setup() {
 //El pin será una entrada para leer el sensor de ultrasonidos
 pinMode(pin_echo_sensor, INPUT);
 //El pin enviará señales ultrasónicas, será una salida.
 pinMode(pin_trigger_sensor, OUTPUT);
 Serial.begin(9600);
}
void loop() {
 long distancia;
 unsigned long tiempo;
 // Ponemos el Triiger en estado bajo y esperamos 2 ms
 digitalWrite(pin_trigger_sensor, LOW);
 delayMicroseconds(2);
 // Ponemos el pin Trigger a estado alto y esperamos 10 ms
 digitalWrite(pin_trigger_sensor, HIGH);
 delayMicroseconds(10);
 digitalWrite(pin_trigger_sensor, LOW);
 //calculamos el tiempo que tarda en recibir la señal
 tiempo = pulseIn(pin_echo_sensor, HIGH);
 //Calculo de la distancia partiendo del tiempo
 distancia = tiempo * 0.000001 * 34000 / 2.0;
 //envío de la distancia al ordenador
 Serial.print(distancia);
 Serial.println(“cm”);
}
