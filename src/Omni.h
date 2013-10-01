#ifndef OMNI_H
#define OMNI_H
#include <vector>

using namespace std;

class Omni{

public:
	Omni(vector<float> location, vector<float>ambient, vector<float>diffuse, vector<float>specular, char *id, bool enabled);

protected:
	vector<float> location, ambient, diffuse, specular;
	char *id;
	bool enabled;
};
#endif