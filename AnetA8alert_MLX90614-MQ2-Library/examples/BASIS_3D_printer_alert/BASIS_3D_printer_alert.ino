/*

  This program is made as a help to avoid fire hasards for 3D printers and is used at your own risk.

  Safty:
  Printer Manufacturers strongly recommend that you do not leave a lit 3D printer unattended, and that is fitted
  with a smoke detector in umeldbart vicinity. This project is intended to provide further assistance.

  IR thermometer (GY-906), addresses the heatblocken so that it measures the temperature, while the smoke detector (MQ-2) measures possible. smoke.
  
  How to:
  Place the IR thermometer (GY-906) so it is pointing at the nozzel
  Place the MQ-2 at a high on the printer 
  The relay is mountet, on the main, befor the Powersuply and is mountet, as Normaly Closed, so if the power is turned off, the printer does not start automatically again

  Description:
  As an additional precaution, it is recommended to add a "Heated Bed Power Expansion moduel" so the power to "Heat Bed" bypassing the controller card

  Hookup:
  MLX90614 Temp Sensor by I2C interface:         A4 (SDA), A5 (SCL) by Limor Fried/Ladyada for Adafruit Industries.
  MQ-2 Smoke detector:                           A3
  Relay                                          D10 Take care, your working with main power
  

  by
  Michel Sommer, OZ1SQT http://markussen-net.dk

*/

#include <Wire.h>
#include <MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#define RELAY_PIN 10             // Relay
#define SMOKE_PIN A3             // MQ2 smokesensor analogpin

#define THRESHOLD_HIGH 310       // threshold level 310
#define THRESHOLD_SMOKE_HIGH 400 // threshold level 400 HIGH

#define PulseTime 1              // Delay time in seconds

float analogSMOKE = 0;
float PrinterTemperature = 0;

void setup() {
  Serial.begin(9600); 
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SMOKE_PIN, INPUT);
  
  mlx.begin();
}

void loop() {
  PrinterTemperature = mlx.readObjectTempC();   
  analogSMOKE = analogRead(SMOKE_PIN);
   
Serial.print("Object = "); 
Serial.print(PrinterTemperature); 
Serial.println(" C");  
Serial.print("Ambient = ");  
Serial.print(mlx.readAmbientTempC()); 
Serial.println(" C");  
  
    // High temp
  if (PrinterTemperature >= THRESHOLD_HIGH) {
    digitalWrite(RELAY_PIN, HIGH);     
  }

      // Smoke alert, AnalogIndput
  if (analogSMOKE > THRESHOLD_SMOKE_HIGH) {
    digitalWrite(RELAY_PIN, HIGH); 
  }
  
    // High temp and smoke alert
  if ((PrinterTemperature >= THRESHOLD_HIGH) && (analogSMOKE > THRESHOLD_SMOKE_HIGH)) {
    digitalWrite(RELAY_PIN, HIGH);
  }
    
    // Idel
  else {
    digitalWrite(RELAY_PIN, LOW); 

  }

  delay(PulseTime * 1000);

}
