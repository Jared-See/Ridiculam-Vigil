#include <SoftwareSerial.h>
SoftwareSerial Geno(7,8); // Rx , Tx

unsigned char Data[10];
unsigned char i;

// defines pins numbers
const int trigPin = 8;
const int echoPin = 9;

// defines variables
long duration;
int distance;

void setup() {
  delay(1000);
  Geno.begin(9600);
  delay(1000);
  SetVolume(30);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void playTrack(int num){

    delay(100);

    Data[0] = 0x7E;
    Data[1] = 0x04;
    Data[2] = 0xA0;
    Data[3] = 0x00;
    Data[4] = 0x00 + num;
    Data[5] = 0x7E;
   Command(Data,5);

    play_pause();

    delay(10000);

}

void SetVolume( int vol){
   Data[0] = 0x7E;          // START
   Data[1] = 0x03;          // Length Not 0x02
   Data[2] = 0xA7;          // Command
   Data[3] = vol;          // new volume
   Data[4] = 0x7E;          // END
   Command(Data,5);
}

void play_pause(){
  Data[0] = 0x7E;          // START
  Data[1] = 0x02;          // Length
  Data[2] = 0xA3;          // Command
  Data[3] = 0x7E;          //Mode parameter
  Command(Data,4);
}

void Command(unsigned char *Data, int length){
    for(int i=0; i<length; i++){
    Geno.write(Data[i]);
    }

    }

void loop() {
  //Assigns a random number
  int song = random(0,200);
  Serial.print("Song is:");
  Serial.print(song);
  Serial.print("\n");
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance= duration*0.034/2;

  Serial.print("Distance: ");
  Serial.println(distance);
  if(distance < 20){
    playTrack(25);
  }
  //playTrack(1);
  //playTrack(2);
}
