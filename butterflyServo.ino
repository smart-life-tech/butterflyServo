#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN 150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600 // This is the 'maximum' pulse length count (out of 4096)

// Initialize the driver with the I2C address
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
void moveServoss(int startServo, int endServo)
{
    // Slowly move all servos from 0 to 180 degrees
    for (int angle = 0; angle <= 180; angle++)
    {
        for (int servoNum = startServo; servoNum <= endServo; servoNum++)
        {
            int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
            pwm.setPWM(servoNum, 0, pulse);
        }
        delay(15); // Delay for smooth movement
    }

    // Reverse the movement (180 to 0 degrees)
    for (int angle = 180; angle >= 0; angle--)
    {
        for (int servoNum = startServo; servoNum <= endServo; servoNum++)
        {
            int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
            pwm.setPWM(servoNum, 0, pulse);
        }
        delay(15); // Delay for smooth movement
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
    moveServoss(0, 11);  // Move servos 0 to 11
    delay(1000);         // Delay for 1 second
    moveServoss(12, 23); // Move servos 12 to 23
    delay(1000);         // Delay for 1 second
}

void moveServos(int startServo, int endServo)
{
    for (int servoNum = startServo; servoNum <= endServo; servoNum++)
    {
        // Slowly move the servo from 0 to 180 degrees
        for (int angle = 0; angle <= 180; angle++)
        {
            int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
            pwm.setPWM(servoNum, 0, pulse);
            delay(15); // Delay for smooth movement
        }

        // Reverse the movement (180 to 0 degrees)
        for (int angle = 180; angle >= 0; angle--)
        {
            int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
            pwm.setPWM(servoNum, 0, pulse);
            delay(15); // Delay for smooth movement
        }
    }
}
