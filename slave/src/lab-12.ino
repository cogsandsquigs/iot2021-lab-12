SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
volatile bool CS = false;

void takeAction(uint8_t state)
{
    if (state)
    {
        CS = true;
    }
}

void setup()
{
    pinMode(D7, OUTPUT);
    pinMode(D8, INPUT);
    SPI1.begin(SPI_MODE_SLAVE, D6);
    SPI1.setClockSpeed(1, MHZ);
    SPI1.setBitOrder(MSBFIRST);
    SPI1.setDataMode(SPI_MODE0);
    SPI1.onSelect(takeAction);
    Serial.begin(9600);
    //Serial.print("Set up SPI1 connection.");
}
void loop()
{
    //Serial.printlnf("-%d-", CS); //digitalRead(D8));
    if (CS == true)
    {
        char rx[1];
        char tx[1];
        CS = false;
        //Serial.printlnf("%d", rx[0]);
        tx[0] = digitalRead(D8);
        SPI1.transfer(tx, rx, 1, NULL);
        if (rx[0] == '1')
        {
            Serial.println("LED HIGH");
            digitalWrite(D7, HIGH);
        }
        else if (rx[0] == '0')
        {
            Serial.println("LED LOW");
            digitalWrite(D7, LOW);
        }
    }
}