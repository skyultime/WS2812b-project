 /* Communique avec l'ordinateur pour lui envoyer la valeur
 * de l'entrée analogique 0 et permettre de contrôler la
 * sortie numérique 7, qui a une bande de led adressables WS2812b.
 */

#include "FastLED.h"

#define NUM_LEDS 92
#define DATA_PIN 7
#define CLOCK_PIN 13 //Useless for WS2812B

// Define the array of leds
  CRGB leds[NUM_LEDS];

const int entree_analogique = 0;
const int sortie_numerique = 13;
int valeur_captee = 0;
char octet_recu;
char previous_octet_recu;
int j,k,l =0;
int compteur;
void setup() {

    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  // Vitesse de la communication = 115200 bauds
  Serial.begin(115200);
  pinMode(sortie_numerique, OUTPUT);
}

void led_test(){
  //Draw rainbow that fades across all pixels at once."""
        for (int i=0;i<=NUM_LEDS;i++){
          for (int j=0;j<256;j++){
            leds[i] = CRGB(255-j,0,0);
         FastLED.show();
         
    }
  }
}

void rainbow_mode(){
  for (int k=0;k<256;k+=8){
    for (int i=0;i<=NUM_LEDS;i++){
    leds[i] = CRGB(255-k,k,0);
     FastLED.show();
  
      delay(15);
    //leds[i] = CRGB(0,0,0);     
  }
}
  for (int k=0;k<256;k+=8){
    for (int i=0;i<=NUM_LEDS;i++){
    leds[i] = CRGB(0,255-k,k);
     FastLED.show();
      delay(15);
      //leds[i] = CRGB(0,0,0);  
  }
}

  for (int k=0;k<256;k+=8){
    for (int i=0;i<=NUM_LEDS;i++){
    leds[i] = CRGB(k,0,255-k);
     FastLED.show();
      delay(5);
      leds[i] = CRGB(0,0,0);  
   }
  }
}

void beat_detection(){
  for (int i=0;i<octet_recu;i++){
    if (octet_recu<5){
      leds[i] = CRGB(0,0,0);
    }
    leds[i] = CRGB(0,0,255);
    FastLED.show();
    delay(100);/*
    if (i!=0){
     leds[0] = CRGB(0,0,0);
     leds[i-1] = CRGB(0,0,0);}
  */}
}
void loop() {
   if (Serial.available() > 0) {
    
    octet_recu = Serial.read();
    if (octet_recu == '1') {
      digitalWrite(sortie_numerique, HIGH);
      Serial.println("Allumons les leds");
      for (int i=0;i<NUM_LEDS;i++){
      leds[i] = CRGB(random(255),random(255),random(255));
      FastLED.show();
     // delay(24);
      }}
      //On adresse les WS2812b
    }else if (octet_recu == '2') { 
      rainbow_mode();
    }else if ((octet_recu >= '3')&&(octet_recu < '7')){
      compteur++;
      if (compteur%3==0){
        j=255;
        k=0;
        l=0;
      }else if (compteur%3==1){
        j=0;
        k=255;
        l=0;
      }else if (compteur%3==2){
        j=0;
        k=0;
        l=255;
      }
       for (int i=0;i<octet_recu;i++){
        leds[i] = CRGB(j,k,l);
         FastLED.show(); 
       }delay(10);
        for (int i=octet_recu;i<NUM_LEDS-octet_recu;i++){
        leds[i] = CRGB(0,0,0);
         FastLED.show(); 
       }
    }
  /*  else if ((sizeof(octet_recu)>4)&&(sizeof(octet_recu)<12)){
       
        int R= octet_recu.substring(octet_recu[0],"g").toInt();
        int G=0;
        int B=0;
        for (int i=0;i<NUM_LEDS;i++){
        leds[i] = CRGB(R, G, B);
        FastLED.show();
        delay(12);
        }
    }*/
     
        else if (octet_recu == '7'){
        for (int i=0;i<NUM_LEDS;i++){
        leds[i] = CRGB(255,0,0);
        if (i>5)
        leds[i-5]= CRGB(0, 0, 0);
        leds[0]= CRGB(0, 0, 0);
        FastLED.show();
        
        }
        for (int i=0;i<NUM_LEDS;i++){
        leds[i] = CRGB(0,0,0);
        FastLED.show();
 
      }}else if (octet_recu == '8'){
        for (int i=0;i<NUM_LEDS;i++){
        leds[i] = CRGB(0,255,0);
        if (i>5)
        leds[i-5]= CRGB(0, 0, 0);
        leds[0]= CRGB(0, 0, 0);
        FastLED.show();
         
        }
        for (int i=0;i<NUM_LEDS;i++){
        leds[i] = CRGB(0,0,0);
        FastLED.show();
 
      } }else if (octet_recu == '9') {
        digitalWrite(sortie_numerique, LOW);
         Serial.println("On clear les leds");
        //On clear toutes les leds dans tous les cas
        for (int i=0;i<NUM_LEDS;i++){
        leds[i] = CRGB(0, 0, 255);
        if (i>5)
        leds[i-5]= CRGB(0, 0, 0);
        leds[0]= CRGB(0, 0, 0);
        FastLED.show();
        
        }
        for (int i=0;i<NUM_LEDS;i++){
        leds[i] = CRGB(0,0,0);
        FastLED.show();
        }
      }else if (octet_recu == '0'){
      for (int i=60;i<92;i++){
        leds[i] = CRGB(0,0,0);
        FastLED.show();
 
    }}
   
  // Lecture de l'entrée analogique 0:
  //valeur_captee = analogRead(entree_analogique);
 // char envoyer = 'a' + map(valeur_captee, 0, 1023, 0, 25);
  //Serial.print(envoyer);
  // On attend un peu pour laisser le temps au ADC de respirer
 // delay(2);
}
