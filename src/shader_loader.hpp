#pragma once

#include <optional>
#include <string>
#include <string_view>

namespace ar_overlay {

std::optional<std::string> loadShaderFile(std::string_view path);

} // namespace ar_overlay