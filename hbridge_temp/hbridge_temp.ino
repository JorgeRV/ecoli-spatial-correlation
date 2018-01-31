// # Description:
// # The sketch for using the H bridge MD1.3 2A Dual Motor Controller SKUDRI0002
// # Run with the PWM mode

// # Connection:
// #        M1 pin  -> Digital pin 4
// #        E1 pin  -> Digital pin 5
// #        M2 pin  -> Digital pin 6
// #        E2 pin  -> Digital pin 7
// #        Motor Power Supply -> Centor blue screw connector(5.08mm 3p connector)
// #        Motor A  ->  Screw terminal close to E1 driver pin
// #        Motor B  ->  Screw terminal close to E2 driver pin
// # 
// # Note: You should connect the GND pin from the DF-MD v1.3 to your MCU controller. They should share the GND pins.
// #
// Connection pins for the DMC controller
int E1 = 7;
int M1 = 6;
int E2 = 5;                         
int M2 = 4;  

// Include the libraries we need for temperature
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS1 2
#define ONE_WIRE_BUS2 3

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire1(ONE_WIRE_BUS1);
OneWire oneWire2(ONE_WIRE_BUS2);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensor1(&oneWire1);
DallasTemperature sensor2(&oneWire2);

                         

void setup() 
{
    Serial.begin(9600); 
    pinMode(M1, OUTPUT);   
    pinMode(M2, OUTPUT);
   
    // Start up the library for temp
    sensor1.begin();
    sensor2.begin();
    
    Serial.println("Starting up...");
} 

void loop() 
{ 
  float temp;
  float temp2;
  float targetT;
  targetT = 37; //Set the target temperature
  
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensor1.requestTemperatures(); // Send the command to get temperatures
  sensor2.requestTemperatures();
  Serial.println("DONE");
  
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  Serial.print("Temperature for the device 1 (index 0) is: ");
  Serial.println(sensor1.getTempCByIndex(0));
  temp = sensor1.getTempCByIndex(0); //outside
  
  Serial.print("Temperature for the device 1 (index 1) is: ");
  Serial.println(sensor1.getTempCByIndex(1));
  temp2 = sensor2.getTempCByIndex(1); //inside
  
  //Power the connections
  int valuef;
  int valuep;
  
  valuef = 255; // Fans PWM
  valuep = 255; // Peltier PWM
  
  if (temp2 > targetT) {
    valuef = 255;
    valuep = 0;
  }

  //Fuente usada 12V 5A
  digitalWrite(M1,LOW);   
  digitalWrite(M2,LOW);       
  analogWrite(E1, valuef);   //Fans connector (>128)
  analogWrite(E2, valuep);   //Peltier connector
  
  Serial.print("Fans at: ");
  Serial.println(valuef);
  Serial.print("Peltier at: ");
  Serial.println(valuep);
  
}
