#include <IRremote.hpp>  // Use .hpp for IRremote 4.x
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define IR_RECEIVE_PIN A0 //analog pin to recieve data
int ledpin = 13;
void setup() {
  Serial.begin(115200); 
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the IR receiver
  Serial.println("IR Receiver Ready - Press a button on your remote");
  lcd.begin(16, 2); //initializes display size to show that many columns and rows. Must be called in setup and manage display memory
  lcd.print("IR decoder"); //prints text to screen
}

void loop() {
  delay(100);
  lcd.setCursor(0, 0);         // First column, first line
  if (IrReceiver.decode()) {
  digitalWrite(ledpin, HIGH); //LED turns on when signal received
    delay(700);
    // Print raw data in old HEX format
    Serial.print("Raw Data (HEX): 0x");
    Serial.println((unsigned long)IrReceiver.decodedIRData.decodedRawData, HEX);

    // Print detailed protocol info (protocol, address, command, etc.)
    //IrReceiver.printIRResultShort(&Serial);

    // Print how to send the same command back
    //IrReceiver.printIRSendUsage(&Serial);

    IrReceiver.resume(); // Ready for next IR signal
    lcd.print("HEX: 0x");  //print HEX on the LCD screen
    lcd.print((unsigned long)IrReceiver.decodedIRData.decodedRawData, HEX);
  }
  digitalWrite(ledpin, LOW); //turns off LED after HEX printed
  
}
