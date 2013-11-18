#pragma once
#include <vector>

using namespace std;

class AmbientLight
{
public:
	AmbientLight(bool doublesided, bool local, bool enabled, vector<float> ambient);
	bool isEnabled();
	bool isLocal();
	bool isDoubleSided();
	vector<float> getAmbient();

protected:
	bool doublesided,local,enabled;
	vector<float> ambient;
};