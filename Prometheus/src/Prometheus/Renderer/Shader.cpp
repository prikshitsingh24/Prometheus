#include "ptpch.h"
#include "Shader.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer.h"
namespace Prometheus {
	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return new OpenGLShader(filepath);
		}
		return nullptr;
	}
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		return nullptr;
	}
}