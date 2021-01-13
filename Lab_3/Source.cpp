#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include <GLFW/glfw3.h>
#include <gl/GL.h>

float timer = 0.0f;

void draw_cylinder(GLfloat radius, GLfloat height)
{
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1;

	glBegin(GL_QUAD_STRIP);
		angle = 0.0;

		while (angle < 2 * M_PI) {
			x = radius * cos(angle);
			y = radius * sin(angle);

			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(x, y, height);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(x, y, 0.0f);

			angle = angle + angle_stepsize;
		}

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(radius, 0.0f, height);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(radius, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, height);

		angle = 0.0;

		while (angle < 2 * M_PI) {
			x = radius * cos(angle);
			y = radius * sin(angle); 

			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(x, y, height);

			angle = angle + angle_stepsize;
		}

		glVertex3f(radius, 0.0f, height);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);

		angle = 0.0;

		while (angle < 2 * M_PI) {
			x = radius * cos(angle);
			y = radius * sin(angle);

			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(x, y, 0.0f);

			angle = angle + angle_stepsize;
		}

		glVertex3f(radius, 0.0f, 0.0f);
	glEnd();
}

void render_loop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glTranslatef(0.0f, 0.25f, 0.0f);
	glRotatef(45.0f, 1.0f, 0.0f, 0.0f);

	draw_cylinder(0.5, 0.75);
}

int main(int argc, char* argv[])
{
	GLFWwindow* window;

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(800, 800, "Lab_3", NULL, NULL);

	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		if (timer == 360) {
			timer = 0.0f;
		}

		timer += 0.5f;

		render_loop();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	exit(EXIT_SUCCESS);
}