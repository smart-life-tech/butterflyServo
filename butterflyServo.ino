#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN 150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600 // This is the 'maximum' pulse length count (out of 4096)
int smoothDelay = 20;
int intervalDelay = 500;
// Initialize the driver with the I2C address
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
void moveServoForward(int startServo, int endServo)
{
    // Slowly move all servos from 0 to 180 degrees
    for (int angle = 0; angle <= 180; angle++)
    {
        for (int servoNum = startServo; servoNum <= endServo; servoNum++)
        {
            int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
            pwm.setPWM(servoNum, 0, pulse);
        }
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
    Serial.println("moving servo 1 to 11");
    moveServoForward(0, 11); // Move servos 0 to 11 to 180 degrees
    delay(intervalDelay);             // Delay for 1 second
    Serial.println("moving servo 12 to 23 forward");
    moveServoForward(12, 23); // Move servos 12 to 23 to 180 degrees
    delay(intervalDelay);              // Delay for 1 second
    Serial.println("moving servo 12 to 23");
    moveServoBackward(12, 23); // Move servos 12 to 23 from 180 degrees
    delay(intervalDelay);               // Delay for 1 second
    Serial.println("moving servo 0 to 11");
    moveServoBackward(0, 11);  // Move servos 0 to 11
    delay(intervalDelay);               // Delay for 1 second from 180 degrees
}

void moveServoBackward(int startServo, int endServo)
{
    // Reverse the movement (180 to 0 degrees)
    for (int angle = 180; angle >= 0; angle--)
    {
        for (int servoNum = startServo; servoNum <= endServo; servoNum++)
        {
            int pulse = map(angle, 180, 0, SERVOMIN, SERVOMAX);
            pwm.setPWM(servoNum, 0, pulse);
        }
        delay(smoothDelay); // Delay for smooth movement
    }
}
