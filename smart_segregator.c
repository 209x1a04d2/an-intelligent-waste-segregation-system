#include <Servo.h>

class Smart_Segregator
/*
   _____________________________________________________________
  |
  | Description
  | -----------
  | - This is a smart segregator which seperates dry and wet
  |   wet waste. (It cannot segregate metal or plastic)
  |
  |.............................................................
  |
  | Attributes
  | ----------
  | pin_1 : int
  |    -  Servo Motor pin number.
  |
  | pin_2 : int
  |    -  Moisture Sensor pin number.
  |
  | pin_3 : int
  |    - Touch Sensor pin number.
  |
  |............................................................
  |
  | Methods
  | -------
  | dry_waste()
  |       - Lid of the segregator slides towards right side.
  |
  | wet_waste()
  |       - Lid of the segregator slides towards left side
  |
  | neutral_state()
  |       - In which the lid of segregator is in the middle.
  |
  | execute()
  |       - Smart Segregator starts operating.
  |
  |___________________________________________________________
  */
{
  public:
     int servo_pin;
     int moisture_sensor_pin;
     int touch_sensor_pin;
     int detect_moisture;
     int detect_touch;
 
     Servo servo;

     Smart_Segregator(int pin_1, int pin_2, int pin_3)
     {
       servo_pin = pin_1;
       moisture_sensor_pin = pin_2;
       touch_sensor_pin = pin_3;

       detect_moisture = 0;
       detect_touch = false;
     }

    void init()
    {
      Serial.begin(9600);
      servo.attach(servo_pin);
      servo.write(90);
      
      pinMode(moisture_sensor_pin, INPUT);
      pinMode(touch_sensor_pin, INPUT);

      Serial.println("Your Smart Segregator is ready to Segregate!");
    }

    void dry_waste()
    {
      servo.write(0);
    }

    void wet_waste()
    {
      servo.write(180);
    }

    void neutral_state()
    {
      servo.write(90);
    }
    
    void execute()
    {
      detect_moisture = analogRead(moisture_sensor_pin);
      detect_touch = digitalRead(touch_sensor_pin);

      if (detect_moisture > 85 && detect_touch == true)
      {
        wet_waste();
      }

      else if (detect_moisture <= 85 && detect_touch == true)
      {
        dry_waste();
      }

      else 
      {
        neutral_state();
      }
    }
}

segregator = Smart_Segregator(8,6,2);

void setup() 
{
  segregator.init();
}

void loop() 
{
 segregator.execute();
}