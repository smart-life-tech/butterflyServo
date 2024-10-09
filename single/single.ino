#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN 150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600 // This is the 'maximum' pulse length count (out of 4096)
int smoothDelay = 50;

int servoNum = 0; // The servo you want to control

// Initialize the driver with the I2C address
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void moveServoBackAndForth(int servo)
{
    // Move from 0 to 180 degrees
    for (int angle = 0; angle <= 180; angle++)
    {
        int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
        pwm.setPWM(servo, 0, pulse);
        delay(smoothDelay); // Delay for smooth movement
    }

    // Move from 180 to 0 degrees
    for (int angle = 180; angle >= 0; angle--)
    {
        int pulse = map(angle, 0, 180, SERVOMAX, SERVOMIN);
        pwm.setPWM(servo, 0, pulse);
        delay(smoothDelay); // Delay for smooth movement
    }
}

void setup()
{
    Serial.begin(9600);

    pwm.begin();
    pwm.setPWMFreq(60); // Analog servos run at ~60 Hz updates

    delay(10);
}

void loop()
{
    Serial.println("Moving servo back and forth");
    moveServoBackAndForth(servoNum); // Move the specified servo back and forth
    delay(500);                      // Delay for half a second before repeating
}
