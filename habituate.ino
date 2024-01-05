/* code for arduino
licks, valve, and motor code

nidaq contains trial structure, mirrors for opto, data collection
*/ 

// name arduino pin numbers
const int lick_from_mouse = 10;  
const int solenoid = 9; 
const int solenoidOpenDur = 50;

int valve_count = 0;

// is pin output or input
void setup(){
    Serial.begin(9600); // for Serial.print debugging

// inputs
    pinMode(lick_from_mouse, INPUT);
// outputs
    pinMode(solenoid, OUTPUT);
    // light
    pinMode(LED_BUILTIN, OUTPUT);

}

void loop(){
// licks
  if(digitalRead(lick_from_mouse) == HIGH){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
  }

  if(digitalRead(lick_from_mouse) == HIGH){

    digitalWrite(solenoid, HIGH);
    delay(solenoidOpenDur);
    digitalWrite(solenoid, LOW);
    valve_count += 1;
    Serial.println(valve_count);
    delay(2000);
  } else {
    digitalWrite(solenoid, LOW);
}
}

