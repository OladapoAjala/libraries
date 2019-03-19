/*
	Original Copyright owner: 2010 Copyright (c) Seeed Technology Inc.  All right reserved.
	Original Author: Bruce.Qin
  
  AirQuality Industrial Ported library v0.0.1
  Editor Copyright owner: 2018 Copyright (c) Diff Digital. All right reserved.
  Edit Author: Joachim.Cardoen
*/
#include"Arduino.h"
#include"AirQuality.h"

void AirQuality::init(int pin)
{
    _pin=pin;
    pinMode(_pin,INPUT);
    unsigned char i=0;
    Serial.println("sys_starting...");
    delay(20000);//200000
    init_voltage=analogRead(_pin);
    Serial.println("The init voltage is ...");
    Serial.println(init_voltage);
    while(init_voltage)
    {
        if(init_voltage<798 && init_voltage>10)// the init voltage is ok
        {
            first_vol=analogRead(_pin);//initialize first value
            last_vol=first_vol;
            vol_standard=last_vol;
            Serial.println("Sensor ready.");
            error=false;;
            break;
        }
        else if(init_voltage>798||init_voltage<=10)
        {
            i++;
            delay(60000);//60000
            Serial.println("waitting sensor init..");
            init_voltage=analogRead(_pin);
            if(i==5)
            {
                i=0;
                error=true;
                Serial.println("Sensor Error!");
            }
          }
        else
        break;
    }
    // initialize timer1 for the ATmega32U4
	noInterrupts();           // disable all interrupts
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 34286;            // preload timer 65536-16MHz/256/2Hz
	TCCR1B |= (1 << CS12);    // 256 prescaler 
	interrupts();             // enable all interrupts
	TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
    Serial.println("Test begin...");
    sei();
}
int AirQuality::slope(void)
{
    while(timer_index)
    {
        if(first_vol-last_vol>400||first_vol>700)
        {
            timer_index=0;
            return 0;
        }
        else if((first_vol-last_vol>400&&first_vol<700)||first_vol-vol_standard>150)
        {
            timer_index=0;
            return 1;

        }
        else if((first_vol-last_vol>200&&first_vol<700)||first_vol-vol_standard>50)
        {
            timer_index=0;
            return 2;
        }
        else
        {
            timer_index=0;
            return 3;
        }
    }
    return -1;
}

/*

LICENSE INFORMATION:
	This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

