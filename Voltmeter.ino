#include <TM1651.h>
#include <TM1637Display.h>

//voltageDisplay - VT
//batteryDisplay - BT

#define VT_CLK 2
#define VT_DIO 3
#define BT_CLK 4
#define BT_DIO 5
#define VOLT_SENSOR A0
#define VOLT_SWITCH 6
 
float in_voltage = 0.0;
int buttonState = 0;

TM1637Display voltDisplay = TM1637Display(VT_CLK, VT_DIO);
TM1651 batteryDisplay(BT_CLK, BT_DIO);

void setup() {

  voltDisplay.setBrightness(7);
  batteryDisplay.init();
  batteryDisplay.displayLevel(BRIGHTEST);
  pinMode(VOLT_SWITCH, INPUT);
  digitalWrite(VOLT_SWITCH, HIGH);
}

void loop() {
  if (digitalRead(VOLT_SWITCH) == LOW) {
    voltageStateShow(buttonState);
    changeButtonState();
  }
  
  voltageCalculate();
  voltageShow(in_voltage);
  delay(500);
}

void voltageCalculate(){
  float adc_voltage = 0.0;
  float R1 = 30000.0;
  float R2 = 7500.0; 
  float ref_voltage = 5.0;
  int adc_value = 0;
  
  adc_value = analogRead(VOLT_SENSOR);
  adc_voltage  = (adc_value * ref_voltage) / 1024.0; 
  in_voltage = adc_voltage / (R2/(R1+R2)) ;
}

void changeButtonState(){
  if (buttonState != 3){
    buttonState++;
  }else{
    buttonState = 0;
  }
}

void voltageShow(float voltage){
    if (voltage < 0.100){
    voltDisplay.showNumberDecEx(0, 0b01000000, true, 4, 0);
    batteryDisplay.clearDisplay();
  }else{
    if (voltage < 10){
      voltDisplay.showNumberDecEx(voltage*100, 0b01000000, true, 4, 0);
      batteryCapacityShow(voltage, buttonState);
    }else{
      voltDisplay.showNumberDecEx(voltage*100, 0b01000000, false, 4, 0);
      batteryCapacityShow(voltage, buttonState);
    }
  } 
}

void voltageStateShow(int state){
  if (state == 0){ //1.5V
    voltDisplay.showNumberDecEx(15, 0b00100000, false, 2, 2);
    delay(1000);
  }else if (state == 1){ //3V
    voltDisplay.showNumberDec(3, false, 1, 3);
    delay(1000);
  }else if (state == 2){ //9V
    voltDisplay.showNumberDec(9, false, 1, 3);
    delay(1000);
  }else if (state == 3){ //12V
    voltDisplay.showNumberDec(12, false, 2, 2);
    delay(1000);
  }
}

void batteryCapacityShow(float voltage, int state){
  if (state == 0){ //1.5V
    show1_5Voltage(voltage);
  }else if (state == 1){ //3V
    show3Voltage(voltage);
  }else if (state == 2){ //9V
    show9Voltage(voltage);
  }else if (state == 3){ //12V
    show12Voltage(voltage);
  }
}

void show1_5Voltage(float voltage){
  if (voltage < 0.3){
    batteryDisplay.displayLevel(0);
    batteryDisplay.frame(FRAME_OFF);
  }else if (voltage < 0.6){
    batteryDisplay.displayLevel(1);
    batteryDisplay.frame(FRAME_OFF);
  }else if (voltage < 0.9){
    batteryDisplay.displayLevel(2);
    batteryDisplay.frame(FRAME_OFF);
  }else if (voltage < 1.2){
    batteryDisplay.displayLevel(3);
    batteryDisplay.frame(FRAME_OFF);
  }else if (voltage < 1.5){
    batteryDisplay.displayLevel(4);
    batteryDisplay.frame(FRAME_OFF);
  }else{
    batteryDisplay.displayLevel(5);
    batteryDisplay.frame(FRAME_ON);
  }
}
void show3Voltage(float voltage){
  if (voltage < 0.6){
    batteryDisplay.displayLevel(0);
    batteryDisplay.frame(FRAME_OFF);
  }else if (voltage < 1.2){
    batteryDisplay.displayLevel(1);
    batteryDisplay.frame(FRAME_OFF);
  }else if (voltage < 1.8){
    batteryDisplay.displayLevel(2);
    batteryDisplay.frame(FRAME_OFF);
  }else if (voltage < 2.4){
    batteryDisplay.displayLevel(3);
    batteryDisplay.frame(FRAME_OFF);
  }else if (voltage < 3){
    batteryDisplay.displayLevel(4);
    batteryDisplay.frame(FRAME_OFF);
  }else{
    batteryDisplay.displayLevel(5);
    batteryDisplay.frame(FRAME_ON);
  }
}
void show9Voltage(float voltage){
  if (voltage < 1.8){
    batteryDisplay.displayLevel(0);
    batteryDisplay.frame(FRAME_OFF);
  }else if (voltage < 3.6){
    batteryDisplay.displayLevel(1);
    batteryDisplay.frame(FRAME_OFF);
  }else if (voltage < 5.4){
    batteryDisplay.displayLevel(2);
    batteryDisplay.frame(FRAME_OFF);
  }else if (voltage < 7.2){
    batteryDisplay.displayLevel(3);
    batteryDisplay.frame(FRAME_OFF);
  }else if (voltage < 9){
    batteryDisplay.displayLevel(4);
    batteryDisplay.frame(FRAME_OFF);
  }else{
    batteryDisplay.displayLevel(5);
    batteryDisplay.frame(FRAME_ON);
  }
}
void show12Voltage(float voltage){
  if (voltage < 2.4){
    batteryDisplay.displayLevel(0);
    batteryDisplay.frame(FRAME_OFF);
  }else if (voltage < 4.8){
    batteryDisplay.displayLevel(1);
    batteryDisplay.frame(FRAME_OFF);
  }else if (voltage < 7.2){
    batteryDisplay.displayLevel(2);
    batteryDisplay.frame(FRAME_OFF);
  }else if (voltage < 9.6){
    batteryDisplay.displayLevel(3);
    batteryDisplay.frame(FRAME_OFF);
  }else if (voltage < 12){
    batteryDisplay.displayLevel(4);
    batteryDisplay.frame(FRAME_OFF);
  }else{
    batteryDisplay.displayLevel(5);
    batteryDisplay.frame(FRAME_ON);
  }
}
