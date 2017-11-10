#include <TimerOne.h>
#include <PinChangeInterrupt.h>
#include <PinChangeInterruptBoards.h>
#include <PinChangeInterruptPins.h>
#include <PinChangeInterruptSettings.h>

#define BAUDRATE 9600
#define MOTENC_RES 3090

//Current measurement
#define CURRENT_PIN A0

//H-bridge
#define MOTOR_A_EN 4
#define MOTOR_A_1 26
#define MOTOR_A_2 27

//motor commands
#define ROTATE_LEFT 0
#define ROTATE_RIGHT 1
#define STOP 2

//motenc
#define MOTENC_1A A8
#define MOTENC_1B A9

unsigned char motor_state = STOP;
long motenc_cntr = 0;
bool motenc1a_val;
bool motenc1b_val;

//controller
int target_position = 1000;

float Kp_pos = 0.5;
float Ki_pos = 0.1;
float err_pos = 0;
float err_int_pos = 0;

float Kp_cur = 0;
float Ki_cur = 0;
float err_cur = 0;
float err_int_cur = 0;


void motenc1a_IT()
{
  motenc1a_val = digitalRead(MOTENC_1A);
  if(motenc1a_val!=motenc1b_val)
  {
    motenc_cntr++;
  }
  else
  {
    motenc_cntr--;
  }
}

void motenc1b_IT()
{
  motenc1b_val = digitalRead(MOTENC_1B);
  if(motenc1a_val==motenc1b_val)
  {
    motenc_cntr++;
  }
  else
  {
    motenc_cntr--;
  }
}

void pi_controller()
{
  //pozíciószabályzó, előtte áramszabályozó
  int error = target_position - motenc_cntr;
  err_pos = Kp_pos * error;
  err_int_pos = error_int_pos + Ki_pos * error
  motor(error_pos + error_int_pos);
}

void setup() {
  Serial.begin(BAUDRATE);
  pinMode(MOTOR_A_EN, OUTPUT);
  pinMode(MOTOR_A_1, OUTPUT);
  pinMode(MOTOR_A_2, OUTPUT);

  digitalWrite(MOTOR_A_EN, HIGH);

  pinMode(MOTENC_1A, INPUT);
  pinMode(MOTENC_1B, INPUT);

  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(MOTENC_1A), motenc1a_IT, CHANGE);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(MOTENC_1B), motenc1b_IT, CHANGE);

  //pinMode(A2, INPUT);
  
  //discrete PI-controller (T = 20ms)
  attachInterrupt(pi_controller, 20000)

}

void motor(int pwm_val)
{
  //reresh state
  /*@todo: előbb le kell állítani, mint hogy 0 lenne a hibajel*/
  if(pwm_val > 0)
  {
    motor_state = ROTATE_LEFT;  
  }
  else if(pwm_val < 0)
  {
    motor_state = ROTATE_RIGHT;  
  }
  else
  {
    motor_state = STOP;  
  }

/*@todo: write float map function*/
  int tmp_pwm = abs(pwm_val);
  int pwm_d = map(tmp_pwm, 0, 750, 0, 255);
  

  //write motor pins
  switch(motor_state)
  {
    case ROTATE_LEFT:
    {
      analogWrite(MOTOR_A_1, pwm_d);
      digitalWrite(MOTOR_A_2, LOW);
      break;
    }
    case ROTATE_RIGHT:
    {
      digitalWrite(MOTOR_A_1, LOW);
      analogWrite(MOTOR_A_2, pwm_d);
      break;
    }
    case STOP:
    default:
    {
      digitalWrite(MOTOR_A_1, LOW);
      digitalWrite(MOTOR_A_2, LOW);
      break;
    }
  }
  
}

void loop() {
  Serial.println(analogRead(CURRENT_PIN));

  //Serial.println(motenc_cntr);
  //target_position += 500;
  delay(200);
}
