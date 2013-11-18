#include "Animation.h"

Animation::Animation(vector<vector<float>> ctrlPoints, int nControlPoints, float duration,char *id):ctrlPoints(ctrlPoints), nControlPoints(nControlPoints), duration(duration), id(id)
{
	timeLeft = duration;

	currentPoint = ctrlPoints[0];
}