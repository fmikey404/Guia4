#include <BluetoothSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;
#define pres 32
#define pote 34
#define btnBack 15
#define btn 13
#define vrX 25
#define btnJstk 35
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int stsBtnBack = 0, stsBtnJstk = 0, stsBtn = 0, posSel = 11, vlrX;

void selec(int posY){
  display.fillRect(3, posY, 5, 5, WHITE);
  display.display();
}

void delSelec(int posY){
  display.fillRect(3, posY, 5, 5, BLACK);
  display.display();
}

void menu(){
   display.clearDisplay();
   display.setTextColor(WHITE);
   display.setCursor(54, 0);
   display.print("MENU");
   display.setCursor(15, 10);
   display.print("Pulsador");
   display.setCursor(15, 20);
   display.print("Sensor de Presion");
   display.setCursor(15, 30);
   display.print("Potenciometro");
   display.display();
}

void senPress(bool t){
  stsBtnBack = 0;
  while (t){
    SerialBT.print('E');
    SerialBT.print("0,");
    SerialBT.print(analogRead(pres));
    SerialBT.println(",0");
    delay(100);
    stsBtnBack = digitalRead(btnBack);
    if (stsBtnBack == 1){
      t = false;
    }
  }
}

void senPote(bool t){
  stsBtnBack = 0;
  while(t){
    SerialBT.print('E');
    SerialBT.print("0,");
    SerialBT.print("0,");
    SerialBT.println(analogRead(pote));
    delay(100); 
    stsBtnBack = digitalRead(btnBack);
    if (stsBtnBack == 1){
      t = false;
    }
  }
}

void senBtn(bool t){
  stsBtnBack = 0;
  while (t){
    stsBtn = digitalRead(btn);
    SerialBT.print('E');
    SerialBT.print(map(stsBtn, 0, 1, 0, 4095));
    SerialBT.print(",0");
    SerialBT.println(",0");
    delay(100);
    stsBtnBack = digitalRead(btnBack);
    if (stsBtnBack == 1){
      t = false;
    }
  }
}

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Snakeman");
  pinMode(pote, INPUT);
  pinMode(pres, INPUT);
  pinMode(btn, INPUT);
  pinMode(vrX, INPUT);
  pinMode(btnJstk, INPUT);
  pinMode(btnBack, INPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  menu();
  selec(posSel);
}

void loop() {
  vlrX = map(analogRead(vrX), 0, 4095, -1, 1);
  if (vlrX == -1){
    delSelec(posSel);
    posSel = posSel + 10;
    if (posSel > 31){
      posSel = 11;
    }
    selec(posSel);
  }else if (vlrX == 1){
    delSelec(posSel);
    posSel = posSel - 10;
    if (posSel < 11){
      posSel = 31;
    }
    selec(posSel);
  }
  delay(200);
  stsBtnJstk = !digitalRead(btnJstk);
  if (stsBtnJstk == 1 and posSel == 11){
    Serial.println("Pulsador seleccionado");
    senBtn(true);
  }else if (stsBtnJstk == 1 and posSel == 21){
    Serial.println("Sensor Presion seleccionado");
    senPress(true);
  }else if (stsBtnJstk == 1 and posSel == 31){
    Serial.println("Potenciometro seleccionado");
    senPote(true);
  }
}
