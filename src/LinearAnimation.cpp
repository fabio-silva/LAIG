#include "LinearAnimation.h"

LinearAnimation::LinearAnimation(vector<vector<float>> ctrlPoints, int nControlPoints, float duration):Animation(ctrlPoints, nControlPoints, duration)
{


	v = new Vehicle("CW");
 
	nextPoint = 1;

	distance = 0;

	for(int i = 0; i < nControlPoints; i++)
	{
		if( (i+1) < nControlPoints) 
		{
			distance += sqrt ( pow(ctrlPoints[i+1][0] - ctrlPoints[i][0],2.0) + pow(ctrlPoints[i+1][1] - ctrlPoints[i][1],2.0) + pow(ctrlPoints[i+1][2] - ctrlPoints[i][2],2.0));
			cout << "PONTO ANIM = " << ctrlPoints[i+1][0] <<", " <<ctrlPoints[i+1][1] << ", " << ctrlPoints[i+1][2] <<   endl;
			cout << "D = " << distance << endl;
		}
	}



	velocity = (distance / duration) / 10; //Dx por decimo de segundo
	currentTime = 0;
	previousTime = 0;

	curX = ctrlPoints[0][0];
	curY = ctrlPoints[0][1];
	curZ = ctrlPoints[0][2];
}

void LinearAnimation::draw()
{
	currentTime = glutGet(GLUT_ELAPSED_TIME);

	int timeInterval = currentTime - previousTime;
	glPushMatrix();
	bool goToNextPoint = true;



	if(timeInterval >= 10) //A cada decimo de segundo
	{
		if(distance > 0)
		{

			if(ctrlPoints[nextPoint][0] > curX) 
			{
				if(curX + velocity <= ctrlPoints[nextPoint][0]) curX += velocity;
				else curX += ctrlPoints[nextPoint][0] - curX;
				if(curX < ctrlPoints[nextPoint][0]) goToNextPoint = false;

				
			}
			else if(ctrlPoints[nextPoint][0] < curX) 
			{
				if(curX - velocity >= ctrlPoints[nextPoint][0]) curX -= velocity;
				else curX -= ctrlPoints[nextPoint][0] + curX;
				if(curX > ctrlPoints[nextPoint][0]) goToNextPoint = false;
			}

			if(ctrlPoints[nextPoint][1] > curY) 
			{
				if(curY + velocity <= ctrlPoints[nextPoint][1]) curY += velocity;
				else curY += ctrlPoints[nextPoint][1] - curY;

				if(curY < ctrlPoints[nextPoint][1]) goToNextPoint = false;
			}
			else if(ctrlPoints[nextPoint][1] < curY) 
			{
				if(curY - velocity >= ctrlPoints[nextPoint][1]) curY -= velocity;
				else curY -= ctrlPoints[nextPoint][1] + curY;

				if(curY > ctrlPoints[nextPoint][1]) goToNextPoint = false;
			}

			if(ctrlPoints[nextPoint][2] > curZ) 
			{
				if(curZ + velocity <= ctrlPoints[nextPoint][2]) curZ += velocity;
				else curZ += ctrlPoints[nextPoint][2] - curZ;

				if(curZ < ctrlPoints[nextPoint][2]) goToNextPoint = false;
			}
			else if(ctrlPoints[nextPoint][2] < curZ) 
			{
				if(curZ - velocity >= ctrlPoints[nextPoint][2]) curZ -= velocity;
				else curZ -= ctrlPoints[nextPoint][2] + curZ;

				if(curZ > ctrlPoints[nextPoint][2]) goToNextPoint = false;
			}


			if(goToNextPoint) 
			{
				nextPoint++;
			}


			distance -= velocity;
		}








		previousTime = currentTime;

	}

	glTranslatef(curX, curY, curZ);

	v->draw();

	glPopMatrix();


}


