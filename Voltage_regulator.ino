
/*
  Arduino Volt Regulator
  
  We normally use batteries to power our arduino projects but the problem
  you would have had is that a 9volt battery runs for hardly 1 week
  (depends on the usage)and you have to buy more and more for testing
  purpose and the finished project...by buying more batteries you will
  waste your money and get E-Waste after using them as they can't be
  recharged.If you go with rechargable batteries then you gotta charge 
  them often as they run out of charge pretty quickly.What I have done 
  is a voltage regulator which you can resist the voltage of output 
  from 0v to 5v.This project has a display which shows the current 
  voltage which is outputted by a graph.

  I hope you will learn something by building this project and never have to waste money on non rechargeable batteries.

  modified 16 Feb 2023
  by Nandan Hegde
  modified 18 Feb 2023
 
  This is a fully functional and Volt Regulator that you can make.
  
  THIS IS :
  Safe unless you play with the plug adapter

  
  Contact:
  nandanhegde01@gmail.com

  
  Releases:

  v1.1.23 -- 18 FEB 2023

  
 
*/

/*start of code
---------------------------------------------
---------------------------------------------
*/
#include "U8glib.h"

int outputValue = 0;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0); // SW SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9, Res = 12


int xmax=128;                                   // max length x-axis

int ymax=62;                                    // max length y-axis

int xcenter=xmax/2;                             // center of x-axis

int ycenter=ymax/2+10;                          // center of y-axis

int arc=ymax/2;                             

int angle=0;                                   

char* label[] = {"VOLT","COOLANT","INTAKE", "VOLT"};    // some custom gauge labels

int labelXpos[] = {53, 45, 49, 53};                     // predefined x-position of a gauge label

#define potmeterPin A1                                  // simulate analogue value with potentiometer

int p, w, m,a=10;

u8g_uint_t xx=0;



// ------------------------------------------------- void gauge() ------------------------------------------

void gauge(uint8_t angle) {



  // draw border of the gauge

  u8g.drawCircle(xcenter,ycenter,arc+6, U8G_DRAW_UPPER_RIGHT);

  u8g.drawCircle(xcenter,ycenter,arc+4, U8G_DRAW_UPPER_RIGHT);

  u8g.drawCircle(xcenter,ycenter,arc+6, U8G_DRAW_UPPER_LEFT);

  u8g.drawCircle(xcenter,ycenter,arc+4, U8G_DRAW_UPPER_LEFT);



  // draw the needle

  float x1=sin(2*angle*2*3.14/360);              // needle position

  float y1=cos(2*angle*2*3.14/360); 

  u8g.drawLine(xcenter, ycenter, xcenter+arc*x1, ycenter-arc*y1);

  u8g.drawDisc(xcenter, ycenter, 5, U8G_DRAW_UPPER_LEFT);

  u8g.drawDisc(xcenter, ycenter, 5, U8G_DRAW_UPPER_RIGHT);

  u8g.setFont(u8g_font_chikita);

 

  // show scale labels

  u8g.drawStr( 20, 42, "0v ");                   

  u8g.drawStr( 25, 18, "1v ");

  u8g.drawStr( 60, 14, "2v ");


  u8g.drawStr( 95, 18, "4v ");

  u8g.drawStr( 105, 42, "5v ");

 

  // show gauge label

  u8g.setPrintPos(labelXpos[0],32);           

  u8g.print(label[0]);

 

  // show digital value and align its position

  u8g.setFont(u8g_font_profont22);             

  u8g.setPrintPos(54,60);

  if (w<10){                                    // leading 0 when value less than 10

    u8g.print("0");

  }

  if (w>99) {                                   // position at 100%

    u8g.setPrintPos(47,60);

  }

  u8g.print(w);

}



// ------------------------------------------------- void setup() ------------------------------------------

void setup(void) {
pinMode(9, OUTPUT);
 

  u8g.setFont(u8g_font_chikita);

  u8g.setColorIndex(1);                         // Instructs the display to draw with a pixel on.



  // assign default color value

  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {

    u8g.setColorIndex(255);                     // white

  }

  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {

    u8g.setColorIndex(3);                       // max intensity

  }

  else if ( u8g.getMode() == U8G_MODE_BW ) {

    u8g.setColorIndex(1);                       // pixel on

  }

  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {

    u8g.setHiColorByRGB(255,255,255);

  }

}



// ------------------------------------------------- void loop() ------------------------------------------



void loop(void) {
  p = analogRead(A0);
// map it to the range of the analog out:
  outputValue = map(p, 0, 1023, 0, 255);
  // change the analog out value:
  analogWrite(9, outputValue);
             

 

 w = map(p,0,1023,0,100);                      // map it between 0 and 100

 m = map(p,0,1023,0,90);                       // map needle movement



   

   



  // show needle and dial

  xx = m;                                      // 135 = zero position, 180 = just before middle, 0 = middle, 45 = max

  if (xx<45){                                   // positie correctie

    xx=xx+135;

  }

  else {

    xx=xx-45;

  }

 

  // picture loop

  {

    u8g.firstPage(); 

    do {             

      gauge(xx);

    }

    while( u8g.nextPage() );

  }

}

/*Code edited by Nandan Hegde

credits-- 
1)There are multiple video's on the topic "potentiometer with Arduino Oled display"


 End of code
------------------------------------------------
------------------------------------------------
*/
