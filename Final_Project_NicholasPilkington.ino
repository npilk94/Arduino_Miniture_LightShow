/*
 * Nicholas Pilkington
 * ISAT-342-001
 * 12-15-17
 * 
 * Miniature LED Christmas Show:
 * This code creates a miniature LED Christmas display using arrays, 
 * 8-bit binary LED setup, and receives the commands from the ESP8266
 * on what tasks to perform.
*/
#include "pitches.h"

#define led0 B00000001  // Used on Red LED
#define led1 B00000010  // Used on Green LED
#define led2 B00000100  // Used on Blue LED
#define led3 B00001000  // Used on Red LED
#define led4 B00010000  // Used on Green LED
#define led5 B00100000  // Used on Red LED
#define led6 B01000000  // Used on Blue LED
#define led7 B10000000  // Used on Green LED

// Array for the LED PINS
int ledPins[] = {
  5,4,3,9,2,7,6,8
};

int pinCount = 8; // Amount of LED PIN connections
/**********************************************************************/
// JingleBells Melody array
int jingleBells_melody[] = {
  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4,
  NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4,
  NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_G4,

  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4,
  NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4,
  NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_C4, NOTE_C4
};
// Jingle Bells Beats array
int jingleBells_beats[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8, 4,
  8, 8, 8, 8, 
  8, 8, 8, 8, 
  8, 8, 8, 8, 4, 4,

  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8, 4,
  8, 8, 8, 8, 
  8, 8, 8, 8,
  8, 8, 8, 8, 4 , 4 
};
// Jingle Bells LEDs array
byte jingleBells_LEDs[] = {
  B00100100, B01100110, B11100111,
  B00100100, B01100110, B11100111,
  B00100100, B01100110, B11100111, B11111111, B11111111,
  B00100100, B01100110, B11100111, B11000011, 
  B00100100, B01100110, B11100111, B10000001,
  B00100100, B01100110, B11100111, B1000001, B11100111, B11111111,

  B00100100, B01100110, B11100111,
  B00100100, B01100110, B11100111,
  B00100100, B01100110, B11100111, B11111111, B11111111,
  B00100100, B01100110, B11100111, B11000011, 
  B00100100, B01100110, B11100111, B10000001,
  B00100100, B01100110, B11100111, B1000001, B11100111, B11111111
};

/**********************************************************************/
// Let it Snow Melody array
int letItSnow_melody[] = {
  NOTE_G3, NOTE_G3,
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_G3,
  NOTE_D4, NOTE_C4, NOTE_D4, NOTE_C4,
  NOTE_B3, NOTE_G3, NOTE_A3,
  NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4,
  NOTE_D4, NOTE_B4, NOTE_A4, 
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_G3, 

  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_G3,
  NOTE_D4, NOTE_C4, NOTE_D4, NOTE_C4,
  NOTE_B3, NOTE_G3, NOTE_A3,
  NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4,
  NOTE_D4, NOTE_B4, NOTE_A4, 
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
  NOTE_C4
};
// Let It Snow Beats array
int letItSnow_beats[] = {
  13,13,
  13, 13, 7, 7, 7,
  7, 3, 13, 13,
  7, 7, 7, 7,
  7, 3, 7,
  13, 13, 7, 7, 7,
  5, 13, 13,
  7, 13, 13, 7, 13, 13, 
  5, 7,

  13, 13, 7, 7, 7,
  7, 3, 13, 13,
  7, 7, 7, 7,
  7, 3, 7,
  13, 13, 7, 7, 7,
  5, 13, 13,
  7, 13, 13, 7, 13, 13, 
  7, 7,
  1
};
// Let It Snow LEDs array
byte letItSnow_LEDs[] = {
  B10000100, B00100001,
  B11100111, B11100111, B11100111, B11000011, B10000001,
  B00011000, B11111111, B10000100, B00100001,
  B10000010, B01000100, B00100010, B00100100, 
  B01100110, B11100111, B10100101,
  B10000001, B00100100, B01000010, B01100110, B10011001,
  B11111111, B00011000, B00010000,
  B01100110, B10000100, B00100001, B11100111, B01100110, B10100101,
  B11111111, B00011000,
  
  B11100111, B11100111, B11100111, B11000011, B10000001,
  B00011000, B11111111, B10000100, B00100001,
  B10000010, B01000100, B00100010, B00100100, 
  B01100110, B11100111, B10100101,
  B10000001, B00100100, B01000010, B01100110, B10011001,
  B11111111, B00011000, B00010000,
  B01100110, B10000100, B00100001, B11100111, B01100110, B10100101,
  B11111111, B00011000,
  B11111111
};
/**********************************************************************/
String inputCheck;        // Holds the user input 
int thisNote = 0;        // Sets the starting place in the array 

// Length of jingleBells_melody, for looping
int notelength1 = (sizeof(jingleBells_melody) / 2); 
// Length of letItSnow_melody, for looping
int notelength2 = (sizeof(letItSnow_melody) / 2);

int tempo = 1800;           // Sets default tempo
int start_JingleBells = 0;  // Sets start_JingleBells to 0 
int start_LetItSnow = 0;    // Setsstart_LetItSnow to 0

void setup() {     
  Serial.begin(9600); //Initializes Serial 9600
  pinMode(12, OUTPUT); //Set speaker as output 
  
// Used to set output mode for the LED PINS
 for (int i=0;i<pinCount;i++)
  {
    pinMode(ledPins[i],OUTPUT); // Sets the ledPins array as output mode
  } 
}  
void loop() { 
  while (Serial.available() > 0)
  {   // While Serial.available is greater than zero, check for user entered data
     inputCheck = Serial.readStringUntil('\n'); //Read string until end of line
     Serial.println(inputCheck);
     
// If inputCheck is equal to one of these numbers, perform the following task
        if (inputCheck == "8" || inputCheck == "9" || inputCheck == "10" || inputCheck == "11" || inputCheck == "12")
        {
          tempo = (inputCheck.toInt()); // Sets tempo equal to inputCheck recieved from ESP8266
          tempo = tempo*180;            // Muliplies tempo by 180 to be used for note duration
        }
  }
  
// if inputCheck is equal to stop, perform the following 
if (inputCheck == "stop")
  {
    startOver(); // Calls this function to start the song over
  } 
  
// if inputCheck is equal to stop10, perform the following 
if (inputCheck == "stop10")
{
  tempo = 1800; // Sets tempo to default
  startOver();  // Calls this function to start the song over 
}

// Used to keep JingleBells array from overlapping with Let It Snow
if (start_JingleBells == 0 && inputCheck == "song1"){      
    start_JingleBells = 1;  // Sets start_JingleBells 1
    delay(10);              // Delay to prevent errors 
 }
// Checks if both statments are true, if they are, starts the song
     if(start_JingleBells == 1 && inputCheck == "song1"){  
       Serial.println(tempo);   // Used for testing to make sure tempo changed    
       Serial.println(thisNote);// Used for testing to check the current note       
  // Creates a note duration based on tempo and the current beat from JingleBells
      int noteDuration = tempo/ jingleBells_beats[thisNote];           
  // Start playing JingleBells 
      tone(12,jingleBells_melody[thisNote],jingleBells_beats);      
  // Turns on the LEDs that are set for the current note     
       jingleBells_LEDon(thisNote);  
  // Delay for how long to play the current note           
       delay(noteDuration);   
  // Turns on the LEDs that are set for the current note 
       jingleBells_LEDoff(thisNote);
  // Creates a pause between the notes based on noteduration multiplied by 30%
       int pauseBetweenNotes = noteDuration * 1.3;
  // Delay for how long to pause between the current note
       delay(pauseBetweenNotes); 
  // Increments to the next note in the array          
       thisNote++;       
      if (inputCheck == "pause"){ // Checks if a button was pressed to pause the song  
          return;   // Reserve word to pause the song   
         }                     
  // Checks if at the end of the song
      else if(thisNote > (notelength1 - 1)){           
       startOver();    // Calls this function to start the song over      
        }              
    }
    
// Used to keep LetItSnow array from overlapping with Jingle Bells
if (start_LetItSnow == 0 && inputCheck == "song2"){   
    start_LetItSnow = 1;  // Sets start_JingleBells 1
    delay(10);            // Delay to prevent errors 
    } 
    
// Checks if both statments are true, if they are, starts the song                     
       if(start_LetItSnow == 1 && inputCheck == "song2"){   
       Serial.println(tempo);   // Used for testing to make sure tempo changed    
       Serial.println(thisNote);// Used for testing to check the current note       
  // Creates a note duration based on tempo and the current beat from LetItSnow
      int noteDuration = tempo/ letItSnow_beats[thisNote];           
  // Start playing LetItSnow 
     tone(12,letItSnow_melody[thisNote],letItSnow_beats);      
  // Turns on the LEDs that are set for the current note     
       letItSnow_LEDon(thisNote);  
  // Delay for how long to play the current note           
       delay(noteDuration);   
  // Turns on the LEDs that are set for the current note 
       letItSnow_LEDoff(thisNote);
  // Creates a pause between the notes based on noteduration multiplied by 30%
       int pauseBetweenNotes = noteDuration * 1.3;
  // Delay for how long to pause between the current note
       delay(pauseBetweenNotes); 
  // Increments to the next note in the array          
       thisNote++;       
      if (inputCheck == "pause"){ // Checks if a button was pressed to pause the song  
          return;   // Reserve word to pause the song   
         }                     
  // Checks if at the end of the song
      else if(thisNote > (notelength2 - 1)){           
       startOver();    // Calls this function to start the song over    
        } 
     }    
}
// This function starts over the song
void startOver(){
       thisNote = 0;           // Sets back to default value
       start_JingleBells = 0;  // Sets back to default value
       start_LetItSnow = 0;    // Sets back to default value
}
// Function to turn Jingle Bells LEDs on
void jingleBells_LEDon(int thisNote)
{ // Checks if the current LED for current note is not equal to zero,
  // If it is not, then set the state of the LED to HIGH or On
  if ((jingleBells_LEDs[thisNote]&led0)!=0) digitalWrite(ledPins[0],HIGH);
  if ((jingleBells_LEDs[thisNote]&led1)!=0) digitalWrite(ledPins[1],HIGH);
  if ((jingleBells_LEDs[thisNote]&led2)!=0) digitalWrite(ledPins[2],HIGH);
  if ((jingleBells_LEDs[thisNote]&led3)!=0) digitalWrite(ledPins[3],HIGH);
  if ((jingleBells_LEDs[thisNote]&led4)!=0) digitalWrite(ledPins[4],HIGH);
  if ((jingleBells_LEDs[thisNote]&led5)!=0) digitalWrite(ledPins[5],HIGH);
  if ((jingleBells_LEDs[thisNote]&led6)!=0) digitalWrite(ledPins[6],HIGH);
  if ((jingleBells_LEDs[thisNote]&led7)!=0) digitalWrite(ledPins[7],HIGH);
}
// Function to turn Let It Snow LEDs on
void letItSnow_LEDon(int thisNote)
{ // Checks if the current LED for current note is not equal to zero,
  // If it is not, then set the state of the LED to HIGH or On
  if ((letItSnow_LEDs[thisNote]&led0)!=0) digitalWrite(ledPins[0],HIGH);
  if ((letItSnow_LEDs[thisNote]&led1)!=0) digitalWrite(ledPins[1],HIGH);
  if ((letItSnow_LEDs[thisNote]&led2)!=0) digitalWrite(ledPins[2],HIGH);
  if ((letItSnow_LEDs[thisNote]&led3)!=0) digitalWrite(ledPins[3],HIGH);
  if ((letItSnow_LEDs[thisNote]&led4)!=0) digitalWrite(ledPins[4],HIGH);
  if ((letItSnow_LEDs[thisNote]&led5)!=0) digitalWrite(ledPins[5],HIGH);
  if ((letItSnow_LEDs[thisNote]&led6)!=0) digitalWrite(ledPins[6],HIGH);
  if ((letItSnow_LEDs[thisNote]&led7)!=0) digitalWrite(ledPins[7],HIGH);
}
// Function to turn Jingle Bells LEDs off
void jingleBells_LEDoff(int thisNote)
{ // Checks if the current LED for current note is not equal to zero,
  // If it is not, then set the state of the LED to LOW or Off
  if ((jingleBells_LEDs[thisNote]&led0)!=0) digitalWrite(ledPins[0],LOW);
  if ((jingleBells_LEDs[thisNote]&led1)!=0) digitalWrite(ledPins[1],LOW);
  if ((jingleBells_LEDs[thisNote]&led2)!=0) digitalWrite(ledPins[2],LOW);
  if ((jingleBells_LEDs[thisNote]&led3)!=0) digitalWrite(ledPins[3],LOW);
  if ((jingleBells_LEDs[thisNote]&led4)!=0) digitalWrite(ledPins[4],LOW);
  if ((jingleBells_LEDs[thisNote]&led5)!=0) digitalWrite(ledPins[5],LOW);
  if ((jingleBells_LEDs[thisNote]&led6)!=0) digitalWrite(ledPins[6],LOW);
  if ((jingleBells_LEDs[thisNote]&led7)!=0) digitalWrite(ledPins[7],LOW);
}
// Function to turn Let It Snow LEDs off
void letItSnow_LEDoff(int thisNote)
{ // Checks if the current LED for current note is not equal to zero,
  // If it is not, then set the state of the LED to LOW or Off
  if ((letItSnow_LEDs[thisNote]&led0)!=0) digitalWrite(ledPins[0],LOW);
  if ((letItSnow_LEDs[thisNote]&led1)!=0) digitalWrite(ledPins[1],LOW);
  if ((letItSnow_LEDs[thisNote]&led2)!=0) digitalWrite(ledPins[2],LOW);
  if ((letItSnow_LEDs[thisNote]&led3)!=0) digitalWrite(ledPins[3],LOW);
  if ((letItSnow_LEDs[thisNote]&led4)!=0) digitalWrite(ledPins[4],LOW);
  if ((letItSnow_LEDs[thisNote]&led5)!=0) digitalWrite(ledPins[5],LOW);
  if ((letItSnow_LEDs[thisNote]&led6)!=0) digitalWrite(ledPins[6],LOW);
  if ((letItSnow_LEDs[thisNote]&led7)!=0) digitalWrite(ledPins[7],LOW);
}


