#include <Arduino.h>

#define button 2
#define LED 4
unsigned long debouncing_ms = 0;
unsigned long debouncing_delay = 50;
int input = LOW;
int input_before = LOW;
int val_before = LOW;
int state = 1;
int tepi_naik = LOW;

void state1();
void state2();

void setup()
{
    Serial.begin(115200);
    pinMode(LED, OUTPUT);
    pinMode(button, INPUT_PULLUP);
}

void loop()
{
    int val = digitalRead(button);
    if (val != val_before)
    {
        debouncing_ms = millis();
    }

    if ((millis() - debouncing_ms) > debouncing_delay)
    {
        if (val != input)
        {
            input = val;
        }
    }

    val_before = val;

    if (input == LOW && input_before == HIGH)
    {
        input_before = input;
    }
    else if (input == HIGH && input_before == LOW)
    {
        input_before = input;
        tepi_naik = LOW;
    }

    switch (state)
    {
    case 1:
        state1();
        Serial.println("State 1");
        state1();
        if (tepi_naik == LOW)
        {
            state = 2;
            Serial.println("Moving to state 2");
        }
        break;
    case 2:
        state2();
        Serial.println("State 2");
        if (tepi_naik == LOW)
        {
            state = 1;
            Serial.println("Moving to state 1");
        }
        break;
    }
    tepi_naik = HIGH;
}

void state1()
{
    digitalWrite(LED, HIGH);
    Serial.println("LED on");
}

void state2()
{
    digitalWrite(LED, LOW);
    Serial.println("LED off");
}
