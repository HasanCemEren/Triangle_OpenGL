#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaderprogram.hpp"

float vertices[] = {
	-0.6f, -0.6f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

unsigned int programId;
//Vertex Buffer Object oluþturuldu.
unsigned int VBO;
//Vertex Array Object oluþturuldu.
unsigned int VAO;
float degerX = 0.0f;
float degerY = 0.0f;

//Input Handling
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE)		glfwTerminate();
	if (key == GLFW_KEY_D)	degerX += 0.01;
	if (key == GLFW_KEY_A)	degerX -= 0.01;
	if (key == GLFW_KEY_W)	degerY += 0.01;
	if (key == GLFW_KEY_S)	degerY -= 0.01;
	
}

int main(int argc, char** argv) {
	if (!glfwInit()) { return -1; }

	GLFWwindow* window = glfwCreateWindow(800, 800, "First Program", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "The Window wasn't created.";
		glfwTerminate();
		return -1;
	}

	
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	ShaderProgram shaderProgram;

	shaderProgram.attachShader("./shaders/simplevs.glsl", GL_VERTEX_SHADER);
	shaderProgram.attachShader("./shaders/simplefs.glsl", GL_FRAGMENT_SHADER);
	shaderProgram.link();

	shaderProgram.addUniform("uMoveX");
	shaderProgram.addUniform("uMoveY");


	//Generating.
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//Vertex Array aktif etme.
	glBindVertexArray(VAO);
	//Vertex Buffer aktif etme.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Verileri ana hafýzadan ekran kartýna iletme.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//Byte içinde özellik belirtme.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//Oluþturduðumuz slotlarý aktif etme.
	glEnableVertexAttribArray(0);

	
	while (!glfwWindowShouldClose(window))
	{
			//Hata kontrolü
			/*
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
			{
				std::cerr << "OpenGL Error: " << error << std::endl;
			}
			*/
			//Ekraný temizleme iþleme.
			glClearColor(0.0f, 0.4f, 0.7f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shaderProgram.use();
			shaderProgram.setFloat("uMoveX", degerX);
			shaderProgram.setFloat("uMoveY", degerY);
			
			glBindVertexArray(VAO);


			//Çizim.
			glDrawArrays(GL_TRIANGLES, 0, 6);



			glfwSwapBuffers(window);
			glfwPollEvents();
	}
}
