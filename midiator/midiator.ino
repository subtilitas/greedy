#include <MIDI.h>
#include <MsTimer2.h>
#include "FastLED.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
	#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    6
	//#define CLK_PIN   4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    256
	CRGB leds[NUM_LEDS];

#define BRIGHTNESS          255
#define FRAMES_PER_SECOND  120
#define ROWS 16
#define COLS 16
#define TYPES 3

const uint8_t note = 0, velocity = 1, instrument = 2;

volatile unsigned char sequencer_data[COLS][ROWS][TYPES];
volatile unsigned char sequencer_data_tmp[COLS][ROWS][TYPES];

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
const int channel = 8;

volatile uint8_t beat_position;

void TIRQ_seq_send(void) {
	if (beat_position >= COLS) {
		beat_position = 0;
	}
	for (int i = 0; i < NUM_LEDS; i++) {
		if ((i / 16) % 2 == 0) {
			if (sequencer_data[i / 16][i % 16][velocity] > 0) {
				leds[i].setRGB(122, 16, 22);
			}
			else {
				leds[i].setRGB(16, 16, 22);
			}
		}else {
			if (sequencer_data[i / 16][15 - (i % 16)][velocity] > 0) {
				leds[i].setRGB(122, 16, 22);
			}
			else {
				leds[i].setRGB(16, 16, 22);
			}
		}
		//leds[i].setRGB(0,0, 0);
	}
	for (int i = 16 * beat_position; i < (16 * beat_position + 16); i++) {
		leds[i].setRGB(55, 233, 233);
	}

	FastLED.show();

	for (int row = 0; row < ROWS; row++) {
		if (sequencer_data[beat_position][row][velocity] == 0) {
			MIDI.sendNoteOff(
				sequencer_data[beat_position][row][note],
				sequencer_data[beat_position][row][velocity],
				sequencer_data[beat_position][row][instrument]
			);
		}
		else {
			MIDI.sendNoteOn(
				sequencer_data[beat_position][row][note],
				sequencer_data[beat_position][row][velocity],
				sequencer_data[beat_position][row][instrument]
			);
		}
	}
	beat_position++;
}

void setup() {
	Serial.begin(115200);
	delay(500); // 3 second delay for recovery

	// tell FastLED about the LED strip configuration
	FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	//FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

	// set master brightness control
	FastLED.setBrightness(BRIGHTNESS);

	beat_position = 0;
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			sequencer_data[i][j][note] = 48;
			sequencer_data[i][j][velocity] = 0;
			sequencer_data[i][j][instrument] = 1;
		}
	}
	MIDI.begin();
	for (int c = 0; c < 17; c++)
		for (int note = 0; note <= 127; note++) {
			MIDI.sendNoteOff(note, 10, c);
		}

	MsTimer2::set(400, TIRQ_seq_send);
	MsTimer2::start();

}


void loop() {
	if (Serial.available()) {
		char trailer1, trailer2;
		char header1, header2;
		header1 = Serial.read();
		while (header1 != 222) {
			if (!Serial.available()) {
				return;
			}
			header1 = Serial.read();
		}
		header2 = Serial.read();
		if (header1 == 222 && header2 == 244) {
			for (int i = 0; i < ROWS; i++) {
				for (int j = 0; j < COLS; j++) {
					while (!Serial.available());// { delayMicroseconds(10); };
						sequencer_data[i][j][note] = Serial.read();
						//Serial.write(sequencer_data[i][j][note]);
					while (!Serial.available());// { delayMicroseconds(10); };
						sequencer_data[i][j][velocity] = Serial.read();
						//Serial.write(sequencer_data[i][j][velocity]);
						while (!Serial.available());// { delayMicroseconds(10); };
						sequencer_data[i][j][instrument] = Serial.read();
						//Serial.println(sequencer_data[i][j][instrument]);
				}
			}
			while (!Serial.available());// { delayMicroseconds(10); };
				trailer1 = Serial.read();
			while (!Serial.available());// { delayMicroseconds(10); };
				trailer2 = Serial.read();

			if (trailer1 == 222 && trailer2 == 244) {
				for (int i = 0; i < ROWS; i++) {
					for (int j = 0; j < COLS; j++) {
						while (!Serial.available());// { delayMicroseconds(10); };
							sequencer_data[i][j][note] = sequencer_data_tmp[i][j][note];
						while (!Serial.available());// { delayMicroseconds(10); };
							sequencer_data[i][j][velocity] = sequencer_data_tmp[i][j][velocity];
						while (!Serial.available());// { delayMicroseconds(10); };
							sequencer_data[i][j][instrument] = sequencer_data_tmp[i][j][instrument];
					}
				}
			}
			else {
				MIDI.sendNoteOn(55, 66, 1);
				delay(10);
				MIDI.sendNoteOff(55, 66, 1);

			}
		}
		else {
			while (Serial.available()) {
				Serial.clear();
			}
		}
	}
}