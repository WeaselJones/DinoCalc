/* DinoCalc Calculator Software 1v1
   by James R. Bundick (weaseljones@gmail.com)
   Programmed using Arduino IDE 1.0.3
................................................................
License
The library, Keypad.h version 3.0, was used without modification
and is authored by Mark Stanley and Alexander Brevig
which they released under the GNU LGPL 2.1 license.

The lowpower/sleep code was from Nick Gammon,
http://www.gammon.com.au/power

The rest of the code done by myself is released under 
the MIT License  http://opensource.org/licenses/MIT
Copyright (c) 2013 James R. Bundick

Permission is hereby granted, free of charge, to any person 
obtaining a copy of this software and associated documentation 
files (the "Software"), to deal in the Software without 
restriction, including without limitation the rights to use, copy,
modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be 
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
OTHER DEALINGS IN THE SOFTWARE.
................................................................

Summary:
This is a clone of a toy I had when younger.  It was a calculator 
that did not have a LCD display but instead had an owl sticker on
the front with two LED lights, one green and one red.  You would 
enter a math problem on the button keypad with what you thought 
the correct answer was, for example, 12 + 12 = 24, and then press 
the "?" key.  If your answer was right the green LED would light 
up, if your answer was wrong, the red LED would light up.

Future objectives will be to: 
1) add multiplication and division to the calculator's 
   capabilities.  
2) develop a custom keypad 
3) add sound for errors or beep whenever custom keypad button is 
   pressed
4) develop code so that it could also be used for a "math" type 
   game for multiple players.  For example, Display a math
   problem and contestants enter answer on their keypads. 
   If right move away from some peril (like a chomping 
   dinosaur) and if wrong move closer to peril.  Loser is the one 
   that gets eaten (chomp,chomp,chomp).
5) Add recharging circuit


References used during development:
1)  http://tronixstuff.wordpress.com/tutorials  > chapter 42a
2)  http://www.arduino.cc/playground/Code/Keypad by Mark Stanley, 
    Alexander Brevig 
3)  "Arduino Cookbook", 2nd edition, by Michael Margolis
4)  "BlinkWithoutDelay" example by David A. Mellis and Paul 
     Soffregen that came with Arduino IDE 1.0.3 
5)  Floating number math with Arduino, http://arduino.cc/en/Reference/Float 
6)  "Power saving techniques for microprocessors", Nick Gammon,
    Gammon Software Solutions forum, http://www.gammon.com.au/power


Hardware layout:
Keypad:  4x4 Matrix Membrane keypad 
          
          7  8  9  + 
          4  5  6  -
          7  8  9  ?
          C  0  .  =
          
         Each Row and Each Column connects to a PIN for total of 
         8 pins.
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
Arduino pin 10 ---> (long leg)RED LED(short leg) ---> 
                     330 ohm resistor ---> GND
Arduino pin 11 ---> (long leg)GRN LED(short leg) ---> 
                     270 ohm resistor ---> GND


Software Logic

1) User enters First Number, then math operator, then Second
   Number, then equal sign, then user's answer, then "?"
   [12 + 12 = 12 ? <-- User's guess]
2) Microprocessor calculates answer to First Number, math 
   operator, Second Number 
   [12 + 12 = 24  <-- Calculated answer]
3) Microprocessor compares calculated answer to  User Inputed 
   Answer.  If they are not equal then light red LED.  If they
   are equal then light green LED. 
   [12 != 24, so light red LED]

................................................................
Version History

1.1  2013-01-15 - JRB:  Low Power Code Added.  Code ported to just 
      Atmega328p chip running at 8MHz and 2.7V.  Sleep when no key 
      is pressed.

1.0  2012-12-31 - JRB:  RELEASE VERSION.  Changed keypad matrix to
      match the layout I printed on the keypad sticker.  Added
      blinkLEDs() to show activity when calculator is first powered
      ON.  Commented out Serial commands and printInfo(), program
      size went from ~12,000 bytes  to 9,868 bytes.
      
0.5  2012-12-22 - JRB:  Changed x,y,z,z2 from integers to floating
      for "real" number calculations. Since floating point math
      is not completly exact http://arduino.cc/en/Reference/Float 
      I added code to check that the absolute value of the 
      difference between the calculated answer and the entered 
      answer is less than some small number.  
      Reformated text layout for printing.

0.4c 2012-12-22 - JRB:  WORKING VERSION of adding and subtracting
      whole numbers only.  Negative number adding and subtracting
      is also supported.  Minus key can be used for negative 
      numbers now, not just subtraction. 
      (ie, can now enter "-3 + -5 = -8")
           
0.4b 2012-12-21 - JRB: Added condition to prevent "?" from giving
      false "correct"

0.4 2012-12-19 - JRB: Added more information to program 
      description.  Added comparison of user entered answer to 
      calculated answer.  Added Green and Red LED code for 
      correct and wrong answer results.  Changed code to allow 
      negative number answers.
                      
0.3 2012-12-18 - JRB: Corrected minor string issue with equal sign
      attaching to stringOne after calculation.  Cleaned up serial
      commands for debugging.

0.2 2012-12-17 - JRB: Worked on code to add multi-digit numbers 
      instead of single digit numbers by doing conversion of 
      strings to integers.

0.1 2012-12-17 - JRB: Got Code working to read key presses of 
      membrane 4x4 keypad.  Serial print commands added for 
      debugging and will be commented out when code is stable.
................................................................
*/

#include "Keypad.h" // http://www.arduino.cc/playground/Code/Keypad by Mark Stanley, Alexander Brevig 
#include <avr/sleep.h>    

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] =
 {{'7','8','9','+'}, //Sticker will be applied over keypad to 
  {'4','5','6','-'}, //match the layout I want and to provide 
  {'1','2','3','?'}, //a custom graphic (eg dinosaur, bird, etc)
  {'C','0','.','='}};// 
byte rowPins[ROWS] = {
  2, 3, 4, 5}; //Arduino pins that connect to the row pinouts of the keypad pins 1 through 4.
byte colPins[COLS] = {
  6, 7, 8, 9}; //Arduino pins that connect to the column pinouts of the keypad pins 5 through 8.

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int ledGRN = 11;  //Arduino output for Green LED
const int ledRED = 10;  //Arduino output for Red LED

long previousMillis = 0; //used to light LED without using delay()
//[DELETE]long previousMillis2 = 0; //used for sleep time
long interval = 3000;  //maximum time to leave LED HIGH (on)
//[DELETE]long interval2 = 30000;  //time till sleep is enabled

float x; //first number that is entered by user
float y; //second number that is entered by user
float z; //calculated answer
float z2; //answer that is entered by user
int h;  //used to indicate if "." has been pressed already
int i;  //placeholder for operator (i=1 for addition, i=2 for subtraction)
int j;  //used to indicate to program that it is time for the user to input an answer

String stringOne;   //Placeholder for First Number entered by user
String stringTwo;   //Placeholder for Second Number entered by user                                                     
String stringThree; //stringThree is used to show operator and if equal has been pressed.
String stringFour;  //Placeholder for Guessed Answer entered by user                                                     
                                                       
//******************Nick Gammon's Code************************
// number of items in an array
#define NUMITEMS(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0])))
/*

Pin change interrupts.

Pin                  Mask / Flag / Enable

D0	  PCINT16 (PCMSK2 / PCIF2 / PCIE2)
D1	  PCINT17 (PCMSK2 / PCIF2 / PCIE2)
D2	  PCINT18 (PCMSK2 / PCIF2 / PCIE2)
D3	  PCINT19 (PCMSK2 / PCIF2 / PCIE2)
D4	  PCINT20 (PCMSK2 / PCIF2 / PCIE2)
D5	  PCINT21 (PCMSK2 / PCIF2 / PCIE2)
D6	  PCINT22 (PCMSK2 / PCIF2 / PCIE2)
D7	  PCINT23 (PCMSK2 / PCIF2 / PCIE2)
D8	  PCINT0 (PCMSK0 / PCIF0 / PCIE0)
D9	  PCINT1 (PCMSK0 / PCIF0 / PCIE0)
D10	  PCINT2 (PCMSK0 / PCIF0 / PCIE0)
D11	  PCINT3 (PCMSK0 / PCIF0 / PCIE0)
D12	  PCINT4 (PCMSK0 / PCIF0 / PCIE0)
D13	  PCINT5 (PCMSK0 / PCIF0 / PCIE0)
A0	  PCINT8 (PCMSK1 / PCIF1 / PCIE1)
A1	  PCINT9 (PCMSK1 / PCIF1 / PCIE1)
A2	  PCINT10 (PCMSK1 / PCIF1 / PCIE1)
A3	  PCINT11 (PCMSK1 / PCIF1 / PCIE1)
A4	  PCINT12 (PCMSK1 / PCIF1 / PCIE1)
A5	  PCINT13 (PCMSK1 / PCIF1 / PCIE1)

*/

// turn off interrupts until we are ready
ISR (PCINT0_vect)
  {
  PCICR = 0;  // cancel pin change interrupts
  } // end of ISR (PCINT0_vect)

ISR (PCINT1_vect)
  {
  PCICR = 0;  // cancel pin change interrupts
  } // end of ISR (PCINT1_vect)

ISR (PCINT2_vect)
  {
  PCICR = 0;  // cancel pin change interrupts
  } // end of ISR (PCINT2_vect)

//*************************************************************

void setup()
{
//  Serial.begin(9600); //for debugging

  pinMode (ledGRN, OUTPUT); //sets up the Arduino pins as outputs
  pinMode (ledRED, OUTPUT);
  
  stringOne = String ();
  stringTwo = String ();
  stringThree = String ();
  stringFour = String ();

  x = 0;
  y = 0;
  z = 0;
  z2 = 0;
  h = 0;
  i = 0;
  j = 0;
  blinkLEDs();
  
//[DELETE]  previousMillis2 = millis();//move this later
//****************Nick Gammon's code****************************
  // pin change interrupt masks (see above list)
  PCMSK2 |= _BV (PCINT22);   // pin 6
  PCMSK2 |= _BV (PCINT23);   // pin 7
  PCMSK0 |= _BV (PCINT0);    // pin 8
  PCMSK0 |= _BV (PCINT1);    // pin 9

  }  // end of setup

// set pins as keypad library expects them
// or call: kpd.initializePins ();
//    however in the library I have that is a private method

void reconfigurePins ()
  {
  byte i;
  
  // go back to all pins as per the keypad library
  
  for (i = 0; i < NUMITEMS (colPins); i++)
    {
    pinMode (colPins [i], OUTPUT);
    digitalWrite (colPins [i], HIGH); 
    }  // end of for each column 

  for (i = 0; i < NUMITEMS (rowPins); i++)
    {
    pinMode (rowPins [i], INPUT);
    digitalWrite (rowPins [i], HIGH); 
    }   // end of for each row

  }  // end of reconfigurePins

//*************************************************************


void loop()
{
  unsigned long currentMillis = millis();       //Make sure LED doesn't stay continuously on, 
//[DELETE]  unsigned long currentMillis2 = millis();       //Make sure LED doesn't stay continuously on, 
  if(currentMillis - previousMillis > interval) //but allow the code to continue without a delay.
  {                                             
    digitalWrite (ledGRN, LOW);                 
    digitalWrite (ledRED, LOW);                 
  }
//[DELETE] if(currentMillis2 - previousMillis2 > interval2) //sleep
//[DELETE]  {      
//[DELETE]    blinkLEDs();    
//[DELETE]    goToSleep();       
//[DELETE]  }


  char key = keypad.getKey();
     if (!key)
     {
     // no key pressed? go to sleep
     goToSleep ();
//     return;
     }
     blinkGRNLED();//let me know I'm out of sleep

  switch (key)
  {
//[DELETE]    previousMillis2 = millis();//key is pressed, reset sleep timer
    
    case 'C':    //If 'C' is pressed then clear calculator
      blinkLEDs();
      clearCalc();
      break;
    
    case '?':    //Calculate answer and compare it to the answer that was entered by the user
      if (j == 3)
      {
        calcAnswer();
      }
      else
      {
        stringThree = "ERROR";  //if '?' is pressed too soon, error out
//        printInfo();
        showError();
        clearCalc();
      }
      break;
    
    case '=':    //Get ready for the answer to be entered by user
      if (j == 2)
      {
        h = 0;  //h = 0 to allow "." to be used in Answer
        j = 3;  //change j to 3 when equal key has been used once
        stringThree = stringThree + key;
//        printInfo();
      }    
      else
      {
        stringThree = "ERROR";  //if equal is pressed too soon, error out
//        printInfo();
        showError();
        clearCalc();
      }
      break;

    case '+':
      if (i == 0)
      {
        h = 0;  //h = 0 to allow "." to be used for Number2
        i = 1;  //i = 1 to denote addition
        j = 1;  //j = 1 to indicate operator has been pressed, now get Number2
        stringThree = stringThree + key;
//        printInfo();
      }    
      else
      {
        stringThree = "ERROR"; //if plus is pressed multiple times, error out
//        printInfo();
        showError();
        clearCalc();
      }
      break;
  
    case '-':
      if (i == 0)
      {
        if (stringOne == "") //If '-' is the first digit pressed for Number1,
        {                    //use '-' to indicate Number1 is a negative number
          stringOne = stringOne + key;
        }
        else
        {
          h = 0;  //h = 0 to allow "." to be used for Number2
          i = 2;  //i = 2 to denote subtraction
          j = 1;  //j = 1 to indicate operator has been pressed, now get Number2
          stringThree = stringThree + key;
        }
//        printInfo();  
      }    
      else
      {
        if (j == 3 && stringFour == "")  //equal key has been pressed once,
        {                                //if '-' is first digit of answer,
          stringFour = stringFour + key; //answer is a negative number
//          printInfo();
        }
        else
        {
          if (stringTwo == "") //if '-' is first digit of Number2, Number2 is a negative number
          {
            stringTwo = stringTwo + key;
//            printInfo();
          }
          else
          {
            stringThree = "ERROR";  //if minus is pressed and is not operator or first digit of number, error out
//            printInfo();
            showError();
            clearCalc();
          }
        }
      }
      break;
  
    case '.':
      if (h == 0)
      {
        h = 1;  //denotes a decimal point has been used once
        if (j == 0)
        {
          stringOne = stringOne + key; //adds decimal to Number1
        }
        if (j == 1 || j == 2)
        {
          stringTwo = stringTwo + key; //adds decimal to Number2
        }
        if (j == 3)
        {
          stringFour = stringFour + key; //adds decimal to Answer
        }
//        printInfo();
     }
     else
     {
       stringThree = "ERROR";  //if you try and enter a second decimal point in a number, error out
//       printInfo();
       showError();
       clearCalc();
     }
     break;

    default:
      if (key != NO_KEY)
      {
        digitalWrite (ledGRN, LOW); //Turn off LED's if they are on
        digitalWrite (ledRED, LOW);

        if (i == 0) //entering Number1
        {
          stringOne = stringOne + key;
        }
        if ((i == 1 || i == 2) && j != 3) //entering Number2, '=' has not been pressed
        {
          stringTwo = stringTwo + key;
          j = 2; //indicated operator has already been used
        }
        if (j == 3) //'=' has been pressed, entering User's answer
        {
          stringFour = stringFour + key;
        }
//        printInfo();
    }
  }
}

void calcAnswer ()  //Calculate answer and compare to user's answer
{
  char charBufx[50]; //might be able to reduce number from 50
  char charBufy[50];
  char charBufz2[50];
  stringOne.toCharArray(charBufx,50);   //convert String to char array
  stringTwo.toCharArray(charBufy,50);   //convert String to char array
  stringFour.toCharArray(charBufz2,50); //convert String to char array

  x = atof(charBufx);   //convert char array to float
  y = atof(charBufy);   //convert char array to float
  z2 = atof(charBufz2); //convert char array to float

  if (i == 1) //operator was addition
  {
    z = x + y;  //Calculate answer
    stringThree = " + ";
  }
  if (i == 2) //operator was subtraction
  {
    z = x - y;  //Calculate answer
    stringThree = " - ";
  }

  float a;     
  a = z2 - z;  //since floating point math is not completly exact, http://arduino.cc/en/Reference/Float 
               //check that the absolute value of the difference between the numbers is less than some small number. 

//.......................................................
//  Print to Serial for Debugging
/*    Serial.print ("\nCalculated answer:");
    Serial.print (x,4);
    Serial.print (stringThree);
    Serial.print (y,4);
    Serial.print (" = ");
    Serial.print (z,4);
    Serial.print ("\nEntered answer:");
    Serial.print (x,4);
    Serial.print (stringThree);
    Serial.print (y,4);
    Serial.print (" = ");
    Serial.print (z2,4);
    Serial.print ("\nDifference between answers:"); 
    Serial.print (a,12);
*/    
//.......................................................
 
  if (abs(a) < 0.000001) //since floating point math is not completly exact http://arduino.cc/en/Reference/Float 
  {                      //check that the absolute value of the difference between the numbers is less than some small number. 
//    Serial.print ("\nCORRECT!!!"); //for Debugging
    digitalWrite (ledGRN, HIGH);
    digitalWrite (ledRED, LOW);
    previousMillis = millis();   
  }
  else
  {
//    Serial.print ("\nWRONG!!!");  //for Debugging
    digitalWrite (ledGRN, LOW);
    digitalWrite (ledRED, HIGH);
    previousMillis = millis();   
  }
  clearCalc();  //get ready for next math problem
}

/*void printInfo ()  //Used for Debugging
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
*/

void clearCalc() //Get ready for next math problem
{
    Serial.println ("\ncleared\n\n\n");  //for debugging

    stringOne = "";
    stringTwo = "";
    stringThree = "";
    stringFour = "";
    x = 0;
    y = 0;
    z = 0;
    h = 0;
    z2 = 0;
    i = 0;
    j = 0;
     
   char key = NO_KEY;
}

void showError() //Blink RED LED to show Errors
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

void blinkLEDs()
{
  for (int k=0; k <5; k++) //flash LED's so you know something is going on
  {
    digitalWrite (ledGRN, HIGH);
    digitalWrite (ledRED, HIGH);
    delay (50);
    digitalWrite (ledGRN, LOW);
    digitalWrite (ledRED, LOW);
    delay (50);
  }  
} 

void blinkGRNLED()
{
  for (int k=0; k <3; k++) //flash LED's so you know something is going on
  {
    digitalWrite (ledGRN, HIGH);
    digitalWrite (ledRED, LOW);
    delay (50);
    digitalWrite (ledGRN, LOW);
    digitalWrite (ledRED, LOW);
    delay (50);
  }  
} 

//****************Nick Gammon's code****************************
void goToSleep()
  {
  byte i;
   
  // set up to detect a keypress
  for (i = 0; i < NUMITEMS (colPins); i++)
    {
    pinMode (colPins [i], OUTPUT);
    digitalWrite (colPins [i], LOW);   // columns low
    }  // end of for each column

  for (i = 0; i < NUMITEMS (rowPins); i++)
    {
    pinMode (rowPins [i], INPUT);
    digitalWrite (rowPins [i], HIGH);  // rows high (pull-up)
    }  // end of for each row
    
   // now check no pins pressed (otherwise we wake on a key release)
   for (i = 0; i < NUMITEMS (rowPins); i++)
    {
    if (digitalRead (rowPins [i]) == LOW)
       {
       reconfigurePins ();
       return; 
       } // end of a pin pressed
    }  // end of for each row
  
  // overcome any debounce delays built into the keypad library
  delay (50);
  
  // at this point, pressing a key should connect the high in the row to the 
  // to the low in the column and trigger a pin change
  
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);  
  sleep_enable();

  byte old_ADCSRA = ADCSRA;
  // disable ADC to save power
  ADCSRA = 0;  

  PRR = 0xFF;  // turn off various modules
   
  PCIFR  |= _BV (PCIF0) | _BV (PCIF1) | _BV (PCIF2);   // clear any outstanding interrupts
  PCICR  |= _BV (PCIE0) | _BV (PCIE1) | _BV (PCIE2);   // enable pin change interrupts
   
  // turn off brown-out enable in software
  MCUCR = _BV (BODS) | _BV (BODSE);
  MCUCR = _BV (BODS); 
  sleep_cpu ();  
 
  // cancel sleep as a precaution
  sleep_disable();
  PRR = 0;    // enable modules again
  ADCSRA = old_ADCSRA; // re-enable ADC conversion
  
  // put keypad pins back how they are expected to be
  reconfigurePins ();
    
  }  // end of goToSleep
//*******************************************************
