/*
Fug

I don't know why the functions are broken up the way they are.
I didn't think about it that much.
Sorry.
*/


int current_hour = 23;
int current_min = 0;

int wakeup_hour = 6;


int red_pin = 4;
int green_pin = 9;
int blue_pin = 10;
int white_pin = 12;

int lights[4] =
{
red_pin,
green_pin,
blue_pin,
white_pin
};
size_t lights_len = sizeof lights / sizeof lights[0];


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
{21,15, 255,16,32,32},
{21,30, 255,4,8,8},
{21,45, 255,2,4,4},
{21,50, 255,1,2,2},
{21,55, 255,0,1,1},
{21,57, 255,0,0,1},
{23,30, 128,0,0,0},
{23,45, 64,0,0,0},
{23,55, 16,0,0,0},
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

void delta_light_selector(int h, int m, int li, int ni){
  // convert time to total minutes
  int now = h*60 + m;
  int last = schedule[li][0]*60 + schedule[li][1];
  int next = schedule[ni][0]*60 + schedule[ni][1];
  // figure out ratio from last schedule time to next schedule time
  float time_ratio = ((now - last)/(next - last));
  
  for (int i=0; i>lights_len; i++){
    // find change from last light level to next light level
    int colour_delta = schedule[ni][i+2] - schedule[li][i+2];
    // add change in light (based on time_ratio
    int light_level = colour_delta * time_ratio + schedule[li][i+2];
    // set the ligth pwm
    analogWrite(lights[i],  light_level);
  }
}

void set_lights(int h,int m) {
  // We check the time intervals in reverse order for reasons!
  int next = 0;
  int prev = schedule_len-1;
  while (prev >= 0 )
  {
    if (schedule[prev][0] <= h)
    {
      if (schedule[prev][1] <= m)
      {
        delta_light_selector(h,m,prev,next);
      }
    }
    // It wasn't that time interval!!! Check the previous!!!
    next = prev;
    prev--;
  }

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

