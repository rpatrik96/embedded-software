#include <TimerOne.h>
#include <PinChangeInterrupt.h>
#include <PinChangeInterruptBoards.h>
#include <PinChangeInterruptPins.h>
#include <PinChangeInterruptSettings.h>

#define DEBUG_PRINT 0

#define BAUDRATE 9600
#define MOTENC_RES 2900.0f
#define INTEGRATOR_OFF_TH 40
#define ROTATION_ACCEPTANCE_THRESHOLD 4

byte serial_read[2];
byte serial_write[2];

//Current measurement
#define CURRENT_PIN A0

#define T_SAMPLE 0.01

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

volatile unsigned char motor_state = STOP;
volatile int motenc_cntr = 0;
volatile bool motenc1a_val;
volatile bool motenc1b_val;

//controller
int target_position = 0;
volatile float u_motor = 0.0f;
volatile float cur_val = 0;

const float Kp_pos = 0.3;
const float Ki_pos = 0.012;
volatile float err_pos = 0;
volatile float err_int_pos = 0;

const float Kp_cur = 0.325;
const float Ki_cur = 0.01;
volatile float err_cur = 0;
volatile float err_int_cur = 0;


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

void setup() {
  analogReference(INTERNAL1V1);
  Serial.begin(BAUDRATE);
  pinMode(MOTOR_A_EN, OUTPUT);
  pinMode(MOTOR_A_1, OUTPUT);
  pinMode(MOTOR_A_2, OUTPUT);

  digitalWrite(MOTOR_A_EN, HIGH);

  pinMode(MOTENC_1A, INPUT);
  pinMode(MOTENC_1B, INPUT);

  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(MOTENC_1A), motenc1a_IT, CHANGE);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(MOTENC_1B), motenc1b_IT, CHANGE);
}


void motor(float pwm_val)
{ 
  int pwm_d = max((abs(pwm_val)),255);
  

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
  cur_val = analogRead(CURRENT_PIN);  
}

void loop() {
  //position controller
  float error = target_position - motenc_cntr;
  err_pos = Kp_pos * error;
  err_int_pos = err_int_pos + Ki_pos * error * T_SAMPLE;

  //current controller
  float u_current;
  if (abs(error) < INTEGRATOR_OFF_TH)
  {
    err_int_pos = 0;
    u_current = err_pos;
  }
  else
  {
    u_current = err_pos + err_int_pos;
  }

  if(error < 0)
  {
    motor_state = ROTATE_LEFT;  
  }
  else if(error > 0)
  {
    motor_state = ROTATE_RIGHT;  
  }
  else
  {
    motor_state = STOP;  
  }

  //current controller
  err_cur = u_current - cur_val;
  err_int_cur = err_int_cur + Ki_cur * err_cur * T_SAMPLE;

  if (abs(error) < INTEGRATOR_OFF_TH)
  {
    err_int_cur = 0;
    u_motor = Kp_cur * err_cur;
  }
  else
  {
    u_motor = Kp_cur * err_cur + err_int_cur;
  }

  if(abs(error) < ROTATION_ACCEPTANCE_THRESHOLD)
  {
    u_motor = 0;
    motor_state = STOP;
  }
  motor(u_motor);

  //Send back current angle
  int tmp = int(motenc_cntr / MOTENC_RES * 360.0f);
  serial_write[1] = highByte(tmp);
  serial_write[0] = lowByte(tmp);
#if !DEBUG_PRINT
  if(Serial)
  {
    Serial.write(serial_write,2);
    Serial.flush();
  }
#endif
  
  if(Serial.readBytes(serial_read, 2))
  {
    target_position = int(byte(serial_read[0]) << 8 | byte(serial_read[1]))/360.0f * MOTENC_RES;
  }

#if DEBUG_PRINT  
  Serial.print(motor_state);
  Serial.print("Err:");
  Serial.print(error);
  Serial.print("\n");


  Serial.print("Pos:");
  Serial.print(motenc_cntr);
  Serial.print("\t");
  
  Serial.print("Cur:");
  Serial.print(cur_val);
  Serial.print("\t");
  
  Serial.print("X_err:");
  Serial.print(err_pos);
  Serial.print("\t");
  
  Serial.print("X_err_int:");
  Serial.print(err_int_pos);
  Serial.print("\t");

  Serial.print("I_err:");
  Serial.print(err_cur);
  Serial.print("\t");
  
  Serial.print("I_err_int:");
  Serial.print(err_int_cur);
  Serial.print("\t");
 
  Serial.print("U_motor:");
  Serial.println(u_motor);
#endif

  delay(10);
}
