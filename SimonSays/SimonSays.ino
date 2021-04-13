  //led and button pins
  int yellowButton = 19;
  int redButton = 4;
  int blueButton = 18;
  int greenButton = 5;
  int yellowLed = 27;
  int redLed = 33;
  int blueLed = 26;
  int greenLed = 25;
  int randomLed[] = {yellowLed, redLed, blueLed, greenLed};

  //button values
  int lastYellowValue = LOW;
  int lastRedValue = LOW;
  int lastBlueValue = LOW;
  int lastGreenValue = LOW;
  int yellowValue = 0;
  int redValue = 0;
  int blueValue = 0;
  int greenValue = 0;



 //GameStates
enum States{
  IDLE
  WAITING_FOR_BUTTON,
  SHOW_SEQUENCE,
  END_GAME
  };

States state;
  
void setup() {
  Serial.begin(9600);
  
  state = IDLE;
    
  pinMode(yellowButton, INPUT);
  pinMode(redButton, INPUT);
  pinMode(blueButton, INPUT);
  pinMode(greenButton, INPUT);

  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(greenLed,OUTPUT);
}

void loop() {
  switch(state){
    case IDLE:
    
    break;

    case WAITING_FOR_BUTTON:
    break;

    case SHOW_SEQUENCE:
    break;

    case END_GAME:
    break;

    default:
    break;
    
  }
  
}

//blinks a led
void showLight(int led){
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led,LOW);
  delay(500);
}

//adds a led to the sequence
void addToSequence(int button){
  state = SHOW_SEQUENCE;
  sequenceSize += 1;
  if(sequenceSize > maxSequenceSize){
    sequenceSize = 0;
  }
  sequence[sequenceSize] = button;
}

//shows the led sequence
void showSequence(){
  Serial.println("Showing Sequence");
  delay(2000);
  for(int i = 0; i <= sequenceSize; i++){
    showLight(sequence[i]);
  }
}
