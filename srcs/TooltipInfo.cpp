#include "all.hpp"

ImGuiIO& initImGui(GLFWwindow *window)
{
	ImGui::CreateContext();	
	ImGuiIO& io = ImGui::GetIO();
	// (void)io
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
	return io;
}

void FrameImGui()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void OptionImGui(Obj &obj, Camera &cam, WindowInfo &windowInfo, ImGuiIO& io)
{
	ImGui::Begin("Tooltip");
	ImGui::SeparatorText("Debug");
	ImGui::Text("FPS: %.1f", io.Framerate);
	ImGui::Text("Render time: %.2f ms", 1000.0f / io.Framerate);
	ImGui::Text("Triangles: %ld", obj.triangleCount);

	ImGui::SeparatorText("Transform Object");
	ImGui::SliderFloat3("O_Position (X,Y,Z)", obj.position, -10.0f, 10.0f);
	ImGui::SliderFloat3("Rotation (X,Y,Z)", obj.rotation, 0.0f, 10.0f);
	if (ImGui::Button("Reset")) {
		obj.position[0] = 0.0f;
		obj.position[1] = 0.0f;
		obj.position[2] = 0.0f;
		obj.rotation[0] = 0.0f;
		obj.rotation[1] = 0.0f;
		obj.rotation[2] = 0.0f;
	}

	ImGui::SeparatorText("Camera");
	float camPosition[3] = {cam.position.x, cam.position.y, cam.position.z};
	ImGui::SliderFloat3("C_Position (X,Y,Z)", camPosition, -20.0f, 20.0f);

	ImGui::SeparatorText("Appearance");
	ImGui::ColorEdit3("R,G,B", windowInfo.BackgroundColors);
	if (obj.hasTexture)
		ImGui::Checkbox("Use Texture", &obj.toggleTexture);
	ImGui::End();
}

void renderImGui()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ShutdownImGui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
