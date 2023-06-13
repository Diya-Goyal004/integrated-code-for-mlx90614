#include <Adafruit_MLX90614.h>
#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Servo s1;
bool servoMoved = false;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Adafruit MLX90614 test");

  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  };

  Serial.print("Emissivity = "); 
  Serial.println(mlx.readEmissivity());
  Serial.println("================================================");

  s1.attach(9);
  lcd.clear();
  
}


void loop() {
  float objectTempF = mlx.readObjectTempF();

  Serial.print("Ambient = "); 
  Serial.print(mlx.readAmbientTempC());
  Serial.print("*C\tObject = "); 
  Serial.print(objectTempF); 
  Serial.println("*F");
  Serial.print("Ambient = "); 
  Serial.print(mlx.readAmbientTempF());
  Serial.print("*F\tObject = "); 
  Serial.print(objectTempF); 
  Serial.println("*F");

  if (objectTempF > 92 && !servoMoved) {
    lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
	lcd.print("Fever Detected.");
    for (int i = 90; i >= 0; i -= 1) {
        s1.write(i);
        delay(5);
    }
    for (int i = 0; i <= 90; i += 1) {
      s1.write(i);
      delay(5);
    }
    
    

    servoMoved = true; // Set the flag to indicate that servo movement has occurred
    
  }
}
