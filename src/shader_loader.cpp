#include "shader_loader.hpp"

#include <fstream>
#include <sstream>

#include "log.hpp"

namespace ar_overlay {

std::optional<std::string> loadShaderFile(std::string_view path) {
  std::ifstream file{std::string(path)};
  if (!file.is_open()) {
    logWarning("Failed to open shader file: " + std::string(path));
    return std::nullopt;
  }
  std::ostringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

} // namespace ar_overlay