/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <samuel@hurtadom.dev>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 10:08:26 by shurtado          #+#    #+#             */
/*   Updated: 2026/06/09 10:08:27 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gst/gst.h>

#include <filesystem>
#include <iostream>

#include "pipeline.hpp"

int main(int argc, char* argv[]) {
  gst_init(&argc, &argv);

  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <media-file>\n";
    return 1;
  }

  std::filesystem::path filePath(argv[1]);
  if (!std::filesystem::exists(filePath)) {
    std::cerr << "File not found: " << filePath << '\n';
    return 1;
  }
  if (!std::filesystem::is_regular_file(filePath)) {
    std::cerr << "Not a regular file: " << filePath << '\n';
    return 1;
  }

  try {
    ar_overlay::Pipeline pipeline(filePath.native());
    if (!pipeline.run()) {
      return 1;
    }
  } catch (const std::exception& e) {
    std::cerr << "Fatal error: " << e.what() << '\n';
    return 1;
  }

  return 0;
}
