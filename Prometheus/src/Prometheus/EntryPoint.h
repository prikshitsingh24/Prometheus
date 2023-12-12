#pragma once


#ifdef PT_PLATFORM_WINDOWS
extern Prometheus::Application* Prometheus::CreateApplication();
int main(int argc,char** argv)
{
	
	auto app = Prometheus::CreateApplication();
	app->Run();
	delete app;
}
#endif 
