/*
Fug
*/

int red_pin = 4;
int green_pin = 9;
int blue_pin = 10;
int white_pin = 12;

int current_hour = 1;
int current_min = 40;

int wakeup_hour = 12;

// { hour, minute, red, green, blue, white }
int schedule[][6] =
{
{0,0, 0,0,0,0},
{5,0, 4,0,4,0},
{5,30, 8,0,8,1},
{5,30, 8,0,16,2},
{6,0, 255,255,255,255},
{9,0, 255,230,240,255},
{12,0, 255,220,230,255},
{15,0, 255,150,180,200},
{18,0, 255,100,130,100},
{21,0, 255,32,64,64},
{21,15, 128,16,32,32},
{21,30, 64,4,8,8},
{21,45, 32,2,4,4},
{21,50, 16,1,2,2},
{21,55, 8,0,1,1},
{21,57, 4,0,0,1},
{21,58, 2,0,0,0},
{21,59, 1,0,0,0},
{22,0, 0,0,0,0},
};
//{3,0, 4,0,4,0},
//{4,0, 8,0,8,1},
//{5,0, 8,0,16,2},
//{6,0, 255,255,255,255},
//{9,0, 255,230,240,255},
//{12,0, 255,220,230,255},
//{15,0, 255,150,180,200},
//{18,0, 255,100,130,100},
//{21,0, 255,32,8,64},
//{21,15, 200,16,4,32},
//{21,30, 180,4,2,8},
//{21,45, 150,2,1,4},
//{21,50, 128,1,0,2},
//{21,55, 64,0,0,1},
//{21,57, 32,0,0,1},
//{21,58, 16,0,0,0},
//{21,59, 8,0,0,0},
//{22,0, 0,0,0,0},
size_t schedule_len = sizeof schedule / sizeof schedule[0];

// the setup function runs once when you press reset or power the board
void setup() {
  // adjust for when to wake up... Note this is hacky
  current_hour = (current_hour + 6 - wakeup_hour + 24 ) % 24;
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  pinMode(white_pin, OUTPUT);
  pinMode(11,OUTPUT);
  for (int i=0;i<5;i++){
    digitalWrite(11,LOW);
    delay(500);
    digitalWrite(11,HIGH);
    delay(500);
  }
    delay(500);
    digitalWrite(11,LOW);
}


void set_lights(int h,int m) {
  int i = schedule_len-1;
  for (i; i>=0; i--)
  {
    if (schedule[i][0] <= h)
    {
      if (schedule[i][1] <= m)
      {
        break;
      }
    }
  }
  analogWrite(red_pin,  schedule[i][2]);
  analogWrite(green_pin, schedule[i][3]);
  analogWrite(blue_pin, schedule[i][4]);
  analogWrite(white_pin, schedule[i][5]);
}

// the loop function runs over and over again forever
void loop() {
  while (current_hour<24){
    while (current_min<60){
      set_lights(current_hour,current_min);
      for (int i=0;i<60;i++) { delay(1000); }
      current_min++;
    }
    current_min = 0;
    current_hour++;
  }
  current_hour = 0;
}

