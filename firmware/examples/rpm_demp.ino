#include "FreqPeriodCounter/FreqPeriodCounter.h"

const int simulated_fan_output_pin = A0;
const int counter_interrupt_pin = D4; 

FreqPeriodCounter counter(counter_interrupt_pin, micros, 0);

const int k_seconds_per_minute = 60;
const int k_pulses_per_revolution = 2;
const int k_hertz_to_RPM_conversion_factor = k_seconds_per_minute / k_pulses_per_revolution;

void setup(void) 
{
    Serial.begin(9600);
    Serial.println("Computer fan RPM Demo");
    
    pinMode(simulated_fan_output_pin, OUTPUT);
    analogWrite(simulated_fan_output_pin, 128); // any number here should create a 500Hz frequency
    
    pinMode(counter_interrupt_pin, INPUT);
    attachInterrupt(counter_interrupt_pin, counter_interrupt_service_routine, CHANGE);
    
}

void loop() 
{
    int period;
    long hertz;
    int RPM;
    
    if(counter.ready()) {
        period = counter.period;
        hertz = counter.hertz();
        RPM = hertz * k_hertz_to_RPM_conversion_factor;
        
        
        Serial.print("Period: ");
        Serial.print(period);
        Serial.print("\t");
        
        Serial.print("Hertz: ");
        Serial.print(hertz);
        Serial.print("\t");
        
        Serial.print("RPM: ");
        Serial.print(RPM);
        Serial.print("\t");
        
        Serial.println();
        
    }
    else {
        Serial.print(".");
    }
}

void counter_interrupt_service_routine()
{ 
    counter.poll();
}

