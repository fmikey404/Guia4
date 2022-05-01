#include <BluetoothSerial.h>

#define pinLedR 21
#define pinLedG 22
#define pinLedB 23
#define canalRed 2
#define canalGreen 3
#define canalBlue 4
int freq = 10000, res = 8;
BluetoothSerial SerialBT;

String recibido, colorRojo, colorVerde, colorAzul;
int rojo, verde, azul;
void setup() {
  Serial.begin(115200);
  SerialBT.begin("Snakeman");
  ledcSetup(canalRed, freq, res);
  ledcSetup(canalGreen, freq, res);
  ledcSetup(canalBlue, freq, res);
  ledcAttachPin(pinLedR, canalRed);
  ledcAttachPin(pinLedG, canalGreen);
  ledcAttachPin(pinLedB, canalBlue);
}

void loop() {
  String recibido = SerialBT.readStringUntil('\n');
  recibido.remove(recibido.length()-1, 1);
  
  byte comaUno = recibido.indexOf(',');
  byte comaDos = recibido.indexOf(',', comaUno + 1);
  byte comaTres = recibido.indexOf(',', comaDos + 1);
  
  Serial.println(recibido);
  
  colorRojo = recibido.substring(0,comaUno);
  colorVerde = recibido.substring(comaUno + 1,comaDos);
  colorAzul = recibido.substring(comaDos +1, comaTres);

  rojo = colorRojo.toInt();
  verde = colorVerde.toInt();
  azul = colorAzul.toInt();

  Serial.println("Rojo: " + (String)rojo);
  Serial.println("Verde: " + (String)verde);
  Serial.println("Azul: " + (String)azul);

  RGB(rojo, verde, azul);
}

void RGB(int R, int G, int B){
  ledcWrite(canalRed, R);
  ledcWrite(canalGreen, G);
  ledcWrite(canalBlue, B);
  
}
