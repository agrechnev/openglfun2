#pragma once

// By Oleksiy Grechnyev
// Work with textures

#include <string>

#include "./glheader.h"

namespace MotokoGL {
    /// Load texture from file
    GLuint loadTexture(const std::string & fileName);

}
