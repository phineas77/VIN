
char input;
int wLED = 4;
int rLED = 5;
int yLED = 6;
int gLED = 7;

void blink(int LEDpin, char Array[7]) 
{
  digitalWrite(LEDpin, HIGH); //*LED on
  Serial.println(Array);
  delay(1000);
  digitalWrite(LEDpin, LOW); //*LED off
}

void setup() 
{
  pinMode(wLED, OUTPUT);
  pinMode(rLED, OUTPUT);
  pinMode(yLED, OUTPUT);
  pinMode(gLED, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  {
    input=Serial.read(); 
    if(input=='a')
    {
      blink(wLED,"cold");
    }
    if(input=='b')
    {
      blink(gLED,"normal");
    }
    if(input=='c')
    {
      blink(yLED,"alert!"); 
    }
    if(input=='d')
    {
      blink(rLED,"danger");
    }
  }    
}


