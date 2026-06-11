#pragma once

#include <string_view>

#include <gst/gst.h>

namespace ar_overlay {

inline void logError(std::string_view msg) {
  g_printerr("ERROR: %.*s\n", static_cast<int>(msg.size()), msg.data());
}

inline void logWarning(std::string_view msg) {
  g_printerr("WARNING: %.*s\n", static_cast<int>(msg.size()), msg.data());
}

inline void logInfo(std::string_view msg) {
  g_print("INFO: %.*s\n", static_cast<int>(msg.size()), msg.data());
}

} // namespace ar_overlay
