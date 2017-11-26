#pragma once
// By Oleksiy Grechnyev
// Create various VAOs

#include "MotokoGL.h"

/// Create a regular polygon
MotokoGL::Vao createRPoly(GLfloat cX, GLfloat cY, GLfloat radX, GLfloat radY, int n);

/// Create a regular polygon with texture coords
MotokoGL::Vao createRPolyTex(GLfloat cX, GLfloat cY, GLfloat radX, GLfloat radY, int n);
