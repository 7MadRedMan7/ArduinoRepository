#define SCL_PIN 9
#define SDO_PIN 10

/* Used to store the key state */
byte Key;

void setup()
{
  /* Initialise the serial interface */
  Serial.begin(9600);
  /* Configure the clock and data pins */
  pinMode(SCL_PIN, OUTPUT);  
  pinMode(SDO_PIN, INPUT); 
}

/* Main program */
void loop()
{
  /* Read the current state of the keypad */
  Key = Read_Keypad();
  
  /* If a key has been pressed output it to the serial port */
  if (Key)
    Serial.println(Key); 

  /* Wait a little before reading again 
     so not to flood the serial port*/
  delay(100);
}


/* Read the state of the keypad */
byte Read_Keypad(void)
{
  byte Count;
  byte Key_State = 0;

  /* Pulse the clock pin 16 times (one for each key of the keypad) 
     and read the state of the data pin on each pulse */
  for(Count = 1; Count <= 16; Count++)
  {
    digitalWrite(SCL_PIN, LOW); 
    
    /* If the data pin is low (active low mode) then store the 
       current key number */
    if (!digitalRead(SDO_PIN))
      Key_State = Count; 
    
    digitalWrite(SCL_PIN, HIGH);
  }  
  
  return Key_State; 
}