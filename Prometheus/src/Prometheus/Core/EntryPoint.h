#pragma once


#ifdef PT_PLATFORM_WINDOWS
extern Prometheus::Application* Prometheus::CreateApplication();
int main(int argc,char** argv)
{
	Prometheus::Log::Init();
	PT_CORE_ERROR("Engine has started");
	PT_WARN("Hello world!!");
	auto app = Prometheus::CreateApplication();
	app->Run();
	delete app;
}
#endif 
