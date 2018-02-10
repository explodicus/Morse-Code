#include <string.h>
#include <LiquidCrystal.h> // Library for the LCD display
const int RS = 12, EN = 11, D4 = 3, D5 = 4, D6 = 5, D7 = 6, V0 = 9; // Setting pins for the LCD
LiquidCrystal LCD(RS, EN, D4, D5, D6, D7);  // Initializing the LCD

int ledPin = 2;
int button = 7;
char* dictionary[91]; // Code of each character
char* enWord = "                                                                                                           "; // The word I want to encode
int enLength = 0;
char* currentLetter = "                                                                                                    "; // The code of the current decoded letter
int letterLength = 0;
char* currentWord = "                                                                                                      "; // The decoded word
int wordLength = 0;
int spaceCalc; // Variable to calculate the time between button presses
int mode; // 0 - Decoding 1 - Encoding
bool fin = false;
int unit = 200;

void createDictionary()
{
  dictionary[65] = ".-";
  dictionary[66] = "-...";
  dictionary[67] = "-.-.";
  dictionary[68] = "-..";
  dictionary[69] = ".";
  dictionary[70] = "..-.";
  dictionary[71] = "--.";
  dictionary[72] = "....";
  dictionary[73] = "..";
  dictionary[74] = ".---";
  dictionary[75] = "-.-";
  dictionary[76] = ".-..";
  dictionary[77] = "--";
  dictionary[78] = "-.";
  dictionary[79] = "---";
  dictionary[80] = ".--.";
  dictionary[81] = "--.-";
  dictionary[82] = ".-.";
  dictionary[83] = "...";
  dictionary[84] = "-";
  dictionary[85] = "..-";
  dictionary[86] = "...-";
  dictionary[87] = ".--";
  dictionary[88] = "-..-";
  dictionary[89] = "-.--";
  dictionary[90] = "--..";
  dictionary[48] = "-----";
  dictionary[49] = ".----";
  dictionary[50] = "..---";
  dictionary[51] = "...--";
  dictionary[52] = "....-";
  dictionary[53] = ".....";
  dictionary[54] = "-....";
  dictionary[55] = "--...";
  dictionary[56] = "---..";
  dictionary[57] = "----.";
}

void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
  createDictionary();
  analogWrite(V0, 100); // For the LCD
  LCD.begin(16,2);
  LCD.print("   Morse Code   ");
  LCD.setCursor(0,1);
  LCD.print(" Encoder/Decoder");
  delay(2000);
  LCD.clear();
}

char interpret(int startTime) // Dash or dot
{
  int val = LOW; // button Value
  while (val != HIGH)
    val = digitalRead(button);
  startTime = millis() - startTime;
  if (startTime == 0)
    return 'f';
  if (startTime <= unit)
    return '.';
  return '-';
}

int deCode() // Code to Letter
{
  for (int i = 65; i<= 90; i++)
    if (strcmp(currentLetter,dictionary[i]) == 0)
      return i;
  for (int i = 48; i<= 57; i++)
    if (strcmp(currentLetter,dictionary[i]) == 0)
      return i;      
  return -1;
}

void code(char chr)
{
  int index = (int)chr;
  //Serial.println(index);
  if (index == 32)
  {
    delay(unit*7);
    return;
  }
  int i = 0;
  Serial.println(dictionary[index][i]);
  while (dictionary[index][i] != '\0')
  {
    
    if (dictionary[index][i] == '-')
    {
      digitalWrite(ledPin,HIGH);
      delay(unit*3);
      digitalWrite(ledPin,LOW);
      delay(unit);
    }
    else
    {
      digitalWrite(ledPin,HIGH);
      delay(unit);
      digitalWrite(ledPin,LOW);
      delay(unit);
    }
    i++;
  }
  delay(unit*2);
}


void loop()
{
  spaceCalc = 30000;
  Serial.println(spaceCalc);
  LCD.print("LP for decoding");
  LCD.setCursor(0,1);
  LCD.print("SP for encoding");
  int val = digitalRead(button);  // button value
  while (val == HIGH)
    val = digitalRead(button);
  int startTime = millis();
  while (val != HIGH)
    val = digitalRead(button);
  startTime = millis() - startTime; // calculates the length of the press
  if (startTime <= 300)
    mode = 1;
  else
    mode = 0;
  LCD.clear();
  if (mode == 0)
    while (!fin)
    {
      val = digitalRead(button);
      while (val == HIGH)
        val = digitalRead(button);
      startTime = millis();
      if (startTime - spaceCalc > 10000)
      {
        Serial.println("END");
        Serial.println(startTime);
        Serial.println(spaceCalc);
        fin = true;
        break;
      }  
      if (startTime - spaceCalc > unit * 3)
      {
        int letterCode = deCode();
        if (letterCode != -1)
        {
          currentWord[wordLength] = (char)letterCode;
          wordLength++;
          currentWord[wordLength] = '\0';
        }
        LCD.clear();
        LCD.print(currentWord);
        currentLetter = "";
        letterLength = 0;
      }
      if (startTime - spaceCalc > unit * 7)
      {
        currentWord[wordLength] = ' ';
        wordLength++;
        currentWord[wordLength] = '\0';
        currentLetter = "";
        letterLength = 0;
      }
      char currentCharacter = interpret(startTime);
  
      if (currentCharacter != 'f')
      {
        currentLetter[letterLength] = currentCharacter;
        letterLength++;
        currentLetter[letterLength] = '\0';
      }
      //Serial.println(currentWord);
      //Serial.println(currentLetter);
      spaceCalc = millis();
    }
  else
  {
    LCD.print("Input Word");
    char chr = 0;
    while (Serial.available() <= 0)
      int t;    
    while (chr != '\n')
    {
      if (Serial.available() > 0) 
      {
        chr = Serial.read();       // get the character
        if (chr != '\n') 
        {
          enWord[enLength] = chr;
          enLength++;
          enWord[enLength] = '\0';
        }
      } 
    }
    LCD.clear();
    LCD.print(enWord);
    int i;
    for (int i = 0; i<enLength; i++)
      code(enWord[i]);
    LCD.clear();
  }
}
 
