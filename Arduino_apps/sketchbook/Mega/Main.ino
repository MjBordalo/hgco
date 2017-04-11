/*
	Main

	Description

	modified
	by Miguel Bordalo
	miguel.b.fernande@gmail.com
 */

/*
 * Libraries Inclue
 */
#include "DHT.h"		//DHT22 temperature and humidity
#include "SHT1X.h"		//SHT15 temperature and humidity
#include <Servo.h>

#include <Wire.h>				//LightSensor
#include <Adafruit_TSL2561_U.h>	// 2561

//Water temperature sensor
#include <OneWire.h>
#include <DallasTemperature.h>

/*
 *	Pins Id
 */
#define DHTPIN_1 7		//DHT22 sensor #1
#define DHTPIN_2 8		//DHT22 sensor #2
#define MY_SERVO 4

#define WATERTEMP 2

//Define RELES pins
#define RELE1 42
#define RELE2 43
#define RELE3 44
#define RELE4 45

#define FAN_PIN 9

/*
 *	Classes
 */
DHT dht1(DHTPIN_1, DHT22);
DHT dht2(DHTPIN_2, DHT22);
Servo myservo;  // create servo object to control a servo
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);		//TSL2561 - LightSensor


// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(WATERTEMP);
DallasTemperature sensors(&oneWire);

/*
 *  Variables
 */
int servo_pos = 10; //angle position of the servo
int fan_speed = 0;
bool RELE1_state = 0;
bool RELE2_state = 0;
bool RELE3_state = 0;
bool RELE4_state = 0;

//Comunication Protocol Variables
String input = ""; // This will capture the serial input commands


/**************************************************************************/
/*
    Configures the gain and integration time for the TSL2561
*/
/**************************************************************************/
void configureTSL(void){
  /* You can also manually set the gain or enable auto-gain support */
  tsl.setGain(TSL2561_GAIN_1X);      /* No gain ... use in bright light to avoid sensor saturation */
  // tsl.setGain(TSL2561_GAIN_16X);     /* 16x gain ... use in low light to boost sensitivity */
  //tsl.enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */

  /* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
  //tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
   //tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */

  /* Update these values depending on what you've set above! */
  //  Serial.println("------------------------------------");
  //  Serial.print  ("Gain:         "); Serial.println("Auto");
  //  Serial.print  ("Timing:       "); Serial.println("13 ms");
  //  Serial.println("------------------------------------");
}

/*
* Fan setup
* to change fan speed: analogWrite(FAN_PIN, value); value (0-255)
*/
void fan_setup(){
  pinMode(FAN_PIN, OUTPUT);
  //---------------------------------------------- Set PWM frequency for D9 & D10 ------------------------------
  TCCR2B = TCCR2B & B11111000 | B00000001;    // set timer 2 divisor to     1 for PWM frequency of 31372.55 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000010;    // set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000011;    // set timer 2 divisor to    32 for PWM frequency of   980.39 Hz
    // TCCR2B = TCCR2B & B11111000 | B00000100;    // set timer 2 divisor to    64 for PWM frequency of   490.20 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000101;    // set timer 2 divisor to   128 for PWM frequency of   245.10 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000110;    // set timer 2 divisor to   256 for PWM frequency of   122.55 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000111;    // set timer 2 divisor to  1024 for PWM frequency of    30.64 Hz

  fan_speed = 0;
}


/*

  Protocol letter taken:
  Actuators:
    S,s: set servo , get servo
    F,f: change fan speed/dutycycle set(0-255) get(0-1024)
    A,a:set RELE1 , get RELE1
    B,b:set RELE2 , get RELE2
    C,c:set RELE3 , get RELE3
    D,d:set RELE4 , get RELE4
  sensors:
    T
    H
    I
    J
    L
    W

*/

void Serial_protocol(){

	 while (Serial.available()>0){
	   char lastRecvd = Serial.read();
	   if (lastRecvd == '\n') { // The end of the command has arrived
	     switch (input[0]) {

	     /*--------------Write Commands-------------------*/
	       case 'S': // A write command has come in
	         input = input.substring(1,input.length());
	         servo_pos = input.toInt();
	         input = "";
	         break;
         case 'F': // set Fan speed
	         input = input.substring(1,input.length());
	         fan_speed = input.toInt();
	         input = "";
	         break;
         case 'A':    //set RELE1
           input = input.substring(1,input.length());
           RELE1_state = input.toInt();
           input = "";
           break;
         case 'B':    //set RELE2
           input = input.substring(1,input.length());
           RELE2_state = input.toInt();
           input = "";
           break;
         case 'C':    //set RELE2
           input = input.substring(1,input.length());
           RELE3_state = input.toInt();
           input = "";
           break;
         case 'D':    //set RELE4
           input = input.substring(1,input.length());
           RELE4_state = input.toInt();
           input = "";
           break;

		 /*--------------Read Commands-------------------*/
         case 'T': // DHT22_1 -temp
           //Serial.print('T');
           Serial.print( dht1.readTemperature() );
           Serial.print("\n");
           input = "";
           break;
         case 'H': // DHT22_1 -Humidity
	         //Serial.print("H");
	         Serial.print( dht1.readHumidity() );
	         Serial.print("\n");
	         input = "";
	         break;
         case 'I': // DHT22_2 -temp
           //Serial.print("H");
           Serial.print( dht2.readTemperature() );
           Serial.print("\n");
           input = "";
           break;
         case 'J': // DHT22_2 - humidity
           //Serial.print('T');
           Serial.print( dht2.readHumidity() );
           Serial.print("\n");
           input = "";
           break;
	       case 'L': // Light Sensor
	    	   sensors_event_t event;
	    	   tsl.getEvent(&event);
	         //Serial.print('T');
	         Serial.print( (int) event.light );
	         Serial.print("\n");
	         input = "";
	         break;
        case 'W': // Light Sensor
          sensors.requestTemperatures(); // Send the command to get temperature readings
          //Serial.print('T');
          Serial.print( sensors.getTempCByIndex(0) ); // You can have more than one DS18B20 on the same bus.
          Serial.print("\n");
          input = "";
          break;

        case 's': // get servo state
          Serial.print(String(servo_pos));
          Serial.print("\n");
          input = "";
          break;
        case 'f': // get fan speed
          Serial.print(String(fan_speed));
          Serial.print("\n");
          input = "";
          break;
        case 'a': // get RELE 1 state
          Serial.print(String(RELE1_state));
          Serial.print("\n");
          input = "";
          break;
        case 'b': // get RELE 2 state
          Serial.print(String(RELE2_state));
          Serial.print("\n");
          input = "";
          break;
        case 'c': // get RELE 3 state
          Serial.print(String(RELE3_state));
          Serial.print("\n");
          input = "";
          break;
        case 'd': // get RELE 4 state
          Serial.print(String(RELE4_state));
          Serial.print("\n");
          input = "";
          break;

	       default:
	    	   input = "";
	         break;
	     }
	   }
	   else { // Input is still coming in
	     input += lastRecvd;
	   }
	 }

}


void setup() {
	Serial.begin(115200);
	/*
	* Init Classes
	*/
	// DHT22
	dht1.begin();
  dht2.begin();
	//Servo
	myservo.attach(MY_SERVO);  // attaches the servo on pin 9 to the servo object
	//TSL2561-lightSensor
	tsl.begin();
	configureTSL();

  //Water temperature
  // Start up the library
  sensors.begin();

  /*
  * Fan setup
  */
  fan_setup();

  //  pinMode(A7, OUTPUT);
  //  digitalWrite(A7, HIGH);

  // Define RELES pin as OUTPUT and set them turn off by default
  pinMode(RELE1, OUTPUT);digitalWrite(RELE1, LOW);
  pinMode(RELE2, OUTPUT);digitalWrite(RELE2, LOW);
  pinMode(RELE3, OUTPUT);digitalWrite(RELE3, LOW);
  pinMode(RELE4, OUTPUT);digitalWrite(RELE4, LOW);

}


void loop() {
//	Measure_n_Print();
    Serial_protocol();
    /*Actuate*/
    myservo.write(servo_pos); // tell servo to go to position in variable 'pos'
    analogWrite(FAN_PIN, fan_speed); // actuate on fan
    digitalWrite(RELE1, RELE1_state);
    digitalWrite(RELE2, RELE2_state);
    digitalWrite(RELE3, RELE3_state);
    digitalWrite(RELE4, RELE4_state);

}
