#ifndef AlaLedRgb_h
#define AlaLedRgb_h

#include "Ala.h"

#include "ExtNeoPixel.h"

/**
 *  AlaLedRgb can be used to drive a single or multiple RGB leds to perform animations.
 *  Available drivers are PWM pin, TLC5940, WS2811.
 */
class AlaLedRgb
{

public:

    AlaLedRgb();

    void initPWM(byte pinsRed, byte pinGreen, byte pinBlue);
    void initPWM(int numLeds, byte *pins);
    void initTLC5940(int numLeds, byte *pins);

    /**
    * Initializes WS2812 LEDs. It be invoked in the setup() function of the main Arduino sketch.
    *
    * The type field can be used to set the RGB order and chipset frequency. Constants are ExtNeoPixel.h file.
    * It is set by default to NEO_GRB + NEO_KHZ800.
    */
    void initWS2812(int numLeds, byte pin, byte type=NEO_GRB+NEO_KHZ800);

   void AlaLedRgb::setMiddle(int booleanV);
	/**
    * Sets the maximum brightness level.
    */
    void setBrightness(AlaColor maxOut);
	AlaColor getBrightness();
	
	void AlaLedRgb::setThresholdNumberOfLed(int threshldLed);
	int getThresholdNumberOfLed();

    void AlaLedRgb::setGap(int gap);
	int getGap();

	/**
    * Sets the number of leds.
    */
    void setNumberOfLeds(int numLeds);
	int  getNumberOfLeds();
	
	void setDuration(int speed);
    int  getDuration();
	void setSpeed(bool val);
    /**
    * Sets the maximum refresh rate in Hz (default value is 50 Hz).
    * May be useful to reduce flickering in some cases.
    */
    void setRefreshRate(int refreshRate);
	
	void setSoundThreshold(int somme);
	int getSoundThreshold();
	
	void setSensitivity(int threshold);
	int  getSensitivity();
	
    int getCurrentRefreshRate();

	void setColor(AlaColor color);
    void setAnimation(int animation, long speed, AlaColor color,int numLeds);
	void setAnimation(int animation, long speed, AlaPalette palette);
    void setAnimation(int animation, long speed, AlaPalette palette,int numLeds);
    void setAnimation(AlaSeq animSeq[]);
    int getAnimation();

    bool runAnimation();



public:

    void setAnimationFunc(int animation);
    void on();
    void off();
    void blink();
    void blinkAlt();
    void sparkle();
    void sparkle2();
    void strobo();
    void cycleColors();

    void pixelShiftRight();
    void pixelShiftLeft();
	void customPixelShift();
    void pixelBounce();
	//void pixelBounceExp();
    void pixelSmoothShiftRight();
    void pixelSmoothShiftLeft();
	void falling_star();
    void comet();
    void cometCol();
    void pixelSmoothBounce();
	void pixelSmoothBounceExp();
    void larsonScanner();
    void larsonScanner2();
	//void larsonScanner_both();

    void fadeIn();
    void fadeOut();
    void fadeInOut();
    void glow();
    void plasma();
    void fadeColors();
    void pixelsFadeColors();
    void fadeColorsLoop();

    void movingBars();
    void movingGradient();

    void fire();
    void bouncingBalls();
    void bubbles();
	//void shine();
	void twinkle();
	void visualizer();
	void simiSpectrum();
	void middle();


    byte driver;    // type of led driver: ALA_PWM, ALA_TLC5940
    byte *pins;     // pins where the leds are attached to
    AlaColor *leds; // array to store leds brightness values
    int numLeds;    // number of leds

    int animation;
    long speed;
    AlaPalette palette;
    AlaSeq *animSeq;
    int animSeqLen;
    long animSeqDuration;
	int soundSensitivity;
	int thrshldNumberLed;
	int gap;
	int somme;
	
    void (AlaLedRgb::*animFunc)();
    AlaColor maxOut;
    int refreshMillis;
    int refreshRate;   // current refresh rate
    unsigned long animStartTime;
    unsigned long animSeqStartTime;
    unsigned long lastRefreshTime;
	bool boolean;
	int booleanV;

    float *pxPos;
    float *pxSpeed;

    Adafruit_NeoPixel *neopixels;

};


#endif