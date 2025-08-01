#include "dewpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "DEWEngine/Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "GLFW/glfw3.h" //Temporary: should use DEWEngine KeyCodes

#include "DEWEngine/Application.h"

namespace DEWEngine {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext(); // Create ImGui context
		ImGui::StyleColorsDark(); // Set dark theme

		ImGuiIO& io = ImGui::GetIO();

		// Mouse Configs
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors; // Enable mouse cursors
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos; // Enable setting mouse position

		//Keyboard Configs 
		//**TEMPORARY**: should use DEWEngine KeyCodes
		io.AddKeyEvent(ImGuiKey_Tab, GLFW_KEY_TAB);
		io.AddKeyEvent(ImGuiKey_LeftArrow, GLFW_KEY_LEFT);
		io.AddKeyEvent(ImGuiKey_RightArrow, GLFW_KEY_RIGHT);
		io.AddKeyEvent(ImGuiKey_UpArrow, GLFW_KEY_UP);
		io.AddKeyEvent(ImGuiKey_DownArrow, GLFW_KEY_DOWN);
		io.AddKeyEvent(ImGuiKey_PageUp, GLFW_KEY_PAGE_UP);
		io.AddKeyEvent(ImGuiKey_PageDown, GLFW_KEY_PAGE_DOWN);
		io.AddKeyEvent(ImGuiKey_Home, GLFW_KEY_HOME);
		io.AddKeyEvent(ImGuiKey_End, GLFW_KEY_END);
		io.AddKeyEvent(ImGuiKey_Insert, GLFW_KEY_INSERT);
		io.AddKeyEvent(ImGuiKey_Delete, GLFW_KEY_DELETE);
		io.AddKeyEvent(ImGuiKey_Backspace, GLFW_KEY_BACKSPACE);
		io.AddKeyEvent(ImGuiKey_Space, GLFW_KEY_SPACE);
		io.AddKeyEvent(ImGuiKey_Enter, GLFW_KEY_ENTER);
		io.AddKeyEvent(ImGuiKey_Escape, GLFW_KEY_ESCAPE);
		io.AddKeyEvent(ImGuiKey_A, GLFW_KEY_A);
		io.AddKeyEvent(ImGuiKey_C, GLFW_KEY_C);
		io.AddKeyEvent(ImGuiKey_V, GLFW_KEY_V);
		io.AddKeyEvent(ImGuiKey_X, GLFW_KEY_X);
		io.AddKeyEvent(ImGuiKey_Y, GLFW_KEY_Y);
		io.AddKeyEvent(ImGuiKey_Z, GLFW_KEY_Z);

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		// Cleanup ImGui context here
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();

		// Setup Display
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		//Setup delta time
		float time = (float)glfwGetTime(); // Get current time in seconds

		// m_Time: previous frame, time: current frame
		// If m_Time is 0.0f, it means this is the first frame
		// So we set delta time to a default value of 1/60 seconds to get the frame duration
		// Otherwise, we calculate the frame duration as the difference between current and previous frame times
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f); 
		m_Time = time; // Update m_Time to current time for next frame
		
		
		
		ImGui_ImplOpenGL3_NewFrame();//Sets up ImGui for a new frame
		ImGui::NewFrame(); // Start a new ImGui frame
		
		
		static bool show = true;
		ImGui::ShowDemoWindow(&show); // Show the ImGui demo window
		
		ImGui::Render(); //compile frame descriptions into draw data
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Send draw data to OpenGL renderer

	}

	void ImGuiLayer::OnEvent(Event& event)
	{


	}

}