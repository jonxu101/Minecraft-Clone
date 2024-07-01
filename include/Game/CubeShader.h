#pragma once

#include <Graphics/Shader.h>

class CubeShader : public Shader {
public:

    CubeShader();
    ~CubeShader();
    
    static void GenShader(int numTextures);
};