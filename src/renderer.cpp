#include "renderer.hpp"

#include <gst/gl/gstglshader.h>

#include <cmath>
#include <iostream>

namespace ar_overlay {

void GLRenderer::configure(GstElement* glshader, const std::string& vertexSrc,
                           const std::string& fragmentSrc) {
  glshader_ = glshader;

  g_object_set(G_OBJECT(glshader_),
    "vertex", vertexSrc.c_str(),
    "fragment", fragmentSrc.c_str(),
    nullptr);

  configured_ = true;
}

void GLRenderer::setTextureSize(int width, int height) {
  if (!configured_) return;

  GstGLShader* shader = nullptr;
  g_object_get(G_OBJECT(glshader_), "shader", &shader, nullptr);
  if (!shader) return;

  float texel[2] = { 1.0f / static_cast<float>(width),
                     1.0f / static_cast<float>(height) };
  gst_gl_shader_set_uniform_2fv(shader, "u_texel_size", 1, texel);
  gst_gl_shader_set_uniform_1f(shader, "u_blur_radius", 12.0f);

  gst_object_unref(shader);
}

void GLRenderer::updateAmplitudes(const std::vector<float>& dBValues) {
  if (!configured_) return;

  GstGLShader* shader = nullptr;
  g_object_get(G_OBJECT(glshader_), "shader", &shader, nullptr);
  if (!shader) return;

  std::vector<float> linear(dBValues.size());
  for (std::size_t i = 0; i < dBValues.size(); ++i) {
    linear[i] = dBtoLinear(dBValues[i]);
  }

  gst_gl_shader_set_uniform_1fv(shader, "u_amplitudes",
                                linear.size(), linear.data());

  gst_object_unref(shader);
}

float GLRenderer::dBtoLinear(float dB) {
  if (dB <= -60.0f) return 0.0f;
  if (dB >= 0.0f) return 1.0f;
  return std::pow(10.0f, dB / 20.0f);
}

void GLRenderer::setUniform1fv(const char* name,
                               const std::vector<float>& values) const {
  if (!configured_) return;

  GstGLShader* shader = nullptr;
  g_object_get(G_OBJECT(glshader_), "shader", &shader, nullptr);
  if (!shader) return;

  gst_gl_shader_set_uniform_1fv(shader, name, values.size(), values.data());

  gst_object_unref(shader);
}

void GLRenderer::setUniform1f(const char* name, float value) const {
  if (!configured_) return;

  GstGLShader* shader = nullptr;
  g_object_get(G_OBJECT(glshader_), "shader", &shader, nullptr);
  if (!shader) return;

  gst_gl_shader_set_uniform_1f(shader, name, value);

  gst_object_unref(shader);
}

} // namespace ar_overlay
