#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4); 

#include <RotaryEncoder.h>


RotaryEncoder encoder(3,4); // Pines de seleccion del encoder

int value = 0;

byte full[8]  = {0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
                                                                    
byte one[8] = {0b11011, 0b10011, 0b11011, 0b11011, 0b11011, 0b11011, 0b10001, 0b11111}; // Sombra de los valores seleccionados
                     
byte two[8] = {0b10001, 0b01110, 0b11110, 0b11101,0b11011, 0b10111, 0b00000, 0b11111};
                     
byte three[8] =  {0b00000, 0b11101, 0b11011, 0b11101,0b11110, 0b01110, 0b10001, 0b11111};
                   
byte four[8] = {0b11101, 0b11001, 0b10101, 0b01101, 0b00000, 0b11101, 0b11101, 0b11111};
                          
byte five[8] = {0b00000, 0b01111, 0b00001, 0b11110,0b11110, 0b01110, 0b10001, 0b11111 };
                          
byte six[8] = {0b11001, 0b10111, 0b01111, 0b00001,0b01110, 0b01110, 0b10001, 0b11111};
                         
                          
static int pos = 1;
int newPos = 0;
int selected = 0;

void setup()
{
  
  pinMode(12, INPUT_PULLUP);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);

  
  lcd.init();
  lcd.backlight();
  //lcd.begin(20, 4);
  lcd.createChar(0, full);
  lcd.createChar(1, one);
  lcd.createChar(2, two);
  lcd.createChar(3, three);
  lcd.createChar(4, four);
  lcd.createChar(5, five);
  lcd.createChar(6, six);

  lcd.setCursor(0, 0);
  lcd.print("  1  2  3  4  5  6  ");
  lcd.setCursor(0, 2);
  lcd.print("Valor actual: ");
 lcd.setCursor(0, 3);
 lcd.print("Seleccionado: ");

}

void loop()
{
  value = digitalRead(12);
  if (value == LOW)
  {
    lcd.setCursor(13, 3);
    selected = newPos;
   lcd.print(selected);
  }
  encoder.tick();
  newPos = encoder.getPosition();
  if (pos != newPos)
  {
    
    if (newPos > 6)
    {
      encoder.setPosition(6);
      newPos = 6;
    }
  
    if (newPos < 1)
    {
      encoder.setPosition(1);
      newPos = 1;
    }
   
    highlightedSelection(newPos);
    pos = newPos; 
  }
}

void highlightedSelection(int count)
{
  
  int present = (count * 3) - 1;
  if (count > pos)
  {
    lcd.setCursor(present - 4, 0);
    lcd.print(" ");
    lcd.print(count - 1);
    lcd.print(" ");
  }
  if (count < pos)
  {
    lcd.setCursor(present + 2, 0);
    lcd.print(" ");
    lcd.print(count + 1);
    lcd.print(" ");
  }

  
  lcd.setCursor(present - 1, 0);
  lcd.write((uint8_t)0);
  lcd.write((uint8_t)0);
  lcd.write((uint8_t)0);

  
  lcd.setCursor(present, 0);
  lcd.write((uint8_t)count);

  
  lcd.setCursor(15, 2);
  lcd.print(count);
}
