/**********************************************************************************************/
/*                                                                                            */
/*  Name: Yu Xiang Dong                                       */
/*                                                                                            */
/*  Project Name: Mastermind			  */
/*  											  */
/*  Added Features, if any: 
	1. Special message pops up when the player loses or wins
    2. Increases num of guesses by adding more strips
	3. Avoid jumping to next lane when missing guess color*/
/*                                                                                         	  */
/***********************************************************************************/
#include <Adafruit_NeoPixel.h>

#define N_LEDS 24

#define PIN1 9
#define PIN2 8
  
Adafruit_NeoPixel GuessStrip = Adafruit_NeoPixel(N_LEDS, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ResponseStrip = Adafruit_NeoPixel(N_LEDS, PIN2, NEO_GRB + NEO_KHZ800);

int pushbutton1 = 13, pushbutton2 = 12, pushbutton3 = 11, pushbutton4 = 10, guessbutton = 7;
int pbvalue1, pbvalue2, pbvalue3, pbvalue4, pbguessvalue;

int GuessStripLane = 0;
int numStripLanes = 6;

const int NONE = 0;
int correctClrNoPos = 0;
int correctClrAndPos = 0;

int guesslist[] ={0,0,0,0};
int secretCode[]={0,0,0,0};

int numSecretCodeColors[] = {0,0,0}; //Red, green and blue
int numGuessColors[] = {0,0,0}; //Red, green and blue

bool missingGuessColor=false;

int Gpixels[] = {1,2,4,7,8,10,11,12,16,19,21,22};
int Npixels[] = {0,3,4,6,7,8,10,11,12,13,15,16,17,19,20,23};
int Opixels[] = {0,1,2,3,4,7,8,11,12,15,16,19,20,21,22,23};

void setup()
{
  pinMode(pushbutton1, OUTPUT);
  pinMode(pushbutton2, OUTPUT);
  pinMode(pushbutton3, OUTPUT);
  pinMode(pushbutton4, OUTPUT);
  pinMode(guessbutton, OUTPUT);
  
  Serial.begin(9600);
  generateRandomCode();
  
  GuessStrip.begin();
  ResponseStrip.begin();
}

void generateRandomCode()
{
  for(int i=0; i<4; i++)//choose 4 random number
  {
    int randomNumber = random(1,4);
    secretCode[i]=randomNumber;
    if(randomNumber==1)
    {
      numSecretCodeColors[0]++;
    }
    if(randomNumber==2)
    {
      numSecretCodeColors[1]++;
    }
    if(randomNumber==3)
    {
      numSecretCodeColors[2]++;
    }
  }
  Serial.print(secretCode[0]);
  Serial.print(secretCode[1]);
  Serial.print(secretCode[2]);
  Serial.println(secretCode[3]);
}

void loop()
{
  pbvalue1 = digitalRead(pushbutton1);
  pbvalue2 = digitalRead(pushbutton2);
  pbvalue3 = digitalRead(pushbutton3);
  pbvalue4 = digitalRead(pushbutton4);
  pbguessvalue = digitalRead(guessbutton);
  
  changeColor(pbvalue1, 0+GuessStripLane*4);
  changeColor(pbvalue2, 1+GuessStripLane*4);
  changeColor(pbvalue3, 2+GuessStripLane*4);
  changeColor(pbvalue4, 3+GuessStripLane*4);
  displayResponse();
  
  delay(50);
}

void changeColor(int pbvalue, int PixelIndex)
{
  if(pbvalue == 1)
  {
    if(GuessStrip.getPixelColor(PixelIndex)==NONE)//if no color, then red
    {
      GuessStrip.setPixelColor(PixelIndex,GuessStrip.Color(255, 0, 0));
      guesslist[PixelIndex%4]=1;
    }
    else
    {
      if(GuessStrip.getPixelColor(PixelIndex)==16711680)//if red, then green
      {
        GuessStrip.setPixelColor(PixelIndex,GuessStrip.Color(0, 255, 0));
        guesslist[PixelIndex%4]=2;
      }
      else
      {
        if(GuessStrip.getPixelColor(PixelIndex)==65280)//if green, then blue
        {
          GuessStrip.setPixelColor(PixelIndex,GuessStrip.Color(0, 0, 255));
          guesslist[PixelIndex%4]=3;
        }
        else
        {
          if(GuessStrip.getPixelColor(PixelIndex)==255)//if blue, then red
          {
            GuessStrip.setPixelColor(PixelIndex,GuessStrip.Color(255, 0, 0));
            guesslist[PixelIndex%4]=1;
          }
        }
      }
    }
  }
  GuessStrip.show();//updates the color of the pixels and send the signal to the hardware.
}

void displayResponse()
{
  //if the 5th button(AKA guessbutton) is pressed
  if(pbguessvalue == 1)
  {
    missingGuessColor = false;
    //it will go over each pixel on the guess strip and see if there are missing colors
    for(int i=0; i<4; i++)
    {
      if(GuessStrip.getPixelColor(i+GuessStripLane*4)==NONE)
      {
        missingGuessColor = true;
      }
    }
    if(missingGuessColor==true)
    {
      Serial.println("Please select 4 colors for your guess");
    }
    else
    {
      Serial.print(guesslist[0]);
      Serial.print(guesslist[1]);
      Serial.print(guesslist[2]);
      Serial.println(guesslist[3]);

      int correctClrNoPos = 0;
      int correctClrAndPos = 0;
      bool ColorInList = false;

      numGuessColors[0]=0;//Reset the value first
      numGuessColors[1]=0;
      numGuessColors[2]=0;

      for(int i=0; i<4; i++)//go through each pixel in the guesslist
      {
        if(guesslist[i]==1)//record how many red, green, and blue color are in the guess strip
        {
          numGuessColors[0]++;
        }
        if(guesslist[i]==2)
        {
          numGuessColors[1]++;
        }
        if(guesslist[i]==3)
        {
          numGuessColors[2]++;
        }

        for(int k=0; k<4; k++)//checks if the color is in the list
        {
          if(secretCode[k]==guesslist[i])
          {
            ColorInList=true;
          }
        }

        if(ColorInList==true)
        {
          correctClrNoPos++; //color is in the list, but not in correct position
          if(guesslist[i]==secretCode[i])// the color is in the list and in correct the position
          {
            correctClrAndPos++;
            correctClrNoPos--;
          }
        }
      }
      for(int i=0; i<3; i++)
      {
        if(numGuessColors[i]>numSecretCodeColors[i])//example: secret code(1,2,2,2), guess(1,1,1,1) 
        {
          correctClrNoPos -= numGuessColors[i]-numSecretCodeColors[i];
        }
      }
      Serial.print(correctClrNoPos);
      Serial.println(correctClrAndPos);

      for(int i=0; i<correctClrAndPos; i++)
      {//for each color that is in the list and in the correct position, change the color to red
        ResponseStrip.setPixelColor(i+GuessStripLane*4,GuessStrip.Color(0, 255, 0));
      }
      for(int i=correctClrAndPos; i<correctClrAndPos+correctClrNoPos; i++)
      {//for each color that is in the list but NOT in the correct position, change the color to green
        ResponseStrip.setPixelColor(i+GuessStripLane*4,GuessStrip.Color(255, 0, 0));
      }
      ResponseStrip.show();//show the pixels
      GuessStripLane++;//move on to the next lane

      if(correctClrAndPos == 4)
      {//if all 4 pixel is red, then the play wins!
        Serial.println("The player wins");
        blinkGG();
      }
      if(GuessStripLane>numStripLanes-1)
      {//if the player run out of chances, then he loses
        Serial.println("The player Loses");
        blinkNO();
      }
      delay(100);
    }
  }
}

void blinkGG()
{
  delay(100);//wait for the user to see there are 4 red colors on the response strip
  for(int k = 0; k<5; k++)//blink 5 times
  {
    GuessStrip.clear();//clear all the pixel on the board first
    ResponseStrip.clear();
    GuessStrip.show();
    ResponseStrip.show(); 
    delay(50);
    for(int i = 0; i<12; i++)
    {
      GuessStrip.setPixelColor(Gpixels[i],GuessStrip.Color(255, 0, 0));
      ResponseStrip.setPixelColor(Gpixels[i],GuessStrip.Color(255, 0, 0));
    }
    GuessStrip.show();
    ResponseStrip.show();
  }
}

void blinkNO()
{
  delay(100);
  for(int k = 0; k<5; k++)//blink 5 times
  {
    GuessStrip.clear();
    ResponseStrip.clear();
    GuessStrip.show();
    ResponseStrip.show();
    delay(50);
    for(int i = 0; i<16; i++)
    {
      GuessStrip.setPixelColor(Npixels[i],GuessStrip.Color(255, 0, 0));
      ResponseStrip.setPixelColor(Opixels[i],GuessStrip.Color(255, 0, 0));
    }
    GuessStrip.show();
    ResponseStrip.show();
  }
}
