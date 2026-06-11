#pragma once

#include <gst/gst.h>
#include <string>
#include <vector>

namespace ar_overlay {

class GLRenderer {
public:
  GLRenderer() = default;
  ~GLRenderer() = default;

  GLRenderer(const GLRenderer&) = delete;
  GLRenderer& operator=(const GLRenderer&) = delete;
  GLRenderer(GLRenderer&&) noexcept = default;
  GLRenderer& operator=(GLRenderer&&) noexcept = default;

  void configure(GstElement* glshader, const std::string& vertexSrc,
                 const std::string& fragmentSrc);
  void setTextureSize(int width, int height);
  void updateAmplitudes(const std::vector<float>& dBValues);

private:
  static float dBtoLinear(float dB);
  void setUniform1fv(const char* name, const std::vector<float>& values) const;
  void setUniform1f(const char* name, float value) const;

  GstElement* glshader_ = nullptr;
  bool configured_ = false;
};

} // namespace ar_overlay
