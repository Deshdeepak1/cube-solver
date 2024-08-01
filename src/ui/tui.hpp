#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include "scroller.hpp"
#include "ui.hpp"

enum class DisplayMode : bool { Text, Canvas };
DisplayMode operator!(DisplayMode mode);

class CubeTUI : public UI {
 private:
  ftxui::Elements shuffle_elements, solution_elements;
  DisplayMode current_display_mode = DisplayMode::Canvas;

  constexpr static auto separator_comp = [](ftxui::Element sep =
                                              ftxui::separator()) {
    return ftxui::Renderer([sep]() { return sep; });
  };
  constexpr static auto window_comp = [](std::string title) {
    return ftxui::Renderer(
      [title](ftxui::Element e) { return window(ftxui::text(title), e); });
  };
  constexpr static auto to_component = [](ftxui::Element el) {
    return ftxui::Renderer([el]() { return el; });
  };

  static ftxui::ComponentDecorator vscroll_renderer;
  static ftxui::ComponentDecorator hscroll_renderer;
  static ftxui::ButtonOption ButtonStyle();

  void select_model_solve_cube(Cube *cube);

  template <typename CubeType>
  void select_solver_solve_cube(CubeType *cube);

 public:
  using UI::UI;
  void run() override;
};
