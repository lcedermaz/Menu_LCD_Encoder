#define Led_ROJO 4 
#define Led_VERDE 5 


const int channelPinA = 2;
const int channelPinB = 3;

const int timeThreshold = 5;
long timeCounter = 0;
 
const int maxSteps = 255;
volatile int ISRCounter = 0;
int counter = 0;
 
bool IsCW = true;
 
void setup()
{
   pinMode(Led_ROJO, OUTPUT);
   pinMode(Led_VERDE, OUTPUT); 
   pinMode(channelPinA, INPUT_PULLUP);
  
   Serial.begin(9600);
   attachInterrupt(digitalPinToInterrupt(channelPinA), doEncodeA, CHANGE);
   attachInterrupt(digitalPinToInterrupt(channelPinB), doEncodeB, CHANGE);
}
 
void loop()
{
   if (counter != ISRCounter)
   {
      counter = ISRCounter;
      Serial.println(counter);
   }
  
  if( counter != ISRCounter) {
    if (IsCW == true){
    digitalWrite (Led_ROJO, HIGH);
    digitalWrite (Led_VERDE, LOW);   
    delay(1000);
 } else {
  
   digitalWrite (Led_ROJO, HIGH);
   digitalWrite (Led_VERDE, HIGH);  
   delay(1000);
}
   
   digitalWrite (Led_ROJO, LOW);
   digitalWrite (Led_VERDE, LOW); 
   counter = ISRCounter;
   delay(10);
}
} 
void doEncodeA()
{
   if (millis() > timeCounter + timeThreshold)
   {
      if (digitalRead(channelPinA) == digitalRead(channelPinB))
      {
         IsCW = true;
        
         if (ISRCounter + 1 <= maxSteps) ISRCounter++;
      }
      else
      {
         IsCW = false;
         if (ISRCounter - 1 > 0) ISRCounter--;
      }
      timeCounter = millis();
   }
}
 
void doEncodeB()
{
   if (millis() > timeCounter + timeThreshold)
   {
      if (digitalRead(channelPinA) != digitalRead(channelPinB))
      {
         IsCW = true;
         if (ISRCounter + 1 <= maxSteps) ISRCounter++;
      }
      else
      {
         IsCW = false;
         if (ISRCounter - 1 > 0) ISRCounter--;
      }
      timeCounter = millis();
   }
}
