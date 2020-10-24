
#define _PIN 5
bool turnedOn = false;

void setup()
{
  pinMode(_PIN,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 0)
  {
    char input = Serial.read();
    switch (input)
    {
      case 'B':
        digitalWrite(_PIN, HIGH);
        delay(100);
        digitalWrite(_PIN, LOW);
        delay(100);
        digitalWrite(_PIN, HIGH);
        delay(100);
        digitalWrite(_PIN, LOW);
        delay(100);
        break;
      case 'T':
        if(turnedOn) 
        {
          digitalWrite(_PIN, LOW);
          delay(100);
          turnedOn=false;
        }
        else
        {
          digitalWrite(_PIN, HIGH);
          delay(100);
          turnedOn=true;
        }
        break;
    }
  }
  delay(500);
}
