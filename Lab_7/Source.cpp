#include <stdlib.h>
#include <stdio.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include <GLFW/glfw3.h>
#include <gl/GL.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>

GLuint cubeTexId;
GLuint cylinderTexId;
GLuint sphereTexId;

GLuint upload_texture(std::string filename) {
	GLuint texId;

	GLint imageWidth;
	GLint imageHeight;
	GLint components;

	unsigned char* data;

	data = stbi_load(filename.c_str(), &imageWidth, &imageHeight, &components, STBI_rgb_alpha);

	if (data == NULL)
	{
		fprintf(stderr, "Texture Error!\n");
		exit(EXIT_FAILURE);
	}

	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texId;
}

void draw_cube() {
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, cubeTexId);

	glBegin(GL_QUADS);
	{
		// Top
		glNormal3f(0.0f, -1.5f, 0.5f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		// Bottom
		glNormal3f(0.0f, 1.5f, 0.5f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		// Back
		glNormal3f(0.0f, 0.0f, 2.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		// Left
		glNormal3f(1.5f, 0.0f, 0.5f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		// Right
		glNormal3f(-1.5f, 0.0f, 0.5f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

	glPopMatrix();
}

void draw_cylinder() {
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, cylinderTexId);

	glTranslatef(-0.5f, 0.2f, 0.0f);
	glScalef(0.2f, 0.2f, 0.2f);
	glRotatef(45.0f, 1.0f, 0.0f, 0.0f);

	double borderCount = 16;
	double borderNumber = 0.0;
	double height = 3;
	double step = 2 * M_PI / borderCount;

	// Tube
	for (double i = 0; i < 2 * M_PI; i += step)
	{
		glBegin(GL_QUADS);
		{
			glTexCoord2d(1 / borderCount * borderNumber, 0.5);
			glNormal3f(cos(i), sin(i), 0);
			glVertex3d(cos(i), sin(i), height);
			glTexCoord2d(1 / borderCount * borderNumber + 1 / borderCount, 0.5);
			glNormal3f(cos(i + step), sin(i + step), 0);
			glVertex3d(cos(i + step), sin(i + step), height);
			glTexCoord2d(1 / borderCount * borderNumber + 1 / borderCount, 0.0);
			glNormal3f(cos(i + step), sin(i + step), 0.0);
			glVertex3d(cos(i + step), sin(i + step), 0.0);
			glTexCoord2d(1 / borderCount * borderNumber, 0.0);
			glNormal3f(cos(i), sin(i), 0.0);
			glVertex3d(cos(i), sin(i), 0.0);
		}
		glEnd();

		borderNumber++;
	}

	// Top
	for (double i = 0; i < 2 * M_PI; i += step)
	{
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2d(0.25, -0.25);
			glVertex3d(0.0, 0.0, height);
			glTexCoord2d(0.25 + cos(i) / 4, -0.25 + sin(i) / 4);
			glVertex3d(cos(i), sin(i), height);
			glTexCoord2d(0.25 + cos(i + step) / 4, -0.25 + sin(i + step) / 4);
			glVertex3d(cos(i + step), sin(i + step), height);
		}
		glEnd();
	}

	// Bottom
	for (double i = 0; i < 2 * M_PI; i += step)
	{
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(0.0, 0.0, -1.0);
			glTexCoord2d(-0.25, -0.25);
			glVertex3d(0.0, 0.0, 0.0);
			glTexCoord2d(-0.25 + cos(i) / 4, -0.25 + sin(i) / 4);
			glVertex3d(cos(i), sin(i), 0);
			glTexCoord2d(-0.25 + cos(i + step) / 4, -0.25 + sin(i + step) / 4);
			glVertex3d(cos(i + step), sin(i + step), 0);
		}
		glEnd();
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	glPopMatrix();
}

void draw_sphere() {
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, sphereTexId);

	glColor3f(0.0f, 1.0f, 0.0f);

	glTranslatef(0.5f, 0.0f, 0.0f);
	glScalef(0.15f, 0.15f, 0.15f);

	double step = (float)M_PI / 12;
	float R = 2.0f;

	for (float i = 0; i < M_PI; i += step) {
		for (float j = 0; j < M_PI * 2; j += step) {
			glBegin(GL_QUADS);
			{
				glNormal3f(sin(i) * cos(j), cos(i), sin(i) * sin(j));
				glTexCoord2f(j / M_PI, 1 - (i / M_PI));
				glVertex3f(sin(i) * cos(j) * R, cos(i) * R, sin(i) * sin(j) * R);
				glNormal3f(sin(i + step) * cos(j), cos(i + step), sin(i + step) * sin(j));
				glTexCoord2f(j / M_PI, 1 - ((i + step) / M_PI));
				glVertex3f(sin(i + step) * cos(j) * R, cos(i + step) * R, sin(i + step) * sin(j) * R);
				glNormal3f(sin(i + step) * cos(j + step), cos(i + step), sin(i + step) * sin(j + step));
				glTexCoord2f((j + step) / M_PI, 1 - ((i + step) / M_PI));
				glVertex3f(sin(i + step) * cos(j + step) * R, cos(i + step) * R, sin(i + step) * sin(j + step) * R);
				glNormal3f(sin(i) * cos(j + step), cos(i), sin(i) * sin(j + step));
				glTexCoord2f((j + step) / M_PI, 1 - (i / M_PI));
				glVertex3f(sin(i) * cos(j + step) * R, cos(i) * R, sin(i) * sin(j + step) * R);
			}
			glEnd();
		}
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	glPopMatrix();
}

void render_loop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat lightPosition[4] = { 0.0f, 0.25f, -0.25f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glDisable(GL_DEPTH_TEST);

	draw_cube();

	glEnable(GL_DEPTH_TEST);

	draw_cylinder();
	draw_sphere();
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
	window = glfwCreateWindow(800, 800, "Lab_7", NULL, NULL);

	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	cubeTexId = upload_texture("cube_texture.jpg");
	cylinderTexId = upload_texture("cylinder_texture.jpg");
	sphereTexId = upload_texture("sphere_texture.jpg");

	while (!glfwWindowShouldClose(window))
	{
		render_loop();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	exit(EXIT_SUCCESS);
}