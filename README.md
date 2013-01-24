DinoCalculator Version 1.0

Download updates from:
http://code.google.com/p/dinocalc/

Summary:
When I was younger I had a calculator that did not have a LCD display but instead had two LED lights, one green and one red.  You would enter a math problem with what you thought the correct answer was (for example, 12 + 12 = 24, and then press the "?" key).  If your answer was right the green LED would light up, if your answer was wrong, the red LED would light up.

This is my salute to that toy from my childhood, as well as a great way for me to engineer and program a neat little project that my preschool son can actually use to check his simple math.

This first part will document the prototype that I have built.  My first objective was to create a calculator capable of just adding and subtracting using off the shelf items.  I plan on starting with an Arduino Pro Mini for the developmental and prototype stage and once I can get most of the major bugs worked out I will then move on to a final version that has a lower cost and device count (ATmega328p on a custom PCB).  


Future objectives (not in any particular order) will be to:

1) Replace the Arduino Pro Mini board with a custom made PCB and reduce parts to a minimum to lower costs (I already have several friends wanting versions for their kids)

2) Add multiplication and division to the calculator's capabilities (low priority for me since this will involve more keys then a 4x4 matrix keypad and my son is only starting addition and subtraction right now)

3) Develop a custom keypad (maybe using tactile buttons and caps, or making my own "membrane" type keypad, or exploring "conductive" type buttons)

4) Add sound for errors or beep whenever custom keypad button is pressed

5) Develop code so that it could also be used for a "math" type game for multiple players. For example, Display a math problem and contestants enter answer on their calculators. If their answer is right, their token moves away from some peril (like a chomping dinosaur) and if wrong moves closer to peril. Loser is the one that gets eaten (chomp,chomp,chomp)

6) Make the circuit low-power for longer battery life and replace the 9V battery with two NiMH AA batteries or perhaps even a button cell rechargeable battery

7) Add a recharging circuit to recharge the rechargeable batteries from USB


