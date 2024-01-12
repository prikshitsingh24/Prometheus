#include <Prometheus.h>

class ExampleLayer :public Prometheus::Layer {
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-2.0f, 2.0f, -2.0f, 2.0f),m_CameraPosition(0.0f)
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
		float squareVertices[12] = {
			-0.75f,-0.75f,0.0f,
			 0.75f,-0.75f,0.0f,
			 0.75f, 0.75f,0.0f,
			-0.75f, 0.75f,0.0f
		};
		std::shared_ptr<Prometheus::VertexBuffer> squareVB;
		squareVB.reset(Prometheus::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		Prometheus::BufferLayout squareVBlayout = {
			{Prometheus::ShaderDataType::Float3,"a_Position"}
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
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position=a_Position;
				v_Color=a_Color;
				gl_Position=u_ViewProjection*vec4(a_Position,1.0);
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
		m_Shader.reset(new Prometheus::Shader(vertexSrc, fragmentSrc));

		std::string vertexSrc2 = R"(
			#version 330 core
						
			layout(location=0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			void main()
			{

				gl_Position=u_ViewProjection*vec4(a_Position,1.0);
			}		

		)";

		std::string fragmentSrc2 = R"(
			#version 330 core
						
			layout(location=0) out vec4 color;
			
			void main()
			{
		
				color=vec4(0.2,0.3,0.8,1.0);
			}		

		)";

		m_Shader2.reset(new Prometheus::Shader(vertexSrc2, fragmentSrc2));
	}

	void OnUpdate() override
	{
		if (Prometheus::Input::IsKeyPressed(PT_KEY_LEFT)) {
			m_CameraPosition.x -= m_CameraSpeed;
		}
		else if (Prometheus::Input::IsKeyPressed(PT_KEY_RIGHT)) {
			m_CameraPosition.x += m_CameraSpeed;
		}
		if (Prometheus::Input::IsKeyPressed(PT_KEY_UP)) {
			m_CameraPosition.y += m_CameraSpeed;
		}
		else if (Prometheus::Input::IsKeyPressed( PT_KEY_DOWN)) {
			m_CameraPosition.y -= m_CameraSpeed;
		}
		if (Prometheus::Input::IsKeyPressed(PT_KEY_A)) {
			m_CameraRotation += m_CameraRotationSpeed ;
		}
		if (Prometheus::Input::IsKeyPressed(PT_KEY_D)) {
			m_CameraRotation -= m_CameraRotationSpeed;
		}

		Prometheus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Prometheus::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Prometheus::Renderer::BeginScene(m_Camera);

		Prometheus::Renderer::Submit(m_Shader2, m_SquareVA);

		Prometheus::Renderer::Submit(m_Shader, m_VertexArray);

		Prometheus::Renderer::EndScene();
	}

	void OnEvent(Prometheus::Event& e) override
	{
		
	}
private:
	std::shared_ptr<Prometheus::Shader> m_Shader;
	std::shared_ptr<Prometheus::VertexArray> m_VertexArray;

	std::shared_ptr<Prometheus::VertexArray> m_SquareVA;
	std::shared_ptr<Prometheus::Shader> m_Shader2;

	Prometheus::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 0.1f;
	float m_CameraRotation=0.0f;
	float m_CameraRotationSpeed = 2.0f;
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