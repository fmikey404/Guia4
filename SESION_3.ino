#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;
#define btn 15

int stsBtn = 0;
void setup() {
  SerialBT.begin("Snakeman");
  Serial.begin(115200);
  pinMode(btn, INPUT);
}

void loop() {
  stsBtn = digitalRead(btn);
  Serial.println(stsBtn);
  SerialBT.println(stsBtn);
  if (stsBtn == 1){
    delay(1500);
  }
  delay(100);
}
