#pragma once
#include "Prometheus/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Prometheus {

	class VulkanContext : public GraphicsContext
	{
	public:
		VulkanContext(GLFWwindow* m_windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_windowHandle;
	};
}