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
import g4p_controls.*; 
import cc.arduino.*; 
import javax.swing.JFrame; 
import javax.swing.JOptionPane; 
import javax.swing.JColorChooser; 
import java.awt.Color; 
import java.awt.Frame; 

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

int numero_du_port = 0;
Serial mon_port; // L'objet qui gère le port série
char dernier_envoye = ' ';  // Dernier octet envoyé
char dernier_recu = ' ';  // Dernier octet reçu

boolean entrance = true;
boolean button = false;
Serial myPort;
Minim minim;
AudioPlayer jingle;
AudioInput input;
BeatDetect beat;
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
public int col = color(255,0,0,50);

public Color BEAT;
//public Color r,g,b;
Color javaColor;

int l,j,k = 0;
int R = 40;
int G = 200;
int B = 200;
double maxi;
double mini;
double h;
double s;
double v;

GButton btnMakeWindow;
GWindow window;

ControlP5 MyController1;
ControlP5 MyController2;
ColorPicker cp;
DropdownList d1;

boolean button1 = false;
boolean button2 = false;
boolean buttonPlay = false;

PImage image;
PImage imageIntro;
PImage colorWheel;
PImage m;

//grid/////////////////////
FFT fftR, fftL;
float x, y;
int grid=32;
int spacing=1;
float yScale = 1;
ColorWheel myColorWheel;
int time;

int numBands = 16;
float[] eRadius;
int[] displayColors;
int[] beatColors;
float levelScale = 1.0f;
float levelIncrement = 0.1f;
float minLevel = 1.0f;

float kickSize,snareSize,hatSize;
AudioPlayer song;
///////////////////////////
public void setup()
{
  time = millis();
  image = loadImage("space.jpg");
  colorWheel=loadImage("colorPicker.jpg");

////////////Image to display before displaying application (Usefull to load images...)
  imageIntro = loadImage("audioVisu.jpg");
  //tint(0, 0, 255);
  background(imageIntro);
//  ellipseMode(CENTER);
////////////////////////////////////////////////
  String nom_du_port = Serial.list()[0];
  mon_port = new Serial(this, nom_du_port, 115200);
  mon_port.write('0');
  
  
  noStroke();
//  noLoop();
  frame.setResizable(false);
  frame.setTitle("Audio visualizer");
  //Play local music:

  /* song = minim.loadFile("aaa.mp3", 2048);// change the file name to your owns, make sure your mp3 file in the /data/ folder.
  song.play()
  */

  /////////////////
  textFont(createFont("Helvetica", 16));
  textAlign(CENTER);
  // arduino.pinMode(ledWs, Arduino.OUTPUT);

  //colorWheel.set(200,120,color(0));

/*Slider*/////////////////////////////////////////////////////

  MyController1 = new ControlP5(this);

  myColorWheel = MyController1.addColorWheel("Lightness", 210 , 5 ,200 )
  .setRGB(color(255,255,255));


  Slider slider1 = MyController1.addSlider("bar height").setRange(1,100).setSensitivity(2)
     .setLabel("bar height")
     .setValue(50)
     .setPosition(2,100)
     .setSize(150,13)
     .setSliderMode(Slider.FLEXIBLE)
     .setColorValue(color(255))
     .setColorActive(color(155))
     .setColorForeground(color(155))
     .setColorBackground(color(255, 0, 0))
     ;

     MyController1.addSlider("Saturation").setRange(0,100).setSensitivity(2)
        .setLabel("Saturation")
        .setValue(50)
        .setPosition(2,50)
        .setSize(150,13)
        .setSliderMode(Slider.FLEXIBLE)
        .setColorValue(color(255))
        .setColorActive(color(155))
        .setColorForeground(color(155))
        .setColorBackground(color(255, 0, 0))
        ;

      MyController1.addSlider("Brightness").setRange(0,100).setSensitivity(2)
         .setLabel("Brightness")
         .setValue(50)
         .setPosition(2,75)
         .setSize(150,13)
         .setSliderMode(Slider.FLEXIBLE)
         .setColorValue(color(255))
         .setColorActive(color(155))
         .setColorForeground(color(155))
         .setColorBackground(color(255, 0, 0))
         ;

     MyController1.addButton("Default")
         .setValue(0)
         .setPosition(10,150)
         .setSize(39,19)
         ;

     MyController1.addButton("Exit")
         .setValue(0)
         .setPosition(430,290)
         .setSize(39,19)
         ;

     MyController1.addButton("RGB EFFECTS")
         .setValue(0)
         .setPosition(418,185)
         .setSize(55,19)
         ;
  /*   ColorPicker picker = MyController1.addColorPicker("picker")
          .setPosition(210 ,160)
          .setColorValue(color(255, 128, 0, 128))
          ;*/
  /*   MyController1.addToggle("Play")
          .setPosition(400,25)
          .setSize(40,10)
          .setValue(false)
          .setMode(ControlP5.SWITCH)
          ;
   */
    d1 = MyController1.addDropdownList("buffer size")
          .setPosition(65, 153);

    customize(d1); // customize the first list

    noTint();

    MyController1.addButton("Play")
       .setPosition(400,20)
       .setImages(loadImage("Off.png"), loadImage("Off.png"), loadImage("Off.png"))  // button.setImages(defaultImage, rolloverImage, pressedImage);
       .updateSize() //Size : 66*24
    ;
    MyController1.addButton("Help")
       .setPosition(395,285)
       .setImages(loadImage("help.png"), loadImage("help.png"), loadImage("help.png"))  // button.setImages(defaultImage, rolloverImage, pressedImage);
       .updateSize() //Size : 24*24
    ;



  /*  MyController1.addButton("Hue")
       .setPosition(235,60)
       .setImages(loadImage("colorWheel.png"), loadImage("colorWheel.png"), loadImage("colorWheel.png"))  // button.setImages(defaultImage, rolloverImage, pressedImage); .updateSize() //Size : 66*24
    ;*/


  /*  MyController1.addNumberbox("numberboxValue")
     .setPosition(100,200)
     .setSize(100,14)
     .setRange(0,200)
     .setMultiplier(0.1) // set the sensitifity of the numberbox
     .setValue(100)
     ;
*/


   MyController2 = new ControlP5(this);
   Slider slider2 = MyController2.addSlider("width").setRange(2,100).setSensitivity(2)
      .setLabel("width")
      .setValue(50)
      .setPosition(2,125)
      .setSize(150,13)
      .setSliderMode(Slider.FLEXIBLE)
      .setColorValue(color(255))
      .setColorActive(color(155))
      .setColorForeground(color(155))
      .setColorBackground(color(255, 0, 0))
      ;

//////////////////////////////////////////////////////////////
  minim = new Minim(this);
  input = minim.getLineIn(Minim.STEREO); //type,bufferSize,sampleRate,bitDepth
//  beat = new BeatDetect(input.bufferSize(),input.sampleRate());
//  beat.setSensitivity(100);
//kickSize = snareSize = hatSize = 16;
  fft = new FFT(input.bufferSize(), input.sampleRate());
  fftR = new FFT (input.bufferSize (), input.sampleRate ());
  fftL = new FFT (input.bufferSize (), input.sampleRate ());
  //ellipseMode(RADIUS);


   MyController1.addKnob("Hue")
                .setRange(0,360)
                .setValue(0)
                .setPosition(260,45)
                .setRadius(50)
                .setNumberOfTickMarks(12)
                .setTickMarkLength(4)
                .snapToTickMarks(false)
                .setImage(colorWheel)
                .setColorForeground(color(255))
                .setColorBackground(color(0, 160, 160))
                .setColorActive(color(0,0,210))
                .setDragDirection(Knob.HORIZONTAL)
                .setViewStyle(Knob.ELLIPSE)
            //    .setFont(createFont("Futura", 12))
                ;

    MyController1.addKnob("Beat pulse / Volume")
                   .setRange(0,100)
                   .setValue(0)
                   .setPosition(380,60)
                   .setRadius(50)
                   .setDragDirection(Knob.HORIZONTAL)
                     ;

       MyController1.addButton("LED color")
          .setPosition(180,152)
         // .setImages(loadImage("colorPicker.jpg"), loadImage("colorPicker.jpg"), loadImage("colorPicker.jpg"))  // button.setImages(defaultImage, rolloverImage, pressedImage);
          .updateSize() //Size : 28*28
       ;
////////////////////////////////////////////////////////////////
  //myPort = new Serial(this,Serial.list()[0],9600);

  //ellipseMode(CENTER_RADIUS);
  delay(2000);

/*  colorMode(HSB,100);
  for(int x=0;x<150;x++){
    for(int y=0;y<150;y++){
      if(dist(200,200,x,y)<=190){
        stroke(map(atan2(x-200,y-200),-PI,PI,0,100),map(dist(200,200,x,y),0,190,0,100),100);
        point(x,y);
        }
      }
    }*/
//  noFill();
//  stroke(0);
//  ellipse(200,200,380,380);
//  m=get();
}

  public void draw(){



    if (mon_port.available() != 0) {
      // Conversion du int en char
      dernier_recu = PApplet.parseChar(mon_port.read());
      }
      //println("Dernier octet recu: " + dernier_recu);
      //println("Dernier octet envoye: " + dernier_envoye);

  //  image(m,0,0);
      if(mousePressed){
      fill(get(mouseX,mouseY));stroke(0);
      ellipse(mouseX,mouseY,30,30);
      }

  if (entrance){
      mon_port.write('0');
  entrance = false;
//  JOptionPane.showMessageDialog(null, "Audio Visualizer made by Debus ALexy", "Information", JOptionPane.INFORMATION_MESSAGE);
}

  fill(50, 10);
  rect(0, 0, width, height);

  if (!button) {
    //tint(0, 0, 255);
    text("Off",20,20);
   }else{
     tint(0,0,125);
     redraw();
    text("On",20,20);
   }
//  myPort.write("Init system");
  background(image);
  text("Hue",235,60);

  //Values of Slider //////////////////////////////////////////////////////////////
   float valueSlider1 = MyController1.getController("bar height").getValue();
   float valueSlider2 = MyController2.getController("width").getValue();

  /////////////////////////////////////////////////////////////////////////////////
  // float valueButton1 = MyController1.getController("Default").getValue();


  for(int i = 0; i < fft.specSize()-1; i++)
  {
    if (button2 == false){
    monVolumeSon = (input.left.get(i)+input.right.get(i)/2)*50;
  }else if (button2 == true){
    monVolumeSon = 0;
  }

   fill(250,0,0);
   fft.forward(input.mix);
   fftR.forward(input.right);
   fftL.forward(input.left);

   fftR.logAverages(11, 16);
   fftL.logAverages(11, 16);
    fill(col);

    if (buttonPlay){
      rect(1+5*fft.getBand(i),2,2,20);
      //println(1+5*fft.getBand(i));
      int sizeFft = PApplet.parseInt (1+5*fft.getBand(i));
      if (sizeFft >100){
        sizeFft = 100;
      }
      if (sizeFft <0){
        sizeFft = 0;
      }
      if (sizeFft <15){
        sizeFft+= 15;
      }

      //println(sizeFft+2);
      if ((sizeFft>=3)&&(millis()-time>=300)){
      mon_port.write(sizeFft);
    //  println(sizeFft);
      time=millis();
    }

      ellipse(i , 250 , valueSlider2/14.2857f+0.01f,fft.getBand(i)%valueSlider1 + 15);
    }else if (!buttonPlay){
      rect(1+5*0.01f,2,2,20);
      ellipse(i , 250 , valueSlider2/14.2857f+0.01f,fft.getBand(i)%0.01f + 15);
    }

  //stroke(150);
  // myPort.write("valeurs mesurées :" + fft.getBand(i));
  l++;
 }

//Linear method/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 for (int i=1; i <= fftR.specSize(); i+=fftR.specSize()/grid) { //for (int i=1; i <= fftL.specSize(); i+=fftL.specSize()/grid) {
     if (buttonPlay){

      if (second()%0.5f==0){
        MyController1.getController("Beat pulse / Volume").setValue(100*(fftR.getBand(i)+fftL.getBand(i))/2*yScale%valueSlider1);

        if (MyController1.getController("Beat pulse / Volume").getValue()<0.2f){
            MyController1.getController("Beat pulse / Volume").setValue(0);
        }
    }
       x = map(i, 0, (fftR.specSize()+fftL.specSize())/2, 0, width);
       y = map((fftR.getBand(i)+fftL.getBand(i))/2*yScale%valueSlider1, 0, 100, 0, height/3) ;
    }else if (!buttonPlay){
       MyController1.getController("Beat pulse / Volume").setValue(0);
      x = map(i, 0, (fftR.specSize()+fftL.specSize())/2, 0, width);
      y = map((fftR.getBand(i)+fftL.getBand(i))/2*0.01f*yScale%valueSlider1, 0, 100, 0, height/3) ;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       fill (102, 100, 250, 85);
      rect(x*valueSlider2/50+spacing, height, width/grid-2*spacing, -y);

       fill (170, 170, 170);
      rect(x*valueSlider2/50+spacing,height -20-y,width/grid-2*spacing,-5);
  }


//Log Method///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*for (int i=0; i <= fftL.avgSize(); i+=fftL.avgSize()/grid) {
    if (buttonPlay){
      x = map(i, 0, (fftR.avgSize()+fftL.avgSize())/2, 0, width);
      y = map((fftL.getAvg(i)+fftR.getAvg(i))/2*yScale%valueSlider1, 0, 100, 0, height/5) ;
   }else if (!buttonPlay){
     x = map(i, 0, (fftR.specSize()+fftL.specSize())/2, 0, width);
     y = map((fftL.getAvg(i)+fftR.getAvg(i))/2*0.01*yScale%valueSlider1, 0, 100, 0, height/5) ;
   }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   fill (102, 145, 250, 100);
 // Rechteck zeichnen
  rect(x*valueSlider2/50+spacing, height, width/grid-2*spacing, -y);
}
 strokeWeight(abs(monVolumeSon));
 //line(width/4,height/2,width*3/4,height/2);
*/
/* if (MyController1.getController("Play").getValue()==false){
  minim.stop();
}*/

}
public void stop(){
//  leaving();
}

public void dispose(){
  minim.stop();
  super.stop();
//  leaving();
}

// When the mouse is pressed, the state of the button is toggled.
// Try moving this code to draw() like in the rollover example.  What goes wrong?
public void mousePressed() {
  if (mouseX > 250 && mouseX < 300 && mouseY > 45 && mouseY < 95) {
  //  createWindows();
  //  btnMakeWindow.setEnabled(false); createWindows();
  }

  if (mouseX > 20 && mouseX < 20+20 && mouseY > 20 && mouseY < 20+20) {
    button = !button;
  }
  if (mouseX > 250 && mouseX < 350 && mouseY > 20 && mouseY < 20+50) {

  }
  if (mouseX > 418 && mouseX < 473 && mouseY > 185 && mouseY < 204) {
    rgbEffects();
  }
  if (mouseX > 10 && mouseX < 49 && mouseY > 150 && mouseY < 169) {
    MyController1.getController("bar height").setValue(50);
    MyController2.getController("width").setValue(50);
    input.disableMonitoring();
  }
  if (mouseX > 395 && mouseX < 395+24 && mouseY > 285 && mouseY < 285+24) {

    JOptionPane.showMessageDialog(null, "Audio Visualizer made by Debus Alexy\nRaccourci clavier : Touche p ou P pour stopper le programme\nTouche d ou D pour reset", "Information", JOptionPane.INFORMATION_MESSAGE);
  }

  if (mouseX > 180 && mouseX < 230 && mouseY > 152 && mouseY < 167) {
    javaColor = JColorChooser.showDialog(null, "color picker",Color.WHITE);

		if (javaColor!= null){
		    BEAT = javaColor;
        rgbToHsv(BEAT);
        MyController1.getController("Saturation").setValue((float)s);
        MyController1.getController("Brightness").setValue((float)v);
        h-=90;
        if (h<0){
          h+=360;
        }
        MyController1.getController("Hue").setValue((float)h);
        MyController1.getController("Hue").setColorBackground(color(javaColor.getRed(),javaColor.getGreen(),javaColor.getBlue()));
      //  MyController1.getController("Hue").setColorValue(color(255-javaColor.getRed(),255-javaColor.getGreen(),255-javaColor.getBlue()));
      //  mon_port.write(javaColor.getRed()+'g'+javaColor.getGreen()+'b'+javaColor.getBlue());
  	}
		else {
		    //default
        BEAT = Color.WHITE;
		}

  }

  if (mouseX > 430 && mouseX < 469 && mouseY > 290 && mouseY < 309) {
    leaving();
  }
  if (mouseX > 420 && mouseX < 450 && mouseY > 25 && mouseY < 35) {
    MyController1.getController("Play").setValue(1);

  }else if (mouseX > 390 && mouseX < 400 && mouseY > 25 && mouseY < 35) {
      MyController1.getController("Play").setValue(0);
      MyController1.getController("Beat pulse").setValue(0);
    }

    if (mouseX > 400 && mouseX < 466 && mouseY > 20 && mouseY < 44) {
      buttonPlay = !buttonPlay;
      if (buttonPlay ==true){
      //  mon_port.write('1');
        MyController1.getController("Play").setImages(loadImage("On.png"),loadImage("On.png"),loadImage("On.png"));
    }else{
      mon_port.write('0');
        MyController1.getController("Play").setImages(loadImage("Off.png"),loadImage("Off.png"),loadImage("Off.png"));
    }
    }
}

public void mouseOver() {
//When mouse is over a define coordinate
}
public void controlEvent(ControlEvent c) {
  // when a value change from a ColorPicker is received, extract the ARGB values
  // from the controller's array value
  if(c.isFrom(cp)) {
    int r = PApplet.parseInt(c.getArrayValue(0));
    int g = PApplet.parseInt(c.getArrayValue(1));
    int b = PApplet.parseInt(c.getArrayValue(2));
    int a = PApplet.parseInt(c.getArrayValue(3));
    col = color(r,g,b,a);
    println(col);
  }
}

/*
void keyPressed() {
  switch(key) {
    case('1'):
    // method A to change color
    cp.setArrayValue(new float[] {120, 0, 120, 255});
    break;
    case('2'):
    // method B to change color
    cp.setColorValue(color(255, 0, 0, 255));
    break;
  }
}*/
public void customize(DropdownList ddl) {
  // a convenience function to customize a DropdownList
  ddl.setBackgroundColor(color(190));
  ddl.setItemHeight(20);
  ddl.setBarHeight(15);

  ddl.addItem(""+1024, 1024);
  ddl.addItem(""+2048, 2048);
  ddl.addItem(""+4096, 4096);


  //ddl.scroll(0);
  ddl.setColorBackground(color(60));
  ddl.setColorActive(color(255, 128));
}

public void addMouseWheelListener() {
  frame.addMouseWheelListener(new java.awt.event.MouseWheelListener() {
    public void mouseWheelMoved(java.awt.event.MouseWheelEvent e) {
      MyController1.setMouseWheelRotation(e.getWheelRotation());
      MyController2.setMouseWheelRotation(e.getWheelRotation());
    }
  }
  );
}

public void keyPressed()
{
  if ( key == 'p' || key == 'P' )
  {
    buttonPlay = !buttonPlay;
    if (buttonPlay ==true){
      //mon_port.write('1');
      MyController1.getController("Play").setImages(loadImage("On.png"),loadImage("On.png"),loadImage("On.png"));
  }else{
    mon_port.write('0');
      MyController1.getController("Play").setImages(loadImage("Off.png"),loadImage("Off.png"),loadImage("Off.png"));
  }
    } if ( key == 'D' || key == 'd' ){
      MyController1.getController("bar height").setValue(50);
      MyController2.getController("width").setValue(50);
      input.disableMonitoring();
    }
    if (key == 'a') {
        //mon_port.write('1');
        dernier_envoye = '1';
        println("Dernier octet recu: " + dernier_recu);
        println("Dernier octet envoye: " + dernier_envoye);
    } if (key == 'e') {
        mon_port.write('0');
        dernier_envoye = '0';
        println("Dernier octet recu: " + dernier_recu);
        println("Dernier octet envoye: " + dernier_envoye);
      }
  }

public void leaving()
{
  if (JOptionPane.showConfirmDialog(null, "Are you sure?", "WARNING",
          JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
      // yes option
      exit();
  } else {
      // no option
  }
}

public interface Coloriable {

	public java.awt.Color getCouleur();

	public void setCouleur(java.awt.Color couleur);

}

public void rgbToHsv(Color colorDisplay){

  R = colorDisplay.getRed();
  G = colorDisplay.getGreen();
  B = colorDisplay.getBlue();
  float[] hsv = new float[3];
  colorDisplay.RGBtoHSB(R,G,B,hsv);
  println(PApplet.parseInt(hsv[0]*360)+"/"+PApplet.parseInt(hsv[1]*100)+"/"+PApplet.parseInt(hsv[2]*100)+"\n");

  h=PApplet.parseInt(hsv[0]*360);
  s=PApplet.parseInt(hsv[1]*100);
  v=PApplet.parseInt(hsv[2]*100);


  /*
    println("current color : R="+colorDisplay.getRed() +"/ G="+colorDisplay.getGreen() +"/ B="+colorDisplay.getBlue());
  R = colorDisplay.getRed()/255;
  G = colorDisplay.getGreen()/255;
  B = colorDisplay.getBlue()/255;


  mini = Math.min(Math.min(R, G), B);
  maxi = Math.max(Math.max(R, G), B);
  println("min:"+mini+"/ max:" + maxi);
  //H = hue/colour (degrees)
    if (maxi==mini){
      h=0;
    } else if(maxi==R){
      h= 60*(((G-B)/(maxi-mini))%6);
    } else if(maxi==G){
      h= 60*(2+(B-R)/(maxi-mini));
    }   else if(maxi==B){
      h= 60*(4+(R-G)/(maxi-mini));
    }

    if(h > 0){
        // h is a positive angle in the color wheel
        h=Math.floor(h);
    }
    else{
        // h is a negative angle.
        h=Math.floor(360 -h);
    }

    if (h==360){
      h=0;
    }
  //S = saturation (1>=S>=0)
  if (maxi==0){
    s=0;
  }else{
    s = (maxi-mini)/maxi;
  }

  //V = value (1>=V>=0)
  v = maxi;

  println("RGB to HSV conversion : H="+ h +"/ S=" + s + "/ V=" + v);*/
}

public void rgbEffects(){

    mon_port.write('2');
    R= (int)random(255);
    G= (int)random(255);
    B= (int)random(255);

    if ((R>120)||(G>120)||(B>120)){
      R/=3;
      G/=3;
      B/=3;

    }

    Color couleur = new Color(R,G,B);
    rgbToHsv(couleur);


    print(R+" /"+G+" /"+B+"\n");
    MyController1.getController("Saturation").setValue((float)s);
    MyController1.getController("Brightness").setValue((float)v);
    h-=90;
    if (h<0){
      h+=360;
    }
    MyController1.getController("Hue").setValue((float)h);
    MyController1.getController("Hue").setColorBackground(color(couleur.getRed(),couleur.getGreen(),couleur.getBlue()));
    myColorWheel.setRGB(color(R,G,B)).setLightness(v/95);
}
  public void settings() {  size(480, 420);  smooth(); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "processing_music_visualizer" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
