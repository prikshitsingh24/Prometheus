#include "Application.h"
#include "Prometheus/Events/ApplicationEvent.h"
#include "Prometheus/Log.h"
namespace Prometheus {

	Application::Application()
	{
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		PT_TRACE(e);

		while (true);
	}
}

