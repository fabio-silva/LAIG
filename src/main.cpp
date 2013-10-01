#include "YafReader.h"
#define DIMX 400
#define DIMY 400

void myGlutIdle();
void display();
void reshape(int w, int h);
void processMouse(int button, int state, int x, int y);
void processMouseMoved(int x, int y);
void processPassiveMouseMoved(int x, int y);

int main_window;
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

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:		// tecla de escape termina o programa
         exit(0);
         break;
   }
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
	glutKeyboardFunc(keyboard);
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseMoved);
	glutPassiveMotionFunc(processPassiveMouseMoved);   

	GLUI_Master.set_glutIdleFunc(myGlutIdle);

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
	x->scene.display();
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
