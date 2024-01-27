#include <cstdlib>

#include <trollworks-imgui-sdl.hpp>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>

namespace tw::sdl::ui {
  imgui_sdl_plugin::imgui_sdl_plugin(sdl_backend& backend)
    : m_backend(backend)
  {}

  void imgui_sdl_plugin::setup(controlflow&) {
    m_ctx = ImGui::CreateContext();
    if (m_ctx == nullptr) {
      SDL_Log("Failed to create ImGui context");
      std::exit(1);
    }

    auto& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.Fonts->AddFontDefault();
    ImGui::StyleColorsDark();

    if (!ImGui_ImplSDL2_InitForSDLRenderer(m_backend.window(), m_backend.renderer())) {
      SDL_Log("Failed to initialize ImGui SDL2 backend");
      std::exit(1);
    }

    if (!ImGui_ImplSDLRenderer2_Init(m_backend.renderer())) {
      SDL_Log("Failed to initialize ImGui SDLRenderer2 backend");
      std::exit(1);
    }
  }

  void imgui_sdl_plugin::teardown() {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext(m_ctx);
  }

  void imgui_sdl_plugin::process_event(const SDL_Event& event, controlflow&) {
    ImGui_ImplSDL2_ProcessEvent(&event);
  }

  void imgui_sdl_plugin::render() {
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame(m_backend.window());
    ImGui::NewFrame();

    m_sigh_render.publish();

    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
  }
}
