#include <Servo.h>

#define LED_red 13
#define LED_green 10

#define Echo_pin 3
#define Trig_pin 4

int pos = 0;
int dist;
int distance = 333;
long duration;

Servo servo_9;

void setup() {
  Serial.begin(9600);
  pinMode(LED_red, OUTPUT);
  pinMode(LED_green, OUTPUT);
  pinMode(Echo_pin, INPUT);
  pinMode(Trig_pin, OUTPUT);
  servo_9.attach(9, 500, 2500);
  digitalWrite(LED_red, HIGH);
  digitalWrite(LED_green, LOW);
}

void loop() {
  dist = get_Distance();
  if (dist >= 329) {
    switch_led();
    for (pos = 0; pos <= 180; pos += 1) {
      servo_9.write(pos);
      delay(15);
    }
    digitalWrite(LED_red, LOW);
    digitalWrite(LED_green, HIGH);
  } else {
    switch_led();
    Serial.println("Error: Objects detected");
    digitalWrite(LED_red, HIGH);
    digitalWrite(LED_green, LOW);
  }
}

void switch_led() {
  if (digitalRead(LED_red)) {
    digitalWrite(LED_red, LOW);
    digitalWrite(LED_green, HIGH);
  } else {
    digitalWrite(LED_red, HIGH);
    digitalWrite(LED_green, LOW);
  }
}

int get_Distance() {
  digitalWrite(Trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_pin, LOW);

  duration = pulseIn(Echo_pin, HIGH);
  distance = (duration * 0.0343) / 2;
  Serial.print(" Distance: ");
  Serial.println(distance);
  return distance;
}
