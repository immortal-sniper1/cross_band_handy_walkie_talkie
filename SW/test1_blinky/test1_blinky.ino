#define MY_LED_PIN 23
#define I2C_SDA 13
#define I2C_SCL 14



// the setup function runs once when you press reset or power the board
void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode( MY_LED_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() 
{
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}