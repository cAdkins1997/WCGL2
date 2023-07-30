//
// Created by ulver on 7/16/2023.
//

#ifndef OPENGLRENDERER_SHADER_H
#define OPENGLRENDERER_SHADER_H

#include "../headers/common.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {

public:

    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);

    void use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 value) const;
    void setMat3(const std::string &name, glm::mat3 value) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif //OPENGLRENDERER_SHADER_H
