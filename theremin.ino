
#include <HardwareSerial.h>


unsigned long sendDataPrevMillis = 0;

//unsigned long count = 0;


//THEREMIN PINS
#define trigPin 13 // define trigPin
#define echoPin 14 // define echoPin.
#define MAX_DISTANCE 700 // Maximum sensor distance is rated at 400-500cm. 
HardwareSerial Unit2(1);

void Theremin_Setup()
{

  //Serial.begin(115200);
 Unit2.begin(9600, SERIAL_8N1, 2, 15);
 

  //THEREMIN SETUP CODE
  pinMode(trigPin,OUTPUT);// set trigPin to output mode
  pinMode(echoPin,INPUT); // set echoPin to input mode
  
}



//Theremin code
//#define trigPin 13 // define trigPin
//#define echoPin 14 // define echoPin.
//#define MAX_DISTANCE 700 // Maximum sensor distance is rated at 400-500cm. 
//timeOut= 2*MAX_DISTANCE /100 /340 *1000000 = MAX_DISTANCE*58.8
float timeOut = MAX_DISTANCE * 60;
int soundVelocity = 340; // define sound speed=340m/s
float note = -1.0;
float oldNote = -1.0;
float noteVelocity = 1.0f;
bool isPitchBendOn = false;
//void Theremin_Setup() {
//  pinMode(trigPin,OUTPUT);// set trigPin to output mode
//  pinMode(echoPin,INPUT); // set echoPin to input mode
//  
//  //Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
//}
void Theremin_Loop() {

  while(Unit2.available()) {
    note = Unit2.read();
    if(oldNote == -1.0){
      Synth_NoteOn(0, note, noteVelocity);
    }
    else if(note != oldNote){
      Synth_NoteOff(0, oldNote);
      Synth_NoteOn(0, note, noteVelocity);
    }
    oldNote = note;
  }
 }
