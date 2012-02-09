// This is the motor controller code.
// We send PWM commands to our H-Bridges to control forward/backward motion.
// See http://arduino.cc/en/Tutorial/PWM for PWM information.
// TODO: figure out a way to jump the serial queue for emergency stop

#include "motor.h"

// left motor
int HighPin_left     = 2; // always keep this one high
int DisablePin_left  = 4; // disables the h bridges, usually keep this low
int ForwardPin_left  = 3;
int BackwardPin_left = 5;

// right motor
int HighPin_right     = 13; // always keep this one high
int DisablePin_right  = 12; // disables the h bridges, usually keep this low
int ForwardPin_right  = 11;
int BackwardPin_right = 10;


void raise_exception(String message) {
    // since there are no exceptions in Arduino-land, make my own fake exception
    // to send back to the user
    Serial.println(message);
}

void setup()  {
    Serial.begin(9600);
}


Motor left_motor(HighPin_left, DisablePin_left, ForwardPin_left, BackwardPin_left);
Motor right_motor(HighPin_right, DisablePin_right, ForwardPin_right, BackwardPin_right);

MotorIterator motor_iterator(left_motor, right_motor);

void loop() {
    // only read when available

    if (Serial.available() > 0) {
        motor_iterator.run(Serial.read(), Serial.read());
    }
}
