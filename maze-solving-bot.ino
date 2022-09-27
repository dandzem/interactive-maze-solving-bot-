int IR1=7;      //Right sensor
int IR2=6;    //left Sensor
// motor one
int enA = 10;    //Right motor
int MotorAip1=8;
int MotorAip2=9;
// motor two
int enB = 11;    //Left motor
int MotorBip1=12;
int MotorBip2=13;

//colorsensorsetup
int colorInput1 = 3;
int colorInput2 = 4;
int outPin  = 2;

// sound 
const int buzzer = 5; //buzzer to arduino pin 5

// variables
int red;
int grn;
int blu;
String color ="";
int count = 0;


void setup() 
{
  // put your setup code here, to run once:
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(IR1,INPUT);
  pinMode(IR2,INPUT);
  pinMode(MotorAip1,OUTPUT);
  pinMode(MotorAip2,OUTPUT);
  pinMode(MotorBip1,OUTPUT);
  pinMode(MotorBip2,OUTPUT);
  pinMode(buzzer, OUTPUT);

  pinMode(colorInput1, OUTPUT);
  pinMode(colorInput2, OUTPUT);
  pinMode(outPin, INPUT); //out from sensor becomes input to arduino
  
}
void loop() 
{
  getColor();
    
if (color == "NONE") {
   if(digitalRead(IR1)==HIGH && digitalRead(IR2)==HIGH) //IR will not glow on black line
  {
    //Stop both Motors
    digitalWrite(MotorAip1,LOW);
    digitalWrite(MotorAip2,LOW);
    digitalWrite(MotorBip1,LOW);
    digitalWrite(MotorBip2,LOW);
   analogWrite (enA, 0);
   analogWrite (enB, 0);
  }

  else if(digitalRead(IR1)==LOW && digitalRead(IR2)==LOW)  //IR not on black line
  {
    //Move both the Motors
    digitalWrite(MotorAip1,LOW);
    digitalWrite(MotorAip2,HIGH);
    digitalWrite(MotorBip1,LOW);
    digitalWrite(MotorBip2,HIGH);
    analogWrite (enA, 70);
    analogWrite (enB, 70);
  }

  else if(digitalRead(IR1)==LOW && digitalRead(IR2)==HIGH)
  {
    //Tilt robot towards left by stopping the left wheel and moving the right one
    digitalWrite(MotorAip1,LOW);     
    digitalWrite(MotorAip2,HIGH);
    digitalWrite(MotorBip1,HIGH);
    digitalWrite(MotorBip2,LOW);
    analogWrite (enA, 70);
    analogWrite (enB, 50);
   delay(100);
  }

  else if(digitalRead(IR1)==HIGH && digitalRead(IR2)==LOW)
  {
    //Tilt robot towards right by stopping the right wheel and moving the left one
     digitalWrite(MotorAip1,HIGH);     
    digitalWrite(MotorAip2,LOW);
    digitalWrite(MotorBip1,LOW);
    digitalWrite(MotorBip2,HIGH);
    analogWrite (enA, 50);
   analogWrite (enB, 70);
   delay(100);    
 
  }

  else
  {
              //Stop both the motors
  driveStop();

  }

} else {
  if (color == "WHITE") {  //drive forward
    //Move both the Motors
    forward();
    }

  if (color == "BLUE") {   //drive left
   turnLeft();
    }

 if (color == "GREEN") {    //drive right
    turnRight();
    }

  if (color == "RED") {    //gameover
    driveStop();
    soundLose(); 
    delay(100000);
    for(;;);
    }
    
  if (color == "YELLOW") { //speedup   
    driveStop();
    soundOneUp();
    delay(775);
    forwardCheese();
    }

  if (color == "PINK") {  //end 
    driveStop();
    soundWin();
    for(;;);
    }
  }
}


void soundOneUp(){
    tone(buzzer,1319,125);
  delay(130);
  tone(buzzer,1568,125);
  delay(130);
  tone(buzzer,2637,125);
  delay(130);
  tone(buzzer,2093,125);
  delay(130);
  tone(buzzer,2349,125);
  delay(130);
  tone(buzzer,3136,125);
  delay(125);
  noTone(buzzer);
}

void soundLose() {
  tone(buzzer,500,200);
  delay(200);
  tone(buzzer,500,200);
  delay(200);
  tone(buzzer,500,200);
  delay(200);
  tone(buzzer,800,150);
  delay(150);
  tone(buzzer,500,500);
  delay(500);
  tone(buzzer,600,1000);
  delay(2000);
}

void soundWin() {
  tone(buzzer,1319,125);
  delay(70);
  tone(buzzer,1568,500);
  delay(500);
  tone(buzzer,1319,125);
  delay(70);
  tone(buzzer,1568,500);
  delay(500);
}

void forward() {
    digitalWrite(MotorAip1,LOW);
    digitalWrite(MotorAip2,HIGH);
    digitalWrite(MotorBip1,LOW);
    digitalWrite(MotorBip2,HIGH);
    analogWrite (enA, 70);
    analogWrite (enB, 70);
    delay(1000);
  }

void forwardCheese() {
    digitalWrite(MotorAip1,LOW);
    digitalWrite(MotorAip2,HIGH);
    digitalWrite(MotorBip1,LOW);
    digitalWrite(MotorBip2,HIGH);
    analogWrite (enA, 90);
    analogWrite (enB, 90);
    delay(1000);
  }

void turnLeft() {
    digitalWrite(MotorAip1,LOW);     
    digitalWrite(MotorAip2,HIGH);
    digitalWrite(MotorBip1,HIGH);
    digitalWrite(MotorBip2,LOW);
    analogWrite (enA, 70);
    analogWrite (enB, 50);
    delay(1000);
  }

void turnRight() {
   digitalWrite(MotorAip1,HIGH);    
    digitalWrite(MotorAip2,LOW);
    digitalWrite(MotorBip1,LOW);
    digitalWrite(MotorBip2,HIGH);
    analogWrite (enA, 50);
    analogWrite (enB, 70);
    delay(1000);
  }

 void driveStop() {
    digitalWrite(MotorAip1,LOW);
    digitalWrite(MotorAip2,LOW);
    digitalWrite(MotorBip1,LOW);
    digitalWrite(MotorBip2,LOW);
    analogWrite (enA, 0);
    analogWrite (enB, 0);
  }

void getColor()
{  
  readRGB();
  
        if (red > 3 && red < 7 && grn > 4 && grn < 7 && blu > 3 && blu < 6) color = "WHITE";
  else if (red > 3 && red < 7 && grn > 11 && grn < 16 && blu > 8 && blu < 13) color = "RED";
  else if (red > 4 && red < 7 && grn > 7 && grn < 10 && blu > 10 && blu < 13) color = "YELLOW";
  else if (red > 10 && red < 14 && grn > 7 && grn < 11 && blu > 5 && blu < 8) color = "BLUE";
  else if (red > 4 && red < 8 && grn > 5 && grn < 8 && blu > 8 && blu < 11) color = "GREEN";
  else if (red > 2 && red < 5 && grn > 9 && grn < 14 && blu > 5 && blu < 8) color = "PINK";
  else if (red > 4 && red < 8 && grn > 11 && grn < 16 && blu > 12 && blu < 15) color = "ORANGE";
  else color = "NONE";
}


void readRGB() 
{
  red = 0;
  grn = 0;
  blu = 0;
  int n = 10;
  for (int i = 0; i <= n; ++i)
  {
    //read red component
    digitalWrite(colorInput1, LOW);
    digitalWrite(colorInput2, LOW);
    red = red + pulseIn(outPin, LOW);
  
   //read green component
    digitalWrite(colorInput1, HIGH);
    digitalWrite(colorInput2, HIGH);
    grn = grn + pulseIn(outPin, LOW);
    
   //let's read blue component
    digitalWrite(colorInput1, LOW);
    digitalWrite(colorInput2, HIGH);
    blu = blu + pulseIn(outPin, LOW);
  }
  red = red/n;
  grn = grn/n;
  blu = blu/n;
}
