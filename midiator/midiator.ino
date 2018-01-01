#include <MIDI.h>
#include <MsTimer2.h>

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