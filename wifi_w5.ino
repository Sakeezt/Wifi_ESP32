#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "VYcwk7-lGd0lmhfsXtQHEBJdesUC-hk9";
char ssid[] = "Realme2Pro";
char pass[] = "12345678";
//select
int motor1Pin1 = 12;    // Set pin for Motor 1 (LEFT)
int motor1Pin2 = 14;
int enable1Pin = 27;
int motor2Pin1 = 26;    // Set pin for Motor 2 (RIGHT)
int motor2Pin2 = 25;
int enable2Pin = 33;

// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle1 = 200;//255
int dutyCycle2 = 200;//200

void forward(){
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}


void backward(){
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void right(){
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}
void left(){
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}
void stop(){
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void setup()
{
pinMode(motor1Pin1, OUTPUT);
pinMode(motor1Pin2, OUTPUT);
pinMode(enable1Pin, OUTPUT);
pinMode(motor2Pin1, OUTPUT);
pinMode(motor2Pin2, OUTPUT);
pinMode(enable2Pin, OUTPUT);
// configure LED PWM functionalitites

ledcSetup(pwmChannel, freq, resolution);
// attach the channel to the GPIO to be controlled

ledcAttachPin(enable1Pin, pwmChannel);
ledcAttachPin(enable2Pin, pwmChannel);

ledcWrite(pwmChannel, dutyCycle1);
ledcWrite(pwmChannel, dutyCycle2);
Serial.begin(115200);
Serial.println();
Blynk.begin(auth, ssid, pass);
}


void loop()
{
  Blynk.run();
}

BLYNK_WRITE(V1)
{
  int value = param.asInt(); // Get value as integer
  // Serial.println("Going Forward");
  if (value)
  {
    forward();

  }
}

BLYNK_WRITE(V2)
{
  int value = param.asInt(); // Get value as integer
  //Serial.println("Moving Left");
  if (value)
  {

    left();
  }
}


BLYNK_WRITE(V3)
{
  int value = param.asInt(); // Get value as integer
  // Serial.println("Going back");
  if (value)
  {
    backward();

  }
}


BLYNK_WRITE(V4)
{
  int value = param.asInt(); // Get value as integer
  //Serial.println("Moving Right");
  if (value)
  {
    right();

  }
}

BLYNK_WRITE(V5)
{
  int value = param.asInt(); // Get value as integer
  // Serial.println("Braking!!");
  if (value)
  {
    stop();
  }
}
