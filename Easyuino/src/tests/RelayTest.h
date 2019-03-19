/*
MIT License

Copyright (c) 2017 Andr� Pires

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
/*
RelayTest.h
*/
#ifndef _EASYUINO_RELAY_TEST_h
#define _EASYUINO_RELAY_TEST_h

#include "Easyuino.h"
#include "ManualTest.h"

using Easyuino::Relay;

class RelayTest : public ManualTest {

	private:
		Relay* relay;

	public:
		RelayTest(Stream &debugStream, uint8_t arduinoPin) : ManualTest(debugStream) {
			relay = new Relay(arduinoPin);
		}

	protected:
		void testsSetup() {
			relay->begin(false, HIGH);
		}

		void tests() {
			testStart("1.ON");
			relay->turnOn();
			_debugStream->println(relay->isOn());
			testEnd();

			testStart("2.NOTHING");
			relay->turnOn();
			_debugStream->println(relay->isOn());
			testEnd();

			testStart("3.OFF");
			relay->turnOff();
			_debugStream->println(relay->isOn());
			testEnd();

			testStart("4.NOTHING");
			relay->turnOff();
			_debugStream->println(relay->isOn());
			testEnd();

			testStart("5.ON");
			relay->turnOn();
			_debugStream->println(relay->isOn());
			testEnd();

			testStart("6.OFF");
			relay->end();
			relay->turnOn();
			_debugStream->println(relay->isOn());
			testEnd();

			testStart("7.NOTHING");
			relay->turnOff();
			_debugStream->println(relay->isOn());
			testEnd();

			testStart("8.NOTHING");
			relay->begin(false, HIGH);
			_debugStream->println(relay->isOn());
			testEnd();

			testStart("9.ON");
			relay->turnOn();
			_debugStream->println(relay->isOn());
			testEnd();

			testStart("10.OFF");
			relay->turnOn();
			_debugStream->println(relay->isOn());
			testEnd();
		}

		void afterTestSuite() {
			relay->end();
			delete relay;
			relay = NULL;
		}

};

#endif
