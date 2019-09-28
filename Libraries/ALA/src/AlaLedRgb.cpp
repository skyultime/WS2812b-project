#include "Ala.h"
#include "AlaLedRgb.h"

#include "ExtNeoPixel.h"
#include "ExtTlc5940.h"

int mic3Range = 2047;
int totalNumLeds = 60;
AlaLedRgb::AlaLedRgb()
{
    // set default values

    maxOut = 0xFFFFFF;
    speed = 1000;
    animSeqLen = 0;
    lastRefreshTime = 0;
    refreshMillis = 1000/50;
    pxPos = NULL;
    pxSpeed = NULL;
	soundSensitivity = 1000;
	thrshldNumberLed=1;
	gap = 1;
	somme = 0;
	booleanV=0;
	boolean = false;
	
}


void AlaLedRgb::initPWM(byte pinRed, byte pinGreen, byte pinBlue)
{
    byte *pins_ = (byte *)malloc(3);
    pins_[0] = pinRed;
    pins_[1] = pinGreen;
    pins_[2] = pinBlue;

    initPWM(1, pins_);
}

void AlaLedRgb::initPWM(int numLeds, byte *pins)
{
    this->driver = ALA_PWM;
    this->numLeds = numLeds;
    this->pins = pins;

    for (int x=0; x<3*numLeds ; x++)
    {
        pinMode(pins[x], OUTPUT);
    }

    // allocate and clear leds array
    leds = (AlaColor *)malloc(3*numLeds);
    memset(leds, 0, 3*numLeds);
}

void AlaLedRgb::initTLC5940(int numLeds, byte *pins)
{
    this->driver = ALA_TLC5940;
    this->numLeds = numLeds;
    this->pins = pins;

    // allocate and clear leds array
    leds = (AlaColor *)malloc(3*numLeds);
    memset(leds, 0, 3*numLeds);

    // call Tlc.init only once
    static bool isTlcInit = false;
    if(!isTlcInit)
    {
        Tlc.init(0);
        isTlcInit=true;
    }
}

void AlaLedRgb::initWS2812(int numLeds, byte pin, byte type)
{
    this->driver = ALA_WS2812;
    this->numLeds = numLeds;
    this->pins = 0;

    // allocate and clear leds array
    leds = (AlaColor *)malloc(3*numLeds);
    memset(leds, 0, 3*numLeds);

    neopixels = new Adafruit_NeoPixel(numLeds, pin, type);

    neopixels->begin();
}

void AlaLedRgb::setMiddle(int booleanV)
{
    this->booleanV = booleanV;
}
void AlaLedRgb::setSpeed(bool val)
{
    this->boolean = val;
}

void AlaLedRgb::setSoundThreshold(int somme)
{
    this->somme = somme;
	//Serial.println(int(56*round(somme/mic3Range)));
}

int AlaLedRgb::getSoundThreshold()
{
	return this->somme;
}


void AlaLedRgb::setBrightness(AlaColor maxOut)
{
    this->maxOut = maxOut;
}

AlaColor AlaLedRgb::getBrightness()
{
	return this->maxOut;
}

void AlaLedRgb::setNumberOfLeds(int number)
{
	this->numLeds = number;	
}

int AlaLedRgb::getNumberOfLeds()
{
	return this->numLeds;
}

void AlaLedRgb::setDuration(int dur)
{
    this->speed =dur ;
}

int AlaLedRgb::getDuration()
{
    return speed;
}

void AlaLedRgb::setRefreshRate(int refreshRate)
{
    this->refreshMillis = 1000/refreshRate;
}

int AlaLedRgb::getCurrentRefreshRate()
{
    return refreshRate;
}

void AlaLedRgb::setThresholdNumberOfLed(int threshldLed)
{
    this->thrshldNumberLed = threshldLed;
}

int AlaLedRgb::getThresholdNumberOfLed()
{
    return this->thrshldNumberLed;
}

void AlaLedRgb::setGap(int gap)
{
    this->gap = gap;
}

int AlaLedRgb::getGap()
{
    return this->gap;
}

void AlaLedRgb::setSensitivity(int threshld)
{
    this->soundSensitivity = threshld;
}

int AlaLedRgb::getSensitivity()
{
    return this->soundSensitivity;
}

void AlaLedRgb::setColor(AlaColor color){
	 if (this->palette.numColors == 1 && this->palette.colors[0] == color)
        return;

    this->palette.numColors = 1;
    this->palette.colors = (AlaColor*)malloc(3);
    this->palette.colors[0] = color;
}	

void AlaLedRgb::setAnimation(int animation, long speed, AlaColor color, int numLeds)
{
    // is there any change?
    if (this->animation == animation && this->speed == speed && this->palette.numColors == 1 && this->palette.colors[0] == color)
        return;

    // delete any previously allocated array
    if (pxPos!=NULL)
    { delete[] pxPos; pxPos=NULL; }
    if (pxSpeed!=NULL)
    { delete[] pxSpeed; pxSpeed=NULL; }

    this-> animation = animation;
    this-> speed = speed;

    this-> palette.numColors = 1;
    this-> palette.colors = (AlaColor*)malloc(3);
    this-> palette.colors[0] = color;
    this-> numLeds = numLeds;    
	
    setAnimationFunc(animation);
    animStartTime = millis();
	Serial.println("Anim");
	middle();
}

void AlaLedRgb::setAnimation(int animation, long speed, AlaPalette palette)
{
    // is there any change?
    if (this->animation == animation && this->speed == speed && this->palette == palette)
        return;

    // delete any previously allocated array
    if (pxPos!=NULL)
    { delete[] pxPos; pxPos=NULL; }
    if (pxSpeed!=NULL)
    { delete[] pxSpeed; pxSpeed=NULL; }

    this->animation = animation;
    this->speed = speed;
    this->palette = palette; 
    setAnimationFunc(animation);
    animStartTime = millis();
}

void AlaLedRgb::setAnimation(int animation, long speed, AlaPalette palette,int numLeds)
{
    // is there any change?
    if (this->animation == animation && this->speed == speed && this->palette == palette)
        return;

    // delete any previously allocated array
    if (pxPos!=NULL)
    { delete[] pxPos; pxPos=NULL; }
    if (pxSpeed!=NULL)
    { delete[] pxSpeed; pxSpeed=NULL; }

    this->animation = animation;
    this->speed = speed;
    this->palette = palette;
	this-> numLeds = numLeds;    
	//this->  k =1;
    setAnimationFunc(animation);
    animStartTime = millis();
}


void AlaLedRgb::setAnimation(AlaSeq animSeq[])
{
    this->animSeq = animSeq;

    // initialize animSeqDuration and animSeqLen variables
    animSeqDuration = 0;
    for(animSeqLen=0; animSeq[animSeqLen].animation!=ALA_ENDSEQ; animSeqLen++)
    {
        animSeqDuration = animSeqDuration + animSeq[animSeqLen].duration;
    }
    animSeqStartTime = millis();
    setAnimation(animSeq[0].animation, animSeq[0].speed, animSeq[0].palette);
}

int AlaLedRgb::getAnimation()
{
    return animation;
}


bool AlaLedRgb::runAnimation()
{
    if(animation == ALA_STOPSEQ)
        return true;
    
    // skip the refresh if not enough time has passed since last update
    unsigned long cTime = millis();
    if (cTime < lastRefreshTime + refreshMillis)
        return false;

    // calculate real refresh rate
    refreshRate = 1000/(cTime - lastRefreshTime);

    lastRefreshTime = cTime;

    // if it's a sequence we have to calculate the current animation
    if (animSeqLen != 0)
    {
        long c = 0;
        long t = (cTime-animSeqStartTime) % animSeqDuration;
        for(int i=0; i<animSeqLen; i++)
        {
            if (t>=c && t<(c+animSeq[i].duration))
            {
                setAnimation(animSeq[i].animation, animSeq[i].speed, animSeq[i].palette);
                break;
            }
            c = c + animSeq[i].duration;
        }
    }


    // run the animantion calculation
    if (animFunc != NULL)
        (this->*animFunc)();

    // update leds
    if(driver==ALA_PWM)
    {
        for(int i=0; i<getNumberOfLeds(); i++)
        {
            int j = 3*i;
            // use an 8 bit shift to divide by 256
            analogWrite(pins[j],   (leds[i].r*maxOut.r)>>8);
            analogWrite(pins[j+1], (leds[i].g*maxOut.g)>>8);
            analogWrite(pins[j+2], (leds[i].b*maxOut.b)>>8);
        }
    }
    else if(driver==ALA_TLC5940)
    {
        // TLC5940 maximum output is 4095 so shifts only 4 bits
        for(int i=0; i<getNumberOfLeds(); i++)
        {
            int j = 3*i;
            Tlc.set(pins[j],   (leds[i].r*maxOut.r)>>4);
            Tlc.set(pins[j+1], (leds[i].g*maxOut.g)>>4);
            Tlc.set(pins[j+2], (leds[i].b*maxOut.b)>>4);
        }
        Tlc.update();
    }
    else if(driver==ALA_WS2812)
    {
        // this is not really so smart...
		for (int i = getNumberOfLeds();i<totalNumLeds;i++){
		         neopixels->setPixelColor(i,0, 0, 0);
		}
        for(int i=0; i<getNumberOfLeds(); i++)
            neopixels->setPixelColor(i, neopixels->Color((leds[i].r*maxOut.r)>>8, (leds[i].g*maxOut.g)>>8, (leds[i].b*maxOut.b)>>8));

        neopixels->show();
    }
    return true;
}


///////////////////////////////////////////////////////////////////////////////

void AlaLedRgb::setAnimationFunc(int animation)
{

    switch(animation)
    {
        case ALA_ON:                    animFunc = &AlaLedRgb::on;                    break;
        case ALA_OFF:                   animFunc = &AlaLedRgb::off;                   break;
        case ALA_BLINK:                 animFunc = &AlaLedRgb::blink;                 break;
        case ALA_BLINKALT:              animFunc = &AlaLedRgb::blinkAlt;              break;
        case ALA_SPARKLE:               animFunc = &AlaLedRgb::sparkle;               break;
        case ALA_SPARKLE2:              animFunc = &AlaLedRgb::sparkle2;              break;
        case ALA_STROBO:                animFunc = &AlaLedRgb::strobo;                break;
        case ALA_CYCLECOLORS:           animFunc = &AlaLedRgb::cycleColors;           break;

        case ALA_PIXELSHIFTRIGHT:       animFunc = &AlaLedRgb::pixelShiftRight;       break;
        case ALA_PIXELSHIFTLEFT:        animFunc = &AlaLedRgb::pixelShiftLeft;        break;
		case ALA_CUSTOMPIXELSHIFT:      animFunc = &AlaLedRgb::customPixelShift;      break;
        case ALA_PIXELBOUNCE:           animFunc = &AlaLedRgb::pixelBounce;           break;
        case ALA_PIXELSMOOTHSHIFTRIGHT: animFunc = &AlaLedRgb::pixelSmoothShiftRight; break;
        case ALA_PIXELSMOOTHSHIFTLEFT:  animFunc = &AlaLedRgb::pixelSmoothShiftLeft;  break;
        case ALA_PIXELSMOOTHBOUNCE:     animFunc = &AlaLedRgb::pixelSmoothBounce;     break;
		case ALA_PIXELSMOOTHBOUNCEEXP:  animFunc = &AlaLedRgb::pixelSmoothBounceExp;  break;
        case ALA_COMET:                 animFunc = &AlaLedRgb::comet;                 break;
        case ALA_COMETCOL:              animFunc = &AlaLedRgb::cometCol;              break;
        case ALA_MOVINGBARS:            animFunc = &AlaLedRgb::movingBars;            break;
        case ALA_MOVINGGRADIENT:        animFunc = &AlaLedRgb::movingGradient;        break;
        case ALA_LARSONSCANNER:         animFunc = &AlaLedRgb::larsonScanner;         break;
        case ALA_LARSONSCANNER2:        animFunc = &AlaLedRgb::larsonScanner2;        break;

        case ALA_FADEIN:                animFunc = &AlaLedRgb::fadeIn;                break;
        case ALA_FADEOUT:               animFunc = &AlaLedRgb::fadeOut;               break;
        case ALA_FADEINOUT:             animFunc = &AlaLedRgb::fadeInOut;             break;
        case ALA_GLOW:                  animFunc = &AlaLedRgb::glow;                  break;
        case ALA_PLASMA:                animFunc = &AlaLedRgb::plasma;                break;
        case ALA_PIXELSFADECOLORS:      animFunc = &AlaLedRgb::pixelsFadeColors;      break;
        case ALA_FADECOLORS:            animFunc = &AlaLedRgb::fadeColors;            break;
        case ALA_FADECOLORSLOOP:        animFunc = &AlaLedRgb::fadeColorsLoop;        break;

        case ALA_FIRE:                  animFunc = &AlaLedRgb::fire;                  break;
        case ALA_BOUNCINGBALLS:         animFunc = &AlaLedRgb::bouncingBalls;         break;
        case ALA_BUBBLES:               animFunc = &AlaLedRgb::bubbles;               break;
		case ALA_TWINKLE:               animFunc = &AlaLedRgb::twinkle;               break;
		case ALA_VISUALIZER:            animFunc = &AlaLedRgb::visualizer;            break;
		case ALA_SIMISPECTRUM:          animFunc = &AlaLedRgb::simiSpectrum;          break;

        default:                        animFunc = &AlaLedRgb::off;
    }

}


void AlaLedRgb::on()
{
    for(int i=0; i<totalNumLeds; i++)
    {
        leds[i] = palette.colors[0];
    }
}

void AlaLedRgb::off()
{
    for(int i=0; i<totalNumLeds; i++)
    {
        leds[i] = 0x000000;
    }
}


void AlaLedRgb::blink()
{
    int t = getStep(animStartTime, speed, 2);
    int k = (t+1)%2;
    for(int x=0; x<numLeds; x++)
    {
        leds[x] = palette.colors[0].scale(k);
    }
}

void AlaLedRgb::blinkAlt()
{
    int t = getStep(animStartTime, speed, 2);

    for(int x=0; x<numLeds; x++)
    {
        int k = (t+x)%2;
        leds[x] = palette.colors[0].scale(k);
    }
  middle();
}

void AlaLedRgb::sparkle() 
{
    int p = speed/100;
    float tx = getStepFloat(animStartTime, speed, palette.numColors);
    AlaColor c = palette.getPalColor(tx);
    int rand = random(palette.numColors);
    for(int x=0; x<numLeds; x++)
    {
		if (random(p) ==1){
        leds[x] = c.scale(1);
		}else{
		leds[x] = c.scale(0);
		}
	}
}

void AlaLedRgb::sparkle2()
{
    int p = speed/10;
    for(int x=0; x<numLeds; x++)
    {
        if(random(p)==0)
            leds[x] = palette.colors[random(palette.numColors)];
        else
            leds[x] = leds[x].scale(0.88);
    }
}


void AlaLedRgb::strobo()
{
    int t = getStep(animStartTime, speed, ALA_STROBODC);

    AlaColor c = palette.colors[0].scale(t==0);
    for(int x=0; x<numLeds; x++)
    {
        leds[x] = c;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
// Shifting effects
////////////////////////////////////////////////////////////////////////////////////////////

void AlaLedRgb::pixelShiftRight()
{
    int t = getStep(animStartTime, speed, numLeds);
    float tx = getStepFloat(animStartTime, speed, palette.numColors);
    AlaColor c = palette.getPalColor(tx);
	
	 for(int x=0; x<numLeds; x++)
    {
		int k =(x==t ? 1:0);
        for (int n=0;n<thrshldNumberLed;n++){
            k =  k or (x==t+gap*n ? 1:0) or (x==t-gap*n ? 1:0);
		    }
		leds[x] = c.scale(k);
	}
	middle();
}

void AlaLedRgb::pixelShiftLeft()
{
    int t = getStep(animStartTime, speed, numLeds);
    float tx = getStepFloat(animStartTime, speed, palette.numColors);
    AlaColor c = palette.getPalColor(tx);

    for(int x=0; x<numLeds; x++)
    {
		int k =(x==(numLeds-1-t) ? 1:0);
         for (int n=0;n<thrshldNumberLed;n++){
            k =  k or (x==(numLeds-1-t)+gap*n ? 1:0) or (x==(numLeds-1-t)-gap*n ? 1:0);
		    }
        leds[x] = c.scale(k);
    }
	middle();
}

void AlaLedRgb::pixelSmoothShiftRight()
{
    float t = getStepFloat(animStartTime, speed, numLeds+1);
    float tx = getStepFloat(animStartTime, speed, palette.numColors);
    AlaColor c = palette.getPalColor(tx);

    for(int x=0; x<numLeds; x++)
    {
        float k = max(0, (-abs(t-1-x)+thrshldNumberLed));
        leds[x] = c.scale(k);
    }
	middle();
}

void AlaLedRgb::pixelSmoothShiftLeft()
{
    float t = getStepFloat(animStartTime, speed, numLeds+1);
    float tx = getStepFloat(animStartTime, speed, palette.numColors);
    AlaColor c = palette.getPalColor(tx);

    for(int x=0; x<numLeds; x++)
    {
        float k = max(0, (-abs(numLeds-t-x)+thrshldNumberLed));
        leds[x] = c.scale(k);
    }
	middle();
}

void AlaLedRgb::customPixelShift() {
  
  long time =0;
  time = millis();
  int t = getStep(animStartTime, speed, numLeds);
  float tx = getStepFloat(animStartTime, speed, palette.numColors);
  AlaColor c = palette.getPalColor(tx);
  byte red = 0xff;
  byte blue,green = 0;
  int speedDelay=50;
  int k = 100;
  int entrance = 1;
    
    if (entrance ==1){	
	for(int x=0; x<numLeds; x++)
    {
        leds[x] = c.scale(0);
    }
	}entrance = 0;
	
    for (int q=0; q < 56-thrshldNumberLed; q++) {
     if (speed <10) {speed = 100;}
	 if (time %(speed/10)==0){
	 for (int i=0; i < numLeds-q; i=i+(56-thrshldNumberLed)) {
        for (int z=0;z<gap;z++){
		neopixels->setPixelColor(i+q+(z-1),red, green, blue);    //turn every third pixel on
		}
	  }
	  neopixels->show();
	 }time = millis();
     	  for (int i=0; i < numLeds-q; i=i+(56-thrshldNumberLed)) {
       for (int z=0;z<gap;z++){
		neopixels->setPixelColor(i+q+(z-1),0, 0, 0);    //turn every third pixel of
	   }
      }
     
    }
	middle();
}

// Bounce back and forth
void AlaLedRgb::pixelBounce()
{
    int t = getStep(animStartTime, speed, 2*numLeds-2);
    float tx = getStepFloat(animStartTime, speed, palette.numColors);
    AlaColor c = palette.getPalColor(tx);

    for(int x=0; x<numLeds; x++)
    {
        int k = x==(-abs(t-numLeds+1)+numLeds-1) ? 1:0;
        leds[x] = c.scale(k);
    }
	middle();
}
    int down = 1;
	int Entrance = 1;

// Bounce back and forth
/*void AlaLedRgb::pixelBounceExp()
{   

    static long lastRefresh;
	lastRefresh = millis();
	int t = getStep(animStartTime, speed, 2*numLeds-2);
    float tx = getStepFloat(animStartTime, speed, palette.numColors);
    AlaColor c = palette.getPalColor(tx);
	if (Entrance == 1){
	  setNumberOfLeds(numLeds);
	  Entrance = 0;
	}
	if ((lastRefresh %(speed/40))==0){
	  
	  if (down == 1){
	  setNumberOfLeds(numLeds-1);
	  }if (down == 0){
	  setNumberOfLeds(numLeds+1);
	  }
	}
	Serial.println(down);
	lastRefresh = millis();
      
	if ((getNumberOfLeds() <2) and (down == 1)){
         setNumberOfLeds(numLeds);
		 down =0;
	}
	
	if ((getNumberOfLeds() >55)and (down == 0)){
         setNumberOfLeds(numLeds);
		 down =1;
	}
	
	for(int x=0; x<getNumberOfLeds(); x++)
    {
        int k = x==(-abs(t-numLeds+1)+numLeds-1) ? 1:0;
        leds[x] = c.scale(k);
    }
	middle();
}
*/
void AlaLedRgb::comet()
{
    float l = numLeds/2; 
    float t = getStepFloat(animStartTime, speed, 2*numLeds-l);
    float tx = getStepFloat(animStartTime, speed, palette.numColors);
    AlaColor c = palette.getPalColor(tx);
   
	for (int n=0;n<thrshldNumberLed;n++){
      float k = 0;
	   for(int x=0; x<numLeds; x++)	  
      {
        k = max(0, (-abs(t-1-x)*n+thrshldNumberLed));
		if (k>(n/2*thrshldNumberLed)){
	        if (x+2 <numLeds){
		      leds[x] = c.scale(k-(n/2*thrshldNumberLed));

		      leds[x+2] = c.scale(k-(n/2*thrshldNumberLed));
			}
		}
}
    }
	
	 for(int x=0; x<numLeds; x++)
    {
        float k = constrain( (((x-t)/thrshldNumberLed+1.2f))*(((x-t)<0)? 1:0), 0, 1);
        leds[x] = c.scale(k);
    }
	middle();

}

void  AlaLedRgb::falling_star()
{
   float motifNumber = 1;
   
   int t = getStep(animStartTime, speed, numLeds);
   float tx = getStepFloat(animStartTime, speed, palette.numColors);
   AlaColor c = palette.getPalColor(tx);
   int k = 0;
   int k2 = 0;
   
   for(int x=0; x<numLeds; x++)
    {
		int k =(x==t ? 1:0);
		for (int n=1;n<thrshldNumberLed+1;n++){
      k = k or (n*x==t+1 ? 0.88:0) or (n*x==t+2 ? 0.66:0) or (n*x==t+3 ? 0.44:0) or (n*x==t+4 ? 0.22:0);
		} 
		leds[x] = c.scale(k);
	  
	}
  middle(); 
}

void AlaLedRgb::cometCol()
{
    float l = numLeds/2;  // length of the tail
    float t = getStepFloat(animStartTime, speed, 2*numLeds-l);

    AlaColor c;
    for(int x=0; x<numLeds; x++)
    {
        float tx = mapfloat(max(t-x, 0), 0, numLeds/1.7, 0, palette.numColors-1);
        c = palette.getPalColor(tx);
        float k = constrain( (((x-t)/l+1.2f))*(((x-t)<0)? 1:0), 0, 1);
        leds[x] = c.scale(k);
    }
	middle();
}

void AlaLedRgb::pixelSmoothBounce()
{
    float t = getStepFloat(animStartTime, speed, 2*numLeds-2);
    AlaColor c = palette.getPalColor(getStepFloat(animStartTime, speed, palette.numColors));

    for(int x=0; x<numLeds; x++)
    {
        float k = constrain((-abs(abs(t-numLeds+1)-x)+1), 0, 1);
        leds[x] = c.scale(k);
    }
	middle();
}

// Bounce back and forth
void AlaLedRgb::pixelSmoothBounceExp()
{   
    static long lastRefresh;
	lastRefresh = millis();
	float t = getStep(animStartTime, speed, 2*numLeds-2);
    float tx = getStepFloat(animStartTime, speed, palette.numColors);
    AlaColor c = palette.getPalColor(tx);
	if (Entrance == 1){
	  setNumberOfLeds(numLeds);
	  Entrance = 0;
	}
	if ((lastRefresh %(speed/40))==0){
	  
	  if (down == 1){
	  setNumberOfLeds(numLeds-1);
	  }if (down == 0){
	  setNumberOfLeds(numLeds+1);
	  }
	}
	lastRefresh = millis();
      
	if ((getNumberOfLeds() <2) and (down == 1)){
         setNumberOfLeds(numLeds);
		 down =0;
	}
	
	if ((getNumberOfLeds() >55)and (down == 0)){
         setNumberOfLeds(numLeds);
		 down =1;
	}
	
	for(int x=0; x<getNumberOfLeds(); x++)
    {
        float k = constrain((-abs(abs(t-numLeds+1)-x)+1), 0, 1);
        leds[x] = c.scale(k);
    }
	middle();
}

void AlaLedRgb::larsonScanner2()
{
    float l = numLeds/4;
    float t = getStepFloat(animStartTime, speed, 2*numLeds-2);
    AlaColor c = palette.getPalColor(getStepFloat(animStartTime, speed, palette.numColors));

    for(int x=0; x<numLeds; x++)
    {
        float k = constrain((-abs(abs(t-numLeds+1)-x)+l), 0, 1);
        leds[x] = c.scale(k);
    }
	middle();
}
/*
void AlaLedRgb::larsonScanner_both()
{
    float l = numLeds/4;  // 2>7, 3-11, 4-14
    float t = getStepFloat(animStartTime, speed, 2*numLeds+(l*4-1));
    AlaColor c = palette.getPalColor(getStepFloat(animStartTime, speed, palette.numColors));

    for(int x=0; x<numLeds; x++)
    {

        float k = constrain((-abs(abs(t-numLeds-2*l)-x-l)+l), 0, 1);
        leds[x] = c.scale(k);
    }
	middle();
}
*/
void AlaLedRgb::larsonScanner()
{
    float l = numLeds/4;  
    float t1 = getStepFloat(animStartTime, speed, 2*numLeds-2);
	float t2 = getStepFloat(animStartTime, speed, 2*numLeds+(l*4-1));
    float t =0;   
    AlaColor c = palette.getPalColor(getStepFloat(animStartTime, speed, palette.numColors));
    
	float k = 0;
	
	for (int i=0 ; i< numLeds;i++){
	    leds[i] = 0x000000;
    }	
	for (int i=0 ; i< thrshldNumberLed;i++){
	
    for(int x=i*(numLeds/thrshldNumberLed); x<(i+1)*(numLeds/thrshldNumberLed); x++)
    {
		if (i%2==0){
			t=t2;
			k = constrain((-abs(abs(t-numLeds-2*l)-x-l)+l), 0, 1) ;
		}else{ 
		    t = t1;
		    k = constrain((-abs(abs(t-numLeds+1)-x)+1), 0, 1);
		}
        
        leds[x] = c.scale(k);
      }  
	}
	middle();
}

////////////////////////////////////////////////////////////////////////////////////////////
// Fading effects
////////////////////////////////////////////////////////////////////////////////////////////

void AlaLedRgb::fadeIn()
{
    float s = getStepFloat(animStartTime, speed, 1);
    AlaColor c = palette.colors[0].scale(s);

    for(int x=0; x<numLeds; x++)
    {
        leds[x] = c;
    }
}


void AlaLedRgb::fadeOut()
{
    float s = getStepFloat(animStartTime, speed, 1);
    AlaColor c = palette.colors[0].scale(1-s);

    for(int x=0; x<numLeds; x++)
    {
        leds[x] = c;
    }
}


void AlaLedRgb::fadeInOut()
{
    float s = getStepFloat(animStartTime, speed, 2) - 1;
    AlaColor c = palette.colors[0].scale(abs(1-abs(s)));

    for(int x=0; x<numLeds; x++)
    {
        leds[x] = c;
    }
}

void AlaLedRgb::glow()
{
    float s = getStepFloat(animStartTime, speed, TWO_PI);
    float k = (-cos(s)+1)/2;

    for(int x=0; x<numLeds; x++)
    {
        leds[x] = palette.colors[0].scale(k);
    }
}

void AlaLedRgb::plasma()
{
    float t = getStepFloat(animStartTime, speed, numLeds);

    for(int x=0; x<numLeds; x++)
    {
        AlaColor c1 = palette.getPalColor((float)((x+t)*palette.numColors)/numLeds);
        AlaColor c2 = palette.getPalColor((float)((2*x-t+numLeds)*palette.numColors)/numLeds);
        leds[x] = c1.interpolate(c2, 0.5);
    }
}


void AlaLedRgb::fadeColors()
{
    float t = getStepFloat(animStartTime, speed, palette.numColors-1);
    AlaColor c = palette.getPalColor(t);
    for(int x=0; x<numLeds; x++)
    {
        leds[x] = c;
    }

}

void AlaLedRgb::pixelsFadeColors()
{
    float t = getStepFloat(animStartTime, speed, palette.numColors);

    for(int x=0; x<numLeds; x++)
    {
        AlaColor c = palette.getPalColor(t+7*x);
        leds[x] = c;
    }
	middle();
}

void AlaLedRgb::fadeColorsLoop()
{
    float t = getStepFloat(animStartTime, speed, palette.numColors);
    AlaColor c = palette.getPalColor(t);
    for(int x=0; x<numLeds; x++)
    {
        leds[x] = c;
    }
	middle();
}


void AlaLedRgb::cycleColors()
{
    int t = getStep(animStartTime, speed, palette.numColors);

    for(int x=0; x<numLeds; x++)
    {
        leds[x] = palette.colors[t];
    }
	middle();
}


void AlaLedRgb::movingBars()
{
    int t = getStep(animStartTime, speed, numLeds);

    for(int x=0; x<numLeds; x++)
    {
        leds[x] = palette.colors[(((t+x)*palette.numColors)/numLeds)%palette.numColors];
    }
	middle();
}
/*
void AlaLedRgb::movingColors()
{
    float t = getStepFloat(animStartTime, speed, numLeds);

    for(int x=0; x<numLeds; x++)
    {
        leds[x] = palette.getPalColor((float)((x+t)*palette.numColors)/numLeds);
    }
}
*/
void AlaLedRgb::movingGradient()
{
    float t = getStepFloat(animStartTime, speed, numLeds);

    for(int x=0; x<numLeds; x++)
    {
		if (x<5){
        leds[x] = palette.getPalColor((float)((x-(x%thrshldNumberLed)+1+t)*palette.numColors)/numLeds);
    }else{
	    leds[x] = palette.getPalColor((float)((x-(x%thrshldNumberLed)+t)*palette.numColors)/numLeds);
	 }
	}
	middle();
}

/*******************************************************************************
* FIRE
* Porting of the famous Fire2012 effect by Mark Kriegsman.
* Actually works at 50 Hz frame rate with up to 50 pixels.
*******************************************************************************/
void AlaLedRgb::fire()
{
    // COOLING: How much does the air cool as it rises?
    // Less cooling = taller flames.  More cooling = shorter flames.
    // Default 550
    #define COOLING  600

    // SPARKING: What chance (out of 255) is there that a new spark will be lit?
    // Higher chance = more roaring fire.  Lower chance = more flickery fire.
    // Default 120, suggested range 50-200.
    #define SPARKING 120

    // Array of temperature readings at each simulation cell
    static byte *heat = NULL;

    // Initialize array if necessary
    if (heat==NULL)
        heat = new byte[numLeds];

    // Step 1.  Cool down every cell a little
    int rMax = (COOLING / numLeds) + 2;
    for(int i=0; i<numLeds; i++)
    {
        heat[i] = max(((int)heat[i]) - random(0, rMax), 0);
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for(int k=numLeds-1; k>=3; k--)
    {
        heat[k] = ((int)heat[k - 1] + (int)heat[k - 2] + (int)heat[k - 3] ) / 3;
    }

    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if(random(255) < SPARKING)
    {
        int y = random(7);
        heat[y] = min(heat[y] + random(160, 255), 255);
    }

    // Step 4.  Map from heat cells to LED colors
    for(int j=0; j<numLeds; j++)
    {
        float colorindex = (float)(heat[j] * (palette.numColors-1) ) / 256;
        leds[j] = palette.getPalColor(colorindex);
    }
	middle();
}

void AlaLedRgb::bouncingBalls()
{
    static long lastRefresh;

    if (pxPos==NULL)
    {
        // allocate new arrays
        pxPos = new float[palette.numColors];
        pxSpeed = new float[palette.numColors];

        for (int i=0; i<palette.numColors; i++)
        {
            pxPos[i] = ((float)random(255))/255;
            pxSpeed[i] = 0;
        }
        lastRefresh = millis();

        return; // skip the first cycle
    }

    float speedReduction = (float)(millis() - lastRefresh)/5000;
    lastRefresh = millis();

    for (int i=0; i<palette.numColors; i++)
    {
        if(pxSpeed[i]>-0.04 and pxSpeed[i]<0 and pxPos[i]>0 and pxPos[i]<0.1)
            pxSpeed[i]=(0.09)-((float)random(10)/1000);

        pxPos[i] = pxPos[i] + pxSpeed[i];
        if(pxPos[i]>=1)
        {
            pxPos[i]=1;
        }
        if(pxPos[i]<0)
        {
            pxPos[i]=-pxPos[i];
            pxSpeed[i]=-0.91*pxSpeed[i];
        }

        pxSpeed[i] = pxSpeed[i]-speedReduction;
    }

    for (int x=0; x<numLeds ; x++)
    {
        leds[x] = 0;
    }
    for (int i=0; i<palette.numColors; i++)
    {
        int p = mapfloat(pxPos[i], 0, 1, 0, numLeds-1);
        leds[p] = leds[p].sum(palette.colors[i]);
    }
  middle();
}

void AlaLedRgb::bubbles()
{/*
    static long lastRefresh;

    if (pxPos==NULL)
    {
        // allocate new arrays
        pxPos = new float[palette.numColors];
        pxSpeed = new float[palette.numColors];

        for (int i=0; i<palette.numColors; i++)
        {
            pxPos[i] = ((float)random(255))/255;
            pxSpeed[i] = 0;
        }
        lastRefresh = millis();

        return; // skip the first cycle
    }

    float speedDelta = (float)(millis() - lastRefresh)/80000;
    lastRefresh = millis();

    for (int i=0; i<palette.numColors; i++)
    {
        //pos[i] = pos[i] + speed[i];
        if(pxPos[i]>=1)
        {
            pxPos[i]=0;
            pxSpeed[i]=0;
        }
        if(random(20)==0 and pxPos[i]==0)
        {
            pxPos[i]=0.0001;
            pxSpeed[i]=0.0001;
        }
        if(pxPos[i]>0)
        {
            pxPos[i] = pxPos[i] + pxSpeed[i];
            pxSpeed[i] = pxSpeed[i] + speedDelta;
        }
    }

    for (int x=0; x<numLeds ; x++)
    {
        leds[x] = 0;
    }
    for (int i=0; i<palette.numColors; i++)
    {
        if (pxPos[i]>0)
        {
            int p = mapfloat(pxPos[i], 0, 1, 0, numLeds-1);
            AlaColor c = palette.colors[i].scale(1-(float)random(10)/30); // add a little flickering
            leds[p] = c;
        }
    }
*/middle();
}
/*void AlaLedRgb::shine()
{
    int t = getStep(animStartTime, speed, numLeds);
    float tx = getStepFloat(animStartTime, speed, palette.numColors);
    AlaColor c = palette.getPalColor(tx);
	float r = 0;
    for(int x=0; x<numLeds; x++)
    {
        r = random(100);
		leds[x] = c.scale(r/100);
    }
}
*/
void AlaLedRgb::twinkle()
{
	static long lastRefresh;
	lastRefresh = millis();
    int t = getStep(animStartTime, speed, numLeds);
    float tx = getStepFloat(animStartTime, speed, palette.numColors);
    AlaColor c = palette.getPalColor(tx);
	float r = 0;
    float g = 0;
	if (speed <100) {speed = 100;}
    if ((lastRefresh %(speed/100))==0){
	for(int x=0; x<numLeds; x++)
    {
	  leds[x] = c.scale(0);
	}
	for(int x=0; x<thrshldNumberLed; x++)
    {
        r = random(100);
		g = random(56);
		
		leds[int(g)] = palette.colors[(((t+x)*palette.numColors)/numLeds)%palette.numColors].scale(r/100);
	}}lastRefresh = millis();
}

void AlaLedRgb::visualizer()
{
	setNumberOfLeds(60);
	static long lastRefresh;
	lastRefresh = millis();
    int t = getStep(animStartTime, speed, numLeds);
    float tx = getStepFloat(animStartTime, speed, palette.numColors);
    AlaColor c = palette.getPalColor(tx);
	AlaColor black = 0x000000;
	  
	 if ((somme >= soundSensitivity )and (lastRefresh%50==0)){
		  for(int x=0; x<numLeds; x++)
          {
	      leds[x] = c.scale(1);
		  }delayMicroseconds(20);
	}else{
		 for(int x=0; x<numLeds; x++)
          {
	      leds[x] = black.scale(round(random(100)/100));
       }delayMicroseconds(20);
	}
}

void AlaLedRgb::simiSpectrum(){
    /*  setNumberOfLeds(60);
	  bool entrance = true;
	  int val = int(56*round(somme/mic3Range));
      static long lastRefresh;
	  lastRefresh = millis();
      int t = getStep(animStartTime, speed, numLeds);
      float tx = getStepFloat(animStartTime, speed, palette.numColors);
      AlaColor c = palette.getPalColor(tx);
	  AlaColor black = 0x000000;
		for(int x=0; x<56; x++)
          {
			leds[x] = black.scale(1);  
		  }entrance = false;	  
		  
	  if ((val<= 5)and ((lastRefresh%50) ==0)){
		 for(int x=0; x<numLeds-51;x++){
		   leds[x] = c.scale(1);
		 }delayMicroseconds(20);
		}else if ((val> numLeds-51)and((lastRefresh%50) ==0)){
		  for(int x=0; x<val;x++){
		   leds[x] = c.scale(1);
		 }delayMicroseconds(20);
		}else if ((val>numLeds-1)and((lastRefresh%50) ==0)){
			for(int x=0; x<numLeds-1;x++){
		   leds[x] = c.scale(1);
		 }delayMicroseconds(20);
		}else {
			delayMicroseconds(20);
		}*/
    }

void AlaLedRgb::middle(){
//	Serial.print("middle:");
	Serial.println(booleanV);
	if (booleanV ==1){
	for (int y=0;y<numLeds/2;y++){
      leds[y] = leds[numLeds-y];
	  }
	}else{ 
	//nothing
	}
}