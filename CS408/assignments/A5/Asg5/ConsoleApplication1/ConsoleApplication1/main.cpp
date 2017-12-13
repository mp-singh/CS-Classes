#include "GetGlut.h"
#include "ObjLibrary\Vector2.h"
#include "Sleep.h"
#include <stdlib.h>
#include <time.h>
#define WIDTH 500
#define HEIGHT 500
#define GRIDSIZE 200
#define MAXTIME 3600

using namespace std;
struct gasParticle
{
	double mass;
	Vector2 vel;
};

gasParticle grid[GRIDSIZE][GRIDSIZE], newStats; //grid and a placeholder for individual cells to update the new stats
void initDisplay();
void keyboard(unsigned char key, int x, int y);
void update();
void reshape(int w, int h);
void display();
void mainProgram();
void UpdateCell(int x, int y);
void initGas();
void displayGrid();
void InitArray(gasParticle particle_new[][WIDTH]);
void CopyArray(gasParticle particle_old[][WIDTH], gasParticle particle_new[][WIDTH]);
void UpdateFromInflow(int x, int y, double m2, double vx2, double vy2);

int gridFull;
double m;
gasParticle particle_old[HEIGHT][WIDTH], particle_new[HEIGHT][WIDTH];

int main(int argc, char** argv)
{

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutCreateWindow("Assignment 5-CS 408");
	glutKeyboardFunc(keyboard);
	glutIdleFunc(update);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	initDisplay();
	glutMainLoop();

	return 1;
}


void initDisplay()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	initGas();  /* fills in values for mass_old, velocity_x_old, and velocity_y_old */
	displayGrid();
	glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // on [ESC]
		exit(0); // normal exit
		break;
	}
}

void update()
{
	/* main simulation loop */
	InitArray(particle_new); //new array set to zero
	/* For each cell in the grid, calculate its outflow and the resulting inflows for other cells */
	for (int y = 0; y < WIDTH; y++)
		for (int x = 0; x < HEIGHT; x++)
			UpdateCell(x, y);

	/* Copy new mass and velocity values into old arrays */
	CopyArray(particle_old, particle_new);           /* copy new into old */

	glutPostRedisplay();
}


void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	int x_center = w / 2;
	int y_center = h / 2;

	// set up a 2D view
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// clear the screen - any drawing before here will not display
	displayGrid();
	// send the current image to the screen - any drawing after here will not display
	glutSwapBuffers();
}




void UpdateCell(int x, int y)
{
	int intx, inty;
	double newx, newy, fractionx, fractiony;

	/* First figure out where the mass from this cell is going, based */
	/* on its velocity.  Assume that its new location is a cell-sized shape, with */
	/* coordinates of lower left hand corner given by newx and newy. */
	newx = x + particle_old[y][x].vel.x;
	newy = y + particle_old[y][x].vel.y;

	/* If the point is outside the grid, move it back inside the grid */
	/* using wraparound. */
	while (newy >= HEIGHT) newy = newy - HEIGHT;
	while (newy < 0.0)             newy = newy + HEIGHT;
	while (newx >= WIDTH)  newx = newx - WIDTH;
	while (newx < 0.0)             newx = newx + WIDTH;

	/* Since the velocity may not be an integer, the new location may */
	/* straddle several adjacent cells.  Find which cells the shape */
	/* overlaps and the fractions of each of these cells that it overlaps. */
	/* These cells are called the destination cells. */
	intx = (int)newx;
	inty = (int)newy;
	fractionx = newx - intx;
	fractiony = newy - inty;

	/* The outflow from the current cell (x y) becomes the  */
	/* inflow to the destination cells. It is divided according to  */
	/* the fraction of the shape that overlaps each of these cells. */
	UpdateFromInflow(
		intx,
		inty,
		(1.0 - fractionx) * (1.0 - fractiony) * particle_old[y][x].mass,
		particle_old[y][x].vel.x,
		particle_old[y][x].vel.y);
	UpdateFromInflow(
		intx,
		inty + 1,
		(1.0 - fractionx) * fractiony          * particle_old[y][x].mass,
		particle_old[y][x].vel.x,
		particle_old[y][x].vel.y);
	UpdateFromInflow(
		intx + 1,
		inty,
		fractionx          * (1.0 - fractiony) * particle_old[y][x].mass,
		particle_old[y][x].vel.x,
		particle_old[y][x].vel.y);
	UpdateFromInflow(
		intx + 1,
		inty + 1,
		fractionx          * fractiony           * particle_old[y][x].mass,
		particle_old[y][x].vel.x,
		particle_old[y][x].vel.y);
}


// add mass m2, which has velocity [vx2, vy2]T, to the existing new mass at location [y, x]
void UpdateFromInflow(int x, int y, double m2, double vx2, double vy2)
{
	double m1, vx1, vy1;

	/* If the point is outside the grid, move it back inside the grid */
	/* using wraparound.  Code not shown.*/

	/* current conditions in this cell before adding the inflow */
	m1 = particle_new[y][x].mass;
	vx1 = particle_new[y][x].vel.x;
	vy1 = particle_new[y][x].vel.y;

	if (m1 + m2 == 0.0)    /* avoid dividing by zero */
	{
		particle_new[y][x].mass = 0.0;
		particle_new[y][x].vel.x = 0.0;
		particle_new[y][x].vel.y = 0.0;
	}
	else
	{
		/* Compute new mass as the sum of the existing and inflowing gases */
		particle_new[y][x].mass = m1 + m2;

		/* Calculate the new velocity as the weighted average of the velocities  */
		/* of the existing and inflowing gases.  The weighting is done according */
		/* to the masses.  */
		particle_new[y][x].vel.x = (m1 * vx1 + m2 * vx2) / (m1 + m2);
		particle_new[y][x].vel.y = (m1 * vy1 + m2 * vy2) / (m1 + m2);
	}
}

void initGas()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if ((rand() % 20 + 1) == 5)
			{
				particle_old[i][j].mass = rand() % 100;
				particle_old[i][j].vel.x = rand() % 6 + (-3);
				particle_old[i][j].vel.y = rand() % 6 + (-3);
			}

			else
			{
				particle_old[i][j].mass = 0;
				particle_old[i][j].vel.x = 0;
				particle_old[i][j].vel.y = 0;
			}
		}
	}
}

void InitArray(gasParticle particle[][WIDTH])
{
	for(int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{
			particle[i][j].mass = 0;
			particle[i][j].vel.x = 0;
			particle[i][j].vel.y = 0;
		}
}

void displayGrid()
{
	float r, g, b;
	//display everything
	for(int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{
			r = particle_old[i][j].mass;
			g = particle_old[i][j].mass * particle_old[i][j].mass * 0.5;
			b = particle_old[i][j].mass * particle_old[i][j].mass *particle_old[i][j].mass * 0.0001;
			glPushMatrix();
				glTranslatef(i, j, 0);
				glColor3f(r, g, b);
					glBegin(GL_QUADS);
						glVertex2f(i, j);
						glVertex2f(i, j + 1);
						glVertex2f(i + 1, j);
						glVertex2f(i + 1, j + 1);
					glEnd();
			glPopMatrix();
		}
}

void CopyArray(gasParticle particle_old[][WIDTH], gasParticle particle_new[][WIDTH])
{
	for(int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{
			particle_old[i][j].mass = particle_new[i][j].mass;
			particle_old[i][j].vel.x = particle_new[i][j].vel.x;
			particle_old[i][j].vel.y = particle_new[i][j].vel.y;
		}

}