#include <Adafruit_Keypad.h>

#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 1, d7 = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1','2','3','*'},
  {'4','5','6','/'},
  {'7','8','9','E'},
  {'+','0','-','='}
};
byte rowPins[ROWS] = {5,4,3,2}; 
byte colPins[COLS] = {9,8,7,6}; 

Adafruit_Keypad customKeypad = Adafruit_Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);
 
 
char v[101];
 int i=0;
float nr=0; 
float aux=0;
float aux1=1;
bool ok=0;
char salv;
int cntr=0,cop;
void setup() {
  customKeypad.begin();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);

}

void loop() {

  customKeypad.tick();

  while(customKeypad.available()){
    
    keypadEvent e = customKeypad.read(); 
   
    if(e.bit.EVENT == KEY_JUST_PRESSED) 
    { lcd.setCursor(0, 0);
     lcd.clear();
    
    if (e.bit.KEY-48>=0&&e.bit.KEY-48<=9)
    {
     if (ok==1)
     {nr=0;
     ok=0;}
    nr=nr*10+((char)e.bit.KEY-48);
    lcd.print(nr);
    
    }
    else 
    {
     
     if (cntr==0)
     aux=nr;
else
if ((char)e.bit.KEY!='=')
{
     if (salv=='+')
         aux+=nr;
     
     if (salv=='-')
        aux-=nr;
     
    if (salv=='*')
         aux*=nr;
     
     if (salv=='/')
        aux/=nr;
    }
lcd.print(nr);
     
    lcd.setCursor(0, 1);
     lcd.print((char)e.bit.KEY);
      cntr++;
     if ((char)e.bit.KEY=='=')
     {
     lcd.clear();
     lcd.print((char)e.bit.KEY);

     
     if (salv=='+')
      {   aux+=nr;
         
     } 
        
     if (salv=='-')
      {  aux-=nr;
        
     } 
    if (salv=='*')
     { aux*=nr;
     
     }
     if (salv=='/')
     {aux/=nr;
      }
      
      lcd.print(aux);
    nr=aux;
    aux=0;
    cntr=0;
    }
  
      salv=(char)e.bit.KEY;
     

     if ((char)e.bit.KEY=='E')
     {
      aux=0;
      cntr=0;
      nr=0;
      lcd.clear();
      
     }
      ok=1;
    }
   
 
    }
    

  
  }
  delay(10);
}
