
#include <SOIL.h>

#include "./fatal.h"

#include "./texture.h"

namespace MotokoGL {

GLuint loadTexture(const std::string &fileName)
{
    // Create and bind texture objects
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image from a file with SOIL
    int imageWidth, imageHeight;
    unsigned char* image = SOIL_load_image(fileName.c_str(),  &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB);

    if (image==NULL)
        fatal2("loadTexture() : Cannot load image ", fileName.c_str());

    // Set up the image
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free memory and unbind
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}


}
