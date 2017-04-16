#include "RCSwitch.h"
// turn sockets 1,2,3,5 when 4 is turned on;

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
  mySwitch.enableTransmit(10);
  mySwitch.setPulseLength(180);
}


/**
 repeat 5 times with 5msec delay in between.
*/
void sendTriState(const char* sCodeWord) {
  for (int i=0; i<5; i++) {
    mySwitch.sendTriState(sCodeWord);
    delay(5);
  }
}

void loop() {
  if (mySwitch.available()) {
    long received = mySwitch.getReceivedValue();
    output(received, mySwitch.getReceivedBitlength(), mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(),mySwitch.getReceivedProtocol());
// 4-on
//Decimal: 1334531 (24Bit) Binary: 000101000101110100000011 Tri-State: 0FF0FF1F0001 PulseLength: 184 microseconds Protocol: 1
//Raw data: 5788,44,592,176,544,188,556,544,212,120,1400,80,572,536,200,164,564,524,296,56,740,388,196,172,560,536,196,176,256,16,3540,60,188,16,216,200,104,552,28,2168,180,248,116,180,112,288,84,52,100,
    if (received == 1334531) {//4-on
      Serial.println("Switching on");
      sendTriState("0FF0FFFF0101");//1-on
      sendTriState("0FF0FFFF1001");//2-on
      sendTriState("0FF0FFF10001");//3-on
      sendTriState("0FF0F1FF0001");//5-on
      Serial.println("Done!");
    }
// 4-off
//Decimal: 1334540 (24Bit) Binary: 000101000101110100001100 Tri-State: 0FF0FF1F0010 PulseLength: 183 microseconds Protocol: 1
//Raw data: 5728,76,720,16,692,48,580,504,168,204,520,560,228,236,580,64,1432,484,136,412,320,44,732,428,160,572,140,608,128,224,536,484,1428,60,568,236,492,596,620,176,512,592,152,544,632,48,1448,24,492,

    if (received == 1334540) {//4-off
      Serial.println("Switching off");
      sendTriState("0FF0FFFF0110");//1-off
      sendTriState("0FF0FFFF1010");//2-off
      sendTriState("0FF0FFF10010");//3-off
      sendTriState("0FF0F1FF0010");//5-off
      Serial.println("Done!");
    }


    mySwitch.resetAvailable();

  }


}
