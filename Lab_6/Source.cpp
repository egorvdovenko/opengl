#include <stdlib.h>
#include <stdio.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include <GLFW/glfw3.h>
#include <gl/GL.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>

float timer = 0.0f;

GLuint texId;

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

void draw_cylinder(GLfloat radius, GLfloat height)
{
	float step = M_PI / 100;

	glBindTexture(GL_TEXTURE_2D, texId);

	for (float i = 0; i < 2 * M_PI; i += step) {
		glBegin(GL_QUADS);
		{
			glTexCoord2f(i / M_PI, 0);
			glNormal3f(cos(i), sin(i), 0);
			glVertex3f(radius * cos(i), radius * sin(i), 0);
			glTexCoord2f((i + step) / M_PI, 0);
			glNormal3f(cos(i + step), sin(i + step), 0);
			glVertex3f(radius * cos(i + step), radius * sin(i + step), 0);
			glTexCoord2f((i + step) / M_PI, height / 2);
			glNormal3f(cos(i + step), sin(i + step), 0);
			glVertex3f(radius * cos(i + step), radius * sin(i + step), height);
			glTexCoord2f(i / M_PI, height / 2);
			glNormal3f(cos(i), sin(i), 0);
			glVertex3f(radius * cos(i), radius * sin(i), height);
		}
		glEnd();
	}

	for (float i = 0; i < 2 * M_PI; i += step) {
		glBegin(GL_TRIANGLES);
		{
			glTexCoord2f(0.5, 0.5);
			glNormal3f(0, 0, 1);
			glVertex3f(0, 0, height);
			glTexCoord2f(cos(i) / 3.4 + 0.5, sin(i) / 3.4 + 0.5);
			glVertex3f(radius * cos(i), radius * sin(i), height);
			glTexCoord2f(cos(i + step) / 3.4 + 0.5, sin(i + step) / 3.4 + 0.5);
			glVertex3f(radius * cos(i + step), radius * sin(i + step), height);
		}
		glEnd();
	}

	for (float i = 0; i < 2 * M_PI; i += step) {
		glBegin(GL_TRIANGLES);
		{
			glTexCoord2f(0.5, 0.5);
			glNormal3f(0, 0, -1);
			glVertex3f(0, 0, 0);
			glTexCoord2f(cos(i) / 3.5 + 0.5, sin(i) / 3.5 + 0.5);
			glVertex3f(radius * cos(i), radius * sin(i), 0);
			glTexCoord2f(cos(i + step) / 3.5 + 0.5, sin(i + step) / 3.5 + 0.5);
			glVertex3f(radius * cos(i + step), radius * sin(i + step), 0);
		}
		glEnd();
	}
}

void render_loop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	float lightPosition[4] = { 5.0f, 5.0f, -5.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glScalef(0.25f, 0.25f, 0.25f);
	glTranslatef(0.0f, 0.5f, 0.0f);
	glRotatef(35.0f, 1.0f, 0.0f, 0.0f);

	draw_cylinder(1.0, 2.0);
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
	window = glfwCreateWindow(800, 800, "Lab_6", NULL, NULL);

	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	texId = upload_texture("texture.jpg");

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