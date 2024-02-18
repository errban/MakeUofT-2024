
#include "Servo.h"
#define NOTE_B0 31




#define NOTE_C1 33




#define NOTE_CS1 35




#define NOTE_D1 37




#define NOTE_DS1 39




#define NOTE_E1 41




#define NOTE_F1 44




#define NOTE_FS1 46




#define NOTE_G1 49




#define NOTE_GS1 52




#define NOTE_A1 55




#define NOTE_AS1 58




#define NOTE_B1 62




#define NOTE_C2 65




#define NOTE_CS2 69




#define NOTE_D2 73




#define NOTE_DS2 78




#define NOTE_E2 82




#define NOTE_F2 87




#define NOTE_FS2 93




#define NOTE_G2 98




#define NOTE_GS2 104




#define NOTE_A2 110




#define NOTE_AS2 117




#define NOTE_B2 123




#define NOTE_C3 131




#define NOTE_CS3 139




#define NOTE_D3 147




#define NOTE_DS3 156




#define NOTE_E3 165




#define NOTE_F3 175




#define NOTE_FS3 185




#define NOTE_G3 196




#define NOTE_GS3 208




#define NOTE_A3 220




#define NOTE_AS3 233




#define NOTE_B3 247




#define NOTE_C4 262




#define NOTE_CS4 277




#define NOTE_D4 294




#define NOTE_DS4 311




#define NOTE_E4 330




#define NOTE_F4 349




#define NOTE_FS4 370




#define NOTE_G4 392




#define NOTE_GS4 415




#define NOTE_A4 440




#define NOTE_AS4 466




#define NOTE_B4 494




#define NOTE_C5 523




#define NOTE_CS5 554




#define NOTE_D5 587




#define NOTE_DS5 622




#define NOTE_E5 659




#define NOTE_F5 698




#define NOTE_FS5 740




#define NOTE_G5 784




#define NOTE_GS5 831




#define NOTE_A5 880




#define NOTE_AS5 932




#define NOTE_B5 988




#define NOTE_C6 1047




#define NOTE_CS6 1109




#define NOTE_D6 1175




#define NOTE_DS6 1245




#define NOTE_E6 1319




#define NOTE_F6 1397




#define NOTE_FS6 1480




#define NOTE_G6 1568




#define NOTE_GS6 1661




#define NOTE_A6 1760




#define NOTE_AS6 1865




#define NOTE_B6 1976




#define NOTE_C7 2093




#define NOTE_CS7 2217




#define NOTE_D7 2349




#define NOTE_DS7 2489




#define NOTE_E7 2637




#define NOTE_F7 2794




#define NOTE_FS7 2960




#define NOTE_G7 3136




#define NOTE_GS7 3322




#define NOTE_A7 3520




#define NOTE_AS7 3729




#define NOTE_B7 3951




#define NOTE_C8 4186




#define NOTE_CS8 4435




#define NOTE_D8 4699




#define NOTE_DS8 4978




#define END -1


// Define pins for servo motor control
const int servoPin = 9; // Servo motor pin


// Define pins for ultrasonic sensor
const int trigPin = 11;
const int echoPin = 12;


// Define pins for LEDs
const int greenLedPin = 13; // Green LED pin
const int redLedPin = 10;   // Red LED pin


// Define pins for force sensor
#define FORCE_SENSOR_PIN A0


// Define melody for the speaker
int melody[] = {
    NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_A4,
    NOTE_G4, NOTE_C5, NOTE_AS4, NOTE_A4,
    NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_FS4, NOTE_DS4, NOTE_D4,
    NOTE_C4, NOTE_D4, END
};


// Define note durations
int noteDurations[] = {
    8, 4, 8, 4,
    4, 4, 4, 12,
    4, 4, 4, 4, 4, 4,
    4, 16, 4
};


// Define servo object
Servo myservo;


void setup() {
    Serial.begin(9600);
    pinMode(servoPin, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(greenLedPin, OUTPUT);
    pinMode(redLedPin, OUTPUT);
    myservo.attach(servoPin);
}


void loop() {
    int forceSensorReading = analogRead(FORCE_SENSOR_PIN);
    Serial.print("Force sensor reading = ");
    Serial.println(forceSensorReading);


    if (forceSensorReading > 10) { // Check if force is greater than threshold
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);


        float duration = pulseIn(echoPin, HIGH);
        float distance = (duration * 0.0343) / 2;


        Serial.print("Distance: ");
        Serial.println(distance);


        if (distance < 20) {
            digitalWrite(greenLedPin, HIGH);
            digitalWrite(redLedPin, LOW);


            for (int i = 0; melody[i] != END; i++) {
                int noteDuration = 1000 / noteDurations[i];
                tone(3, melody[i], noteDuration);
                myservo.write(90); // Rotate servo to open position
                delay(noteDuration);
                noTone(3);
            }
        } else {
            digitalWrite(greenLedPin, LOW);
            digitalWrite(redLedPin, HIGH);
            myservo.write(0); // Rotate servo to closed position
        }
    } else {
        digitalWrite(greenLedPin, LOW);
        digitalWrite(redLedPin, LOW);
        myservo.write(0); // Rotate servo to closed position
    }


    delay(1000);
}
