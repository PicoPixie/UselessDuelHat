#include <Servo.h> 

Servo servo_0, servo_1;  
 
// holds current angle of servo arm
int nowAt = 0; 
int randomArm = 0, randomDelay = 0, randomAngle = 0, randomStep = 0;


void setup() {

	// seed pRNG with noise from unconnected PIN 7 
	randomSeed(analogRead(7)); 
	servo_0.attach(9); 
	servo_1.attach(10); 
	servo_0.write(90); // bring 'em in to start sequence
	servo_1.write(180);
	delay(1000); // wait 1 sec
}
 
void loop() {

        // choose which tentacle -- L or R servo arm.?
	randomArm = random(0,2); // will give us 0 xor 1
        // choose angle to move servo arm to this time
        randomAngle = random(90,181); // 90..180
        // choose how long to wait before next move
        randomDelay = random(300,801); // 300..800ms  
        
        if(randomArm == 0) { 
		nowAt = servo_0.read();
		Sweep(0,nowAt,randomAngle,randomDelay);
        } else { 
		nowAt = servo_1.read();
		Sweep(1,nowAt,randomAngle,randomDelay);
        }

}


/* 

Takes as args:  which servo arm (0||1), the current position of that arm,
the angle to now put the arm, and a delay to wait between moves.

*/

void Sweep(int arm, int start, int stopAt, int usec) {

	// step size for ctrl of speed of arm movement
	randomStep = random(10,46);
  
	// which arm we moving.?
	if(arm == 0) { 
		// arm not > position we want yet, increase angle to meet it
		if(start <= stopAt) { 
			for(int angle = start; angle < stopAt; angle += randomStep) {
				servo_0.write(angle);
				delay(usec); 
			}
		// already > angle wanted, decrease angle to meet requirement
		} else { 
			for(int angle = start; angle >= stopAt; angle -= randomStep) {
				servo_0.write(angle);
				delay(usec);
			} 
		}
    
    
	} else { 
		if(start <= stopAt) {
			for(int angle = start; angle < stopAt; angle += randomStep) {
				servo_1.write(angle);
				delay(usec); 
			}
		} else {
			for(int angle = start; angle >= stopAt; angle -= randomStep) {
				servo_1.write(angle);
				delay(usec); 
			}
		}

	}
}
	
	
