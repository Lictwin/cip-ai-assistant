#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "WARNING.h"

using std::vector;
using std::string;
using std::find;

typedef long long int llint;

class OneCIDDataFormat;
typedef OneCIDDataFormat OCDF;


class OneCIDDataFormat {
public:
	short cid;
	int time;
	float value;

	OneCIDDataFormat();
	OneCIDDataFormat(const OneCIDDataFormat& data);
	OneCIDDataFormat(short cid, int time, float value);

	friend std::ostream& operator<<(std::ostream& os, const OneCIDDataFormat& data);
	friend std::istream& operator>>(std::istream& is, const OneCIDDataFormat& data);

	void operator=(const OneCIDDataFormat& data);
};
