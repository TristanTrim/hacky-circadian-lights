/*
Fug

I don't know why the functions are broken up the way they are.
I didn't think about it that much.
Sorry.

I think this should be for a teensy 2.0 by the way.
*/


int current_hour = 21;
int current_min = 0;

// if 6, there is no offset. 6 is the correct hour to wake up.
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
{5,30, 0,0,0,0},
{5,45, 8,0,16,2},
{6,0, 255,255,255,255},
{7,0, 255,255,255,255},
//{7,30, 1,0,0,1},
//{15,0, 1,0,0,1},
{7,30, 0,255,255,255},
{15,0, 0,255,255,255},
{15,30, 255,150,180,200},
{18,0, 255,100,130,100},
{21,0, 255,0,0,1},
{22,0, 0,0,0,0},
{24,0, 0,0,0,0},
};
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
  for (int i=0;i<3;i++){
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
  float now = h*60 + m;
  float last = schedule[li][0]*60 + schedule[li][1];
  float next = schedule[ni][0]*60 + schedule[ni][1];
  // figure out ratio from last schedule time to next schedule time
  float time_ratio = (now - last)/(next - last);
    
    float colour_delta;
    int light_level;
  
    // find change from last light level to next light level
    colour_delta = schedule[ni][2] - schedule[li][2];
    // add change in light (based on time_ratio
    light_level = colour_delta * time_ratio + schedule[li][2];
    // set the ligth pwm
    analogWrite(red_pin,  light_level);

    // find change from last light level to next light level
    colour_delta = schedule[ni][3] - schedule[li][3];
    // add change in light (based on time_ratio
    light_level = colour_delta * time_ratio + schedule[li][3];
    // set the ligth pwm
    analogWrite(green_pin,  light_level);

    // find change from last light level to next light level
    colour_delta = schedule[ni][4] - schedule[li][4];
    // add change in light (based on time_ratio
    light_level = colour_delta * time_ratio + schedule[li][4];
    // set the ligth pwm
    analogWrite(blue_pin,  light_level);

    // find change from last light level to next light level
    colour_delta = schedule[ni][5] - schedule[li][5];
    // add change in light (based on time_ratio
    light_level = colour_delta * time_ratio + schedule[li][5];
    // set the ligth pwm
    analogWrite(white_pin,  light_level);
}

void set_lights(int h,int m) {
  // We check the time intervals in reverse order for reasons!
  int next = 0;
  int prev = schedule_len-1;
  // iterate, setting back the time interval until
  // the current time falls within the time interval
  while (prev >= 0 )
  {
    if (schedule[prev][0] <= h)
    {
      if (schedule[prev][1] <= m)
      {
        break;
      }
    }
    // It wasn't that time interval!!! Check the previous!!!
    next = prev;
    prev--;
  }
  // Selected the interval, lets call the light level selector!
  delta_light_selector(h,m,prev,next);

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

