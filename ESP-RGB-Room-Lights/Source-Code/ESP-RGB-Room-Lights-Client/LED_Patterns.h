#include <FastLED.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIXEL_PIN    12  // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 242   // Number of NeoPixels (242)
#define LED_HALF  PIXEL_COUNT/2

int BRIGHTNESS = 120;
int MIN_BRIGHTNESS = 10;
int MAX_BRIGHTNESS = 130; // Try not to exceed 130

long randNumber;  //Pixel random number variable
long randNumberR;  //RED random number variable
long randNumberG;  //GREEN random number variable
long randNumberB;  //BLUE random number variable

// Parmeters for Music Visualizer
//#define AUDIO_PIN A0
#define SECONDS_PER_PALETTE 20 // 10 seconds per color palette makes a good demo, 20-120 is better for deployment

uint16_t gradient = 0; //Used to iterate and loop through each color palette gradually

uint8_t volume = 0;    //Holds the volume level read from the sound detector.
uint8_t last = 0;      //Holds the value of volume from the previous loop() pass.

float maxVol = 15;     //Holds the largest volume recorded thus far to proportionally adjust the visual's responsiveness.
float avgVol = 0;      //Holds the "average" volume-level to proportionally adjust the visual experience.
float avgBump = 0;     //Holds the "average" volume-change to trigger a "bump."

bool bump = false;     //Used to pass if there was a "bump" in volume

typedef struct struct_message {
  uint8_t vol;
} struct_message;

// Create a struct_message called myData
struct_message AudioData;

CRGB leds[PIXEL_COUNT];
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

/* Basic framework functions to incorporate both Adafruit Neopixel & FastLED Libraries */
void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < strip.numPixels(); i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}
/* ------------------- End of framework functions -------------------- */

/* --------------------- Functions and Effects ----------------------- */
void FadeInOut(byte red, byte green, byte blue){
  float r, g, b;
     
  for(int k = 0; k < 256; k=k+1) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    showStrip();
  }
     
  for(int k = 255; k >= 0; k=k-2) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    showStrip();
  }
}

void Strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause){
  for(int j = 0; j < StrobeCount; j++) {
    setAll(red,green,blue);
    showStrip();
    delay(FlashDelay);
    setAll(0,0,0);
    showStrip();
    delay(FlashDelay);
  }
 
 delay(EndPause);
}

void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){
  randomSeed(analogRead(0));
  for(int i = 0; i < strip.numPixels()-EyeSize-2; i++) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for(int i = strip.numPixels()-EyeSize-2; i > 0; i--) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
  
  delay(ReturnDelay);
}

void Twinkle(byte red, byte green, byte blue, int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0,0,0);
  
  for (int i=0; i<Count; i++) {
     setPixel(random(strip.numPixels()),red,green,blue);
     showStrip();
     delay(SpeedDelay);
     if(OnlyOne) { 
       setAll(0,0,0); 
     }
   }
  
  delay(SpeedDelay);
}

void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0,0,0);
  
  for (int i=0; i<Count; i++) {
     setPixel(random(strip.numPixels()),random(0,255),random(0,255),random(0,255));
     showStrip();
     delay(SpeedDelay);
     if(OnlyOne) { 
       setAll(0,0,0); 
     }
   }
  
  delay(SpeedDelay);
}

void Sparkle(byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel = random(strip.numPixels());
  setPixel(Pixel,red,green,blue);
  showStrip();
  delay(SpeedDelay);
  setPixel(Pixel,0,0,0);
}

void SnowSparkle(byte red, byte green, byte blue, int SparkleDelay, int SpeedDelay) {
  setAll(red,green,blue);
  
  int Pixel = random(strip.numPixels());
  setPixel(Pixel,0xff,0xff,0xff);
  showStrip();
  delay(SparkleDelay);
  setPixel(Pixel,red,green,blue);
  showStrip();
  delay(SpeedDelay);
}

void RunningLights(byte red, byte green, byte blue, int WaveDelay) {
  int Position=0;
  
  for(int i=0; i<strip.numPixels()*2; i++)
  {
      Position++; // = 0; //Position + Rate;
      for(int i=0; i<strip.numPixels(); i++) {
        // sine wave, 3 offset waves make a rainbow!
        //float level = sin(i+Position) * 127 + 128;
        //setPixel(i,level,0,0);
        //float level = sin(i+Position) * 127 + 128;
        setPixel(i,((sin(i+Position) * 127 + 128)/255)*red,
                   ((sin(i+Position) * 127 + 128)/255)*green,
                   ((sin(i+Position) * 127 + 128)/255)*blue);
      }
      
      showStrip();
      delay(WaveDelay);
  }
}

/* Fire Effect */
void setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    setPixel(Pixel, 50, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    setPixel(Pixel, 50, heatramp, 0);
  } else {                               // coolest
    setPixel(Pixel, heatramp, 0, 0);
  }
}

void Fire(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[PIXEL_COUNT];
  int cooldown;
 
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < strip.numPixels(); i++) {
    cooldown = random(0, ((Cooling * 10) / strip.numPixels()) + 2);
   
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
 
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= strip.numPixels() - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
   
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < strip.numPixels(); j++) {
    setPixelHeatColor(j, heat[j] );
  }

  showStrip();
  delay(SpeedDelay);
}
/* End of Fire Effect */

/* Meteor Rain */
void fadeToBlack(int ledNo, byte fadeValue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
    // NeoPixel
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
    
    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
    
    strip.setPixelColor(ledNo, r,g,b);
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[ledNo].fadeToBlackBy( fadeValue );
 #endif  
}

void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
  setAll(0,0,0);
 
  for(int i = 0; i < strip.numPixels()+strip.numPixels(); i++) {
   
   
    // fade brightness all LEDs one step
    for(int j=0; j<strip.numPixels(); j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
   
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <strip.numPixels()) && (i-j>=0) ) {
        setPixel(i-j, red, green, blue);
      }
    }
   
    showStrip();
    delay(SpeedDelay);
  }
}

/* End Meteor Rain */

void colorWipe(uint32_t color, int wait) {
  for(int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<50; a++) {  // Repeat 50 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all strip in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 3 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 3*65536. Adding 256 to firstPixelHue each time
  // means we'll make 3*65536/256 = 768 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all strip in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}

/* ------------------------- Custom-Made Effects ------------------------- */


void flag() {
  for(int i = 0; i < strip.numPixels()/3; i++) { 
    strip.setPixelColor(i, strip.Color(0, 221, 237));        
    strip.show();                  
    delay(5);                           
  }
  for(int j = strip.numPixels()/3; j < (strip.numPixels()/3)*2; j++) {
    strip.setPixelColor(j, strip.Color(120, 5, 120));
    strip.show(); 
    delay(5);
  }
  for(int k = (strip.numPixels()/3)*2; k < strip.numPixels(); k++) {
    strip.setPixelColor(k, strip.Color(0, 221, 237));
    strip.show(); 
    delay(5);
  }
}

void flag2() {
  for(int i = 0; i < strip.numPixels(); i+=3) { // Red
    strip.setPixelColor(i, strip.Color(220, 0, 0));        
    strip.show();                  
    delay(5);                           
  }
   for(int i = 1; i < strip.numPixels(); i+=3) { // White
    strip.setPixelColor(i, strip.Color(100, 100, 100));        
    strip.show();                  
    delay(5);                           
  }
   for(int i = 2; i < strip.numPixels(); i+=3) { // Blue
    strip.setPixelColor(i, strip.Color(0, 0, 220));        
    strip.show();                  
    delay(5);                           
  }
}

void hogwarts() {
  colorWipe(strip.Color(255,   0,   0), 5);    // Gryffindor
  delay(50);
  colorWipe(strip.Color(  0, 255,   0), 5);    // Slytherin
  delay(50);
  colorWipe(strip.Color(  0, 0,   255), 5);    // Ravenclaw
  delay(50);
  colorWipe(strip.Color(  200, 200,   0), 5);    // Hufflepuff
  delay(50);
  for(int i = 0; i < strip.numPixels()/4; i++) { // Gryffindor
    strip.setPixelColor(i, strip.Color(255, 0, 0));        
    strip.show();                  
    delay(5);                           
  }
  for(int j = strip.numPixels()/4; j < (strip.numPixels()/2); j++) { // Slytherin
    strip.setPixelColor(j, strip.Color(0, 255, 0)); 
    strip.show(); 
    delay(5);
  }
  for(int k = (strip.numPixels()/2); k < (strip.numPixels()/4)*3; k++) { // Ravenclaw
    strip.setPixelColor(k, strip.Color(0, 0, 200));
    strip.show(); 
    delay(5);
  }
  for(int i = (strip.numPixels()/4)*3; i < strip.numPixels(); i++) { // Hufflepuff
    strip.setPixelColor(i, strip.Color(200, 200, 0));        
    strip.show();                  
    delay(5);                           
  }
}

// Generate and set the strip to a random color
void randomPixel(uint32_t c, uint8_t wait) {
  for (int i = 0; i < strip.numPixels(); i = i++) {
    strip.setPixelColor(randNumber, c);    //turn random pixel on
  }
  
  strip.show();
  delay(wait);

  for (int i = 0; i < strip.numPixels(); i = i++) {
    strip.setPixelColor(randNumber, 0);        //turn pixel off
  }
}
/* ---------------------- End of Custom-Made Effects ---------------------- */

/* Helper functions for Music Visualizer */
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  Serial.println("Audio Data Recieved!");
  memcpy(&AudioData, incomingData, sizeof(AudioData));
  
}
//This function simply take a value and returns a gradient color
//  in the form of an unsigned 32-bit integer

//The gradient returns a different, changing color for each multiple of 255
//  This is because the max value of any of the 3 LEDs is 255, so it's
//  an intuitive cutoff for the next color to start appearing.
//  Gradients should also loop back to their starting color so there's no jumps in color.

uint32_t Rainbow(unsigned int i) {
  if (i > 1529) return Rainbow(i % 1530);
  if (i > 1274) return strip.Color(255, 0, 255 - (i % 255));   //violet -> red
  if (i > 1019) return strip.Color((i % 255), 0, 255);         //blue -> violet
  if (i > 764) return strip.Color(0, 255 - (i % 255), 255);    //aqua -> blue
  if (i > 509) return strip.Color(0, 255, (i % 255));          //green -> aqua
  if (i > 255) return strip.Color(255 - (i % 255), 255, 0);    //yellow -> green
  return strip.Color(255, i, 0);                               //red -> yellow
}

uint8_t split(uint32_t color, uint8_t i ) {

  //0 = Red, 1 = Green, 2 = Blue

  if (i == 0) return color >> 16;
  if (i == 1) return color >> 8;
  if (i == 2) return color >> 0;
  return -1;
}

void fade(float damper) { //Fades lights by multiplying them by a value between 0 and 1 each pass of loop().

  //"damper" must be between 0 and 1, or else you'll end up brightening the lights or doing nothing.
  if (damper >= 1) damper = 0.99;

  for (int i = 0; i < strip.numPixels(); i++) {

    //Retrieve the color at the current position.
    uint32_t col = (strip.getPixelColor(i)) ? strip.getPixelColor(i) : strip.Color(0, 0, 0);

    //If it's black, you can't fade that any further.
    if (col == 0) continue;

    float colors[3]; //Array of the three RGB values

    //Multiply each value by "damper"
    for (int j = 0; j < 3; j++) colors[j] = split(col, j) * damper;

    //Set the dampened colors back to their spot.
    strip.setPixelColor(i, strip.Color(colors[0] , colors[1], colors[2]));
  }
}

void Pulse() { //Pulse from center of the strip

  fade(0.75);   //Listed below, this function simply dims the colors a little bit each pass of loop()

  //Advances the gradient to the next noticeable color if there is a "bump"
  if (bump) gradient += 64;

  //If it's silent, we want the fade effect to take over, hence this if-statement
  if (volume > 0) {
    uint32_t col = Rainbow(gradient); //Our retrieved 32-bit color

    //These variables determine where to start and end the pulse since it starts from the middle of the strip.
    //  The quantities are stored in variables so they only have to be computed once.
    int start = LED_HALF - (LED_HALF * (volume / maxVol));
    int finish = LED_HALF + (LED_HALF * (volume / maxVol)) + strip.numPixels() % 2;
    //Listed above, LED_HALF is simply half the number of LEDs on your strip. ↑ this part adjusts for an odd quantity.

    for (int i = start; i < finish; i++) {

      //"damp" creates the fade effect of being dimmer the farther the pixel is from the center of the strip.
      //  It returns a value between 0 and 1 that peaks at 1 at the center of the strip and 0 at the ends.
      float damp = float(
                     ((finish - start) / 2.0) -
                     abs((i - start) - ((finish - start) / 2.0))
                   )
                   / float((finish - start) / 2.0);

      //Sets the each pixel on the strip to the appropriate color and intensity
      //  strip.Color() takes 3 values between 0 & 255, and returns a 32-bit integer.
      //  Notice "knob" affecting the brightness, as in the rest of the visuals.
      //  Also notice split() being used to get the red, green, and blue values.
      strip.setPixelColor(i, strip.Color(
                             split(col, 0) * pow(damp, 2.0) ,
                             split(col, 1) * pow(damp, 2.0) ,
                             split(col, 2) * pow(damp, 2.0) 
                           ));
    }
    //Sets the max brightness of all LEDs. If it's loud, it's brighter.
    //  "knob" was not used here because it occasionally caused minor errors in color display.
    strip.setBrightness(255.0 * pow(volume / maxVol, 2));
  }

  //This command actually shows the lights. If you make a new visualization, don't forget this!
  strip.show();
}
/* Actual Music Visualizer function */
void MusicVisualizer() {  
  volume = AudioData.vol; 
  avgVol = (avgVol + volume) / 2.0;
   //Sets a threshold for volume.
  //  In practice I've found noise can get up to 15, so if it's lower, the visual thinks it's silent.
  //  Also if the volume is less than average volume / 2 (essentially an average with 0), it's considered silent.
  if (volume < avgVol / 2.0 || volume < 15) volume = 0;

  //If the current volume is larger than the loudest value recorded, overwrite
  if (volume > maxVol) maxVol = volume;

  //This is where "gradient" is reset to prevent overflow.
  if (gradient > 1529) {

    gradient %= 1530;

    //Everytime a palette gets completed is a good time to readjust "maxVol," just in case
    //  the song gets quieter; we also don't want to lose brightness intensity permanently 
    //  because of one stray loud sound.
    maxVol = (maxVol + volume) / 2.0;
  }

  //If there is a decent change in volume since the last pass, average it into "avgBump"
  if (volume - last > avgVol - last && avgVol - last > 0) avgBump = (avgBump + (volume - last)) / 2.0;

  //if there is a notable change in volume, trigger a "bump"
  bump = (volume - last) > avgBump;

  Pulse();   //Calls the visual to be displayed with the globals as they are.

  gradient++;    //Increments gradient

  last = volume; //Records current volume for next pass

  delay(10);   //Paces visuals so they aren't too fast to be enjoyable
}
