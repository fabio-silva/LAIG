#ifndef SPOT_H
#define SPOT_H
#include <vector>

using namespace std;
class Spot{

public:
	Spot(vector<float> location, vector<float>ambient, vector<float>diffuse, vector<float>specular, vector<float> direction, char *id, bool enabled, float angle, float exponent);

protected:
	vector<float> location, ambient, diffuse, specular,direction;
	char *id;
	bool enabled;
	float angle,exponent;
};
#endif