import ddf.minim.*;
import ddf.minim.analysis.*;
import processing.serial.*;

Minim minim;
BeatDetect beat;
AudioInput in;

int time;
int numBands = 16;
float[] eRadius;
color[] displayColors;
float levelScale = 1.0;
float levelIncrement = 0.1;
float minLevel = 1.0;

boolean kick = false;
boolean snare = false;
boolean hat = false;

Serial mon_port; // L'objet qui gère le port série

void setup()
{
  time=millis();
  String nom_du_port = "COM23";
  mon_port = new Serial(this, nom_du_port, 115200);
  mon_port.write('0');

  eRadius = new float[numBands];
  displayColors = new color[numBands];
  for(int i = 0; i < numBands; ++i)
  {
    eRadius[i] = 20;
    displayColors[i] = color(0, 0, 0);
  }
  size(1000, 400, P3D);
  minim = new Minim(this);
  in = minim.getLineIn(Minim.STEREO);
  beat = new BeatDetect(in.bufferSize(), in.sampleRate());
  beat.setSensitivity(100);

  ellipseMode(RADIUS);
  stroke(255, 255, 255);
  background(0);
}
color pixelOnColor = color(25, 25, 25, 255);
color pixelOffColor = color(0, 0, 0, 255);

boolean pixelsOn = true;
void togglePixels(int d)
{
  color pixelsColor;
  if (pixelsOn)
  {
    pixelsOn = false;
    pixelsColor = pixelOnColor;
  }
  else
  {
    pixelsOn = true;
    pixelsColor = pixelOffColor;
  }
  background(pixelsColor);
}
int p = 0;


void draw()
{
  background(0);
  detectBeat();
}
void detectBeat()
{
  if (keyPressed)
  {
     if (key == '+')
     {
       levelScale += levelIncrement;
       println("Level scale: "+levelScale);
     }
     else if (key == '-')
     {
       levelScale -= levelIncrement;
       if (levelScale <= 0.0001)
       {
         levelScale = 0.0001;
       }
       println("Level scale: "+levelScale);
     }
     else if (key == '.')
     {
       minLevel += levelIncrement;
       println("Min level: "+minLevel);
     }
     else if (key == ',')
     {
       minLevel -= levelIncrement;
         println("Min level: "+minLevel);
     } else if (key == '0')
     {
      mon_port.write("0");
     }
     else if ((key == 'K')||(key == 'k'))
     {
      kick = true;
      snare = hat = false;
      
     }
     else if ((key == 'S')||(key == 's'))
     {
     snare=true;
      kick = hat = false;
     }
     else if ((key == 'H')||(key == 'h'))
     {
      hat=true;
       snare = kick = false;
     } else if ((key == 'A')||(key == 'a'))
     {
      
       hat = snare = kick = false;
     }
     
  }
  beat.detect(in.mix);
  int size = beat.detectSize();
  float w = (size * 1.0) / (numBands * 1.0);
  float level = abs(in.mix.level()) * levelScale * 100 * 2;

  for (int bandIndex = 0; bandIndex < numBands; bandIndex++)
  {
    int band = (int)(w * (bandIndex + 1) - w / 2.0);
    if (beat.isOnset(band) && level >= minLevel)
    {
      eRadius[bandIndex] = level;

      int red = 0;
      int green =  0;
      int blue = 0;

      if ((beat.isKick())&&(!hat)&&(!snare))
      {
        if(millis()-time>=0){
        time=millis();
        mon_port.write("7");
        }
        red = 255;
        
      }
      else if ((beat.isSnare())&&(!hat)&&(!kick))
      {
        if(millis()-time>=0){
        time=millis();   
        mon_port.write("8");
        }
        green = 255;
      }
      else if ((beat.isHat())&&(!kick)&&(!snare))
      {
       if(millis()-time>=0){
        mon_port.write("9"); 
        time=millis();   
        }
        blue = 255;
      }
      else
      {
        red = green = blue = 255;
        mon_port.write("0");
      }
      displayColors[bandIndex] = color(red, green, blue, 200);
      
    }
    drawCircle(bandIndex, numBands, band, level, eRadius[bandIndex]);
    eRadius[bandIndex] *= 0.8;
  }
}
void drawCircle(int bandIndex, int numBands, int band, float level, float radius)
{
  fill(displayColors[bandIndex]);
  float x = width * (bandIndex + 1)/(numBands + 1);
  float y = height / 2.0;
  ellipse(x, y, radius, radius);
  fill(color(255, 255, 255, 255));
  float stry = height - 3 * 20;
  if (bandIndex == 0)
  {
    text("Index", 10, stry);
  }
  text(str(bandIndex), x, stry);
  stry += 20;
  if (bandIndex == 0)
  {
    text("Band", 10, stry);
  }
  text(str(band), x, stry);
  stry += 20;
  if (bandIndex == 0)
  {
    text("Level", 10, stry);
  }
  text(nf(level,3,2), x, stry);
}
