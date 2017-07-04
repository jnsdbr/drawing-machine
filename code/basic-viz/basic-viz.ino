#include <AccelStepper.h>
#include <Servo.h>
#define HALFSTEP 8

int counter = 0;
unsigned long timeout = 0;
boolean resetClock = false;

// Motor pin definitions
#define motorPin1  6     // IN1 on the ULN2003 driver 1
#define motorPin2  7     // IN2 on the ULN2003 driver 1
#define motorPin3  8     // IN3 on the ULN2003 driver 1
#define motorPin4  9     // IN4 on the ULN2003 driver 1

AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
Servo servo;

void setup()
{
  stepper1.setMaxSpeed(2000.0);
  stepper1.setAcceleration(500.0);
  stepper1.setSpeed(2000);

  servo.attach(10);
  servo.write(0);
}

void loop()
{
  if (stepper1.distanceToGo() == 0 && timeout < millis())
  {
    int pos = counter * 68;
    stepper1.moveTo(pos);
    servo.write(map(analogRead(A1), 400, 1000, 0, 45));

    if (resetClock)
    {
      resetClock = false;
      timeout = millis() + 10000;
    }
    else
    {
      timeout = millis() + 1000;
    }

    counter++;

    if (pos >= 4012)
    {
      counter = 0;
      resetClock = true;
    }
  }
  stepper1.run();
}
