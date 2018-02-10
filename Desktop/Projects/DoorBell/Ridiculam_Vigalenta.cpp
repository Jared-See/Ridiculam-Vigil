#include <SoftwareSerial.h>
SoftwareSerial Geno(7,8); // Rx , Tx pins

//Variables
unsigned char Data[10];
unsigned char i;

void setup() {
  delay(1000);
  Geno.begin(9600);
  delay(1000);
  SetVolume(30);
  playTrack(1);
}

void playTrack(int num){

    delay(1000);

    Data[0] = 0x7E;
    Data[1] = 0x04;
    Data[2] = 0xA0;
    Data[3] = 0x00;
    Data[4] = 0x00 + num;
    Data[5] = 0x7E;
   Command(Data,5);

    play_pause();

    delay(3000);

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

//Writes each file on the sd card as a piece of date
void Command(unsigned char *Data, int length){
    for(int i=0; i<length; i++){
    Geno.write(Data[i]);
    }

    }

void loop() {


  playTrack(1);

  playTrack(2);

}
