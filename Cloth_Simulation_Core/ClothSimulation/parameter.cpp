#include "stdafx.h"
#include "parameter.h"

Parameters::Parameters() {
	for (int i = 0; i < 100; i++)
		fixedPointsCopy[i] = fixedPoints[i] = -10.0f;
}

void Parameters::resetFixedPoints() {
	for (int i = 0; i < 100; i++)
		fixedPoints[i] = fixedPointsCopy[i];
}