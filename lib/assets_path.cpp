#include "assets_path.hpp"
#include <filesystem>

std::string ktp::Assets::getAssetsPath(const std::string& sub_dir) {
  const std::string kPROJECT_FOLDER = "kete-arka";
  constexpr auto kASSETS_FOLDER = "assets";

  #ifdef _WIN32
    constexpr auto kPATH_SEPARATOR = '\\';
  #else
    constexpr auto kPATH_SEPARATOR = '/';
  #endif

  auto path {std::filesystem::current_path().string()};
  const auto kPos {path.rfind(kPROJECT_FOLDER) + kPROJECT_FOLDER.length()};

  path = path.substr(0, kPos) + kPATH_SEPARATOR + kASSETS_FOLDER + kPATH_SEPARATOR;
  return sub_dir.empty() ? path : path + sub_dir + kPATH_SEPARATOR;
}
