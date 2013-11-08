#include "Animation.h"

Animation::Animation(vector<vector<float>> ctrlPoints, int nControlPoints, float duration):ctrlPoints(ctrlPoints), nControlPoints(nControlPoints), duration(duration)
{
	timeLeft = duration;

	currentPoint = ctrlPoints[0];
}