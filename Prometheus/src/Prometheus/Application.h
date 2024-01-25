#pragma once
#include "Core.h"
#include <Prometheus/Window.h>
#include "Prometheus/Events/ApplicationEvent.h"
#include "Prometheus/LayerStack.h"
#include "Prometheus/Input.h"
#include "Prometheus/ImGui/ImGuiLayer.h"
#include "Prometheus/Renderer/Shader.h"
#include "Prometheus/Renderer/Buffer.h"
#include "Prometheus/Renderer/VertexArray.h"
#include "Prometheus/Renderer/OrthographicCamera.h"
#include "Prometheus/Core/Timestep.h"

namespace Prometheus {
	class  Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime=0.0f;
		
	private:
		static Application* s_Instance;
		
	};

	//To be defined in client..
	Application* CreateApplication();
}

