# คู่มือการใช้งานโมดูล PZEM-004T V3.0 ด้วย Arduino

คู่มือนี้อธิบายวิธีใช้งานโมดูล PZEM-004T V3.0 เพื่อการจัดการที่อยู่ (Address) ผ่านพอร์ต Serial บน Arduino โดยใช้ไลบรารี [PZEM004Tv30.h](https://github.com/mandulaj/PZEM-004T-v30 "Library link") ทำงานบน ESP32.

## การเตรียมงานและการติดตั้ง

1. เชื่อมต่อโมดูล PZEM-004T V3.0 กับ ESP32 ตามพินที่กำหนด:
   - **PZEM_RX_PIN**: 16
   - **PZEM_TX_PIN**: 17
2. ติดตั้งไลบรารี PZEM004Tv30 ผ่าน Arduino IDE Library Manager.
3. อัพโหลดโค้ดลง ESP32 ให้เรียบร้อย.

## ตัวอย่างการใช้งาน

1. เมื่อเปิด Serial Monitor และโมดูลพร้อมทำงาน:

   - พิมพ์ "set" เพื่อเปลี่ยนค่าที่อยู่.
   - ป้อนค่าที่อยู่ใหม่ตามที่ระบุ.
   - ระบบจะพยายามเปลี่ยนค่าที่อยู่และแสดงผลลัพธ์.

2. หรือ

   - พิมพ์ "get" เพื่ออ่านค่าที่อยู่ปัจจุบัน.

3. หากมีคำสั่งไม่ถูกต้อง:

   - ระบบจะแสดงข้อความ "Invalid command. Available commands: 'set', 'get'."

## การทำงานของโค้ด

```cpp
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

// ... ฟังก์ชันเพิ่มเติม ...
```

## ฟังก์ชันหลัก

`setAddress(uint8_t customAddress)` : ใช้สำหรับตั้งค่าที่อยู่ที่กำหนดเอง.
`setAddressFromSerial()` : ใช้สำหรับกำหนดค่าที่อยู่ผ่าน Serial Monitor.
`getAddressFromSerial()` : ใช้อ่านค่าที่อยู่ปัจจุบันจากโมดูล.# PZEM-Address-Changer
