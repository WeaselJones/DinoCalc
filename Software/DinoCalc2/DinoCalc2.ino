/* DinoCalc Calculator Software 2v0alpha */
//Trying to add more than one operator

#include "Keypad.h" // http://www.arduino.cc/playground/Code/Keypad by Mark Stanley, Alexander Brevig 
    
//****************Keypad Configuration****************************
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
//****************************

long previousMillis = 0; //used to light LED without using delay()
long interval = 3000;  //maximum time to leave LED HIGH (on)

const int ledGRN = 11;  //Arduino output for Green LED
const int ledRED = 10;  //Arduino output for Red LED

int x = 0;
int z = 0;
char buildnum[12] = {0,0,0,0,0,0,0,0,0,0,0,0}; 
float numstorage [4] = {0,0,0,0};

void setup()
{
  Serial.begin(9600);
  pinMode (ledGRN, OUTPUT); //sets up the Arduino pins as outputs
  pinMode (ledRED, OUTPUT);
  blinkLEDs();
}

void loop()
{
  unsigned long currentMillis = millis();       //Make sure LED doesn't stay continuously on, 
  if(currentMillis - previousMillis > interval) //but allow the code to continue without a delay.
  {                                             
    digitalWrite (ledGRN, LOW);                 
    digitalWrite (ledRED, LOW);                 
  }

  char key = keypad.getKey();
  
 if (key != NO_KEY)
  {
    switch(key)
    {
    case 'C':
      ClearAll();
      break;
    case '+':
      CalcAns();
      numstorage[1] = 1;  //1 for addition, 2 for subtraction
      PrintInfo();
      break;
     case '-':
       if (x == 0){    //Assume if '-' is pressed first, this is a negative numbers.
         buildnum[x]=key;
         x++;
       }
       else{           //if '-' isn't pressed first, then we are subtracting
         CalcAns();
         numstorage[1] = 2;  //1 for addition, 2 for subtraction
         PrintInfo();
       }
      break;
    case '.':
      buildnum[x]=key;
      x++;
      break;
    case '=':
      CalcAns();
      numstorage[1] = 0;
      PrintInfo();
      break;
    case '?':
      x=0;
      numstorage[2] = atof(buildnum);  
      for(int i = 0; i < 12; i++){
        buildnum[i] = 0;
      }
      CheckAns();
      PrintInfo();
      break;
    default:
      buildnum[x]=key;
      x++;
      PrintInfo();
    }
  }
}

void ClearAll()
{
  x = 0;
  z = 0;
  for(int i = 0; i < 12; i++){
    buildnum[i] = 0;
    numstorage[i] = 0;
  }
  PrintInfo();
  Serial.print ("\nCLEARED!!");
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

void CalcAns()
{
      x=0;
      if (numstorage[1] <= 1){
        numstorage[0] = numstorage[0] + atof(buildnum);
      }
      if (numstorage[1] == 2){
        numstorage[0] = numstorage[0] - atof(buildnum);
      }
      numstorage[11] = atof(buildnum);  
      for(int i = 0; i < 12; i++){
        buildnum[i] = 0;
      }
     
}

void CheckAns()
{
  float a;
  a = numstorage[0] - numstorage[2];
  numstorage[10];
  //since floating point math is not completly exact, http://arduino.cc/en/Reference/Float 
  //check that the absolute value of the difference between the numbers is less than some small number. 
    if (abs(a) < 0.000001) 
  {                      
    digitalWrite (ledGRN, HIGH);
    digitalWrite (ledRED, LOW);
    previousMillis = millis();   
  }
  else
  {
    digitalWrite (ledGRN, LOW);
    digitalWrite (ledRED, HIGH);
    previousMillis = millis();   
  }
}

void PrintInfo()
{
  Serial.print ("\n\nx : ");
  Serial.print(x);
  Serial.print ("\nz : ");
  Serial.print(z);
  for(int i = 0; i < 12; i++){
    Serial.print ("\nNumber ");
    Serial.print (i);
    Serial.print (": ");
    Serial.print(numstorage[i],9);
  }
}
