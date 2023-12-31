#include "ptpch.h"
#include "Prometheus/Core.h"
#include "VulkanContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Prometheus {
	VulkanContext::VulkanContext(GLFWwindow* windowHandle)
		:m_windowHandle(windowHandle)
	{
	}
	void VulkanContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PT_CORE_ASSERT(status, "failed to initialize Glad");
	}
	void VulkanContext::SwapBuffers()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_windowHandle);
	}
}
