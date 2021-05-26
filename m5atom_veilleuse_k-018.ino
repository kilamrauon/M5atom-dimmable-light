#include "M5Atom.h"  //not needed
#include <FastLED.h>

/* definitions fastled*/
#define NUM_LEDS 25
#define DATA_PIN 27
int sensorPin = 25; //define analog pin 25


//déclaration des variables
int value = 0;
int couleur = 0;
int num = 0;
int value1 = 0;

//initialisation fastled
CRGB leds[NUM_LEDS];


void setup() {
  Serial.begin(115200);
  delay(1000);
  //M5.begin();
  //  delay(10);
  Serial.println("");
  Serial.println("Initializing M5Stack Atom Matrix");
  M5.begin(true, false, true);  //not needed

  // Initialize the FastLED library for this device's configuration
  Serial.println("\nInitializing FastLED");
  //FastLED.addLeds<WS2812, DATA_PIN>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);

  // M5Stack recommends not setting this value greater than 20
  // to avoid melting the screen/cover over the LEDs
  Serial.println("Setting brightness");
  FastLED.setBrightness(20);
  Serial.println("Finishing setup");
  // Initialize device LEDs to on (red), one at a time
  Serial.println("Showing LEDs");
  for (num = -1; num <= NUM_LEDS; num++) {
    Serial.println(num);
    leds[num] = CRGB::Black;
    FastLED.show();
    // delay(10);
  }

  for ( num = -1; num <= NUM_LEDS; num++) {
    //Serial.println(num);
    leds[num] = CRGB::White;
    FastLED.show();
    //delay(50);
  }
}

void loop() {
  
// attention : certaines couleur font clignoter le m5atom
// chaque appui change de couleur
  if (M5.Btn.wasPressed())
  {
    int num=0;
    Serial.print("bouton pressé : ");
    switch (couleur)
    {
      case 0:
       
          couleur = 1;
          for (num; num < NUM_LEDS; num++) {
            leds[num] = CRGB::Blue;
          }
          break;
        

      case 1:
        
          couleur = 2;
          for (num ; num < NUM_LEDS; num++) {
            leds[num] = CRGB::Fuchsia;
          }
          break;
        

      case 2:
        
          couleur = 3;
          for (num ; num < NUM_LEDS; num++) {
            leds[num] = CRGB(0,255,0);
          }
          break;
        

      case 3:
        
          couleur = 4;
          for (num ; num < NUM_LEDS; num++) {
            leds[num] = CRGB(255,0,0);
          }
          break;
        

      case 4:
        
          couleur = 5;
          for (num ; num < NUM_LEDS; num++) {
            leds[num] = CRGB(0,255,255);
          }
          break;
        

       case 5:
        
          couleur = 0;
          for (num ; num < NUM_LEDS; num++) {
            leds[num] = CRGB::White;
          }
          break;
    }
  }
  

 value = 0;


  value = analogRead(sensorPin);



  Serial.println(value, DEC); // light intensity
  // high values for bright environment
  // low values for dark environment
/* la valeur brightness à 5 fait que les led sont à fond...
 *  eviter cette valeur
 *  ne pas dépasser 50 pour eviter la surchauffe

 */
   if (value>3000 && value<3500) {value1=4;}
    else  if (value>=3500 && value<3700) {value1=10;}
    else if (value>=3700 && value<4000) {value1=20;}
    else if(value>=4000) {value1=50;}
    else value1=0;
 
  
  /*
   *la valeur de la résistance ne varie pas de façon linéaire mais logarithmique donc la formule 
   *ci dessous n'est pas la meilleure, à utiliser au cas où
   value1 = map(value, 0, 4095, 0, 50) * 1; /* ne pas dépasser 50 pour la luminosité du m5atom matrix 
                                             et au delà d'un mapping de 0 à 9 sinon les leds ont un comportement étrange
                                             "changement de couleur par exemple" 
    */
    Serial.println(value1);
  FastLED.setBrightness(value1);
  FastLED.show();

  delay(500);
  M5.update();

}
