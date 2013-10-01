#ifndef LIGHT_H
#define LIGHT_H
#include <vector>

using namespace std;
class Light{

public:
	Light(bool doublesided, bool local, bool enabled, vector<float> ambient);
	bool isDoubleSided();
	bool isLocal();
	bool isEnabled();
	vector<float> getAmbient();

protected:

	bool doublesided,local,enabled;
	vector <float> ambient;
};
#endif