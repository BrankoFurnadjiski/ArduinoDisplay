int seconds = 0;
int minutes = 59;
int hours = 10;
int temperature;
float sensorValue;
float celsius = 0;
unsigned long previousMillis = 0;
const long interval = 1000;

int digit = 1;
bool minuteButton = false;
bool hourButton = false;
bool showTime = true;

void setup() {
  for(int i = 0; i <= 13; i++) {
      pinMode(i, OUTPUT);
  }
}

void increaseSeconds(){
  seconds++;
  if(seconds == 60){
    seconds = 0;
    minutes++;
    if(minutes == 60){
      minutes = 0;
      hours++;
      if(hours == 24){
        hours = 0;
      }
    }
  }
}

void setDigit(int a, int b, int c, int d, int e, int f, int g){
  digitalWrite(7,a);
  digitalWrite(8,b);
  digitalWrite(9,c);
  digitalWrite(10,d);
  digitalWrite(11,e);
  digitalWrite(12,f);
  digitalWrite(13,g);
}

void selectSegment(int n){
  setDigit(0,0,0,0,0,0,0);
  for(int i = 0; i < 4; ++i){
    if(i == n-1){
      digitalWrite(2*i,1);
    }else{
      digitalWrite(2*i,0);
    }
  }
}

void showDigit(int n){
  if(n==0){
    setDigit(1,1,1,1,1,1,0);
  }
  if(n==1){
    setDigit(0,1,1,0,0,0,0);
  }
  if(n==2){
    setDigit(1,1,0,1,1,0,1);
  }
  if(n==3){
    setDigit(1,1,1,1,0,0,1);
  }
  if(n==4){
    setDigit(0,1,1,0,0,1,1);
  }
  if(n==5){
    setDigit(1,0,1,1,0,1,1);
  }
  if(n==6){
    setDigit(1,0,1,1,1,1,1);
  }
  if(n==7){
    setDigit(1,1,1,0,0,0,0);
  }
  if(n==8){
    setDigit(1,1,1,1,1,1,1);
  }
  if(n==9){
    setDigit(1,1,1,1,0,1,1);
  }
  if(n==10){
    setDigit(1,1,0,0,0,1,1);
  }
  if(n==11){
    setDigit(1,0,0,1,1,1,0);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  if(showTime){
    digitalWrite(5,0);
    selectSegment(digit);
    if(digit == 4){
      showDigit(hours/10);
    }
    if(digit == 3){
      showDigit(hours%10);
      if(currentMillis - previousMillis >= interval/2)
        digitalWrite(5,1);
    }
    if(digit == 2){
      showDigit(minutes/10);
    }
    if(digit == 1){
      showDigit(minutes%10);
    }
  } else {
    selectSegment(digit);
    if(digit == 4)
      showDigit(temperature/10);
    if(digit == 3)
      showDigit(temperature%10);
    if(digit == 2)
      showDigit(10);
    if(digit == 1)
      showDigit(11);
  }

  digit++;
  if(digit == 5)
    digit = 1;

  if(seconds % 5 == 2 && currentMillis - previousMillis == interval){
    if(!showTime)
      showTime = true;
    else{
      showTime = false;
      sensorValue = ((analogRead(A2)/1024.0)*5000);
      celsius = (sensorValue/10);
      temperature = int(celsius);
      digitalWrite(5,0);
    }
  }

  if(currentMillis-previousMillis >= interval){
    previousMillis = currentMillis;
    increaseSeconds();
  }

  if(analogRead(A0) < 50 && !minuteButton){
    for(int i = 0; i < 60; ++i)
      increaseSeconds();
    minuteButton = true;
    showTime = true;
  }
  
  if(analogRead(A0) >= 50 && minuteButton){
    minuteButton = false;
  }
  
  if(analogRead(A1) < 50 && !hourButton){
    for(int i = 0; i < 3600; ++i)
      increaseSeconds();
    hourButton = true;
    showTime = true;
  }
  
  if(analogRead(A1) >= 50 && hourButton){
    hourButton = false;
  }
  
}
