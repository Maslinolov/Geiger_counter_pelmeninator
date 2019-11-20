#include <MsTimer2.h>
#include <LiquidCrystal.h>

int beeps;
bool count = false;
int mkrH = 0;
LiquidCrystal lcd(10, A0, A1, A2, A3, A4);
int vls[10];
int i = 0;

void setup() { 
  pinMode(2, INPUT);
  TCCR0B = TCCR0B & 0b11111000 | 0x01;
  attachInterrupt(0, beep, FALLING);
  MsTimer2::set (6500, tm); 
  MsTimer2::start ();  
  lcd.begin(5, 2);  
  lcd.setCursor(0, 0);             
  lcd.print("REV "); 
  lcd.setCursor(0, 1);             
  lcd.print("1.3");  
  //analogWrite(5, 100);
  delay(500);  
}

void disp(){  
  lcd.clear();
  lcd.setCursor(0, 0);               
  lcd.print("T:"); 
  lcd.print(i);
  lcd.setCursor(3, 0); 
  lcd.print("uR"); 
  lcd.setCursor(0, 1);             
  lcd.print(":");  
  lcd.print(mkrH);  
}

void beep(){
  beeps++;
}

void tm(){
  count = true;
}

void loop() {   
  int Uh = analogRead(A5);   
  int shm = 0;
  if(Uh > 680){
    shm = 0;
  }
  else{
    shm = 1;
  }
  if(Uh < 660) 
    shm = 20;
  analogWrite(5, shm);

  if(count){    
    if(i == 10){      
      i = 0;
    }      
    vls[i] = beeps;    
    int a = 0;
    for(int n = 0; n <= i; n++){
      a += vls[n];
    }
    mkrH = a / (i + 1);   
    if(i == 0){
      mkrH = beeps;
    }     
    count = false;
    beeps = 0;    
    disp();
    i++;         
  }  
}
