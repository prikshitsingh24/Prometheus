#include <Prometheus.h>

class ExampleLayer :public Prometheus::Layer {
public:
	ExampleLayer()
		:Layer("Example")
	{}

	void OnUpdate() override
	{
		PT_INFO("Example layer:: OnUpdate");
	}

	void OnEvent(Prometheus::Event& e) override
	{
		PT_TRACE("{0}", e);
	}
};
class Sandbox :public Prometheus::Application {
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Prometheus::Application* Prometheus::CreateApplication()
{
	return new Sandbox;
}