//MACRO_KEYPAD
//Takumi Ito
//1/25/19
//This is a code to control an aruduino micro to send commands to the PC based on the key pressed on the keypad.

//////////////////////////////////////////////////////
//Initialization
//////////////////////////////////////////////////////
#include <Encoder.h>
#include <HID-Project.h>

#define B1 1
#define B2 0
#define B3 4
#define B4 5
#define B5 6
#define B6 7

#define L1 8
#define L2 9

Encoder myEnc(15,14);
const int pinLed = LED_BUILTIN;
const int pinButton = 16;
int bulbPin = 9; 
int oldPosition  = -999;
boolean muted = 0;
int safePosition = 0;
int volume = 0;
int oldVolume = 0;
int actualVolume = 0;
String app;
String url;

//////////////////////////////////////////////////////
//Setup
//////////////////////////////////////////////////////
void setup() {
Serial.print("set ");
  pinMode(pinButton, INPUT_PULLUP);
  pinMode (B1, INPUT_PULLUP);
  pinMode (B2, INPUT_PULLUP);
  pinMode (B3, INPUT_PULLUP);
  pinMode (B4, INPUT_PULLUP);
  pinMode (B5, INPUT_PULLUP);
  pinMode (B6, INPUT_PULLUP);

  
  // initialize the LED pin as an output:
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  digitalWrite(L2, HIGH);
  

  Serial.begin(9600);
  Consumer.begin();
  delay(1000);
  
  for(int i = 50; i > 0; i--){
  Consumer.write(MEDIA_VOLUME_DOWN);
  delay(1);
  }
}

//////////////////////////////////////////////////////
//Loop
//////////////////////////////////////////////////////
void loop() {
  int newPosition = myEnc.read();

  if (newPosition != oldPosition) {
    Serial.println("new");
    safePosition = newPosition;
    if(newPosition < 0){
      safePosition = 0;
      myEnc.write(safePosition);
    }
    if(newPosition > 400){
      safePosition = 400;
      myEnc.write(safePosition);
    }
    oldPosition = safePosition;
    volume = safePosition / 4;
    volume = volume / 2;
    noInterrupts();  
    Serial.print("calc volume: ");
    Serial.print(volume);
    Serial.print(" act volume: ");
    Serial.print(actualVolume);
    Serial.println("");
    changeVolume();
    interrupts();
  }
  
  if (!digitalRead(pinButton)) {
   
    Consumer.write(MEDIA_VOLUME_MUTE);
    muted = !muted;
    digitalWrite(L1, HIGH);
    keyrelease();
  }
  if (digitalRead(B1) == LOW)
  {
    Consumer.write(MEDIA_PREVIOUS);
    keyrelease();

  }
  if (digitalRead(B2) == LOW)
  {
    Consumer.write(MEDIA_PLAY_PAUSE);
    keyrelease();

  }
  if (digitalRead(B3) == LOW)
  {
    Consumer.write(MEDIA_NEXT);
    keyrelease();

  }
  if (digitalRead(B4) == LOW)
  {
    app = "Terminal";
    spotlight(app);
    keyrelease();

  }
    if (digitalRead(B5) == LOW)
  {
    url = "https://unomaha.instructure.com/";
    chrome(url);
    keyrelease();

  }
    if (digitalRead(B6) == LOW)
  {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('4');
    keyrelease();
  }
}
//////////////////////////////////////////////////////
//Functions
//////////////////////////////////////////////////////

void changeVolume(){
if (volume != oldVolume) {
    if(volume > oldVolume){
      //delay(100);
      Consumer.write(MEDIA_VOLUME_UP);
      actualVolume = actualVolume + 2;
      oldVolume = volume; 
    }
    else{
      //delay(100);
      Consumer.write(MEDIA_VOLUME_DOWN);
      actualVolume = actualVolume - 2;
      oldVolume = volume; 
    }
  }
}
void spotlight(String app)
{
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_SPACE);
    delay(100);
    Keyboard.releaseAll();
    Keyboard.println(app);
    delay(300);
    Keyboard.press(KEY_RETURN);
    delay(200);
    Keyboard.releaseAll();
}
void chrome(String url){
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_SPACE);
    delay(200);
    Keyboard.releaseAll();
    Keyboard.println("chrome");
    delay(300);
    
    Keyboard.press(KEY_RETURN);
    delay(300);
    Keyboard.releaseAll();
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('T');
    delay(300);
    Keyboard.releaseAll();
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('l');
    delay(300);
    Keyboard.releaseAll();
    Keyboard.println(url);
    delay(300);
    Keyboard.press(KEY_RETURN);
    delay(300);
    Keyboard.releaseAll();
}
void keyrelease(){
    digitalWrite(L1, HIGH);
    delay(100);
    Keyboard.releaseAll();
    digitalWrite(L1, LOW);
    delay(300);
}
