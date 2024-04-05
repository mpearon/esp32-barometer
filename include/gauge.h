#ifndef GAUGE_H
#define GAUGE_H

#include <Arduino.h>

class gauge{
	public:
		gauge( String name, double floor, double ceiling, bool antiClockwiseRotation );

		String name;
		double floor;
		double ceiling;
		bool antiClockwiseRotation;
};

#endif
