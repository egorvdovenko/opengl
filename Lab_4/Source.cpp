#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include <GLFW/glfw3.h>
#include <gl/GL.h>

float timer = 0;

void draw_line(float R, float G, float B) {
	float step = ((4 * M_PI) / 1000.0f);
	float x = 0;
	float y = 0;
	float z = 0;

	for (float i = 0; i <= 4 * M_PI; i += step)
	{
		y = 2;
		x = 2 + y;
		z = i * 0.1 * sin(i + timer);

		glBegin(GL_QUADS);
		glColor3f(R, G, B);
		glVertex3f(i, y, z);
		glVertex3f(i, x, z);
		glVertex3f(i + step, x, z);
		glVertex3f(i + step, y, z);
		glEnd();
	}
}

void render_loop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
	glScalef(0.1f, 0.1f, 0.1f);

	glTranslatef(-6.0f, 0.0f, 0.0f);
	draw_line(1.0f, 0.0f, 0.0f);

	glTranslatef(0.0f, -2.0f, 0.0f);
	draw_line(0.0f, 1.0f, 0.0f);

	glTranslatef(0.0f, -2.0f, 0.0f);
	draw_line(0.0f, 0.0f, 1.0f);
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
	window = glfwCreateWindow(800, 800, "Lab_4", NULL, NULL);

	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		timer += 0.025;

		render_loop();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	exit(EXIT_SUCCESS);
}