#include "MainWindow.hpp"

void MainWindow::Draw()
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);
	ImGui::SetNextWindowSize({ 1920, 1080 }, ImGuiCond_FirstUseEver);

	if (m_isOpen && ImGui::Begin("Luminous###LuminousUI", &m_isOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar))
	{
		// TODO: Add Draw calls of dependent popup windows here
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::MenuItem("New Project", "", false);

				ImGui::MenuItem("Open project ...", "", false);

				if (ImGui::BeginMenu("Open recent Project"))
				{
					ImGui::MenuItem("Project1", "", false);

					ImGui::MenuItem("Project2", "", false);

					ImGui::EndMenu();
				}
				ImGui::Separator();
				ImGui::MenuItem("Save all", "", false);

				ImGui::MenuItem("Save all as ...", "", false);

				ImGui::Separator();
				ImGui::MenuItem("Build Project", "", false);

				ImGui::MenuItem("Build Project and Run", "", false);

				ImGui::Separator();
				ImGui::MenuItem("Exit", "", false);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{

				ImGui::MenuItem("Undo", "", false);

				ImGui::MenuItem("Redo", "", false);

				ImGui::Separator();
				ImGui::MenuItem("Cut", "", false);

				ImGui::MenuItem("Copy", "", false);

				ImGui::MenuItem("Paste", "", false);

				ImGui::MenuItem("Duplicate", "", false);

				ImGui::MenuItem("Delete", "", false);

				ImGui::Separator();
				ImGui::MenuItem("Settings", "", false);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Window"))
			{
				ImGui::MenuItem("Console", "", false);

				ImGui::MenuItem("Scene", "", false);

				ImGui::MenuItem("Game", "", false);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Help"))
			{
				ImGui::MenuItem("About", "", false);

				ImGui::Separator();
				ImGui::MenuItem("Luminous Engine Docmentation", "", false);

				ImGui::MenuItem("Credits", "", false);

				ImGui::MenuItem("Report a bug", "", false);

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		static ImTextureID moveButton = LoadTexture("../../Assets/Move Button.png");
		static ImTextureID rotateButton = LoadTexture("../../Assets/Rotate Button.png");
		static ImTextureID resizeButton = LoadTexture("../../Assets/Resize Button.png");
		static ImTextureID playButton = LoadTexture("../../Assets/Play Button.png");
		static ImTextureID stopButton = LoadTexture("../../Assets/Stop Button.png");

		ImGui::Image(moveButton, { 25, 25 }, { 0, 0 }, { 1, 1 });
		//if (ImGui::IsItemClicked()) #Fonction;
		//if (ImGui::IsItemActivated()) #Fonction;

		ImGui::SameLine();
		ImGui::Image(rotateButton, { 25, 25 }, { 0, 0 }, { 1, 1 });

		ImGui::SameLine();
		ImGui::Image(resizeButton, { 25, 25 }, { 0, 0 }, { 1, 1 });

		ImGui::SameLine(0, 100 * ImGui::GetStyle().ItemSpacing.x);
		ImGui::Image(playButton, { 25, 25 }, { 0, 0 }, { 1, 1 });

		ImGui::SameLine();
		ImGui::Image(stopButton, { 25, 25 }, { 0, 0 }, { 1, 1 });


		ImGui::TableSetColumnIndex(0);
		ImGui::Begin("tab1", { -1, 255 }, true);
		ImGui::End();

		ImGui::TableNextColumn();
		ImGui::Begin("tab2", { -1, 255 }, true);
		ImGui::End();

		ImGui::Begin("tab2", { -1, -1 }, true);
		ImGui::End();
	}
	ImGui::PopStyleColor();
}