#include <DHT.h>
#include <Servo.h>

#define DHTPIN 2      
#define DHTTYPE DHT11 
#define SERVOPIN 9    
#define BUZZERPIN 13  
DHT dht(DHTPIN, DHTTYPE);
Servo myservo;  

bool isServoAt90 = false;  
void setup() {
  Serial.begin(9600);
  dht.begin();
  myservo.attach(SERVOPIN);  
  myservo.write(0);          
  pinMode(BUZZERPIN, OUTPUT);  
  digitalWrite(BUZZERPIN, LOW); 
}

void loop() {
  delay(1000);  
 
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

 
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\t");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  
//  myservo.write(90);
  Serial.println("Now checking for threshold");

  if (temperature > 30 && !isServoAt90) {
    delay(3000);
    Serial.println("Temperature above 30°C. Moving servo to 90 degrees and activating buzzer.");
    myservo.write(90);  
    digitalWrite(BUZZERPIN, HIGH); 
    delay(1000); 
    digitalWrite(BUZZERPIN, LOW);   
    isServoAt90 = true; 
    Serial.println("Motor rotated done");
    Serial.println("Done rotating hinge and buzzer turned off!");

  } else if (temperature <= 30 && isServoAt90) {
    Serial.println("Temperature 30°C or below. Moving servo back to 0 degrees.");
    myservo.write(0);   
    isServoAt90 =false;
}
}