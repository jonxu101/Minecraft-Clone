#pragma once

#include <Graphics/Shader.h>

class BlockShader : Shader {
    Shader shader_;

    BlockShader(int numTextures);

    void Bind();
    void Unbind();
};