#include<LiquidCrystal.h>     //include the library code

LiquidCrystal lcd(12,11,6,5,4,3);    //initilize the library with numbers of the interface pins

volatile int FlowPulse;       //mesuring the rising edges of the signals
int Calc;
int flowsensor = 2;           //The pin location of sensor

void setup(){
  
  pinMode(flowsensor,INPUT); //initilizes digital pin 2 as an input
  Serial.begin(9600);        //This is a setup fuction where where the serial port in initialised.
  attachInterrupt(0,rpm,RISING); // and the interrept  is attached 
  
  lcd.begin(16,2);    //Set up the LCD number of columns and rows:
  lcd.setCursor(0,1); //print a message to the LCD.
  lcd.print("Flow Meter");
}
void loop(){
  
  FlowPulse = 0;  //set Nb Tops to 0 ready for calculations 
  sei();          //Enables interrupts
  delay(1000);    //Wait 4 second
  cli();          //Disable interrupts
  Calc = (FlowPulse *60/7.5); //(pulse frequency X 60)/7.5Q=Flow rate in L/hour
  Serial.print(Calc,DEC);     //print the number calcculated above
  Serial.print("L/hour\r\n"); //print "L/hour" and returns a new line
  
  lcd.setCursor(0,2);
  lcd.print(Calc,DEC);
  lcd.print("L/hour");
}

void rpm()
{
  FlowPulse++;
}
