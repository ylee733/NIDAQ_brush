/* code for arduino
licks, valve, and motor code

nidaq contains trial structure, mirrors for opto, data collection
*/ 

#define enA 9 // Power
#define in1 6 // Direction
#define in2 7 // Direction

// name arduino pin numbers
const int lick_from_mouse = 0;  
const int lick_to_NIDAQ = 0;  
const int solenoid = 0; 
const int dir1Pin = 0;    
const int dir2Pin = 0;   
const int reward_window = 0; 
const int trial_start = 0; 

unsigned long iti = 5000;
unsigned long reward_time = millis();
unsigned long current_time = millis();

// constants
const int solenoidOpenDur = 500;

// is pin output or input
void setup(){
    Serial.begin(9600); // for Serial.print debugging

// inputs
    pinMode(lick_from_mouse, INPUT);
    pinMode(reward_window, INPUT);
    pinMode(trial_start, INPUT);
    pinMode(dir1Pin, INPUT);
    pinMode(dir2Pin, INPUT);

// outputs
    pinMode(lick_to_NIDAQ, OUTPUT);
    pinMode(solenoid, OUTPUT);
    // motor output
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    // light
    pinMode(LED_BUILTIN, OUTPUT)

}

void loop(){
// motor
  int dir1 = digitalRead(dir1Pin);    // pin from nidaq
  int dir2 = digitalRead(dir2Pin);    // pin from nidaq

  if (dir1 ==  HIGH) {
    startMotor(HIGH, LOW, 50);  // Rotate clockwise
    Serial.print(F("dir1HIGH\n"));
  } else if (dir2 == HIGH) {
    startMotor(LOW, HIGH, 50);  // Rotate counterclockwise
    Serial.print(F("dir2HIGH)\n"));
  } else {
    stopMotor();
  }

// licks
  if(digitalRead(lick_from_mouse) == HIGH){
    digitalWrite(lick_to_NIDAQ, HIGH);
  } else {
    digitalWrite(lick_to_NIDAQ, LOW);
}

// reward
  current_time = millis();
  if(digitalRead(reward_window) == HIGH & digitalRead(lick_from_mouse) == HIGH & current_time - reward_time > iti){
    reward_time = millis();
    digitalWrite(solenoid, HIGH);
    delay(solenoidOpenDur);
    digitalWrite(solenoid, LOW);  
  }

void stopMotor(){
    analogWrite(enA, 0);
}

void startMotor(int dir1, int dir2, int power){
  digitalWrite(in1, dir1);
  digitalWrite(in2, dir2);
  analogWrite(enA, power);
}

