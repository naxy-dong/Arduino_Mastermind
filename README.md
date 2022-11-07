# Arduino_Mastermind
The goal of this project is to implement a simplified version of the classic game, Mastermind, using the Arduino Microcontroller and any supporting components you need.  A definition of how the game works can be found by looking up Mastermind on Wikipedia, but we are modifying the rules to make it easier to design & build.  In general your design will randomly generate a “secret code” of four (4) random colors when it is first run.  The colors can be either Red, Green or Blue (RGB) and each color can be used up to 4 times (i.e all pixels = Red).  The player will get four chances to guess the code and the arduino will respond to each guess with a four (4) pixel response.

### Mastermind - The Rules
[Please read the rules here](https://webgamesonline.com/mastermind/rules.php)
[Try out the online version of Mastermind](https://webgamesonline.com/mastermind/index.php)

## The Guesses
Once the secret code is determined, the player will get four (4) tries at guessing the secret code by generating a series of 4 colors on a 4-pixel strip (the guess).  Each pixel in a 4 pixel guess strip will be controlled by an individual PB.  Initially all pixels should be off and each PB should ONLY change a pixel in the 1st guess row.  The first guess is determined by the player, using the push buttons (PB) to change the color of each pixel, rotating from Red-to-Green-to-Blue repeatedly until they are satisfied with their choice for each pixel.  Once all 4 pixels are at the desired color, a 5th PB will be pressed indicating the player wants the Arduino to respond to their guess.  If they are incorrect, this process will repeat using the 2nd guess and 2nd response, etc.

## The Responses
Initially, at the start of the game, all Response pixels are off.  When the player pushes the 5th PB, indicating they have a guess ready to be checked, the arduino will compare their guess to the randomly generated secret code.  After comparing, the response pixels for the guess should indicate how correct or incorrect the guess was.  Each response pixel will be either off (incorrect color), Green (Correct color guess in correct location) or Red (Correct color guess in the wrong location).  If ALL FOUR of the pixels in the guess are incorrect, then the 4 response pixels should all blink 5 times, with a 50 millisecond delay between blinks, and then go off.

## Resources:
This project will require the use of some new componentry, primarily an LED strip, where each LED is individually addressable and RGB, so a few helpful sites have been provided here.  There are more than just these, but these should assist you getting started.

How to add a code library in Arduino IDE to Address an RGB LED Strip (only if you have Arduino HW)
An example of using an Adafruit library to Address an NeoPixel Strip (Tinkercad, Adafruit site is very useful!)

## Arduino or Tinkercad Hardware Requirements:
Arduino (1)
NeoPixel Strip 4 (8) - [ requires installing NeoPixel Library, click the link for NeoPixel instruction ]
Pushbuttons (5)
Other Supporting Components as required

## Project Functional Requirements:
Each guess is 4 pixels
---
3 different colors (Red, Green & Blue) possible
---
Up to 4 guesses allowed
---
4 PB’s control guess pixels
1 PB indicates guess is complete
Responses must indicate correctness (blink 5 times if all 4 incorrect)
Indicate win or lose (Print to the Serial Monitor)

## Potential Additions/Enhancements:
- [x] Add an indicator (your choice) which activates when the player guesses the secret code correctly. --DONE 
- [x] Add more guess/response rows (4 is required, beware of Arduino pin limitations)                   --DONE
- [ ] Add more colors (this is only to be done if you do enhancement #2)                                --NOT DONE
- [ ] Increase number of colors in the secret code (hard to do given Arduino pin limitations)            --NOT DONE
