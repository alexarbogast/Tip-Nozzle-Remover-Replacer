char receivedChar;

void removeNozzle() { }
void removeTip() { }
void replaceTip() { }
void replaceNozzle() { }

void setup() 
{
    Serial.begin(9600);
    while(!Serial)
    {
        // wait for serial port to connect
    }  
}

void loop() 
{
    if (Serial.available() > 0)
    {
        receivedChar = Serial.read();

        switch (receivedChar)
        {
            case 'a':
                removeNozzle();
                break;
            case 'b':
                removeTip();
                break;
            case 'c':
                replaceTip();
                break;
            case 'd':
                replaceNozzle();
                break;
            default:
                // do nothing
                break;
        }
    }
}
