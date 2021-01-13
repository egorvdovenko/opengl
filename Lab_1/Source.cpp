#include <iostream>

using namespace std;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

GLFWwindow* window;
const char* Title = "OpenGL Window";
int width = 500, height = 500;

GLuint vbo, vao;
GLuint vs, fs, program;

const char* vertexShader = "#version 330 core\n"
"layout(location=0) in vec3 pos;\n"
"layout(location=1) in vec3 color;\n"
"out vec3 Color;\n"
"uniform mat4 transform;\n"
"void main(){\n"
"Color = color;"
"gl_Position = transform * vec4(pos, 1.0f);\n"
"}";

const char* fragmentShader = "#version 330 core\n"
"in vec3 Color;\n"
"out vec4 fragcolor;\n"
"void main(){\n"
"fragcolor = vec4(Color, 1.0f);\n"
"}";

GLfloat vertices[] = {
	//front
	-1.0f, 1.0f,-1.0f, 1.0f, 0.0f, 0.0f,	//top-left
	 1.0f, 1.0f,-1.0f, 1.0f, 0.0f, 0.0f,	//top-right
	 1.0f,-1.0f,-1.0f, 1.0f, 0.0f, 0.0f,	//bottom-right
	-1.0f, 1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 	//top-left
	 1.0f,-1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 	//bottom-right
	-1.0f,-1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 	//bottom-left

	//back
	-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 	//top-left
	 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 	//top-right
	 1.0f,-1.0f, 1.0f, 0.0f, 1.0f, 1.0f,	//bottom-right
	-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,	//top-left
	 1.0f,-1.0f, 1.0f, 0.0f, 1.0f, 1.0f,	//bottom-right
	-1.0f,-1.0f, 1.0f, 0.0f, 1.0f, 1.0f,	//bottom-left

	//left
	-1.0f, 1.0f,-1.0f, 0.0f, 0.0f, 1.0f,	//top-left
	-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,	//top-right
	-1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,	//bottom-right
	-1.0f, 1.0f,-1.0f, 0.0f, 0.0f, 1.0f,	//top-left
	-1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,	//bottom-right
	-1.0f,-1.0f,-1.0f, 0.0f, 0.0f, 1.0f,	//bottom-left

	//right
	 1.0f, 1.0f,-1.0f, 1.0f, 0.0f, 1.0f,	//top-left
	 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	//top-right
	 1.0f,-1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	//bottom-right
	 1.0f, 1.0f,-1.0f, 1.0f, 0.0f, 1.0f,	//top-left
	 1.0f,-1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	//bottom-right
	 1.0f,-1.0f,-1.0f, 1.0f, 0.0f, 1.0f,	//bottom-left

	//top
	-1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,	//back top-left
	 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,	//back top-right
	 1.0f, 1.0f,-1.0f, 1.0f, 1.0f, 0.0f,	//front top-right
	-1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,	//back top-left
	 1.0f, 1.0f,-1.0f, 1.0f, 1.0f, 0.0f,	//front top-right
	-1.0f, 1.0f,-1.0f, 1.0f, 1.0f, 0.0f,	//front top-left				 

	//bottom
	-1.0f,-1.0f, 1.0f, 0.0f, 1.0f, 0.0f,	//back bottom-left
	 1.0f,-1.0f, 1.0f, 0.0f, 1.0f, 0.0f,	//back bottom-right
	 1.0f,-1.0f,-1.0f, 0.0f, 1.0f, 0.0f,	//front bottom-right
	-1.0f,-1.0f, 1.0f, 0.0f, 1.0f, 0.0f,	//back bottom-left
	 1.0f,-1.0f,-1.0f, 0.0f, 1.0f, 0.0f,	//front bottom-right
	-1.0f,-1.0f,-1.0f, 0.0f, 1.0f, 0.0f,	//front bottom-left
};

int main()
{
	if (!glfwInit())
	{
		cerr << "Error!!GLFW";
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	if (!(window = glfwCreateWindow(width, height, Title, NULL, NULL)))
	{
		cerr << "Error!!GLFW window";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// glad: загрузка указателей на OpenGL-функции
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	vs = glCreateShader(GL_VERTEX_SHADER);
	fs = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vs, 1, &vertexShader, NULL);
	glShaderSource(fs, 1, &fragmentShader, NULL);

	glCompileShader(vs);
	glCompileShader(fs);

	int result;
	GLchar infoLog[1024];

	glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vs, sizeof(infoLog), NULL, infoLog);
		cerr << "Vertex Shader : Error !! " << infoLog;
	}

	glGetShaderiv(fs, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fs, sizeof(infoLog), NULL, infoLog);
		cerr << "Fragment Shader : Error !! " << infoLog;
	}

	program = glCreateProgram();

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGetProgramiv(fs, GL_LINK_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(fs, sizeof(infoLog), NULL, infoLog);
		cerr << "Shader Program : Error !! " << infoLog;
	}

	mat4 trans = mat4(1.0f);

	trans = glm::rotate(trans, radians(15.0f), vec3(1.0, 0.0, 0.0));
	trans = glm::rotate(trans, radians(-15.0f), vec3(0.0, 1.0, 0.0));
	trans = glm::scale(trans, vec3(0.5, 0.5, 0.5));

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glBindVertexArray(vao);

		glUseProgram(program);

		glUniformMatrix4fv(glGetUniformLocation(program, "transform"), 1, GL_FALSE, glm::value_ptr(trans));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);

		glEnable(GL_DEPTH_TEST);

		glfwSwapBuffers(window);
	}

	glDetachShader(program, vs);
	glDetachShader(program, fs);
	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteProgram(program);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	glfwTerminate();

	return 0;
}