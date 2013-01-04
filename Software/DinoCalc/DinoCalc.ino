/* Quiz Kid Calculator clone
by James R. Bundick 
Arduino IDE 1.0.3
Released under license:  (Note to self, find out more on Creative Commons)


This is a clone of a toy I had when younger.  It was a calculator that did not have
a LCD display but instead had an owl sticker on the front with two LED lights, 
one green and one red.  You would enter a math problem on the button keypad with 
what you thought the correct answer was, ie, 12 + 12 = 24, and then press the "?" key.  
If your answer was right the green LED would light up, if your answer was wrong, 
the red LED would light up.

I believe this will be a great way for my preschool son to check his simple
arithmatic without having a calculator just give him the answer.

For now the objective is to create a calculator capable of just adding and 
subtracting whole numbers.  Future objectives will be to replace the Arduino UNO
with a custom made PCB and to add multiplication and division to the calculator's 
capabilities as well as allow for decimals.  Code could also be used for a
"math" type game.  For example, Enter problem with answer and if right move away from some
peril (like a chomping dinosaur) and if wrong move closer to peril.  Loser is the one
that gets eaten (chomp,chomp,chomp).

References used during devolpment:
1)  http://tronixstuff.wordpress.com/tutorials > chapter 42a
2)  http://www.arduino.cc/playground/Code/Keypad by Mark Stanley, Alexander Brevig 
3)  "Arduino Cookbook", 2nd edition, by Michael Margolis
4)  "BlinkWithoutDelay" example by David A. Mellis and Paul Soffregen with Arduino IDE 1.0.3 

Bill of Material:
1)  Arduino UNO board
2)  4x4 Matrix keypad
3)  Red LED
4)  Green LED
5)  220 ohm resistor
6)  220 ohm resistor

Hardware layout:
Keypad:  4x4 Matrix Membrane keypad purchased on Amazon.com
          
          1  2  3  A 
          4  5  6  B
          7  8  9  C
          *  0  #  D
          
         Each Row and Each Column connects to a PIN for total of 8 pins.
         Row 1 >> Pin 1      Column 1 >> Pin 5
         Row 2 >> Pin 2      Column 2 >> Pin 6
         Row 3 >> Pin 3      Column 3 >> Pin 7
         Row 4 >> Pin 4      Column 4 >> Pin 8

Arduino pin 2 ---> 4x4 keypad pin 1
Arduino pin 3 ---> 4x4 keypad pin 2
Arduino pin 4 ---> 4x4 keypad pin 3
Arduino pin 5 ---> 4x4 keypad pin 4
Arduino pin 6 ---> 4x4 keypad pin 5
Arduino pin 7 ---> 4x4 keypad pin 6
Arduino pin 8 ---> 4x4 keypad pin 7
Arduino pin 9 ---> 4x4 keypad pin 8
Arduino pin 10 ---> (long leg)RED LED(short leg) ---> 220 ohm resistor ---> GND
Arduino pin 11 ---> (long leg)GRN LED(short leg) ---> 220 ohm resistor ---> GND


Software Logic

1) Number1 operator Number2 equals User Inputed Answer
  (eg, 12 + 12 = 24)
2) If User Inputed Answer is equal to Calculated Answer
    then light green LED
3) If User Inputed Answer is not equal to Calculated Answer
    then light red LED

Version History

0.4c 2012-12-22 - JRB:  WORKING VERSION of adding and subtracting whole numbers only.  Negative number adding and
                        subtracting is also supported.  Minus key can be used for negative numbers now, 
                        not just subtraction (ie, can now enter "-3 + -5 = -8).
           
0.4b 2012-12-21 - JRB: Added condition to prevent "?" from giving false "correct"

0.4 2012-12-19 - JRB: Added more information to program description.  Added comparison of user entered answer to calculated answer.
                      Added Green and Red LED code for correct and wrong answer results.  Changed code to allow negative number answers.
                      

0.3 2012-12-18 - JRB: Corrected minor string issue with equal sign attaching to stringOne after calculation.
                      Cleaned up serial commands for debugging.

0.2 2012-12-17 - JRB: Worked on code to add multi-digit numbers instead of single digit numbers by doing 
                      conversion of strings to integers.

0.1 2012-12-17 - James R. Bundick: Got Code working to read key presses of membrane 4x4 keypad.  Serial print commands
                                   added for debugging and will be commented out when code is stable.

*/

#include "Keypad.h"

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] =
 {{'1','2','3','+'},                      //Sticker will be applied over keypad to match the layout I want
  {'4','5','6','-'},                      //and to provide a custom graphic (eg dinosaur, bird, etc)
  {'7','8','9','?'},                      //
  {'C','0','.','='}};                     // 
byte rowPins[ROWS] = {
  2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {
  6, 7, 8, 9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const int ledGRN = 11;  //Arduino pin for Green LED
const int ledRED = 10;  //Arduino pin for Red LED

long previousMillis = 0;
long interval = 3000;  //maximum time to leave LED HIGH (on)

int x; //first number that was entered
int y; //second number that was entered
int z; //calculated answer
int z2; //answer that was entered
int i;  //placeholder for operator (i=1 for addition, i=2 for subtraction)
int j;  //used to indicate to program that it is time for the user to input an answer

String stringOne, stringTwo, stringThree, stringFour;  //Place Holders for Numbers that are entered into calculator,
                                                       //ie, Number1 operator Number2 = Answer
                                                       //stringOne holds Number1, stringTwo holds Number2, and stringFour holds Answer 
                                                       //          entered by user
                                                       //stringThree is used to show operator and if equal has been pressed.

void setup()
{
  Serial.begin(9600);

  pinMode (ledGRN, OUTPUT);
  pinMode (ledRED, OUTPUT);
  
  stringOne = String ();
  stringTwo = String ();
  stringThree = String ();
  stringFour = String ();
      x = 0;
      y = 0;
      z = 0;
      z2 = 0;
      i = 0;
      j = 0;
}

void loop()
{
  unsigned long currentMillis = millis();              //Make sure LED doesn't stay continuously on, but allow the code to 
  if(currentMillis - previousMillis > interval)        //continue without a delay.
  {                                                    //
    digitalWrite (ledGRN, LOW);                        //
    digitalWrite (ledRED, LOW);                        //
  }


  char key = keypad.getKey();
  switch (key)
  {
    case 'C':    //If 'C' is pressed then clear calculator
  for (int k=0; k <5; k++) 
  {
    digitalWrite (ledGRN, HIGH);
    digitalWrite (ledRED, HIGH);
    delay (50);
    digitalWrite (ledGRN, LOW);
    digitalWrite (ledRED, LOW);
    delay (50);
  }   
      clearCalc();
      break;
    
    case '?':    //Calculate answer and compare it to the answer that was entered by the user
      if (j == 3)
      {
      calcAnswer();
      }
      else
      {
        stringThree = "ERROR";  //if equal is pressed too soon, error out
        printInfo();
        showError();
        clearCalc();
      }
      break;
    
    case '=':    //Get ready for the answer to be entered by user
      if (j == 2)
      {
        j = 3;  
        stringThree = stringThree + key;
        printInfo();
      }    
      else
      {
        stringThree = "ERROR";  //if equal is pressed too soon, error out
        printInfo();
        showError();
        clearCalc();
      }
      break;

    case '+':
      if (i == 0)
      {
        i = 1;  //i = 1 to denote addition
        j = 1;  //j = 1 to indicate operator has been pressed, now get Number2
        stringThree = stringThree + key;
        printInfo();
      }    
      else
      {
        stringThree = "ERROR"; //if plus or minus is pressed multiple times, error out
        printInfo();
        showError();
        clearCalc();
      }
      break;
  
    case '-':
      if (i == 0)
      {
        if (stringOne == "")
        {
          stringOne = stringOne + key;
        }
        else
        {
          i = 2;  //i = 2 to denote subtraction
          j = 1;  //j = 1 to indicate operator has been pressed, now get Number2
          stringThree = stringThree + key;
        }
        printInfo();  
      }    
      else
      {
        if (j == 3 && stringFour == "")
        {
          stringFour = stringFour + key;
          printInfo();
        }
        else
        {
          if (stringTwo == "")
          {
            stringTwo = stringTwo + key;
            printInfo();
          }
          else
          {
            stringThree = "ERROR";  //if plus or minus is pressed multiple times, error out
            printInfo();
            showError();
            clearCalc();
          }
        }
      }
      break;
  
   /* case '.':
        stringThree = "ERROR";  //if equal is pressed too soon, error out
        printInfo();
        showError();
        clearCalc();
    break;
*/

    default:

      if (key != NO_KEY)
      {
        digitalWrite (ledGRN, LOW);
        digitalWrite (ledRED, LOW);

        if (i == 0)
        {
            stringOne = stringOne + key;
        }

        if ((i == 1 || i == 2) && j != 3)
        {
            stringTwo = stringTwo + key;
            j = 2;
        }

        if (j == 3)
        {
          stringFour = stringFour + key;
        }
        
        printInfo();
    
    }
  }
}

void calcAnswer ()
{
  x = stringOne.toInt();
  y = stringTwo.toInt();
  z2 = stringFour.toInt();
  if (i == 1)
  {
    z = x + y;
    stringThree = " + ";
  }
  if (i == 2)
  {
    z = x - y;
    stringThree = " - ";
  }

    Serial.print ("\nCalculated answer:");
    Serial.print (x);
    Serial.print (stringThree);
    Serial.print (y);
    Serial.print (" = ");
    Serial.print (z);
    Serial.print ("\nEntered answer:");
    Serial.print (x);
    Serial.print (stringThree);
    Serial.print (y);
    Serial.print (" = ");
    Serial.print (z2);
 if (z == z2)
 {
   Serial.print ("\nCORRECT!!!");
    digitalWrite (ledGRN, HIGH);
    digitalWrite (ledRED, LOW);
    previousMillis = millis();   
 }
else
{
   Serial.print ("\nWRONG!!!");
    digitalWrite (ledGRN, LOW);
    digitalWrite (ledRED, HIGH);
    previousMillis = millis();   
}
clearCalc();

}

void printInfo ()
{
     Serial.print ("\nString1 : ");
     Serial.println (stringOne);
     Serial.print ("\nString2 : ");
     Serial.println (stringTwo);
     Serial.print ("\nString3 : ");
     Serial.println (stringThree);
     Serial.print ("\nString4 : ");
     Serial.println (stringFour);
}

void clearCalc()
{
      Serial.println ("\ncleared\n\n\n");

      stringOne = "";
      stringTwo = "";
      stringThree = "";
      stringFour = "";
      x = 0;
      y = 0;
      z = 0;
      z2 = 0;
      i = 0;
      j = 0;
      
     char key = NO_KEY;
}

void showError()
{
  for (int k=0; k <10; k++) 
  {
    digitalWrite (ledGRN, LOW);
    digitalWrite (ledRED, HIGH);
    delay (50);
    digitalWrite (ledGRN, LOW);
    digitalWrite (ledRED, LOW);
    delay (50);
  }   
}
