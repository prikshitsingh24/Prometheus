#include "Sandbox2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}
void Sandbox2D::OnAttach()
{
	
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Prometheus::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Prometheus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Prometheus::RenderCommand::Clear();



	Prometheus::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Prometheus::Renderer2D::DrawQuad({ 0.5f,0.5f }, { 0.8f,0.8f }, m_SquareColor);
	Prometheus::Renderer2D::DrawQuad({ 0.5f,-0.5f }, { 0.5f,0.75f }, m_SquareColor2);
	Prometheus::Renderer2D::EndScene();


}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Color Picker");
	ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));
	ImGui::ColorEdit4("Square color2", glm::value_ptr(m_SquareColor2));
	ImGui::End();

}

void Sandbox2D::OnEvent(Prometheus::Event& event)
{
	m_CameraController.OnEvent(event);
}
