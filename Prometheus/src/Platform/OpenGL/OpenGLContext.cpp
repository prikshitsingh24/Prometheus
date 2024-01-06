#include "ptpch.h"
#include "Prometheus/Core.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenGLContext.h"


namespace Prometheus {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_windowHandle(windowHandle)
	{
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PT_CORE_ASSERT(status, "failed to initialize Glad");

	}
	void OpenGLContext::SwapBuffers()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_windowHandle);
	}
	
}
