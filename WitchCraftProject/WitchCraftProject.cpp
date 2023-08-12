#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "TextureLoader.h"

#define WINDOW_HEIGHT 480
#define WINDOW_WIDTH  640

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
float horizontal_directions = 0;
float vertical_directions = 0;
float resize = 0;


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		horizontal_directions -= 0.0001f;

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		horizontal_directions += 0.0001f;

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		vertical_directions += 0.0001f;

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		vertical_directions -= 0.0001f;

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		resize += 0.0001f;

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		resize -= 0.0001f;

}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "the lagacy", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "something went wrong with glad !" << std::endl;
		return -1;
	}
	

	unsigned int texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_uc* data = stbi_load("ds.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);



	unsigned int texture2;
	glGenTextures(1, &texture2);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);


	stbi_uc* data2 = stbi_load("face.png", &width, &height,&nrChannels,0);
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "failed to load the image file" << std::endl;
	}

	stbi_image_free(data2);



	//HERE IS THE DRAWING DETAILS
	float vertices[] =
	{
		//POSITIONS   //COLORS   //TEXTURE
		-0.5,-0.5,0,   1,1,1,	 1.0f,1.0f,
		-0.5, 0.5,0,   1,1,0,	 1.0f,0.0f,
		 0.5, 0.5,0,   0,0,0,	 0.0f,0.0f,
		 0.5,-0.5,0,   0,1,1,	 0.0f,1.0f,
	};
	unsigned int indecies[] =
	{
		0,1,2,
		2,0,3
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int EAO;
	glGenBuffers(1, &EAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EAO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), &indecies, GL_STATIC_DRAW);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	Shader shader("VertexShader.shader", "FragmentShader.shader");


	shader.UnBind();
	glUniform1i(glGetUniformLocation(shader.shader_program, "textureFrag"), 0); // set it manually
	shader.setInt("textureFrag2", 1); // or with shader class
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	/* Make the window's context current */

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0, 0, 0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Bind();

		shader.set4Float("colorTest", 1, 1, 0, 1);
		shader.setFloat("Xoffset", horizontal_directions);
		shader.setFloat("Yoffset", vertical_directions);
		shader.setFloat("Zoffset", resize);
		shader.setInt("textureFrag", 0); // or with shader class
		shader.setInt("textureFrag2", 1); // or with shader class

	
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		processInput(window);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}