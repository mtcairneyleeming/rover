int e1d = 4;
int e1p = 3;
int e2d = 6;
int e2p = 5;
int e3d = 10;
int e3p = 9;
int e4d = 12;
int e4p = 11;
int temp_data;
char identifier;
float zero = 0.0;
int rmotor_callback(int powerlevel) {

  //move right motors at powerlevel given
  //direction
  if (powerlevel < zero) {
    //set front right motor to forwards
    digitalWrite(e1d, 1);
    //set back right motor to backwards
    digitalWrite(e3d, 0);
  } else {
    //set front right motor to backwards
    digitalWrite(e1d, 0);
    //set back right motor to forwards
    digitalWrite(e3d, 1);
  }
  //set powerlevels
  analogWrite(e1p, powerlevel);
  analogWrite(e3p, powerlevel);
  return 1;
};

int lmotor_callback(int powerlevel) {

  //move left motors at powerlevel given
  //direction
  if (powerlevel < zero) {
    //set front left motor to forwards
    digitalWrite(e2d, 1);
    //set back left motor to backwards
    digitalWrite(e4d, 0);
    analogWrite(e2p, 255-powerlevel);
    analogWrite(e4p, 255-powerlevel);
  } else {
    //set front left motor to backwards
    digitalWrite(e2d, 0);
    //set back left motor to forwards
    digitalWrite(e4d, 1);
    analogWrite(e2p, powerlevel);
    analogWrite(e4p, powerlevel);
  }
  //set powerlevels
  
  return 1;
}


void setup()
{
  // initialize serial:
  Serial.begin(9600);
  pinMode(e1d, OUTPUT);
  pinMode(e2d, OUTPUT);
  pinMode(e3d, OUTPUT);
  pinMode(e4d, OUTPUT);
}

void loop()
{
  if(Serial.available()) {
    temp_data = Serial.parseInt();
    //Serial.println(temp_data);
    identifier = Serial.read();
    if (identifier == 'r') {
      Serial.println("r");     
      rmotor_callback(temp_data);
    }
    if (identifier == 'l') {
      Serial.println("l");
      lmotor_callback(temp_data);
    }
    else {
      delay(100);
    }
  }
    
}
