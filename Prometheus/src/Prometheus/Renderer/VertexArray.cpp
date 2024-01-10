#include "ptpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Prometheus {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
				PT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!!");
				return nullptr;
		case RendererAPI::API::OpenGL:
				return new OpenGLVertexArray();
		}
		PT_CORE_ASSERT(false, "Unknown renderer api");
		return nullptr;
	}
}