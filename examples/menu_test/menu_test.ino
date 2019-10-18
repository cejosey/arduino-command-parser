#include <CommandParser.h>

#define DEBUG_SERIAL_PARSER 1

SerialCommandParser commandParser;
bool cmdNew = true;
int counter = 0; 

int setpoint = 0;
int stepLow = 0;
int stepHigh = 0;
float Kp = 0.0;

void setup()
{
	Serial.begin(9600);

    commandParser.addCommand('h', F("Help"), showHelp, 0);
    commandParser.addCommand('s', F("Step sequence -low- -high-"), step, 2);
    commandParser.addCommand('f', F("Fixed setpoint -setpoint-"), fixed, 1);
    commandParser.addCommand('p', F("Kp"), setKp, 1);

    commandParser.PrintCommandList();
}

void loop()
{
    commandParser.parseSerialInput();
    
    if(cmdNew)
    {
        Serial.println("-----------------------------------------------------");
        cmdNew = false;
    }
	Serial.println(counter);
	counter++;
	delay(100);
}

void fixed()
{
	setpoint = commandParser.getParameterInt(0);
    Serial.print("Fixed setpoint = ");
	Serial.println(setpoint);
    cmdNew = true;
}

void step()
{
	stepLow = commandParser.getParameterInt(0);
	stepHigh = commandParser.getParameterInt(1);
    Serial.print("Step, low = ");
    Serial.print(stepLow);
	Serial.print(", high = ");
    Serial.println(stepHigh);
    cmdNew = true;

}

void setKp()
{
	Kp = commandParser.getParameterFloat(0);
	Serial.print("Kp = ");
	Serial.println(Kp);
	cmdNew = true;
}

void showHelp()
{
    commandParser.PrintCommandList();
	while(!Serial.available())

    cmdNew = true;
}
