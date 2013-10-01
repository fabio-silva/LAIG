
#include "YafReader.h"
#include "LightingScene.h"
#include "TPinterface.h"
#define DIMX 400
#define DIMY 400

void myGlutIdle();
void display();
void reshape(int w, int h);
void processMouse(int button, int state, int x, int y);
void processMouseMoved(int x, int y);
void processPassiveMouseMoved(int x, int y);

int main_window;
CGFaxis *axis = new CGFaxis();
YafReader *x;
float xy_aspect;
GLUI  *glui2;
float obj_pos[] = { 0.0, 0.0, 0.0 };
float view_rotate[16] =	{ 1,0,0,0,
						  0,1,0,0,
						  0,0,1,0,
						  0,0,0,1 };

void init()
{
	x->scene.init();
}

int main(int argc, char* argv[])
{	
	if(argc == 2) x = new YafReader(argv[1]);
	else x = new YafReader("projXML.yaf");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(30,30);


	main_window = glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseMoved);
	glutPassiveMotionFunc(processPassiveMouseMoved);   

	GLUI_Master.set_glutIdleFunc(myGlutIdle);
	/*** Create the bottom subwindow ***/
	glui2 = GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_BOTTOM );
	glui2->set_main_gfx_window( main_window );

	GLUI_Rotation *view_rot = glui2->add_rotation( "Rotacao", view_rotate );
	view_rot->set_spin( 1.0 );
	glui2->add_column( false );

	GLUI_Translation *trans_z = 
		glui2->add_translation( "Zoom", GLUI_TRANSLATION_Z, &obj_pos[2] );
	trans_z->set_speed( .02 );
	init();	

	glutMainLoop();


}

void myGlutIdle()
{
	if ( glutGetWindow() != main_window ) 
		glutSetWindow(main_window);  

	glutPostRedisplay();
}

void reshape(int w, int h)
{
	int tx, ty, tw, th;

	GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
	glViewport( tx, ty, tw, th );
	xy_aspect = (float)tw / (float)th;

	glutPostRedisplay();

}

void display()
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glFrustum(-100, 100, -100, 100, 5, 100.0 ); //Alterar de acordo com yaf
    glTranslatef( obj_pos[0], obj_pos[1], -obj_pos[2] );    
	glMultMatrixf( view_rotate );

	axis->draw();
	GLUquadric *quad =  gluNewQuadric();
	glPushMatrix();
	glTranslated(2,1,2);
	gluSphere( quad,0.3,200,200);
	glPopMatrix();
	glutSwapBuffers();
	glFlush();
}

void processMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{	 
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{	
	}

	glutPostRedisplay();

}


void processMouseMoved(int x, int y)
{

	// pedido de refrescamento da janela
	glutPostRedisplay();				

}

void processPassiveMouseMoved(int x, int y)
{

	// pedido de refrescamento da janela
	glutPostRedisplay();				
}

