#include <PZEM004Tv30.h>

#define PZEM_RX_PIN 16
#define PZEM_TX_PIN 17
#define PZEM_SERIAL Serial2

PZEM004Tv30 pzem(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN);

void setup() {
  Serial.begin(115200);
  Serial.println("PZEM004T Address Management");
  Serial.println("Type 'set' to set a new custom address.");
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    if (command.equalsIgnoreCase("set")) {
      setAddressFromSerial();
    } else if (command.equalsIgnoreCase("get")) {
      getAddressFromSerial();
    } else {
      Serial.println("Invalid command. Available commands: 'set', 'get'");
    }
  }
}

void setAddress(uint8_t customAddress) {
  Serial.print("Setting address to: 0x");
  Serial.println(customAddress, HEX);
  if (!pzem.setAddress(customAddress)) {
    Serial.println("Error setting address.");
  } else {
    Serial.println("Address set successfully.");
  }
  delay(1000);  // Delay for stability before reading
}

void setAddressFromSerial() {
  Serial.println("Enter the custom address (0x01 - 0xF7):");
  while (!Serial.available()) {
    // Wait for user input
  }
  
  String input = Serial.readStringUntil('\n');
  input.trim();
  
  if (input.startsWith("0x")) {
    input = input.substring(2);
  }
  
  uint8_t customAddress = strtol(input.c_str(), NULL, 16);
  
  if (customAddress >= 0x01 && customAddress <= 0xF7) {
    for (int i = 0; i < 5; i++) {
      if (pzem.setAddress(customAddress)) {
        Serial.println("Address set successfully.");
        break;
      } else {
        Serial.println("Error setting address. Retrying...");
        delay(1000); // Delay before retrying
      }
    }
  } else {
    Serial.println("Invalid address. Please enter an address between 0x01 and 0xF7.");
  }
}

void getAddressFromSerial() {
  uint8_t currentAddress = pzem.readAddress();
  Serial.print("Current address: 0x");
  Serial.println(currentAddress, HEX);
}