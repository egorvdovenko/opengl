#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include <GLFW/glfw3.h>
#include <gl/GL.h>

float timer = 0;

void drawSphere(double r, int lats, int longs) {
	for (int i = 0; i <= lats; i++) {
		double lat0 = M_PI * (-0.5 + (double)(i - 1) / lats);
		double z0 = sin(lat0);
		double zr0 = cos(lat0);

		double lat1 = M_PI * (-0.5 + (double)i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= longs; j++) {
			double lng = 2 * M_PI * (double)(j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);


			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(r * x * zr0, r * y * zr0, r * z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(r * x * zr1, r * y * zr1, r * z1);
		}
		glEnd();
	}
}

void render_loop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glScalef(0.1f, 0.1f, 0.1f);

	float lightPosition[4] = { 0, 0, 0, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	float lightColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);

	//Sun
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 0.0f);
	drawSphere(1, 50, 50);
	glEnable(GL_LIGHTING);

	//Mercury
	glPushMatrix();
	glColor3f(0.6f, 0.3f, 0.0f);
	glTranslatef(-1.5f * cos(timer * 4.15f), -1.5f * sin(timer * 4.15f), 0.0f);
	glScaled(0.02f, 0.02f, 0.02f);
	drawSphere(1, 50, 50);
	glPopMatrix();

	//Venus
	glPushMatrix();
	glColor3f(0.8f, 0.5f, 0.2f);
	glTranslatef(-2.0f * cos(timer * 1.62f), -2.0f * sin(timer * 1.62f), 0.0f);
	glScaled(0.035f, 0.035f, 0.035f);
	drawSphere(1, 50, 50);
	glPopMatrix();

	//Earth
	glPushMatrix();
	glColor3f(0.1f, 0.0f, 0.8f);
	glTranslatef(-2.5f * cos(timer), -2.5f * sin(timer), 0.0f);
	glScaled(0.055f, 0.055f, 0.055f);
	drawSphere(1, 50, 50);
	glPopMatrix();

	//Mars
	glPushMatrix();
	glColor3f(0.9f, 0.2f, 0.1f);
	glTranslatef(-3.0f * cos(timer * 0.53f), -3.0f * sin(timer * 0.53f), 0.0f);
	glScaled(0.03f, 0.03f, 0.03f);
	drawSphere(1, 50, 50);
	glPopMatrix();

	//Jupiter
	glPushMatrix();
	glColor3f(0.8f, 0.5f, 0.1f);
	glTranslatef(-4.3f * cos(timer * 0.083f), -4.3f * sin(timer * 0.083f), 0.0f);
	glScaled(0.15f, 0.15f, 0.15f);
	drawSphere(1, 50, 50);
	glPopMatrix();

	//Saturn
	glPushMatrix();
	glColor3f(0.9f, 0.6f, 0.1f);
	glTranslatef(-5.5f * cos(timer * 0.0345f), -5.5f * sin(timer * 0.0345f), 0.0f);
	glScaled(0.1f, 0.1f, 0.1f);
	drawSphere(1, 50, 50);
	glPopMatrix();

	//Uranus
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.9f);
	glTranslatef(-6.5f * cos(timer * 0.0119f), -6.5f * sin(timer * 0.0119f), 0.0f);
	glScaled(0.08f, 0.08f, 0.08f);
	drawSphere(1, 50, 50);
	glPopMatrix();

	//Neptune
	glPushMatrix();
	glColor3f(0.1f, 0.0f, 0.8f);
	glTranslatef(-7.5f * cos(timer * 0.0061f), -7.5f * sin(timer * 0.0061f), 0.0f);
	glScaled(0.1f, 0.1f, 0.1f);
	drawSphere(1, 50, 50);
	glPopMatrix();
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
	window = glfwCreateWindow(800, 800, "Lab_5", NULL, NULL);

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
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	while (!glfwWindowShouldClose(window))
	{
		timer += 0.05;

		render_loop();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	exit(EXIT_SUCCESS);
}