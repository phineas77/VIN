
char trig1='a';
char trig2='b';
char trig3='c';
char trig4='d';
int tmpPin = A1;  //*TMP36 temp senzor na analogni pin
double temp;	  //* temperatura
double tempC;     //*temperatura in Celziusima
  
void setup() 
{
  pinMode(tmpPin, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  temp = analogRead(tmpPin);
  temp  = temp / 1024; 
  temp  = temp * 5;    
  temp  = temp - 0.5;  
  tempC = temp * 100;  //*stepen celzijusa 
  
  Serial.print(tempC);
  Serial.print("\xB0");
  Serial.println("C");

  if (tempC<15)
  {
    Serial.write(trig1);
  }
  else if (tempC>=15 & tempC<30)
  {
    Serial.write(trig2);
  }
  else if (tempC>=30 & tempC<70)
  {
    Serial.write(trig3);
  }
  else
  {
    Serial.write(trig4);
  }  
  delay(2000);
}