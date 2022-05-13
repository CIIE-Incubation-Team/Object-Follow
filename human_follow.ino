#include <Servo.h>
#define RIGHT 13
#define LEFT 12
#define trigpin 8
#define echopin 7

const int MOTOR1 = 5;
const int MOTOR2 = 6;
const int MOTOR3 = 9;
const int MOTOR4 = 10;

const int GO = 225;
const int NO = 0;

Servo myservo;

int pos = 0;
long time;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    myservo.attach(10);

    for (pos = 90; pos <= 160; pos += 1)
    {
        myservo.write(pos);
        delay(15);
    }

    for (pos = 160; pos >= 0; pos -= 1)
    {
        myservo.write(pos);
        delay(15);
    }

    for (pos = 0; pos <= 90; pos += 1)
    {
        myservo.write(pos);
        delay(15);
    }

    pinMode(RIGHT, INPUT);
    pinMode(LEFT, INPUT);

    pinMode(trigpin, OUTPUT);
    pinMode(echopin, INPUT);
}

void loop()
{
    unsigned int distance = read_cm();

    int Right_Value = digitalRead(RIGHT);
    int Left_Value = digitalRead(LEFT);

    Serial.print("R= ");
    Serial.print(Right_Value);
    Serial.print(" L= ");
    Serial.print(Left_Value);
    Serial.print(" D= ");
    Serial.println(distance);

    if ((Right_Value == 1) && (distance >= 10 && distance <= 30) && (Left_Value == 1))
    {
        forward();
    }
    else if ((Right_Value == 0) && (Left_Value == 1))
    {
        turnRight();
    }
    else if ((Right_Value == 1) && (Left_Value == 0))
    {
        turnLeft();
    }
    else if ((Right_Value == 1) && (Left_Value == 1))
    {
        stop();
    }
    else if (distance > 6 && distance < 10)
    {
        stop();
    }
    else if (distance < 6)
    {
        backward();
    }

    delay(50);
}

long read_cm()
{
    digitalWrite(trigpin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigpin, HIGH);
    delayMicroseconds(10);
    time = pulseIn(echopin, HIGH);
    return time / 29 / 2;
}

void forward()
{ // turn it on going forward
    analogWrite(5,125);
    analogWrite(6,125);
    digitalWrite(MOTOR1,HIGH);
    digitalWrite(MOTOR2,LOW);
    digitalWrite(MOTOR3,HIGH);
    digitalWrite(MOTOR4,LOW);
}

void backward()
{ // the other way
    analogWrite(5,125);
    analogWrite(6,125);
    digitalWrite(MOTOR1,LOW);
    digitalWrite(MOTOR2,HIGH);
    digitalWrite(MOTOR3,LOW);
    digitalWrite(MOTOR4,HIGH);
}

void turnRight()
{ // the other right
    analogWrite(5,125);
    analogWrite(6,125);
    digitalWrite(MOTOR1,HIGH);
    digitalWrite(MOTOR2,LOW);
    digitalWrite(MOTOR3,LOW);
    digitalWrite(MOTOR4,HIGH);

}

void turnLeft()
{ // turn it on going left
    analogWrite(5,125);
    analogWrite(6,125);
    digitalWrite(MOTOR1,LOW);
    digitalWrite(MOTOR2,HIGH);
    digitalWrite(MOTOR3,HIGH);
    digitalWrite(MOTOR4,LOW);
}

void stop()
{ // stopped
    analogWrite(5,125);
    analogWrite(6,125);
    digitalWrite(MOTOR1,LOW);
    digitalWrite(MOTOR2,LOW);
    digitalWrite(MOTOR3,LOW);
    digitalWrite(MOTOR4,LOW);
}