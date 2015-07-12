////////////////// User settings ////////////////// 

// Number of lights we're controlling.
const int numLeds = 4;

// List of pins connected to your lights.
// These need to be digital pins that have a ~ next to them.
int ledPins[numLeds] = { 6, 9, 10, 11 };

// Maximum LED brightness value.
const int maxValue = 150;

// Analog pin that the photoresistor is connected to.
const int brightnessPin = 0;

// Unused analog pin for random seed
const int unusedPin = 2; 

// Values to switch the lights on and off at (on must be greater than off)
const int lightsOn = 450;
const int lightsOff = 300;

// Time in MS to delay before turning lights on or off.
const int preLightDelay = 200;

////////////// End of user settings ////////////// 


// Prints stuff out to the serial port for debug purposes.
const bool debugMode = false;

// Time to delay in our loop.
const int loopDelay = 100;

// [Internal] Keeps track of whether the lights are currently on.
bool isLightOn = false;

///////////////////////////////////////////////////

// Makes a copy of an array of ints.
void copyArray(const int source[], int dest[], int arrayLength) {
  for(int i = 0 ; i < arrayLength; i++) {
    dest[i] = source[i];
  }
}

// Performs a Knuth-Fisher-Yates shuffle on an array of ints.
void kfyShuffle(int array[], int arrayLength) {
  int swap;
  for (int i = arrayLength - 1; i > 0; i--) {
    int n = random(i + 1);
    swap = array[i];
    array[i] = array[n];
    array[n] = swap;
  }
}

void fadeInPin(int pin) {
  if (debugMode) {
    Serial.print("Fade in pin:");
    Serial.println(pin);
  }
  
  for (int i = 0; i < maxValue; i++) {
    analogWrite(pin, i);
    delay(10);
  }
}

void fadeOutPin(int pin) {
  if (debugMode) {
    Serial.print("Fade out pin:");
    Serial.println(pin);
  }
  
  for (int i = maxValue; i >= 0; i--) {
    analogWrite(pin, i);
    delay(10);
  }
}

void fadeWithFunc(void (*fadeFunc)(int)) {
    // Copy our list of light pins and shuffle it.
  int shuffle[numLeds];
  copyArray(ledPins, shuffle, numLeds);
  kfyShuffle(shuffle, numLeds);

  // Perform the fade.
  for(int i = 0 ; i < numLeds; i++) {
    fadeFunc(shuffle[i]);
  }
}

// Global fade in
void fadeIn() {
  if (debugMode) {
    Serial.println("Lights on");
  }

  fadeWithFunc(fadeInPin);
}

// Global fade out
void fadeOut() {
  if (debugMode) {
    Serial.println("Lights off");
  }

  fadeWithFunc(fadeOutPin);
}

///////////////////////////////////////////////////

void setup() {
  if (debugMode) {
    Serial.begin(9600);
    Serial.println("Starting...");
    Serial.println("Debug mode enabled");
    Serial.println("");
  }

  // Set pin modes.    
  randomSeed(analogRead(unusedPin));

  for(int i = 0 ; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  int bright = analogRead(brightnessPin);
  if (isLightOn && bright > lightsOn) {
    delay(preLightDelay);
    fadeOut();
    isLightOn = false;
  } else if (!isLightOn && bright < lightsOff) {
    delay(preLightDelay);
    fadeIn();
    isLightOn = true;
  }

  delay(loopDelay);
}
