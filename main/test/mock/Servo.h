#pragma once

class Servo {
public:
	void attach(uint8_t);
	int read() const;
	void write(int);
};
