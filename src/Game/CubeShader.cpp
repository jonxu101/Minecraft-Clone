#include <Game/CubeShader.h>

#include <fstream>
#include <iostream>

const std::string IN_PATH = "../resources/shaders/basic.shader";
const std::string OUT_PATH = "../resources/shaders/out/block_basic.shader";

void CubeShader::GenShader(int numTextures) {
    std::cout << "Generating Cube Shader!" << std::endl;
    std::ifstream inFile(IN_PATH);
    std::ofstream outFile(OUT_PATH);
    std::string buffer;

    int lineNum = 0;

    while (std::getline(inFile, buffer)) {
        // if (lineNum == 16) {
        //     outFile << buffer << std::to_string(numTextures) << ".0);\n";
        //     lineNum++;
        //     continue;
        // }
        outFile << buffer << "\n";
        lineNum++;
    }
}

CubeShader::CubeShader() : Shader(OUT_PATH) {
    std::cout << "CubeShader: init" << std::endl;
}

CubeShader::~CubeShader() {}