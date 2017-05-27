#pragma once
// By Oleksiy Grechnyev

#include "./Tex.h"

namespace MotokoGL {

/// Material properties with textures
struct MaterialT{

    /// Constructor
    MaterialT(const Tex & ambient,
              const Tex & diffuse,
              const Tex & specular,
              const Tex & emission,
              float shininess) :
        ambient(ambient),
        diffuse(diffuse),
        specular(specular),
        emission(emission),
        shininess(shininess) {}

    /// Textures
    Tex ambient;
    Tex diffuse;
    Tex specular;
    Tex emission;
    float shininess;
};
}
