#include "ptpch.h"
#include "Application.h"
#include "Prometheus/Events/ApplicationEvent.h"
#include "Prometheus/Log.h"
namespace Prometheus {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		

		while (m_Running) {
			m_Window->OnUpdate();
		}
	}
}

