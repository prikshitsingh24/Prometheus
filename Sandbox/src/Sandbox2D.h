#pragma once
#include "Prometheus.h"

class Sandbox2D: public Prometheus::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Prometheus::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Prometheus::Event& event) override;
private:
	Prometheus::OrthographicCameraController m_CameraController;
	Prometheus::Ref<Prometheus::Shader> m_Shader;
	Prometheus::Ref<Prometheus::VertexArray> m_SquareVA;
	glm::vec4 m_SquareColor = { 0.8f,0.3f,0.2f,1.0f };
	glm::vec4 m_SquareColor2 = { 0.2f,0.3f,0.8f,1.0f };
	Prometheus::Ref<Prometheus::Texture2D> m_Sword,m_Tiles;
};