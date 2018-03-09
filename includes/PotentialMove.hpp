#pragma once

class PotentialMove
{
public:
	int y;
	int x;
	int priority;
	PotentialMove(int iy, int ix, int ipriority) : y(iy), x(ix), priority(ipriority) {};

};