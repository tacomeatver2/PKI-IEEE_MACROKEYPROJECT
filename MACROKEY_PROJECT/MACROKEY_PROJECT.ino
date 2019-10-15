
//MACRO_KEYPAD
//Takumi Ito
//10/12/19
//This is a code to control an aruduino micro to send commands to the PC based on the key pressed on the keypad.

//////////////////////////////////////////////////////
//Initialization
//////////////////////////////////////////////////////
#include <Encoder.h>
#include <HID-Project.h>
//import library https://github.com/NicoHood/HID
//import library https://github.com/PaulStoffregen/Encoder
// or click Tools>> Manage libraries >> search for HID >> scroll down until you see HID-Project by NicoHood version 2.6.1 >> then install that if you are unsure of how to import the libraries correctly
// same steps but search for encoder >> scroll down until you see Encoder by PaulStoffregen verson 1.4.1 >> then install it.

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
boolean modeos = 0; //mac = 0 win = 1

//////////////////////////////////////////////////////
//Tools
//////////////////////////////////////////////////////

void changeVolume(){
if (volume != oldVolume) {
    if(volume > oldVolume){
      //delay(100);
      //Consumer.write(MEDIA_VOLUME_UP);

      String app = "spotify";
      spotlight_mac(app);
      delay(300);

      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_UP_ARROW);
      digitalWrite(L1, HIGH);
      delay(100);
      Keyboard.releaseAll();
      digitalWrite(L1, LOW);
      actualVolume = actualVolume + 2;
      oldVolume = volume;
      delay(500);
    }
    else{
      //delay(100);
      //Consumer.write(MEDIA_VOLUME_DOWN);
      String app = "spotify";
      spotlight_mac(app);
      delay(300);
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_DOWN_ARROW);
      delay(300);
      digitalWrite(L1, HIGH);
      delay(100);
      Keyboard.releaseAll();
      digitalWrite(L1, LOW);
      actualVolume = actualVolume - 2;
      oldVolume = volume;
      delay(300);
    }
  }
}
void spotlight_mac(String app)
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

void start_win(String app)
{
    Keyboard.press(KEY_LEFT_GUI);
    delay(500);
    Keyboard.releaseAll();
    delay(200);
    Keyboard.println(app);
    delay(1000);
    Keyboard.press(KEY_ENTER);
    delay(200);
}

void chrome_mac(String url){
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_SPACE);
    delay(200);
    Keyboard.releaseAll();
    Keyboard.println("chrome_mac");
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
void chrome_win(String url){
    Keyboard.press(KEY_LEFT_GUI);
    delay(500);
    Keyboard.releaseAll();
    delay(200);
    Keyboard.println("Google Chrome");                     //HERE IS WHERE YOU WILL CHANGE THE CHARACTERS INSIDE THE "____" TO BE THE WEB BROWSER YOU USE.
    delay(1000);                                          //YOU MIGHT HAVE TO MESS AROUND WITH THE DELAY AMOUNTS FOR YOUR SPECIFIC COMPUTER.
    Keyboard.press(KEY_ENTER);
    Keyboard.releaseAll();
    delay(1500);
    Keyboard.println(url);
    delay(1000);
    Keyboard.press(KEY_ENTER);
    delay(200);
}

void keyrelease(){
    digitalWrite(L1, HIGH);
    delay(100);
    Keyboard.releaseAll();
    digitalWrite(L1, LOW);
    delay(300);
}
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
  if (modeos = 0){
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
    //Previous media
    if (digitalRead(B1) == LOW)
    {
      Consumer.write(MEDIA_PREVIOUS);
      keyrelease();

    }
    // play and pause media
    if (digitalRead(B2) == LOW)
    {
      Consumer.write(MEDIA_PLAY_PAUSE);
      keyrelease();

    }
    // Next media
    if (digitalRead(B3) == LOW)
    {
      Consumer.write(MEDIA_NEXT);
      keyrelease();

    }
    //Open terminal
    if (digitalRead(B4) == LOW)
    {
      app = "Terminal";
      spotlight_mac(app);
      keyrelease();

    }
    //Opening Unomaha Canvas page
      if (digitalRead(B5) == LOW)
    {
      url = "https://unomaha.instructure.com/";
      chrome_mac(url);
      keyrelease();
    }
    //Taking screenshot on a MAC
      if (digitalRead(B6) == LOW)
    {
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('4');
      keyrelease();
    }
  }
  
  else{
    int newPosition = myEnc.read();
    if (newPosition != oldPosition)
    {
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
    if (!digitalRead(pinButton))
    {

      Consumer.write(MEDIA_VOLUME_MUTE);
      muted = !muted;
      digitalWrite(L1, HIGH);
      keyrelease();
    }
    //Previous media
    if (digitalRead(B1) == LOW)
    {
      Consumer.write(MEDIA_PREVIOUS);
      keyrelease();

    }
    //Play and stop media
    if (digitalRead(B2) == LOW)
    {
      Consumer.write(MEDIA_PLAY_PAUSE);
      keyrelease();

    }
    //Next media
    if (digitalRead(B3) == LOW)
    {
      Consumer.write(MEDIA_NEXT);
      keyrelease();

    }
    //Open specific app
    if (digitalRead(B4) == LOW)
    {
      app = "xxxxxxx";
      start_win(app);
      keyrelease();
    }
    //Open specific website
    if (digitalRead(B5) == LOW)
    {
      url = "google.com";
      chrome_win(url);
      keyrelease();
    }
    //Screenshot on win10
    if (digitalRead(B6) == LOW)
    {
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('s');
      keyrelease();
    }

  }
  }
