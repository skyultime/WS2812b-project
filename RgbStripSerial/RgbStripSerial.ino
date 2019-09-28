///////////////////////////////////////////////////////////////////////////////////////////
//
// WS2812b library example: RgbStripSerial
//
// Example to demonstrate how to control WS2812 RGB LED strip lighting and animations
// sending AT commands through the serial port.
///////////////////////////////////////////////////////////////////////////////////////////

/* The circuit:
 * RX is digital pin 2 (connect to TX of other device)
 * TX is digital pin 3 (connect to RX of other device)
*/

#include <avr/wdt.h>
#include <AlaLedRgb.h>
#include <stdlib.h>
#include <SPI.h>

#define CS 10 // Assignment of the CS pin
#define WS2811_PIN 5    // WS2811 control connected to pin 6
#define NUM_PIXELS 60   // number of leds in the LED strip
#define CMDBUFSIZE 16   // buffer size for receiving serial commands

//SoftwareSerial mySerial(2, 3); // RX, TX

AlaLedRgb rgbStrip;
char cmdBuffer[CMDBUFSIZE];

char * colorString = "0xffffff";
char * endPtr;

// global settings and initial values
int animation = ALA_OFF;
AlaColor color = 0xdddddd;
AlaColor white = 0xffffff;
AlaColor black = 0x000000;
AlaPalette palette = alaPalNull;
AlaColor colorV = 0x000000;
int paletteId=0;
float brightness = 0.3;
int threshold = 500;
int gap =1;
int booleanV = false;
int thresholdNumberLed=1;
long duration = 5000;
int number = NUM_PIXELS;

int soundstate = 0;
boolean etatBouton = false;
boolean etatBouton2 = false;
boolean entrance = true;
boolean entrance2 = true;
boolean entrance3 = !true;
boolean entrance_middle = false;
boolean val = false;
int seuil = 2025;
int sensorRange = 1024;
//int mic3Range = 3000;//2048; //Nettement supérieur !!!

/*///////////////////////////////////////////led RGB de contrôle////////////////////////////////////////////
*/
int PIR;

int redPin = 6;
int greenPin = 2;
int bluePin = 3;

boolean greenState=false;
boolean blueState=false;

boolean react = false;
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////*/

unsigned long time;

/**********************************Pmod mic3 SPI init*********************************************************************
*/
int i;
byte recu[3]; // storage of data of the module
int X;
long somme = 0;


/**************************************************************************************************************************
*/

/*////////////////////////////////////////////Pot//////////////////////////////////////
//
// #define outputA 11
// #define outputB 2
// int counter = 0; 
// int aState;
// int aLastState; 
//
////////////////////////////////////////////////////////////////////////////////////
*/

/*////////////////////////////////////JY-30 (Bluetooth)///////////////////////////*/

char Incoming_value = 0;                //Variable for storing Incoming_value

/*/////////////////////////////////////////////////////////////////////////////////*/

/*//////////////////////////////////////////////IR////////////////////////////////

const int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;
//////////////////////////////////////////////////////////////////////////////////*/


void setup()
{
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);

//  pinMode(outputA, INPUT);  
//  pinMode(outputB, INPUT); 
  
  rgbStrip.initWS2812(NUM_PIXELS, WS2811_PIN);
  rgbStrip.setBrightness(color.scale(brightness));
  rgbStrip.setAnimation(101, duration, 0x000000,rgbStrip.getNumberOfLeds());
  rgbStrip.setNumberOfLeds(NUM_PIXELS);
  Serial.begin(9600);
//  mySerial.begin(115200);
//  aLastState = digitalRead(outputA);
  
//******************************************SPI setup mode********************************************************************************
 SPI.begin(); // initialization of SPI port
 SPI.setDataMode(SPI_MODE0); // configuration of SPI communication in mode 0
 SPI.setClockDivider(SPI_CLOCK_DIV16); // configuration of clock at 1MHz
 pinMode(CS, OUTPUT);

 /************************************************************************************************************************** 
 */ 
  pinMode(4,INPUT); 
  pinMode(7,INPUT); //SIG of the Parallax Sound Impact Sensor connected to Digital Pin 7
//  irrecv.enableIRIn();
//  irrecv.blink13(true);


  Serial.println(F("Welcome to ALA RgbStripSerial example"));
//  Serial.println("A=[animation code] Set the animation. See https://github.com/bportaluri/ALA/blob/master/src/AlaLed.h");
//  Serial.println("B=[brightness]     Set the brightness [0-100]");
//  Serial.println("D=[duration]       Set the duration in milliseconds of the animation cycle");
//  Serial.println("C=[color]          Set the color (hexadecimal RGB representation ex. 0xE8A240)");
//  Serial.println("P=[palette]        Set the palette.");                                                                               

/*                                                                                                                                                        
//  Serial.println("V=[visualizer]             Set the audio reactive led processus.");                                                                  
//  Serial.println("W=[Linear visualizer]      Set the audio reactive led processus driving growing range of leds.");                                
//  Serial.println("S=[soundSensitivity]       Set the audio reactive led processus.");                                                                  
//  Serial.println("N=[set the number of LED]  Set the number of LED to deal with.");                                                                                                                                                                                                                      
*/
//mySerial.println("Hello world from Arduino (USBtoUART connection)");
}



void(* resetFunc) (void) = 0; //declare reset function @ address 0

void software_Reboot()
{
  wdt_enable(WDTO_15MS);

  while(1)
  {

  }
}

void loop()
{

  // lire l'état du PIR
    PIR = digitalRead(4);
    
//  Serial.print(F(F("PIR status : "));
//  Serial.println(PIR);
  somme = 0;
 digitalWrite(CS, LOW); // activation of CS line
   delayMicroseconds(20);
   for (i=0;i<2;i=i+1)
    {
    recu[i] = SPI.transfer(0); // send 2 data to retrieve the value of the two-byte conversion
    delayMicroseconds(20);
    }
   digitalWrite(CS, HIGH); // deactivation of CS line
   X = recu[1]; // X is on 12 bit format
   X |= (recu[0] << 8);
 
for(int i=0; i<32; i++) // Development of the sound curve //32
 {
   somme = somme + X;
 }

 somme >>= 5;
 rgbStrip.setSoundThreshold(somme);
 /*if (time %10 ==0){
 Serial.println(somme); // Display in serial plotter
 
 }
 delay(10);
 */
 
 //time = millis();
 

/*aState = digitalRead(outputA);
if (aState != aLastState){ 
     if (digitalRead(outputB) != aState) { 
       counter ++;
     } else {
       counter --;
  }
}      
 if (time%1000==0){
  
  //Serial.print(F("valeur pot. : "));
  //Serial.println(counter);
 }*/
  entrance = true;
 
 if (Serial.available())
{
  if (entrance) {
   rgbStrip.setAnimation(101, duration, color,60);
  }entrance = false;
  //char state = Serial.read();
  //Serial.println(state);
    /////////////////////////Bth///////////////////////////////   
    //Incoming_value = Serial.read();         //Read the incoming data and store it into variable Incoming_value
    //Serial.print(F(F("Bluetooth value");        //Print Value of Incoming_value in Serial monitor
    //Serial.println(Incoming_value);
    /////////////////////////////////////////////////////////

    int charsRead;
    charsRead = Serial.readBytesUntil('\n', cmdBuffer, sizeof(cmdBuffer) - 1);  //read entire line
    cmdBuffer[charsRead] = '\0';       // Make it a C string
    Serial.print(F(">"));
    Serial.println(cmdBuffer);
   // mySerial.print(cmdBuffer);
    if(cmdBuffer[1] != '=' || strlen(cmdBuffer)<3)
    {
      Serial.println(F("KO"));
    }
    else
    {
       
      switch(toupper(cmdBuffer[0]))
      {
      case 'A':
        greenState = true; //TODO A adapter pour le déclencher une fois seulement que la connexion avec le serveur (PS: le rpi) sera établie !   
        etatBouton = false;
        etatBouton2 = false;
        animation = atoi(&cmdBuffer[2]);
       // Serial.println(F("OK"));
        break;
      case 'B':
        brightness = atoi(&cmdBuffer[2]);
        rgbStrip.setBrightness(white.scale((float)brightness / 100));
        //Serial.println(F("OK"));
        break;
      case 'C':
        color = strtol(&cmdBuffer[2], 0, 16);
        palette=alaPalNull;
        rgbStrip.setColor(color);
        break;
      case 'D':
        duration = atol(&cmdBuffer[2]);
       // Serial.println(F("OK"));
        break; 

      case 'G':
        gap = atoi(&cmdBuffer[2]);
        rgbStrip.setGap(gap);
       // Serial.print(F("OK :"));
       // Serial.println(rgbStrip.getGap());
        break;

      case 'M':
        booleanV = atoi(&cmdBuffer[2]);
        rgbStrip.setMiddle(booleanV);
        break;
      case 'K':
        thresholdNumberLed = atoi(&cmdBuffer[2]);
        rgbStrip.setThresholdNumberOfLed(thresholdNumberLed);
       // Serial.print(F("OK :"));
       // Serial.println(rgbStrip.getThresholdNumberOfLed());
        break;
      case 'P':
        paletteId = atoi(&cmdBuffer[2]);
        switch(paletteId)
        {
        case 0:
          palette=alaPalNull;
          break;
        case 1:
          palette=alaPalRgb;
          break;
        case 2:
          palette=alaPalRainbow;
          break;
        case 3:
          palette=alaPalParty;
          break;
        case 4:
          palette=alaPalHeat;
          break;
        case 5:
          palette=alaPalFire;
          break;
        case 6:
          palette=alaPalCool;
          break;
        case 7:
          palette=alaPalBW;
          break;
        }
        break;
      case 'V':     
        colorV = strtol(&cmdBuffer[2], 0, 16);
        react = !react;
        if (!(react)){
          rgbStrip.setDuration(1000);
        }
        
      /*if (etatBouton == false){
         blueState = false;
         Serial.println("Audio Visualizer disable");
       }
     if ((entrance)&&(etatBouton == true)){
        greenState = false;
        blueState = true;
        Serial.println("Audio Visualizer enable\nValeurs: ");
        }entrance = false;
   */
       //animation = 601;
       
       break;

       case 'W':
   /*      etatBouton = false;
        etatBouton2 = !etatBouton2;
      if (etatBouton2 == false){
         blueState = false;
         Serial.println("Audio Visualizer disable");
         //rgbStrip.setBrightness(white.scale((float)50 / 100));
       }
      if ((entrance2)&&(etatBouton2 == true)){
        greenState = false;
        blueState = true;
        Serial.println("Audio Visualizer enable\nValeurs: ");
        }entrance2 = false;
      */
       animation = 602;
       break;
     
      case 'N':
         number = atoi(&cmdBuffer[2]);
         rgbStrip.setNumberOfLeds(number);
         //rgbStrip.setAnimation(int(animation), long(duration), AlaColor(color),int(number));
         //animation = atoi(102);//A=101
         rgbStrip.setAnimation(animation, duration, color,rgbStrip.getNumberOfLeds());
         break;
       case 'S':
         threshold = atoi(&cmdBuffer[2]);
         rgbStrip.setSensitivity(int(threshold));
         //Serial.println(rgbStrip.getSensitivity()); 
         break;

      case 'T':
      rgbStrip.setSpeed(!val);
      case 'R':
        // Serial.println(F("Reset system"));
         software_Reboot();//resetFunc();
         break;
      
      case 'Z':
      break; //Useless
      
      default:
        Serial.println(F("KO"));
      }
           
      if(palette==alaPalNull)
        rgbStrip.setAnimation(animation, duration, color,rgbStrip.getNumberOfLeds());
      else
        rgbStrip.setAnimation(animation, duration, palette,rgbStrip.getNumberOfLeds());
    }
  }
 if (entrance3 == true){
      animation = 104;
      color = 0x0000ff;
      duration = 500;
      rgbStrip.setAnimation(animation, duration, color,rgbStrip.getNumberOfLeds());
      entrance3 = false;
     // Serial.println(F("\n//// INIT DONE ////"));
    }
 
 /* if ((etatBouton == true)&&(etatBouton2==false)){      

       if (soundstate == 0){
          rgbStrip.setColor(colorV);
          rgbStrip.setAnimation(101, duration, colorV,rgbStrip.getNumberOfLeds()); 
       }else{
         rgbStrip.setColor(black);
         rgbStrip.setAnimation(102, duration, black,rgbStrip.getNumberOfLeds()); 
       }
      }
  if ((etatBouton2 == true)&&(etatBouton==false)){ 

          if (mic3Range != 0){
          if ((somme*NUM_PIXELS/mic3Range>=10) and (somme*NUM_PIXELS/mic3Range)<= 56){
              rgbStrip.setNumberOfLeds(int((somme*NUM_PIXELS)/mic3Range));
            }else if ((somme*NUM_PIXELS/mic3Range)> 56){
              rgbStrip.setNumberOfLeds(56);
              rgbStrip.setAnimation(animation, duration, color,rgbStrip.getNumberOfLeds());
            }else{
              rgbStrip.setNumberOfLeds(5);
              rgbStrip.setAnimation(animation, duration, color,rgbStrip.getNumberOfLeds());
            }
            color = strtol(&cmdBuffer[2], 0, 16);
            palette=alaPalNull;
            rgbStrip.setColor(color);    

  }//}

  }*//*
  if ((greenState)&&(!(blueState))){
       digitalWrite(redPin,LOW);
       digitalWrite(greenPin,HIGH);
       digitalWrite(bluePin,LOW);
  }else if ((blueState)&&(!(greenState))){
    if (somme >=rgbStrip.getSensitivity()){
       digitalWrite(redPin,LOW);
       digitalWrite(greenPin,LOW);
       digitalWrite(bluePin,HIGH);
    }else {
      digitalWrite(redPin,LOW);
      digitalWrite(greenPin,LOW);
      digitalWrite(bluePin,LOW);
    }
  }else{
      digitalWrite(redPin,HIGH);
      digitalWrite(greenPin,LOW);
      digitalWrite(bluePin,LOW);
  }*/

  if (react ==true){
    rgbStrip.setDuration(2048-somme);
   // Serial.println(rgbStrip.getDuration());
  }
  rgbStrip.runAnimation();
  //time=millis();
}
