/*
*   Whatever it receives from the Serial USB (usually commands and queries) 
 *  is sent to the Dynamixel bus, and what it receives from the Dynamixel bus
 *  is sent to the SerialUSB (usually answers):
 *  Created by aprendiendo
 *  http://softwaresouls.com/softwaresouls/2013/06/12/robotis-cm-900-as-a-tosser-for-dynamixel-commands/
 *
 *  Most recent modification by Thierry Chantier on 2016-04-05.
 */
Dynamixel Dxl(1); //Dynamixel on Serial1(USART1)

bool onlyOnceHappened;

void setup()
{  
  pinMode(BOARD_LED_PIN, OUTPUT);

  onlyOnceHappened=false;

  //USB Serial initialize
  SerialUSB.begin();
  //  SerialUSB.attachInterrupt(USBDataReceived);
  //DXL initialize
  Dxl.begin(3);  
}

byte aByte=0;
uint8 aUint8;

void loop() 
{    
  //  SerialUSB.println (counter++);

  if (onlyOnceHappened==false)
  {    
    onlyOnceHappened=true;
    delay (3000); //Some time to the user to activate the monitor/console
    SerialUSB.println ("v1.1.1 Orders receiver started");  
  }    

  if (SerialUSB.available())
  {
    aUint8=SerialUSB.read();
    Dxl.writeRaw(aUint8);
  }   

  if (Dxl.available())
  {
    aByte=Dxl.readRaw();
    SerialUSB.write(aByte);
  } 
}



