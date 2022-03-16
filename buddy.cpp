int led = D7;


// We start with the setup function.

void setup()
{
    Serial.begin(9600);

	pinMode(led, OUTPUT); // Our on-board LED is output as well

	Particle.subscribe("buddy", myHandler);
	// Subscribe will listen for the event "buddy" and, when it finds it, will run the function myHandler()
}

// The Particle cloud is no longer supporting public events 
// and I only have 1 particle device for now
// So I have to publish the event by the device itself.
void loop()
{
	// This loop sends a publish every 5 seconds
	Particle.publish("buddy", "wave");
	delay(5000);
	Particle.publish("buddy", "pat");
	delay(5000);
}

// Now for the myHandler function, which is called when the cloud tells us that the event is published.
void myHandler(const char *event, const char *data)
{
  	if (strcmp(data, "wave") == 0)
	{
		Serial.println("wave");
		for (int i = 0; i < 3; i++)
		{
		    digitalWrite(led, HIGH);
		    delay(1000);
		    digitalWrite(led, LOW);
		    delay(1000);
		}
	} else if (strcmp(data, "pat") == 0)
	{
		// if the beam is intact, then turn your board LED off
		Serial.println("pat");
		digitalWrite(led, HIGH);
	    delay(500);
	    digitalWrite(led, LOW);
	} else {
	    Serial.print("unknown message from buddy: ");
	    Serial.println(data);
	}
}
