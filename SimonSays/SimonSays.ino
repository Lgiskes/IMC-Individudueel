  //led and button pins
  int const yellowButton = 19;
  int const redButton = 4;
  int const blueButton = 18;
  int const greenButton = 5;
  int const yellowLed = 27;
  int const redLed = 33;
  int const blueLed = 26;
  int const greenLed = 25;
  int const randomLed[] = {yellowLed, redLed, blueLed, greenLed};
  int const buttonPins[] = {yellowButton, redButton, blueButton, greenButton};


  //sequence parameters
  int sequenceSize = -1;
  int const maxSequenceSize = 5;
  int sequence[maxSequenceSize];
  int currentIndex = 0;

  //button values
  int lastYellowValue = LOW;
  int lastRedValue = LOW;
  int lastBlueValue = LOW;
  int lastGreenValue = LOW;
  int yellowValue = 0;
  int redValue = 0;
  int blueValue = 0;
  int greenValue = 0;
  int buttonPressed = 0;
  int lastButtonPressed = 0;

  boolean wonGame = false;

  int startGameLightSequence[] = {yellowLed, redLed, blueLed, greenLed, blueLed, redLed, yellowLed};
  
 //GameStates
enum States{
  IDLE,
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

//blinks a led
void showLight(int led){
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led,LOW);
  delay(500);
}

//adds a led to the sequence
void addToSequence(){
  state = SHOW_SEQUENCE;
  sequenceSize += 1;
  if(sequenceSize > maxSequenceSize){
    sequenceSize = 0;
  }
  sequence[sequenceSize] = randomLed[random(4)];
}

//shows the led sequence
void showSequence(){
  Serial.println("Showing Sequence");
  delay(2000);
  for(int i = 0; i <= sequenceSize; i++){
    showLight(sequence[i]);
  }
}

void startGameLights(){
  for(int i = 0; i < sizeof(startGameLightSequence); i++){
    digitalWrite(startGameLightSequence[i], HIGH);
    delay(100);
    digitalWrite(startGameLightSequence[i], LOW);
    delay(100);
  }
}

void wonLights(){
  for(int i = 0; i< 10; i++){
    digitalWrite(yellowLed, HIGH);
    digitalWrite(redLed, HIGH);
    digitalWrite(blueLed, HIGH);
    digitalWrite(greenLed, HIGH);
    delay(100);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, LOW);
    digitalWrite(blueLed, LOW);
    digitalWrite(greenLed, LOW);
    delay(100);
  }
}

void gameOverLights(){
    for(int i = 0; i< 3; i++){
    digitalWrite(yellowLed, HIGH);
    digitalWrite(redLed, HIGH);
    digitalWrite(blueLed, HIGH);
    digitalWrite(greenLed, HIGH);
    delay(500);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, LOW);
    digitalWrite(blueLed, LOW);
    digitalWrite(greenLed, LOW);
    delay(500);
  }
}

void resetGame(){
    clearSequence();
    sequenceSize = -1;
    state = IDLE;
    currentIndex = 0;
    wonGame = false;
    lastYellowValue = LOW;
    lastRedValue = LOW;
    lastBlueValue = LOW;
    lastGreenValue = LOW;
  }

  //clears the sequence
void clearSequence(){
  for(int i = 0; i <= maxSequenceSize; i++){
    sequence[i] = -1;
  }
}

void loop() {
  if(state == IDLE){
    Serial.print("IDLE STATE");
    //if any button is pressed, the game starts
    if(yellowValue == HIGH || redValue == HIGH || blueValue == HIGH || greenValue == HIGH){
      startGameLights();
      addToSequence();
    }  
  }
  else if( state == WAITING_FOR_BUTTON){
    Serial.print("WAITING FOR BUTTON STATE");
    //read pressed button the button
    int readValue;
    buttonPressed = 0;
    while(buttonPressed != 0){
      for(int i = 0; i<4; i++){
          readValue = digitalRead(buttonPins[i]);
          if(readValue == HIGH && lastButtonPressed != buttonPins[i]){
            buttonPressed = buttonPins[i];
          }
      }
    }
      
    lastButtonPressed = buttonPressed;

    //checks if the correct button has been pressed
      
    if(buttonPressed == sequence[currentIndex]){
      if(currentIndex == sequenceSize){
        if(sequenceSize == maxSequenceSize -1){
          //The answer is correct and the end has been reached
          wonGame = true;
          state = END_GAME;
          Serial.print("YOU WON THE GAME!");
        }
         else{
          //The answer is correct and a new sequence will play
          currentIndex = 0;
          addToSequence();
          Serial.print("CORRECT!");
         }
        }
      else{
      //The answer is correct and the sequence is not finished
      currentIndex ++;
      Serial.print("CORRECT!");
      }
    }
    else{
      //The answer is incorrect and the game ends
      state = END_GAME;
      Serial.print("You pressed the wrong button");
    }
  }
  else if( state == SHOW_SEQUENCE){
    Serial.print("SHOWING SEQUENCE");
    showSequence();
    state = WAITING_FOR_BUTTON;
  }
  else if( state = END_GAME){
    Serial.print("END GAME STATE");
    if(wonGame){
      wonLights();
    }
    else{
      gameOverLights();
    }
    resetGame();
  }
  else{
    Serial.print("UNKNOWN STATE: "+state);
    //unhanlded state
  }
}
