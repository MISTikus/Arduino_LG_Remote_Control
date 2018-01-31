#include <LCD_1602_RUS.h>
#include <IRremote.h>

LCD_1602_RUS lcd(0x27, 16, 2);
IRsend irsend;

#define switcherPin 2
#define disp_power 12    // питание дисплея

// Эти коды я нашел в интернете, не все проверил...
// Так же есть коды, по этой ссылке, но их я не проверял вообще, только взял цифры: https://gist.github.com/francis2110/8f69843dd57ae07dce80
#define home 0x20DF3EC1
#define power 0x20DF10EF
#define energyRcv 0x20DFA956 // energy economy
#define avMode 0x20DF0CF3
#define input 0x20DFD02F
#define tvRad 0x20DF0FF0
#define list 0x20DFCA35 // list of channels
#define quickView 0x20DF58A7 //?? (q.view)
#define volumeUp 0x20DF40BF
#define volumeDown 0x20DFC03F
#define programUP 0x20DF00FF
#define programDown 0x20DF807F
#define guide 0x20DFD52A // tv.guide
#define homeBtn 0x20DFC23D //q.settings
#define fav 0x20DF7887
#define ratio 0x20DF9E61
#define mute 0x20DF906F
#define arrowUp 0x20DF02FD
#define arrowDown 0x20DF827D
#define arrowLeft 0x20DFE01F //
#define arrowRight 0x20DF609F //
#define ok 0x20DF22DD //
#define back 0x20DF14EB 
#define info 0x20DF55AA // current place info
#define exit 0x20DFDA25
#define redBttn 0x20DF4EB1
#define greenBttn 0x20DF8E71
#define yellowBttn 0x20DFC639
#define blueBttn 0x20DF8679
#define text 0x20DF04FB
#define tOpt 0x20DF847B // text options
#define subtitle 0x20DF9C63
#define stopBttn 0x20DF8D72
#define playBttn 0x20DF0DF2
#define pause 0x20DF5DA2
#define rew 0x20DFF10E
#define forward 0x20DF718E
#define ad 0x20DF8976
#define recent 0x20DFAD52

// Цифры от 0 до 9
long nums[] = { 0x20DF08F7,
    0x20DF8877, 0x20DF48B7, 0x20DFC837,
    0x20DF28D7, 0x20DFA857, 0x20DF6897,
    0x20DFE817, 0x20DF18E7, 0x20DF9867
};

long mainArr[] = { power, home, back,
                   volumeUp, arrowUp, programUP,
                   arrowLeft, ok, arrowRight,
                   volumeDown, arrowDown, programDown};
long alterArr[] = { power, nums[0], ok,
                    nums[7],nums[8],nums[9],
                    nums[4],nums[5],nums[6],
                    nums[1],nums[2],nums[3]};

String mainDesc[] = { "power", "home", "back",
                   "volumeUp", "arrowUp", "programUP",
                   "arrowLeft", "ok", "arrowRight",
                   "volumeDown", "arrowDown", "programDown"};
String alterDesc[] = { "power", "Ch0", "ok",
                    "Ch7","Ch8","Ch9",
                    "Ch4","Ch5","Ch6",
                    "Ch1","Ch2","Ch3" };

void setup() {
  delay(200);
  
  //Инициализируем экран
  pinMode(disp_power, OUTPUT);
  digitalWrite(disp_power, 1);
  lcd.init();
  lcd.backlight();
  
  // Инициализация переключателя
  pinMode(switcherPin, INPUT_PULLUP);
}

void loop() {
  bool isAlterMode = !digitalRead(switcherPin);
  int pressedButton = 0;
  while (pressedButton == 0) {
    pressedButton = analogToButton(analogRead(A1));
  }

  lcd.setCursor(0, 0);
  lcd.print("Кнопка: ");
  
  if (isAlterMode){
    sendIr(mainArr[pressedButton-1]);    
    lcd.print(alterDesc[pressedButton-1]);
  }
  else{
    sendIr(mainArr[pressedButton-1]);    
    lcd.print(mainDesc[pressedButton-1]);
  }
 
  delay(200);
  lcd.clear();
}

void sendIr(long value){
  irsend.sendNEC(value, 32);
  delay(300);
}
 
//Функция определяет нажатую кнопку по аналоговому значению
int analogToButton(int val)
{
    Serial.println(val);
  if (val == 0)
    return 0;
  if (val < 200)
    return 0;
    
  if (val < 340)
    return 12;
  if (val < 360)
    return 11;
  if (val < 380)
    return 10;
  if (val < 400)
    return 9;
  if (val < 420)
    return 8;
  if (val < 450)
    return 7;
  if (val < 480)
    return 6;
  if (val < 510)
    return 5;
  if (val < 550)
    return 4;
  if (val < 600)
    return 3;
  if (val < 650)
    return 2;
  if (val < 715)
    return 1;
}
