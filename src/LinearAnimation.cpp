#include "LinearAnimation.h"

LinearAnimation::LinearAnimation(vector<vector<float>> ctrlPoints, int nControlPoints, float duration,char *id):Animation(ctrlPoints, nControlPoints, duration,id)
{


	v = new Vehicle("CW");
 
	nextPoint = 1;

	distance = 0;

	for(int i = 0; i < nControlPoints; i++)
	{
		cout << "CTRL = " << ctrlPoints[i][0] << ", " << ctrlPoints[i][1] << ", " << ctrlPoints[i][2] << endl;
		if( (i+1) < nControlPoints) 
		{
			vector<float>pt; 
			pt.push_back(ctrlPoints[i+1][0] - ctrlPoints[i][0]);
			pt.push_back(ctrlPoints[i+1][1] - ctrlPoints[i][1]);
			pt.push_back(ctrlPoints[i+1][2] - ctrlPoints[i][2]);

			distance += sqrt ( pow(ctrlPoints[i+1][0] - ctrlPoints[i][0],2.0) + pow(ctrlPoints[i+1][1] - ctrlPoints[i][1],2.0) + pow(ctrlPoints[i+1][2] - ctrlPoints[i][2],2.0));
			vectors.push_back(pt);
		}
	}

	for(int i = 0;  i < vectors.size(); i++) cout << "VETOR = " << vectors[i][0] << ", " << vectors[i][1] << ", " << vectors[i][2] << endl;
	

	float initialAngle = acos((0*vectors[0][0] + 0*vectors[0][1] + 1*vectors[0][2]) /  sqrt(vectors[0][0]*vectors[0][0]+/*vectors[0][1]*vectors[0][1]*/+vectors[0][2]*vectors[0][2]) ) * 180/PI;
	if(ctrlPoints[1][0] < ctrlPoints[0][0]) initialAngle = -initialAngle;

	angles.push_back(initialAngle);

	cout << "inicial angle = " << initialAngle << endl;

	for(int i = 0 ; i < vectors.size(); i++)
	{
		if( (i+1) < vectors.size())
		{
			float angle = acos( (vectors[i][0] * vectors[i+1][0] + /*vectors[i][1] * vectors[i+1][1]*/ + vectors[i][2] * vectors[i+1][2]) / ( sqrt(vectors[i][0]*vectors[i][0] + /*vectors[i][1]*vectors[i][1] + */vectors[i][2]*vectors[i][2]) * sqrt(vectors[i+1][0]*vectors[i+1][0] +/* vectors[i+1][1]*vectors[i+1][1]*/ + vectors[i+1][2]*vectors[i+1][2])));
			angle = angle * 180/PI;
			if(vectors[i+1][0] < vectors[i][0]) angle = -angle;
			angles.push_back(angle);

			
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
		if(distance > 0 && (curX != ctrlPoints[nControlPoints-1][0] || curY != ctrlPoints[nControlPoints-1][1] || curZ != ctrlPoints[nControlPoints-1][2]))
		{
			
			if(ctrlPoints[nextPoint][0] > curX) 
			{
				if(curX + velocity <= ctrlPoints[nextPoint][0]) curX += velocity;
				else curX = (ctrlPoints[nextPoint][0]);
				if(curX < ctrlPoints[nextPoint][0]) goToNextPoint = false;

				
			}
			else if(ctrlPoints[nextPoint][0] < curX) 
			{
				if(curX - velocity >= ctrlPoints[nextPoint][0]) curX -= velocity;
				else curX = (ctrlPoints[nextPoint][0]);
				if(curX > ctrlPoints[nextPoint][0]) goToNextPoint = false;
			}

			if(ctrlPoints[nextPoint][1] > curY) 
			{
				if(curY + velocity <= ctrlPoints[nextPoint][1]) curY += velocity;
				else curY = ctrlPoints[nextPoint][1];

				if(curY < ctrlPoints[nextPoint][1]) goToNextPoint = false;
			}
			else if(ctrlPoints[nextPoint][1] < curY) 
			{
				if(curY - velocity >= ctrlPoints[nextPoint][1]) curY -= velocity;
				else curY = ctrlPoints[nextPoint][1];

				if(curY > ctrlPoints[nextPoint][1]) goToNextPoint = false;
			}

			if(ctrlPoints[nextPoint][2] > curZ) 
			{
				if(curZ + velocity <= ctrlPoints[nextPoint][2]) curZ += velocity;
				else curZ = ctrlPoints[nextPoint][2];

				if(curZ < ctrlPoints[nextPoint][2]) goToNextPoint = false;
			}
			else if(ctrlPoints[nextPoint][2] < curZ) 
			{
				if(curZ - velocity >= ctrlPoints[nextPoint][2]) curZ -= velocity;
				else curZ = ctrlPoints[nextPoint][2];

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
	if(nextPoint <= angles.size()) 
		{
			glRotatef(angles[nextPoint-1], 0, 1, 0);
			cout << "angle = " << angles[nextPoint-1
			] << endl;
		}

	else glRotatef(angles[angles.size()-1],0,1,0);
	
	
	v->draw();

	glPopMatrix();


}


