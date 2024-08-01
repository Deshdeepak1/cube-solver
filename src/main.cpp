#include "main.hpp"

#include <boost/program_options.hpp>

#include "pattern_databases/CornerDBMaker.hpp"
#include "ui/cli.hpp"
#include "ui/tui.hpp"

namespace po = boost::program_options;

std::filesystem::path exe_path =
  std::filesystem::canonical("/proc/self/exe").remove_filename();

std::string default_corner_db_file_name =
  exe_path / (std::filesystem::path(DATABASES) / "corner_db.bin");

void print_version() {
  std::cout << PROJECT_NAME << " " << PROJECT_VERSION << "\n";
}

void print_usage() { std::cout << "Usage: " << PROJECT_NAME << " [options]\n"; }

int main(int argc, char *argv[]) {
  try {
    po::options_description desc("Allowed options");
    // clang-format off
    desc.add_options()
    ("help,h", "Print this help message")
    ("version,v", "Print the project version")
    ("model,m", po::value<int>()->default_value(3)->value_name("MODEL"),
     "Choose model:\n"
     "1: 1DArray\n"
     "2: 3DArray\n"
     "3: Bitboard")
    ("solver,s", po::value<int>()->default_value(4)->value_name("SOLVER"),
     "Choose solver:\n"
     "1: BFS\n"
     "2: DFS\n"
     "3: IDDFS\n"
     "4: IDAStar")
    ("random-shuffles,r", po::value<int>()->default_value(6)->value_name("RANDOM_SHUFFLES"),
     "Number of random shuffles")
    ("corner-db,d", po::value<std::string>()->default_value(default_corner_db_file_name)->value_name("CORNER_DB"),
     "Path to the corner DB file")
    ("corner-db-make,c", po::value<std::string>()->value_name("CORNER_DB"),
     "Make corner db at CORNER_DB")
    ("tui,t", "Use TUI")
    ;
    // clang-format on

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);

    if (vm.count("help")) {
      print_usage();
      std::cout << desc;
      return 0;
    }

    if (vm.count("version")) {
      print_version();
      return 0;
    }

    po::notify(vm);

    if (vm.count("corner-db-make")) {
      std::string corner_db_file_name = vm["corner-db-make"].as<std::string>();
      CornerDBMaker corner_db(corner_db_file_name);
      corner_db.bfs_and_store();
      return 0;
    }

    int model_type = vm["model"].as<int>();
    if (model_type < 1 || model_type > 3) {
      throw std::invalid_argument("MODEL type must be 1, 2, or 3.");
    }

    int solver_type = vm["solver"].as<int>();
    if (solver_type < 1 || solver_type > 4) {
      throw std::invalid_argument("SOLVER type must be >= 1 && <= 4");
    }

    int random_shuffles = vm["random-shuffles"].as<int>();
    if (random_shuffles < 1) {
      throw std::invalid_argument("RANDOM_SHUFFLES type must be positive");
    }

    std::string corner_db_file_name = vm["corner-db"].as<std::string>();

    std::unique_ptr<UI> ui;
    if (vm.count("tui")) {
      ui = std::make_unique<CubeTUI>(model_type, solver_type, random_shuffles,
                                     corner_db_file_name);
    } else {
      ui = std::make_unique<CubeCLI>(model_type, solver_type, random_shuffles,
                                     corner_db_file_name);
    }
    ui->run();

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  } catch (...) {
    std::cerr << "Unknown error!\n";
    return 1;
  }
  return 0;
}
