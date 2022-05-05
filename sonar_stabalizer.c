// --------------------------------------------------------------------------------------
//Mark Tan - 2021, May 5

//This program uses the sonar sensor to control the servo motor continuosly
//such that it remains horizontal on a level-ground.

//LED's indicate the amount of tilt in a specific direction.

// Code for Sonar sourced from APSC 101- 2020WT2:
// https://canvas.ubc.ca/courses/57724/pages/arduino-mechanical-and-demo-videos
// --------------------------------------------------------------------------------------


#include <Servo.h>

#define TRUE 1
#define FALSE 0

Servo myservo1 ;
Servo myservo2 ;

// int closedloopran = FALSE;        // condition to check if for loop for slow increment has ran

// SONAR CODE ---------------

#define VCC_PIN 13
#define TRIGGER_PIN 12    // sonar trigger pin will be attached to Arduino pin 12
#define ECHO_PIN 11       // sonar echo pint will be attached to Arduino pin 11
#define GROUND_PIN 10     //
#define MAX_DISTANCE 16 // maximum distance set to 200 cm
#define MIN_DISTANCE 4  // maximum distance set to 4 cm
#define MID_DISTANCE 9  // middle distance set to 9 cm (stable position)

// defines variables
long duration;
int distance;

// variable to count for stability (so that it does not oscillate between two values)

int count = 3;
int stable = TRUE;

// END SONAR CODE -------------

// LED variables -------------
int ORANGE = 6;
int BLUE = 5;
int WHITE = 4;
int GREEN = 3;
int YELLOW = 2;

void setup()

{
  Serial.begin(9600);
  myservo1.attach(8);                  // attaches the servo on pin 8 to the servo object
                 

// SONAR CODE ---------------

  Serial. begin(9600);            // set data transmission rate to communicate with computer
  pinMode(ECHO_PIN, INPUT) ;  
  pinMode(TRIGGER_PIN, OUTPUT) ;
  pinMode(GROUND_PIN, OUTPUT);    // tell pin 10 it is going to be an output
  pinMode(VCC_PIN, OUTPUT);       // tell pin 13 it is going to be an output
  digitalWrite(GROUND_PIN,LOW);   // tell pin 10 to output LOW (OV, or ground)
  digitalWrite(VCC_PIN, HIGH) ;   // tell pin 13 to output HIGH (+5V)

// END SONAR CODE -------------

// LED ---------------

  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(ORANGE, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(WHITE, OUTPUT);

}

void loop()
{

  // SONAR CODE ---------------

  digitalWrite(TRIGGER_PIN, LOW);   // Clears the trigPin
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(20);
  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance= duration*0.034/2;       // Calculating the distance

  // if the distance measurement becomes extremely high, it is likely an error.  
  // Default to a maximum value of MAX_DISTANCE to identify this condition.
  if (distance > MAX_DISTANCE)   
    {distance = MAX_DISTANCE ;}

    
  Serial.print("Distance: ") ;      // Prints the distance on the Serial Monitor
  Serial.print(distance);

  // END SONAR CODE -------------

  int servoValX = map(distance, 4 , 14, 0, 90) ; //changes the value to a raneg of 0 to 180.   See "map" function for further details.

  // check if it is stable
  if (distance == MID_DISTANCE){
     
    count = count + 1;
   
  }

  // stable if at mid distance for number of times, then it is stable
  if (count > 20){
    stable = TRUE;
  }

  // increase range for servo value to be equal to the stable distance value to prevent stutters/fluctations due to sonar inaccuracy
  if (stable == TRUE){

    if (distance == MID_DISTANCE + 1 || distance == MID_DISTANCE - 1){

      distance = MID_DISTANCE;
    }
  
  }

  // not stable if any other values

  if ( distance > MID_DISTANCE + 1 || distance < MID_DISTANCE - 1 ){

    stable = FALSE;
    count = 0;
  }
  
  Serial.print(" $$ [ XXXX ] servo = ");          
  Serial.print(servoValX);
  Serial.print(" $$ count value = " );
  Serial.print(count);
  Serial.print(" $$ stable value = " );
  Serial.print(stable);
  
  Serial.println();
  
  servoValX = map(distance, 4, 16, 0, 50) ; //changes the value to a raneg of 0 to 180.  


  myservo1.write(servoValX);                            //write the calculated value to the servo

  if (distance >= 8 && distance <= 10){
    
    digitalWrite(WHITE, HIGH);
    //turn off others
    digitalWrite(ORANGE, LOW);
    digitalWrite(BLUE, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, LOW);
    
  }
    
   if (distance >= 6 && distance <= 7){               // GREEN LED LOOP
    
    digitalWrite(GREEN, HIGH);
    //turn off others
    digitalWrite(ORANGE, LOW);
    digitalWrite(BLUE, LOW);
    digitalWrite(WHITE, LOW);
    digitalWrite(YELLOW, LOW);
    
  }
  
   if (distance <= 5){
    
    digitalWrite(YELLOW, HIGH);                       // YELLOW LED LOOP
    //turn off others
    digitalWrite(ORANGE, LOW);
    digitalWrite(BLUE, LOW);
    digitalWrite(WHITE, LOW);
    digitalWrite(GREEN, LOW);
    
  }

  if (distance >= 11 && distance <= 12){               // BLUE LED LOOP
    
    digitalWrite(BLUE, HIGH);
    //turn off others
    digitalWrite(ORANGE, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(WHITE, LOW);
    digitalWrite(YELLOW, LOW);
    
  }

  if (distance >= 13){                                // ORANGE LED LOOP
    
    digitalWrite(ORANGE, HIGH);
    //turn off others
    digitalWrite(BLUE, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(WHITE, LOW);
    digitalWrite(YELLOW, LOW);
    
  }
 
}