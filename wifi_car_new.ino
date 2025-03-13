#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3BRTf2QRY"
#define BLYNK_TEMPLATE_NAME "wifi car"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Motor PINs for Motor 1 (Left Motor)
#define ENA D0
#define IN1 D1
#define IN2 D2

// Motor PINs for Motor 2 (Right Motor)
#define ENB D3
#define IN3 D4
#define IN4 D5

bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int Speed;
char auth[] = "PBo-5Rposh-ltDH83ChKjwX32AQ3G5hj"; // Enter your Blynk application auth token
char ssid[] = "Galaxy S23 Ultra"; // Enter your WIFI name
char pass[] = "12345678"; // Enter your WIFI password

void setup() {
  Serial.begin(9600);
  
  // Set motor pins as OUTPUT
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Blynk.begin(auth, ssid, pass);
}

BLYNK_WRITE(V0) {
  forward = param.asInt();
}

BLYNK_WRITE(V1) {
  backward = param.asInt();
}

BLYNK_WRITE(V2) {
  left = param.asInt();
}

BLYNK_WRITE(V3) {
  right = param.asInt();
}

BLYNK_WRITE(V4) {
  Speed = param.asInt();
}

void smartcar() {
  if (forward == 1) {
    carforward();
    Serial.println("carforward");
  } else if (backward == 1) {
    carbackward();
    Serial.println("carbackward");
  } else if (left == 1) {
    carturnleft();
    Serial.println("carleft");
  } else if (right == 1) {
    carturnright();
    Serial.println("carright");
  } else if (forward == 0 && backward == 0 && left == 0 && right == 0) {
    carStop();
    Serial.println("carstop");
  }
}

void loop() {
  Blynk.run();
  smartcar();
}

void carforward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);  // Left motor forward
  digitalWrite(IN2, LOW);   // Left motor forward
  digitalWrite(IN3, HIGH);  // Right motor forward
  digitalWrite(IN4, LOW);   // Right motor forward
}

void carbackward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);   // Left motor backward
  digitalWrite(IN2, HIGH);  // Left motor backward
  digitalWrite(IN3, LOW);   // Right motor backward
  digitalWrite(IN4, HIGH);  // Right motor backward
}

void carturnleft() {
  analogWrite(ENA, Speed / 2); // Slow down left motor
  analogWrite(ENB, Speed);     // Right motor at full speed
  digitalWrite(IN1, HIGH);  // Left motor forward
  digitalWrite(IN2, LOW);   // Left motor forward
  digitalWrite(IN3, HIGH);  // Right motor forward
  digitalWrite(IN4, LOW);   // Right motor forward
}

void carturnright() {
  analogWrite(ENA, Speed);     // Left motor at full speed
  analogWrite(ENB, Speed / 2); // Slow down right motor
  digitalWrite(IN1, HIGH);  // Left motor forward
  digitalWrite(IN2, LOW);   // Left motor forward
  digitalWrite(IN3, HIGH);  // Right motor forward
  digitalWrite(IN4, LOW);   // Right motor forward
}

void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); // Stop left motor
  analogWrite(ENB, 0); // Stop right motor
}
