/* Quiz Kid Calculator clone

References used during devolpment:
Example 42.3 - Numeric keypad and I2C LCD
http://tronixstuff.wordpress.com/tutorials > chapter 42a

http://www.arduino.cc/playground/Code/Keypad
   by Mark Stanley, Alexander Brevig 
*/

/*Version History

0.1 2012-12-17 - James R. Bundick: Reading of membrane 4x4 keypad

*/

#include "Keypad.h"

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] =
 {{'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','?'},
  {'C','0','.','='}};
byte rowPins[ROWS] = {
  2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {
  6, 7, 8, 9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int x;
int y;
int z;
int i;
int j;

String stringOne, stringTwo, stringThree;

void setup()
{
  Serial.begin(9600);
  stringOne = String ();
  stringTwo = String ();
  stringThree = String ();
  i = 0;
}

void loop()
{
  char key = keypad.getKey();
  
  if (key != NO_KEY)
  {
    if (i == 0)
    {
      if (key != '+')
      {
        stringOne = stringOne + key;
      }
    }

    if (i == 1)
    {
      if (key != '+')
      {
        stringTwo = stringTwo + key;
      }
    }

    
    if (key == '+')
    {
      Serial.println ("plus");
      i = 1;
      j = 1;
    }
     Serial.print(key);
     Serial.println ("\n\nString1 = ");
     Serial.println (stringOne);
     Serial.println ("\n\nString2 = ");
     Serial.println (stringTwo);

     if (key == 'C')
    {
      Serial.println ("cleared");
      stringOne = String ();
      stringTwo = String ();
      stringThree = String ();
      i = 0;
      j = 0;
    }

  }
}
