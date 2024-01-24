#pragma once

#include <cstdlib>

#include "../../vendor/trollworks-sdk-core/include/trollworks.hpp"
#include "../../vendor/trollworks-sdk-backend-sdl/include/trollworks-backend-sdl.hpp"

#include "./imgui.hpp"

namespace tw::sdl::ui {
  class imgui_sdl_plugin {
    public:
      using sigh_render_type = entt::sigh<void()>;

    private:
      sigh_render_type m_sigh_render;
      entt::sink<sigh_render_type> m_sink_render{m_sigh_render};

    public:
      imgui_sdl_plugin(sdl_backend& backend);

      template <auto Candidate, typename... Args>
      imgui_sdl_plugin& on_render(Args&&... args) {
        m_sink_render.template connect<Candidate>(std::forward<Args>(args)...);
        return *this;
      }

      void setup(controlflow& cf);
      void teardown();

      void process_event(const SDL_Event& event, controlflow& cf);
      void render();

    private:
      sdl_backend& m_backend;
      ImGuiContext* m_ctx;

  };
}
