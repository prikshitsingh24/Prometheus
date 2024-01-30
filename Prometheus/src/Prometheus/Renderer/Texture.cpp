#include "ptpch.h"
#include "Texture.h"
#include "Prometheus/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"
namespace Prometheus {
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width,height);
		}
		return nullptr;
	}
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
		}
		return nullptr;
	}
}