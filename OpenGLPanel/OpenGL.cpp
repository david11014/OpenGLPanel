#include "stdafx.h"
#include "OpenGL.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <experimental\filesystem>


OpenGLCore::OpenGLCore(HDC hdc)
{
	//init handle
	_hdc = hdc;

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_SUPPORT_GDI | PFD_DOUBLEBUFFER;

	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.cStencilBits = 2;

	int cpf = ChoosePixelFormat(_hdc, &pfd);
	if (!cpf)
	{
		set_error("Choose Pixel Format Error");
		return;
	}

	SetPixelFormat(_hdc, cpf, &pfd);
	_rc = wglCreateContext(_hdc);

	if (!_rc)
	{
		set_error("Create Render Context Error");
		return;
	}

	if (!wglMakeCurrent(_hdc, _rc))
	{
		set_error("wglMakeCurrent Error");
		return;
	}


	if (!gladLoadGL())
	{
		set_error("gladLoadGL failed");
		return;
	}
	if (!glfwInit())
	{
		set_error("glfwInit failed");
		return;
	}

	HMODULE hModule = GetModuleHandleW(NULL);
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(hModule, path, MAX_PATH);
	std::wstring ws(path);
	std::string str(ws.begin(), ws.end());
	std::cout << str << std::endl;

	std::cout << std::experimental::filesystem::current_path() << std::endl;
	std::ostream s;
	s << std::experimental::filesystem::absolute(".\\shader\\vertexShader.glsl") << std::endl;
	std::string path;
	s >> path;
	shader = new Shader(std::experimental::filesystem::absolute(".\\shader\\vertexShader.glsl").c_str(), std::experimental::filesystem::absolute(".\\shader\\fragmentShader.glsl").c_str());

	if (!shader->success)
	{
		set_error("Create shader failed");
		return;
	}
		


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Bind VAO
	glBindVertexArray(VAO);

	//bind VBO and copy vertics to VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//set vertex attribute pointer 
	//positiion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//unbind VAO
	glBindVertexArray(0);
	glEnable(GL_DEPTH_TEST);
	return;

}

bool OpenGLCore::render()
{

	glClearColor(0.0f, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Create transformations
	glm::mat4 model(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4 view(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4 projection(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

	model = glm::rotate(model, (GLfloat)glfwGetTime() * 5.0f, rotate_axis);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.f);

	shader->Use();

	// Get matrix's uniform location and set matrix
	GLint modelLoc = glGetUniformLocation(shader->Program, "model");
	if (modelLoc < 0)
	{
		set_error("glGetUniformLocation model failed");
		return false;
	}
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	GLint viewLoc = glGetUniformLocation(shader->Program, "view");
	if (viewLoc < 0)
	{
		set_error("glGetUniformLocation view failed");
		return false;
	}
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	GLint projectionLoc = glGetUniformLocation(shader->Program, "projection");
	if (projectionLoc < 0)
	{
		set_error("glGetUniformLocation projection failed");
		return false;
	}
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);

	return true;
}

void OpenGLCore::SwapBuffers() const
{
	::SwapBuffers(_hdc);
}

bool OpenGLCore::resize(int width, int height)
{
	// glViewport should not be called with width or height zero
	if (width == 0 || height == 0) return true;

	screenWidth = width;
	screenHeight = height;

	glViewport(0, 0, width, height);
	return true;
}
