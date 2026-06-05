#include <Adafruit_LiquidCrystal.h>
Adafruit_LiquidCrystal lcd(0);

int led_vd = 2;
int led_am = 3;
int led_vm = 4;
int buzzer = 8;

int tmp = A0;
int ldr = A1;
int pot = A2;


void setup()
{
  	Serial.begin(9600);
  
	pinMode(led_vd, OUTPUT);
  	pinMode(led_am, OUTPUT);
  	pinMode(led_vm, OUTPUT);
  	pinMode(buzzer, OUTPUT);

    lcd.begin(16, 2);					
    lcd.print("Iniciando...");
  	delay(1000);
  
  	lcd.clear();
}

void loop()
{
  int luz = map(analogRead(ldr), 54, 974, 0, 100);
  int vibracao = map(analogRead(pot), 0, 1023, 0, 100);
  int temperatura = map(analogRead(tmp), 20, 358, -40, 126);
  
  
  
  lcd.setCursor(0, 0);
  lcd.print("L:");
  lcd.print(luz);
  lcd.print("% ");

  lcd.print("V:");
  lcd.print(vibracao);
  lcd.print("%");

  // Limpa sobra de caracteres
  lcd.print("   ");

  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(temperatura);
  lcd.print((char)223); // símbolo °
  lcd.print("C ");
  
  if(luz < 25 || vibracao > 80 || temperatura > 35 || temperatura < 15){
  	digitalWrite(led_vd, LOW);
    digitalWrite(led_am, LOW);
    digitalWrite(led_vm, HIGH);
    
    lcd.print("CRITICO ");
    
    tone(buzzer, 800, 1000);
    delay(250);
    noTone(buzzer);
  }
  
  else if(luz < 95 || vibracao > 50 || temperatura > 30 && temperatura <= 35|| temperatura < 20 && temperatura >= 15){
  	digitalWrite(led_vd, LOW);
    digitalWrite(led_am, HIGH);
    digitalWrite(led_vm, LOW);
    
    lcd.print("ATENCAO ");
    
    delay(250);
  }
  
  else if(luz >= 95 && vibracao <= 50 && temperatura <= 30 && temperatura >= 20){
  	digitalWrite(led_vd, HIGH);
    digitalWrite(led_am, LOW);
    digitalWrite(led_vm, LOW);
    
    lcd.print("NORMAL ");
    
    delay(250);
  }
}