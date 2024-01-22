#include <Prometheus.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <Platform/OpenGL/OpenGLShader.h>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer :public Prometheus::Layer {
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-2.0f, 2.0f, -2.0f, 2.0f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Prometheus::VertexArray::Create());


		float vertices[21] = {
			-0.5f,-0.5f,0.0f,0.8f,0.2f,1.8f,1.0f,
			 0.5f,-0.5f,0.0f,0.2f,0.3f,0.8f,1.0f,
			 0.0f, 0.5f,0.0f,0.8f,0.8f,0.2f,1.0f,
		};
		std::shared_ptr<Prometheus::VertexBuffer> triangleVB;
		triangleVB.reset(Prometheus::VertexBuffer::Create(vertices, sizeof(vertices)));

		Prometheus::BufferLayout layout = {
			{Prometheus::ShaderDataType::Float3,"a_Position"},
			{Prometheus::ShaderDataType::Float4,"a_Color"}
		};
		triangleVB->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(triangleVB);

		uint32_t indices[3] = { 0,1,2 };

		std::shared_ptr<Prometheus::IndexBuffer> triangleIB;
		triangleIB.reset(Prometheus::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(triangleIB);

		m_SquareVA.reset(Prometheus::VertexArray::Create());
		float squareVertices[4*5] = {
			-0.75f,-0.75f,0.0f,0.0f,0.0f,
			 0.75f,-0.75f,0.0f,1.0f,0.0f,
			 0.75f, 0.75f,0.0f,1.0f,1.0f,
			-0.75f, 0.75f,0.0f,0.0f,1.0f
		};
		std::shared_ptr<Prometheus::VertexBuffer> squareVB;
		squareVB.reset(Prometheus::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		Prometheus::BufferLayout squareVBlayout = {
			{Prometheus::ShaderDataType::Float3,"a_Position"},
			{Prometheus::ShaderDataType::Float2,"a_Texture"},
		};
		squareVB->SetLayout(squareVBlayout);

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };

		std::shared_ptr<Prometheus::IndexBuffer> squareIB;
		squareIB.reset(Prometheus::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
						
			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position=a_Position;
				v_Color=a_Color;
				gl_Position=u_ViewProjection * u_Transform * vec4(a_Position,1.0);
			}		

		)";

		std::string fragmentSrc = R"(
			#version 330 core
						
			layout(location=0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
		
				color=vec4(v_Position+0.2,1.0);
				color=v_Color;
			}		

		)";
		m_Shader= Prometheus::Shader::Create("VertexPosition",vertexSrc, fragmentSrc);

		m_Shader2=Prometheus::Shader::Create("assets/Shaders/Texture.glsl");

		m_Texture= Prometheus::Texture2D::Create("assets/textures/1.png");

		std::dynamic_pointer_cast<Prometheus::OpenGLShader>(m_Shader2)->Bind();
		std::dynamic_pointer_cast<Prometheus::OpenGLShader>(m_Shader2)->UploadUniformInt("u_Texture",0);
	}

	void OnUpdate(Prometheus::Timestep ts) override
	{
		
		if (Prometheus::Input::IsKeyPressed(PT_KEY_LEFT)) {
			m_CameraPosition.x -= m_CameraSpeed * ts;
		}
		else if (Prometheus::Input::IsKeyPressed(PT_KEY_RIGHT)) {
			m_CameraPosition.x += m_CameraSpeed * ts;
		}
		if (Prometheus::Input::IsKeyPressed(PT_KEY_UP)) {
			m_CameraPosition.y += m_CameraSpeed * ts;
		}
		else if (Prometheus::Input::IsKeyPressed( PT_KEY_DOWN)) {
			m_CameraPosition.y -= m_CameraSpeed * ts;
		}
		if (Prometheus::Input::IsKeyPressed(PT_KEY_A)) {
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}
		if (Prometheus::Input::IsKeyPressed(PT_KEY_D)) {
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}

		Prometheus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Prometheus::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Prometheus::Renderer::BeginScene(m_Camera);


		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);

		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

		std::dynamic_pointer_cast<Prometheus::OpenGLShader>(m_Shader2)->Bind();
		std::dynamic_pointer_cast<Prometheus::OpenGLShader>(m_Shader2)->UploadUniformFloat3("u_Color",m_SquareColor);

		m_Texture->Bind();

		Prometheus::Renderer::Submit(m_Shader, m_VertexArray);
				
		Prometheus::Renderer::Submit(m_Shader2, m_SquareVA);
			
		

		Prometheus::Renderer::EndScene();
	}
	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}
	void OnEvent(Prometheus::Event& e) override
	{
		
	}
private:
	Prometheus::Ref<Prometheus::Shader> m_Shader;
	Prometheus::Ref<Prometheus::VertexArray> m_VertexArray;

	Prometheus::Ref<Prometheus::VertexArray> m_SquareVA;
	Prometheus::Ref<Prometheus::Shader> m_Shader2;

	Prometheus::Ref<Prometheus::Texture2D> m_Texture;

	Prometheus::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 5.0f;
	float m_CameraRotation=0.0f;
	float m_CameraRotationSpeed = 40.0f;
	glm::vec3 m_SquareColor = { 0.2f,0.3f,0.8f };
};
class Sandbox :public Prometheus::Application {
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Prometheus::Application* Prometheus::CreateApplication()
{
	return new Sandbox;
}