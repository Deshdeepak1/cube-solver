#include "tui.hpp"

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

ftxui::Element SquareElementText(Cube::Color cube_color) {
  using namespace ftxui;
  auto color_char = Cube::get_color_char(cube_color);
  auto ftxui_color = CubeColorToFtxuiColor(cube_color);
  Element square = text(std::string{color_char}) | bgcolor(ftxui_color) |
                   color(Color::Black) | border;
  return square;
}

ftxui::Element SquareElementCanvas(Cube::Color cube_color) {
  using namespace ftxui;
  auto ftxui_color = CubeColorToFtxuiColor(cube_color);
  auto c = Canvas(6, 6);
  c.DrawBlockLine(1, 1, 4, 1, ftxui_color);
  c.DrawBlockLine(1, 2, 4, 2, ftxui_color);
  return canvas(std::move(c));
}

DisplayMode operator!(DisplayMode mode) { return DisplayMode((!(bool)mode)); }

using SquareElementFunction = std::function<ftxui::Element(Cube::Color)>;

SquareElementFunction square_element_renderer(DisplayMode display_mode) {
  switch (display_mode) {
    case DisplayMode::Text:
      return SquareElementText;
    case DisplayMode::Canvas:
      return SquareElementCanvas;
  }
}

ftxui::Element render_face(const Cube& cube, Cube::Face face,
                           DisplayMode display_mode) {
  using namespace ftxui;
  Elements rows;
  for (int row = 0; row < cube.total_rows; row++) {
    Elements cols;
    for (int col = 0; col < cube.total_cols; col++) {
      auto cube_color = cube.get_color(face, row, col);
      auto square = square_element_renderer(display_mode)(cube_color);
      cols.push_back(square);
    }
    rows.push_back(hbox(std::move(cols)));
  }
  return vbox(std::move(rows));
}

ftxui::Element CubeElement(Cube& cube, DisplayMode display_mode) {
  using namespace ftxui;

  auto up_face = render_face(cube, Cube::Face::UP, display_mode);
  auto down_face = render_face(cube, Cube::Face::DOWN, display_mode);

  Elements middle_faces;
  for (const auto& middle_face : cube.middle_faces) {
    middle_faces.push_back(render_face(cube, middle_face, display_mode));
  }

  return gridbox({
           {emptyElement(), up_face, emptyElement()},
           middle_faces,
           {emptyElement(), down_face, emptyElement()},
         }) |
         border;
}

ftxui::Element MoveElement(Cube::Move move) {
  using namespace ftxui;

  auto c = Canvas(20, 12);
  c.DrawText(8, 2, Cube::get_move(move), Color::MediumTurquoise);
  c.DrawPointLine(16, 2, 20, 5, Color::Pink1);
  c.DrawPointLine(0, 5, 20, 5, Color::Pink1);
  c.DrawPointLine(16, 8, 20, 5, Color::Pink1);

  return canvas(std::move(c));
}

template <typename CubeType>
void CubeTUI::select_solver_solve_cube(CubeType* cube) {
  solution_elements.push_back(CubeElement(*cube, current_display_mode));

  auto solver =
    create_solver(cube, solver_selected, random_shuffles, corner_db_file_name);

  auto moves = solver->solve();

  for (const auto& move : moves) {
    solution_elements.push_back(MoveElement(move));
    cube->move(move);
    solution_elements.push_back(CubeElement(*cube, current_display_mode));
  }
}

void CubeTUI::select_model_solve_cube(Cube* cube) {
  switch (model_selected) {
    case 0: {
      auto concrete_cube = static_cast<Cube1DArray*>(cube);
      select_solver_solve_cube(concrete_cube);
      break;
    }
    case 1: {
      auto concrete_type = static_cast<Cube3DArray*>(cube);
      select_solver_solve_cube(concrete_type);
      break;
    }
    case 2: {
      auto concrete_type = static_cast<CubeBitboard*>(cube);
      select_solver_solve_cube(concrete_type);
      break;
    }
    default:
      throw std::invalid_argument("Invalid model_type");
  }
}

void CubeTUI::run() {
  using namespace ftxui;
  auto screen = ScreenInteractive::FullscreenAlternateScreen();
  std::unique_ptr<Cube> cube, cube_duplicate;

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

  std::string display_mode_button_texts[] = {"Switch to Text mode (m)",
                                             "Switch to Canvas mode (m)"};

  std::string display_mode_button_text =
    display_mode_button_texts[(bool)current_display_mode];

  auto toggle_mode = [&] {
    current_display_mode = !current_display_mode;
    display_mode_button_text =
      display_mode_button_texts[(bool)current_display_mode];
  };

  auto display_mode_button =
    Button(&display_mode_button_text, toggle_mode, ButtonStyle());

  auto fconf = FlexboxConfig();
  fconf.gap_x = 1;
  fconf.gap_y = 1;
  fconf.align_items = FlexboxConfig::AlignItems::Center;

  auto shuffle_window_box = Container::Horizontal({});
  auto shuffle_window = shuffle_window_box | Scroller | window_comp("Shuffle");

  auto solution_window_box = Container::Horizontal({});
  auto solution_window =
    solution_window_box | Scroller | window_comp("Solution");

  auto detach_elements = [&] {
    solution_window_box->DetachAllChildren();
    shuffle_window_box->DetachAllChildren();
  };

  auto attach_elements = [&] {
    shuffle_window_box->Add(to_component(flexbox(shuffle_elements, fconf)));
    solution_window_box->Add(to_component(flexbox(solution_elements, fconf)));
  };

  auto reset = [&] {
    detach_elements();

    cube = create_cube(model_selected);
    cube_duplicate = cube->clone();

    shuffle_elements.clear();
    shuffle_elements.push_back(
      CubeElement(*cube_duplicate, current_display_mode));
    solution_elements.clear();

    attach_elements();
  };

  auto reset_button = Button("Reset (r)", reset, ButtonStyle());

  auto shuffle = [&] {
    detach_elements();

    auto moves = cube->random_shuffle(random_shuffles);
    for (const auto& move : moves) {
      cube_duplicate->move(move);
      shuffle_elements.push_back(MoveElement(move));
      shuffle_elements.push_back(
        CubeElement(*cube_duplicate, current_display_mode));
    }

    solution_elements.clear();

    attach_elements();
  };

  auto shuffle_button = Button("Shuffle (s)", shuffle, ButtonStyle());

  auto solve = [&] {
    detach_elements();

    solution_elements.clear();
    cube_duplicate = cube->clone();

    select_model_solve_cube(cube_duplicate.get());

    attach_elements();
  };

  auto solve_button = Button("Solve (S)", solve, ButtonStyle());

  auto quit_button =
    Button("Quit (q)", screen.ExitLoopClosure(), ButtonStyle());

  auto move_function = [&](Cube& curr_cube, Cube::Move move) {
    detach_elements();

    curr_cube.move(move);
    shuffle_elements.push_back(MoveElement(move));
    shuffle_elements.push_back(CubeElement(curr_cube, current_display_mode));
    solution_elements.clear();

    attach_elements();
  };

  auto move_buttons = Container::Horizontal({});
  for (int i = 0; i < Cube::total_moves; i++) {
    auto move = Cube::Move(i);
    auto move_button = Button(
      Cube::get_move(move),
      [move, &cube, &move_function] { move_function(*cube, move); },
      ButtonStyle());

    Component layer;
    if (i % 3 == 0) {
      layer = Container::Vertical({});
      move_buttons->Add(layer);
    } else {
      layer = move_buttons->ChildAt(i / 3);
    }

    layer->Add(move_button);
  }
  move_buttons |= window_comp("Moves");
  move_buttons |= center;

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
    display_mode_button,
    separator_comp(separatorEmpty()),
    reset_button,
    separator_comp(separatorEmpty()),
    quit_button,
    move_buttons,
  });

  auto leftpanel = Container::Vertical({
    options,
    buttons,
  });

  leftpanel |= size(WIDTH, GREATER_THAN, 28);
  leftpanel |= window_comp("Control");
  leftpanel |= vscroll_renderer;

  int shuffle_window_size = 24;
  auto cube_windows =
    ResizableSplitTop(shuffle_window, solution_window, &shuffle_window_size);

  auto rightpanel = Container::Vertical({cube_windows | yflex_grow});
  rightpanel = rightpanel | xflex_grow;

  auto main_container = Container::Horizontal({
    leftpanel,
    separator_comp(),
    rightpanel,
  });

  auto app = main_container;
  app |= window_comp("CubeSolver");

  app = app | CatchEvent([&](Event event) {
          if (event == Event::q) {
            screen.Exit();
            return true;
          } else if (event == Event::r) {
            reset();
            return true;
          } else if (event == Event::s) {
            shuffle();
            return true;
          } else if (event == Event::S) {
            solve();
            return true;
          } else if (event == Event::m) {
            toggle_mode();
            return true;
          }
          return false;
        });

  reset();
  screen.Loop(app);
}

ftxui::ButtonOption CubeTUI::ButtonStyle() {
  using namespace ftxui;
  auto option = ButtonOption::Animated(Color::Cyan1);
  option.transform = [](const EntryState& s) {
    auto element = text(s.label);
    return element | center | borderEmpty;
  };
  return option;
}
