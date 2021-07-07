SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
void setup()
{
  pinMode(D5, OUTPUT);
  SPI.begin(SPI_MODE_MASTER, D5);
  SPI.setClockSpeed(1, MHZ);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  Serial.begin(9600);
  Serial.print("Set up SPI connection");
}
void loop()
{
  /*while (!Serial.available())
  {
    Serial.println("Serial not available");
  }*/
  if (Serial.available())
  {
    char value = Serial.read();
    Serial.printlnf("input: %d", value);

    char rx[1];
    char tx[1];
    tx[0] = value;

    digitalWrite(D5, LOW);
    SPI.transfer(tx, rx, 1, NULL);
    digitalWrite(D5, HIGH);
    if (value == '?')
    {
      Serial.printlnf("Button: %d", rx[0]);
    }
  }
}