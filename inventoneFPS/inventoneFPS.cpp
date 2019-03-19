/*	This library is for sparkfun finger print sensors
*	GT-511C3
*	GT-511C1R
*	GT-521F32
*	GT-521F52	
*/

#include "Arduino.h"
#include "inventoneFPS.h"

#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"

#define ENROLL_SUCESSFULL 0

int tx_pin;
int rx_pin;

FPS_GT511C3 fps(rx_pin, tx_pin);

inventoneFPS::inventoneFPS(uint8_t _rx_pin, uint8_t _tx_pin) {
    FPS_GT511C3 _fps(_rx_pin, _tx_pin);
    fps = _fps;
}

void inventoneFPS::setupFPS() {
	Serial.begin(115200);
    fps.Open();
    fps.SetLED(true);
}

bool inventoneFPS::enrollFinger(int ID) {
    fps.DeleteID(ID);
	fps.EnrollStart(ID);

    /*Wait until a figer is pressed, then exit the loop*/
	while (fps.IsPressFinger() == false) delay(100);

	bool capture = fps.CaptureFinger(true);
    bool enroll = false;
	int iret = 0;
	
    if (capture == true) {
        /*Enroll finger after capturing for the first time*/
		fps.Enroll1(); 
		while(fps.IsPressFinger() == true) delay(100); //Ensure the user removes finger before doing anything
		
        /*Prompt user to press same finger again to capture second time*/
		while(fps.IsPressFinger() == false) delay(100);
		capture = fps.CaptureFinger(true);
		
        if (capture == true) {
            /*Enroll finger after capturing the second time*/
			fps.Enroll2();
			while(fps.IsPressFinger() == true) delay(100); //Ensure user removes finger before doing anything
			
            /*Capture finger for the last time*/
			while(fps.IsPressFinger() == false) delay(100);
			capture = fps.CaptureFinger(true);
			
            if (capture == true) {
			
				iret = fps.Enroll3();
				if (iret == ENROLL_SUCESSFULL) {
					Serial.println("Enrolling Successful");
                    return true;
				}
				else
				{
					Serial.print("Enrolling Failed with error code:");
					Serial.println(iret);
				}
			}
			else Serial.println("Failed to capture third finger");
		}
		else Serial.println("Failed to capture second finger");
	}
	else Serial.println("Failed to capture first finger");    
}

int inventoneFPS::searchFreeID() {
   	int freeID = 0;
    bool isUsedID = true;
	
    while (isUsedID == true) {
	    isUsedID = fps.CheckEnrolled(freeID);

		if (isUsedID == true) {
            freeID++;
        }
	} 
    return freeID;
}