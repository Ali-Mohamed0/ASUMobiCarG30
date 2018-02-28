const int trigPin = 9;     // defines pins numbers
const int echoPin = 10;

long duration;             // defines variables
int distance;

void setup() {
pinMode(trigPin, OUTPUT);     // Sets the trigPin as an Output
pinMode(echoPin, INPUT);     // Sets the echoPin as an Input
Serial.begin(9600);         // Starts the serial communication
}

void loop() {

digitalWrite(trigPin, LOW);       // Clears the trigPin
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);       // Sets the trigPin on HIGH state for 10 micro seconds
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);    // Reads the echoPin, returns the sound wave travel time in microseconds

distance= duration*0.034/2;             // Calculating the distance

Serial.print("Distance: ");              // Prints the distance on the Serial Monitor
Serial.println(distance);
}
