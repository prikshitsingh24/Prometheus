#include "ptpch.h"
#include "Texture.h"
#include "Prometheus/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"
namespace Prometheus {
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}
		return nullptr;
	}
}