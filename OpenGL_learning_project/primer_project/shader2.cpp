#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>

//build a VertexShader SourceCode
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"}\0";

//build a fragmentShader Sourcecode
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";


//settings
#define DEF_WINDOW_WIDTH 800
#define DEF_WINDOW_HEIGHT 600

#define ORIGIN

#ifndef ORIGIN

float stride = 0.001;

float m_x = 0.5;
float m_y = 0.5;
float m_z = 0.5;
float m_h = 0.5;

#endif//not define origin


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
#ifndef ORIGIN
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		m_x += stride;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		m_x -= stride;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		m_y += stride;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		m_y -= stride;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		m_z += stride;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		m_z -= stride;
	if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS)
		m_h += stride;
	if (glfwGetKey(window, GLFW_KEY_END) == GLFW_PRESS)
		m_h -= stride;
#endif // not define origin

}



int main()
{
	//Initial glfw window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Creat a window object
	GLFWwindow* window = glfwCreateWindow(DEF_WINDOW_WIDTH, DEF_WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳����������ˡ�


	//register a callback function to manipulate window's size
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	//Initial GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//-------------------------------------------
	//start setting shader and execute


	//####Vertex shader object####
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	/*unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);Ϊʲô��������д��*/

	//attach shader source code to shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//check success
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "EERRO::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//####Fragment shader object####11111111111111111111
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	/*unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);Ϊʲô��������д��*/
	//attach shader source code to shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//check success
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "EERRO::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	//shader program object
	unsigned int shaderProgram = glCreateProgram();
	/*unsigned int shaderProgram;
	shaderProgram = glCreateProgram();Ϊʲô��������д��*/

	//link the shaders
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "EERRO::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//Delete remnent
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	float vertices[] = {
		// first triangle
		-0.5f, -0.5f, 0.0f,  // left 
		0.5f, -0.5f, 0.0f,  // right
		0.0f, 0.5f, 0.0f,  // top 
	};

	unsigned int VBO, VAO;//��ʵ���������飡
	//OpenGL�ĺ���ģʽҪ������ʹ��VAO��������֪������δ������ǵĶ������롣������ǰ�VAOʧ�ܣ�OpenGL��ܾ������κζ�����
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//ʹ��glEnableVertexAttribArray���Զ�������λ��ֵ��Ϊ���������ö������ԣ���������Ĭ���ǽ��õġ�
	glEnableVertexAttribArray(0);


	//Դ����Ϊʲô�������ʧЧ��
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))//check the exit request
	{

		processInput(window);//react to press keyboard

#ifndef ORIGIN
		glClearColor(m_x, m_y, m_z, m_h);
#else
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
#endif
		glClear(GL_COLOR_BUFFER_BIT);

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");


		//activate program
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3);//�����6��ô�죿
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glfwSwapBuffers(window);//Swap colour buffer(backgroundcolour)
		glfwPollEvents();//check if trigger anyevents

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);



	glfwTerminate();
	return 0;
}