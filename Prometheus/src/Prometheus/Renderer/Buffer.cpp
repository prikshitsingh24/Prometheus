#include "ptpch.h"
#include "Prometheus/Renderer/Buffer.h"
#include "Prometheus/Renderer/Renderer.h"
#include "Prometheus/Core/Core.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Prometheus {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			PT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}
		PT_CORE_ASSERT(false,"Unknown renderer api");
		return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			PT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		}
		PT_CORE_ASSERT(false, "Unknown renderer api");
		return nullptr;
		return nullptr;
	}
}