#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include "ui.hpp"

class CubeTUI : public UI {
 private:
  constexpr static auto separator_comp = [](ftxui::Element sep =
                                              ftxui::separator()) {
    return ftxui::Renderer([sep]() { return sep; });
  };
  constexpr static auto window_comp = [](std::string title) {
    return ftxui::Renderer(
      [title](ftxui::Element e) { return window(ftxui::text(title), e); });
  };

  static ftxui::ComponentDecorator vscroll_renderer;
  static ftxui::ButtonOption ButtonStyle();

 public:
  using UI::UI;
  void run() override;
};
