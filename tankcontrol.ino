// -----------------------------------------
// Function and Variable with Photoresistors
// -----------------------------------------
// In this example, we're going to register a Particle.variable() with the cloud so that we can read brightness levels from the photoresistor.
// We'll also register a Particle.function so that we can turn the LED on and off remotely.

// We're going to start by declaring which pins everything is plugged into.

int led = D7;
int a1 = D0; // This is where your LED is plugged in. The other side goes to a resistor connected to GND.
int a2 = D1;
int a3 = D2; // This is where your LED is plugged in. The other side goes to a resistor connected to GND.
int a4 = D3;
int speed = 40;
String commandglobal = "";
void setup() {
    // First, declare all of our pins. This lets our device know which ones will be used for outputting voltage, and which ones will read incoming voltage.
    pinMode(led, OUTPUT);
    pinMode(a1,OUTPUT); // Our LED pin is output (lighting up the LED)
    pinMode(a2,OUTPUT); // The pin powering the photoresistor is output (sending out consistent power)
    pinMode(a3,OUTPUT); // Our LED pin is output (lighting up the LED)
    pinMode(a4,OUTPUT); // The pin powering the photoresistor is output (sending out consistent power)

    // We are also going to declare a Particle.function so that we can turn the LED on and off from the cloud.
    Particle.function("led",ledToggle);
    Particle.function("speed",speedToggle);
    // This is saying that when we ask the cloud for the function "led", it will employ the function ledToggle() from this app.
}


// Next is the loop function...

void loop() {
    Particle.publish("DEBUG", "Code has reached point A");
    delay(1000);
}


int speedToggle(String s) {
    Particle.publish("DEBUG", "Code has reached point B");
    int value = s.toInt();
    if (value <=255 and value >=0) {
        speed = value;
    }
    run(commandglobal);
    return speed;
}
// Finally, we will write out our ledToggle function, which is referenced by the Particle.function() called "led"
int ledToggle(String command) {
    Particle.publish("DEBUG", "Code has reached point B");
    commandglobal = command;
    return run(command);
}

int run(String command){
    if (command=="w") {
        forwardleft();
        forwardright();
        return 1;
    }
    else if(command=="s"){
        backleft();
        backright();
        return 2;
    }
    else if(command=="a"){
        forwardright();
        backleft();
        return 3;
    }
    else if(command=="d"){
        forwardleft();
        backright();
        return 4;
    }
    else if (command=="off") {
        off();
        return 0.5;
    }
    else {
        off();
        return -1;
    }
}

void forwardleft(){
    analogWrite(a1,LOW);
    analogWrite(a2,speed);
}
void backleft(){
    analogWrite(a1,speed);
    analogWrite(a2,LOW);
}
void backright(){
    analogWrite(a3,LOW);
    analogWrite(a4,speed);
}
void forwardright(){
    analogWrite(a3,speed);
    analogWrite(a4,LOW);
}
void off(){
    analogWrite(a1,LOW);
    analogWrite(a2,LOW);
    analogWrite(a3,LOW);
    analogWrite(a4,LOW);
}
