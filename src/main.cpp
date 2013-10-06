#include "YafReader.h"
#include "GL/glui.h"
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

//Light checkboxes variables
vector<int> spot_light_vars;
vector<int> omni_light_vars;

void init()
{
	x->scene.init();
}

void display()
{
	glLoadIdentity();
	glMultMatrixf( view_rotate );
	glTranslatef( obj_pos[0], obj_pos[1], -obj_pos[2] );  
	x->scene.display();
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:		// tecla de escape termina o programa
		exit(0);
		break;
	}
}

void initLightCheckboxesVariables()
{

	for (int i = 0; i < 8; i++)
	{
		spot_light_vars.push_back(2);
	}

	for (int i = 0; i < 8; i++)
	{
		omni_light_vars.push_back(2);
	}

	vector<Spot *> spots = x->scene.getSpots();
	vector<Omni *> omnis = x->scene.getOmnis();

	for (int i = 0; i < spots.size(); i++)
	{
		if (spots[i]->isEnabled())
		{
			spot_light_vars[i] = 1;
		}
		else
		{
			spot_light_vars[i] = 0;
		}
	}

	for (int i = 0; i < omnis.size(); i++)
	{
		if (omnis[i]->isEnabled())
		{
			omni_light_vars[i] = 1;
		}
		else
		{
			omni_light_vars[i] = 0;
		}
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

	GLUI  *glui2 = GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_BOTTOM );
	glui2->set_main_gfx_window( main_window );

	GLUI_Rotation *view_rot = glui2->add_rotation( "Rotacao", view_rotate );
	view_rot->set_spin( 1.0 );
	glui2->add_column( false );

	GLUI_Translation *trans_z = 
		glui2->add_translation( "Zoom", GLUI_TRANSLATION_Z, &obj_pos[2] );
	trans_z->set_speed( .02 );

	//Controlos de interface

	glui2->add_column(1);

	initLightCheckboxesVariables();

	//Desenhar apenas as checkboxes das luzes que existem
	if (spot_light_vars[0] != 2)
	glui2->add_checkbox("Spot Light 0", &spot_light_vars[0], 1);
	if (spot_light_vars[1] != 2)
	glui2->add_checkbox("Spot Light 1", &spot_light_vars[1], 2);
	if (spot_light_vars[2] != 2)
	glui2->add_checkbox("Spot Light 2", &spot_light_vars[2], 3);
	if (spot_light_vars[3] != 2)
	glui2->add_checkbox("Spot Light 3", &spot_light_vars[3], 4);
	if (spot_light_vars[4] != 2)
	glui2->add_checkbox("Spot Light 4", &spot_light_vars[4], 5);
	if (spot_light_vars[5] != 2)
	glui2->add_checkbox("Spot Light 5", &spot_light_vars[5], 6);
	if (spot_light_vars[6] != 2)
	glui2->add_checkbox("Spot Light 6", &spot_light_vars[6], 7);
	if (spot_light_vars[7] != 2)
	glui2->add_checkbox("Spot Light 7", &spot_light_vars[7], 8);

	if (omni_light_vars[0] != 2)
	glui2->add_checkbox("Omni Light 0", &omni_light_vars[0], 1);
	if (omni_light_vars[1] != 2)
	glui2->add_checkbox("Omni Light 1", &omni_light_vars[1], 2);
	if (omni_light_vars[2] != 2)
	glui2->add_checkbox("Omni Light 2", &omni_light_vars[2], 3);
	if (omni_light_vars[3] != 2)
	glui2->add_checkbox("Omni Light 3", &omni_light_vars[3], 4);
	if (omni_light_vars[4] != 2)
	glui2->add_checkbox("Omni Light 4", &omni_light_vars[4], 5);
	if (omni_light_vars[5] != 2)
	glui2->add_checkbox("Omni Light 5", &omni_light_vars[5], 6);
	if (omni_light_vars[6] != 2)
	glui2->add_checkbox("Omni Light 6", &omni_light_vars[6], 7);
	if (omni_light_vars[7] != 2)
	glui2->add_checkbox("Omni Light 7", &omni_light_vars[7], 8);

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
