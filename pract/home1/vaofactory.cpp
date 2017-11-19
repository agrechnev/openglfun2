#include <cmath>
#include <vector>
#include <iostream>

#include "./vaofactory.h"

using namespace std;

MotokoGL::Vao createRPoly(GLfloat cX, GLfloat cY, GLfloat radX, GLfloat radY, int n)
{
    vector<GLfloat> vertices{cX, cY, 0.0f}; // Center as vertex 0
    vector<GLuint> indices;

    if (n<3 || radX<0 || radY<0)
        throw runtime_error("createRPoly : wrong arguments !");

    vertices.reserve((n+1)*3);
    indices.reserve(3*(n-2));
    GLfloat a = 2*M_PI/n; // Elementary angle
    for (int i = 0; i <n; ++i) {
        GLfloat x = cX - radX*sinf(a*i);
        GLfloat y = cY + radY*cosf(a*i);
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.0f);
        indices.push_back(0); // Center
        indices.push_back(0==i ? n : i);  // Previous vertex
        indices.push_back(i+1);  // Curent vertex
    }
    return MotokoGL::Vao({3}, vertices, indices);
}
