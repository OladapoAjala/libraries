#include "inventoneLCD.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x3F, 16, 2);

inventoneLCD::inventoneLCD(uint8_t length, uint8_t breadth, int address) {
    LiquidCrystal_I2C _lcd(address, length, breadth);
    lcd = _lcd;
}

void inventoneLCD::setupLCD() {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
}

void inventoneLCD::printText(char *text) {
    lcd.clear();
    lcd.print(text);
}

void inventoneLCD::scrollText (int speed, char direction) {
    switch (direction) {
        case 'R':
        case 'r':
            for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
                // scroll one position right:
                lcd.scrollDisplayRight();
                // wait a bit:
                delay(speed);
            }
            break;
        case 'L':
        case 'l':
            for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
                // scroll one position left:
                lcd.scrollDisplayLeft();
                // wait a bit:
                delay(speed);
            } 
            break;
        default:
            lcd.autoscroll();
    }
}