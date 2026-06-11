/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <samuel@hurtadom.dev>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:07:27 by shurtado          #+#    #+#             */
/*   Updated: 2026/06/11 15:07:33 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.hpp"

#include <cmath>
#include <iostream>

namespace ar_overlay {

void GLRenderer::configure(GstElement* glshader, const std::string& /*vertexSrc*/,
                           const std::string& /*fragmentSrc*/) {
  glshader_ = glshader;

  g_object_set(G_OBJECT(glshader_),
    "fragment",
    "#version 100\n"
    "#ifdef GL_ES\n"
    "precision mediump float;\n"
    "#endif\n"
    "varying vec2 v_texcoord;\n"
    "uniform sampler2D tex;\n"
    "uniform float u_a0;\n"
    "uniform float u_a1;\n"
    "uniform float u_a2;\n"
    "uniform float u_a3;\n"
    "uniform float u_a4;\n"
    "uniform float u_a5;\n"
    "uniform float u_a6;\n"
    "uniform float u_a7;\n"
    "uniform float u_a8;\n"
    "uniform float u_a9;\n"
    "uniform float u_a10;\n"
    "uniform float u_a11;\n"
    "uniform float u_a12;\n"
    "uniform float u_a13;\n"
    "uniform float u_a14;\n"
    "uniform float u_a15;\n"
    "uniform float u_texel_x;\n"
    "uniform float u_texel_y;\n"
    "uniform float u_blur;\n"
    "vec3 neonColor(int band) {\n"
    "  if (band==0)  return vec3(0.0,1.0,1.0);\n"
    "  if (band==1)  return vec3(0.2,0.8,1.0);\n"
    "  if (band==2)  return vec3(0.2,1.0,0.4);\n"
    "  if (band==3)  return vec3(0.5,1.0,0.0);\n"
    "  if (band==4)  return vec3(1.0,1.0,0.0);\n"
    "  if (band==5)  return vec3(1.0,0.7,0.0);\n"
    "  if (band==6)  return vec3(1.0,0.4,0.0);\n"
    "  if (band==7)  return vec3(1.0,0.1,0.1);\n"
    "  if (band==8)  return vec3(1.0,0.0,0.5);\n"
    "  if (band==9)  return vec3(0.8,0.0,1.0);\n"
    "  if (band==10) return vec3(0.5,0.0,1.0);\n"
    "  if (band==11) return vec3(0.3,0.0,1.0);\n"
    "  if (band==12) return vec3(0.0,0.3,1.0);\n"
    "  if (band==13) return vec3(0.0,0.6,1.0);\n"
    "  if (band==14) return vec3(0.0,0.9,0.8);\n"
    "  return vec3(0.0,1.0,1.0);\n"
    "}\n"
    "void main(void) {\n"
    "  float colW = 1.0/16.0;\n"
    "  int band = int(floor(v_texcoord.x/colW));\n"
    "  if (band<0) band=0; if (band>15) band=15;\n"
    "  float posInCol = (v_texcoord.x-float(band)*colW)/colW;\n"
    "  float gapMargin = 0.08;\n"
    "  if (posInCol<gapMargin || posInCol>(1.0-gapMargin)) { gl_FragColor=texture2D(tex,v_texcoord); return; }\n"
    "  float a;\n"
    "  if      (band==0)  a=u_a0;\n"
    "  else if (band==1)  a=u_a1;\n"
    "  else if (band==2)  a=u_a2;\n"
    "  else if (band==3)  a=u_a3;\n"
    "  else if (band==4)  a=u_a4;\n"
    "  else if (band==5)  a=u_a5;\n"
    "  else if (band==6)  a=u_a6;\n"
    "  else if (band==7)  a=u_a7;\n"
    "  else if (band==8)  a=u_a8;\n"
    "  else if (band==9)  a=u_a9;\n"
    "  else if (band==10) a=u_a10;\n"
    "  else if (band==11) a=u_a11;\n"
    "  else if (band==12) a=u_a12;\n"
    "  else if (band==13) a=u_a13;\n"
    "  else if (band==14) a=u_a14;\n"
    "  else               a=u_a15;\n"
    "  float amp = clamp(a,0.0,1.0);\n"
    "  amp = max(amp,0.08);\n"
    "  float yb = 1.0 - v_texcoord.y;\n"
    "  if (yb >= amp) { gl_FragColor=texture2D(tex,v_texcoord); return; }\n"
    "  vec3 ncol = neonColor(band);\n"
    "  vec4 blurred = vec4(0.0);\n"
    "  float total = 0.0;\n"
    "  for (float x=-2.0; x<=2.0; x+=1.0) {\n"
    "    for (float y=-2.0; y<=2.0; y+=1.0) {\n"
    "      vec2 off = vec2(x*u_texel_x*u_blur, y*u_texel_y*u_blur);\n"
    "      blurred += texture2D(tex, v_texcoord+off);\n"
    "      total += 1.0;\n"
    "    }\n"
    "  }\n"
    "  blurred /= total;\n"
    "  float edgeV = 0.02;\n"  // vertical edge in screen coords
    "  float edgeH = edgeV * 16.0;\n"  // horizontal in column-local coords
    "  float distTop = amp - yb;\n"
    "  float distBot = yb;\n"
    "  float distLeft = (posInCol - gapMargin) / (1.0 - 2.0*gapMargin);\n"
    "  float distRight = 1.0 - distLeft;\n"
    "  float edgeT = distTop < edgeV ? 1.0 - distTop/edgeV : 0.0;\n"
    "  float edgeB = distBot < edgeV ? 1.0 - distBot/edgeV : 0.0;\n"
    "  float edgeL = distLeft < edgeH ? 1.0 - distLeft/edgeH : 0.0;\n"
    "  float edgeR = distRight < edgeH ? 1.0 - distRight/edgeH : 0.0;\n"
    "  float edgeMax = max(max(edgeT, edgeB), max(edgeL, edgeR));\n"
    "  if (edgeMax > 0.0) {\n"
    "    gl_FragColor = mix(blurred, vec4(ncol,1.0), edgeMax*0.65);\n"
    "  } else {\n"
    "    gl_FragColor = blurred * vec4(mix(vec3(1.0), ncol, 0.12), 1.0);\n"
    "  }\n"
    "}\n",
    nullptr);

  configured_ = true;
}

void GLRenderer::setTextureSize(int width, int height) {
  width_ = width;
  height_ = height;
}

void GLRenderer::updateAmplitudes(const std::vector<float>& dBValues) {
  if (!configured_ || dBValues.empty()) return;

  GstStructure* s = gst_structure_new_empty("uniforms");
  const char* names[] = {
    "u_a0","u_a1","u_a2","u_a3","u_a4","u_a5","u_a6","u_a7",
    "u_a8","u_a9","u_a10","u_a11","u_a12","u_a13","u_a14","u_a15"
  };

  for (int i = 0; i < 16 && i < (int)dBValues.size(); ++i) {
    float val = dBtoLinear(dBValues[i]);
    gst_structure_set(s, names[i], G_TYPE_FLOAT, val, NULL);
  }

  gst_structure_set(s, "u_texel_x", G_TYPE_FLOAT,
                    1.0f / static_cast<float>(width_),
                    "u_texel_y", G_TYPE_FLOAT,
                    1.0f / static_cast<float>(height_),
                    "u_blur", G_TYPE_FLOAT, 15.0f, NULL);

  g_object_set(G_OBJECT(glshader_), "uniforms", s, NULL);
  g_object_set(G_OBJECT(glshader_), "update-shader", TRUE, NULL);
  gst_structure_free(s);
}

float GLRenderer::dBtoLinear(float dB) {
  if (dB <= -60.0f) return 0.0f;
  if (dB >= 0.0f) return 1.0f;
  return (dB + 60.0f) / 60.0f;
}

} // namespace ar_overlay
