#include <BluetoothSerial.h>
#include <Servo_ESP32.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;

#define pinLedR 21
#define pinLedG 22
#define pinLedB 23
#define canalRed 2
#define canalGreen 3
#define canalBlue 4
int freq = 10000, res = 8, valorRecibido;
#define pinServo 13
Servo_ESP32 servo;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Snakeman");
  ledcSetup(canalRed, freq, res);
  ledcSetup(canalGreen, freq, res);
  ledcSetup(canalBlue, freq, res);
  ledcAttachPin(pinLedR, canalRed);
  ledcAttachPin(pinLedG, canalGreen);
  ledcAttachPin(pinLedB, canalBlue);
  servo.attach(pinServo);
}

void loop() {
  valorRecibido = SerialBT.read();
  switch(valorRecibido){
    case 82:
      SerialBT.println("Led en Rojo");
      RGB(255, 0, 0);
      break;
    case 71:
      SerialBT.println("Led en Verde");
      RGB(0, 255, 0);
      break;
    case 66:
      SerialBT.println("Led en Azul");
      RGB(0, 0, 255);
      break;
    case 89:
      SerialBT.println("Led en Amarillo");
      RGB(245, 209, 29);
      break;  
    case 80:
      SerialBT.println("Led en Morado");
      RGB(133, 29, 245);
      break;
    case 69:
      SerialBT.println("Led Totalmente Encendido");
      RGB(255, 255, 255);
      break;
    case 65:
      SerialBT.println("Led Totalmente Apagado");
      RGB(0,0,0);
      break;
    case 48:
      SerialBT.println("Servomotor en 0°");
      servo.write(0);
      break;
    case 49:
      SerialBT.println("Servomotor en 20°");
      servo.write(20);
      break;
    case 50:
      SerialBT.println("Servomotor en 45°");
      servo.write(45);
      break;
    case 51:
      SerialBT.println("Servomotor en 90°");
      servo.write(90);
      break;
    case 52:
      SerialBT.println("Servomotor en 135°");
      servo.write(135);
      break;
    case 53:
      SerialBT.println("Servomotor en 150°");
      servo.write(150);
      break;
    case 54:
      SerialBT.println("Servomotor en 180°");
      servo.write(180);
      break;
  }
}

void RGB(int R, int G, int B){
  ledcWrite(canalRed, R);
  ledcWrite(canalGreen, G);
  ledcWrite(canalBlue, B);
  
}
