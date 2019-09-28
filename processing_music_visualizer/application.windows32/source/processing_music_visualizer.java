import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import ddf.minim.analysis.*; 
import ddf.minim.*; 
import processing.serial.*; 
import ddf.minim.signals.*; 
import ddf.minim.effects.*; 
import controlP5.*; 
import cc.arduino.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class processing_music_visualizer extends PApplet {










Arduino arduino;
int ledWs = 7; // LED WS2812b connected to digital pin 7

boolean button = false;
Serial myPort;
Minim minim;
AudioPlayer jingle;
AudioInput input;
FFT fft;
int[][] colo=new int[300][3];
float monVolumeSon;

PFont font;
PFont Helvetica;
PFont Tahoma;
PFont Kalinga;
PFont Khmer;
PFont Courier;


int colorChooser = 0;
int redChooser = PApplet.parseInt(random(255));
int greenChooser = PApplet.parseInt(random(255));
int blueChooser = PApplet.parseInt(random(255));

int l,j,k = 0;
int R = 40;
int G = 200;
int B = 200;
ControlP5 MyController1;
ControlP5 MyController2;

boolean button1 = false;

public void setup()
{

  //arduino = new Arduino(this, Arduino.list()[0], 57600);
  
  noStroke();
  frame.setResizable(true);
  frame.setTitle("Audio visualizer");
  //Play local music:

  /* song = minim.loadFile("aaa.mp3", 2048);// change the file name to your owns, make sure your mp3 file in the /data/ folder.
  song.play()
  */

  /////////////////
  textFont(createFont("Helvetica", 16));
  textAlign(CENTER);
  // arduino.pinMode(ledWs, Arduino.OUTPUT);


/*Slider*/////////////////////////////////////////////////////

  MyController1 = new ControlP5(this);
  Slider slider1 = MyController1.addSlider("bar height").setRange(1,100).setSensitivity(2)
     .setLabel("bar height")
     .setValue(50)
     .setPosition(10,100)
     .setSize(150,13)
     .setSliderMode(Slider.FLEXIBLE)
     .setColorValue(color(255))
     .setColorActive(color(155))
     .setColorForeground(color(155))
     .setColorBackground(color(255, 0, 0))
     ;

     MyController1.addButton("Default")
         .setValue(0)
         .setPosition(10,160)
         .setSize(39,19)
         ;

     MyController1.addButton("Exit")
         .setValue(0)
         .setPosition(430,290)
         .setSize(39,19)
         ;

  /*   MyController1.addToggle("Play")
          .setPosition(400,25)
          .setSize(40,10)
          .setValue(false)
          .setMode(ControlP5.SWITCH)
          ;
   */

   MyController2 = new ControlP5(this);
   Slider slider2 = MyController2.addSlider("ellipse width").setRange(2,100).setSensitivity(2)
      .setLabel("ellipse width")
      .setValue(50)
      .setPosition(10,125)
      .setSize(150,13)
      .setSliderMode(Slider.FLEXIBLE)
      .setColorValue(color(255))
      .setColorActive(color(155))
      .setColorForeground(color(155))
      .setColorBackground(color(255, 0, 0))
      ;

//////////////////////////////////////////////////////////////
  minim = new Minim(this);
  input = minim.getLineIn(Minim.STEREO, 4096,44100,16); //type,bufferSize,sampleRate,bitDepth
  fft = new FFT(input.bufferSize(), input.sampleRate());

  text("Off",20,20);
  //myPort = new Serial(this,Serial.list()[0],9600);
}

public void draw()
{
  if (!button) {
    text("Off",20,20);
   }else{
    text("On",20,20);
   }
//  myPort.write("Init system");
  background(0,0,0);

  //Values of Slider //////////////////////////////////////////////////////////////
   float valueSlider1 = MyController1.getController("bar height").getValue();
   float valueSlider2 = MyController2.getController("ellipse width").getValue();
  /////////////////////////////////////////////////////////////////////////////////
  // float valueButton1 = MyController1.getController("Default").getValue();

  fft.forward(input.mix);

  for(int i = 0; i < fft.specSize()-1; i++)
  {
    monVolumeSon = (input.left.get(i)+input.right.get(i)/2)*50;
   rect(1+5*fft.getBand(i),2,2,20);
  // fill(250,0,0);
    fill(l,j,k);
   ellipse(i , 250 , valueSlider2/14.2857f+0.01f,fft.getBand(i)%valueSlider1 + 15);
   //rect(i , 300 , 15,fft.getBand(i) + 10);

  //stroke(150);
  // myPort.write("valeurs mesurées :" + fft.getBand(i));
  l++;
 }
 strokeWeight(abs(monVolumeSon));
 //line(width/4,height/2,width*3/4,height/2);

/*if (MyController1.getController("Play").getValue()==false){
  minim.stop();
}
*/
}
public void stop(){
  //song.close();
  minim.stop();
  super.stop();
}

// When the mouse is pressed, the state of the button is toggled.
// Try moving this code to draw() like in the rollover example.  What goes wrong?
public void mousePressed() {
  if (mouseX > 20 && mouseX < 20+20 && mouseY > 20 && mouseY < 20+20) {
    button = !button;
  }
  if (mouseX > 10 && mouseX < 49 && mouseY > 160 && mouseY < 179) {
    MyController1.getController("bar height").setValue(50);
    MyController2.getController("ellipse width").setValue(50);
  }
  if (mouseX > 430 && mouseX < 469 && mouseY > 290 && mouseY < 309) {
    exit();
  }
  if (mouseX > 420 && mouseX < 450 && mouseY > 25 && mouseY < 35) {
    MyController1.getController("Play").setValue(1);

  }else if (mouseX > 390 && mouseX < 400 && mouseY > 25 && mouseY < 35) {
      MyController1.getController("Play").setValue(0);
    }
}
  public void settings() {  size(480, 320); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "processing_music_visualizer" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
