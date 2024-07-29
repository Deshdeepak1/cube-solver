#include "tui.hpp"

#include <cstdlib>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/mouse.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/string.hpp>
#include <ftxui/screen/terminal.hpp>
#include <iterator>
#include <string>
#include <vector>

ftxui::ComponentDecorator CubeTUI::vscroll_renderer = ftxui::Renderer(
  [](ftxui::Element e) { return e | ftxui::vscroll_indicator | ftxui::frame; });

ftxui::Color CubeColorToFtxuiColor(Cube::Color color) {
  using namespace ftxui;
  switch (color) {
    case Cube::Color::WHITE:
      return Color::White;
    case Cube::Color::YELLOW:
      return Color::Yellow;
    case Cube::Color::RED:
      return Color::Red;
    case Cube::Color::ORANGE:
      return Color::Orange1;
    case Cube::Color::GREEN:
      return Color::Green;
    case Cube::Color::BLUE:
      return Color::Blue;
    default:
      return Color::Default;
  }
}

ftxui::Element render_face(const Cube& cube, Cube::Face face) {
  using namespace ftxui;
  Elements rows;
  for (unsigned int row = 0; row < cube.total_rows; row++) {
    Elements cols;
    for (unsigned int col = 0; col < cube.total_cols; col++) {
      auto cube_color = cube.get_color(face, row, col);
      auto color_char = cube.get_color_char(cube_color);
      auto ftxui_color = CubeColorToFtxuiColor(cube_color);
      Element square = text(std::string{color_char}) | bgcolor(ftxui_color) |
                       color(Color::Black) | border;
      cols.push_back(square);
    }
    rows.push_back(hbox(std::move(cols)));
  }
  return vbox(std::move(rows));
}

ftxui::Element CubeElement(Cube& cube) {
  using namespace ftxui;

  auto up_face = render_face(cube, Cube::Face::UP);
  auto down_face = render_face(cube, Cube::Face::DOWN);

  Elements middle_faces;
  for (const auto& middle_face : cube.middle_faces) {
    middle_faces.push_back(render_face(cube, middle_face));
  }

  return gridbox({
    {emptyElement(), up_face, emptyElement()},
    middle_faces,
    {emptyElement(), down_face, emptyElement()},
  });
}

class CubeComponent : public ftxui::ComponentBase {
 public:
  CubeComponent(Cube& cube) : cube_(cube) {}

  ftxui::Element Render() override {
    auto elements = std::vector<ftxui::Element>();
    for (int i = 0; i < 10; i++) {
      elements.push_back(CubeElement(cube_) | ftxui::border);
    }
    return ftxui::vbox(std::move(elements)) | ftxui::vscroll_indicator |
           ftxui::frame;
  }

 private:
  Cube& cube_;
};

void CubeTUI::run() {
  using namespace ftxui;
  auto screen = ScreenInteractive::FullscreenAlternateScreen();

  std::vector<std::string> model_entries;
  for (int i = 0; i < (int)MODEL::LAST; i++) {
    model_entries.push_back(get_model(i));
  }
  auto model_radiobox = Radiobox(&model_entries, &model_selected);
  model_radiobox |= window_comp("Model");

  std::vector<std::string> solver_entries;
  for (int i = 0; i < (int)SOLVER::LAST; i++) {
    solver_entries.push_back(get_solver(i));
  }
  auto solver_radiobox = Radiobox(&solver_entries, &solver_selected);
  solver_radiobox |= window_comp("Solver");

  std::vector<std::string> shuffle_entries;
  for (int i = 0; i <= 15; i++) {
    shuffle_entries.push_back(std::to_string(i));
  }
  auto shuffle_dropdown = Dropdown(&shuffle_entries, &random_shuffles);
  shuffle_dropdown |= window_comp("Random Shuffle");

  auto shuffle_button = Button(
    "Shuffle", [&] { std::system("dunstify Shuffling"); }, ButtonStyle());

  auto solve_button =
    Button("Solve", [&] { std::system("dunstify Solving"); }, ButtonStyle());

  auto quit_button = Button("Quit", [&] { screen.Exit(); }, ButtonStyle());
  auto options = Container::Vertical({
    model_radiobox,
    solver_radiobox,
    shuffle_dropdown,
  });

  auto buttons = Container::Vertical({
    shuffle_button,
    separator_comp(separatorEmpty()),
    solve_button,
    separator_comp(separatorEmpty()),
    quit_button,
  });

  auto leftpanel = Container::Vertical({
    options,
    separator_comp(),
    buttons,
  });
  leftpanel |= vscroll_renderer;

  std::unique_ptr<Cube> cube = create_cube(model_selected);

  // Make the right panel scrollable
  auto rightpanel = Renderer([&] { return CubeElement(*cube); });

  auto main_container = Container::Horizontal({
    leftpanel,
    separator_comp(),
    rightpanel,
  });

  // auto app = leftpanel;
  // auto app = rightpanel;
  auto app = main_container;
  app |= window_comp("CubeSolver");

  app = app | CatchEvent([&](Event event) {
          if (event == Event::q) {
            screen.Exit();
            return true;
          }
          return false;
        });
  screen.Loop(app);
}

ftxui::ButtonOption CubeTUI::ButtonStyle() {
  using namespace ftxui;
  auto option = ButtonOption::Animated(Color::Cyan1);
  option.transform = [](const EntryState& s) {
    auto element = text(s.label);
    // if (s.focused) {
    //   element |= bold;
    // }
    return element | center | borderEmpty;
  };
  return option;
}
