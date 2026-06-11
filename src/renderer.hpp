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
  void setSmoothing(float alpha) { smoothingAlpha_ = alpha; }
  void updateAmplitudes(const std::vector<float>& dBValues);

private:
  static float dBtoLinear(float dB);

  GstElement* glshader_ = nullptr;
  float smoothingAlpha_ = 0.3f;
  int width_ = 0;
  int height_ = 0;
  bool configured_ = false;
};

} // namespace ar_overlay
