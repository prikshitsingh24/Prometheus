#pragma once
#include "Prometheus/Renderer/Buffer.h"

namespace Prometheus {

	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices,uint32_t size);
		virtual ~OpenGLVertexBuffer();
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void SetLayout(const BufferLayout& layout) override { m_layout = layout; }
		virtual const BufferLayout GetLayout()const override { return m_layout; }
	private:
		uint32_t m_RendererID;
		BufferLayout m_layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual ~OpenGLIndexBuffer();
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual uint32_t GetCount() const { return m_Count; }
	private:
		uint32_t m_Count;
		uint32_t m_RendererID;
	};
}