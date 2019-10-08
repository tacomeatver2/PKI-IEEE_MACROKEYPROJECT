
//MACROKEY PROJECT

//PKI-IEEE

//Takumi Ito

//9/30/19

//Revised by Jake Tierney to work on Windows 10.

//10/7/19

//This is a code to control an aruduino micro to send commands to the PC based on the key pressed on the keypad.



//////////////////////////////////////////////////////

//Initialization  (DO NOT MESS WITH THE INITIALIZATION!!)

//////////////////////////////////////////////////////

#include <Encoder.h>
#include <HID-Project.h>

//import library https://github.com/NicoHood/HID
//import library https://github.com/PaulStoffregen/Encoder

// or click Tools>> Manage libraries >> search for HID >> scroll down until you see HID-Project by NicoHood version 2.6.1 >> then install that if you are unsure of how to import the libraries correctly
// same steps but search for encoder >> scroll down until you see Encoder by PaulStoffregen verson 1.4.1 >> then install it.
//



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

//Setup    (DO NOT MESS WITH THE SET UP!!)

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
  Keyboard.begin(); // use this to open the library for a standard layout keyboard

  delay(1000);

  

  for(int i = 50; i > 0; i--){

  Consumer.write(MEDIA_VOLUME_DOWN);

  delay(1);

  }

}



//////////////////////////////////////////////////////

//Loop   (THINGS TO MESS WITH HERE, IF YOU WISH TO CHANGE A KEY'S OPERATION)

//////////////////////////////////////////////////////

void loop() {

  int newPosition = myEnc.read();



  if (newPosition != oldPosition) {

    Serial.println("new");

    safePosition = newPosition;

    if(newPosition > 0){

      safePosition = 0;

      myEnc.write(safePosition);

    }

    if(newPosition < -400){

      safePosition = -400;

      myEnc.write(safePosition);

    }

    oldPosition = safePosition;

    volume = -safePosition / 4;

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
                                                      //IF YOU WISH TO CHANGE THE TOP 3 BUTTONS TO SOMETHING ELSE, YOU WOULD WANT TO VIEW THE CONSUMER API OR CHANGE IT SO SOMETHING ELSE LIKE BUTTONS 4-6.
                                                      
  if (digitalRead(B1) == LOW)                         //THIS STARTS THE BUTTONS OPERATIONS, B1 IS THE TOP LEFT BUTTON.
 
  {

    Consumer.write(MEDIA_PREVIOUS);                   //PREVIOUS SONG

    keyrelease();



  }

  if (digitalRead(B2) == LOW)                         //BUTTON 2 IS TOP MIDDLE

  {

    Consumer.write(MEDIA_PLAY_PAUSE);                 //PAUSE AND PLAY MUSIC

    keyrelease(); 



  }

  if (digitalRead(B3) == LOW)                         //BUTTON 3 IS TOP RIGHT

  {

    Consumer.write(MEDIA_NEXT);                       // NEXT SONG

    keyrelease();



  }

  if (digitalRead(B4) == LOW)

  {

    app = "Autodesk Fusion 360";    //Change the characters inside the "" to change which app opens.

    start(app);      //This is the same as tapping the windows key to open the start menu, then types the string app and then hits enter. Thus opening the desired app.

    keyrelease();



  }

    if (digitalRead(B5) == LOW)

  {

    url = "https://youtu.be/ZXsQAXx_ao0";        //TO CHANGE WHAT WEBSITE BUTTON 5 TAKES YOU TO, JUST CHANGE THE STRING URL TO THE WEBSITE YOU WISH TO GO TO.

    chrome(url);                            //IF YOU DO NOT USE GOOGLE CHROME AND WISH TO USE THIS FUNCTION PLEASE LOOK IN THE FUNCTIONS AT THE BOTTOM FOR MORE COMMENTS.

    keyrelease();



  }

    if (digitalRead(B6) == LOW)             //HERE IS BUTTON 6 FOR COPY AND PASTE

  {
    delay(250);
    
    if (digitalRead(B6) == LOW)
    
    {

      Keyboard.press(KEY_LEFT_CTRL);          //PLAY AROUND WITH THIS ONE AND CUSTOMIZE IT TO BE YOUR MACRO KEY BOARD!!!

      Keyboard.press('c');                    //CURRENTLY THIS IS USED TO COPY TEXT IF HELD PAST THE 250 DELAY

      keyrelease();

    }

    else

    {
      Keyboard.press(KEY_LEFT_CTRL);          

      Keyboard.press('v');                    //CURRENTLY THIS IS USED TO PASTE TEXT  IF BUTTON 6 IS TAPPED

      keyrelease();
    
    
    }

  }

}

//////////////////////////////////////////////////////

//Functions (DON'T MESS WITH FUNCTIONS UNLESS YOU REALLY UNDERSTAND WHATS GOING ON!!!) 

//////////////////////////////////////////////////////



void changeVolume(){

if (volume != oldVolume) {

    if(volume > oldVolume){

      //delay(100);

      Consumer.write(MEDIA_VOLUME_UP);

      actualVolume = actualVolume + 5;

      oldVolume = volume; 

    }

    else{

      //delay(100);

      Consumer.write(MEDIA_VOLUME_DOWN);

      actualVolume = actualVolume - 5;

      oldVolume = volume; 

    }

  }

}

void start(String app)

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

void chrome(String url){

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
