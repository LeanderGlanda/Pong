#include "Main.h"
#include <fstream>
#include <sstream>

std::string readShaderCode(const char* filename)
{
    std::string computeCode;
    std::ifstream cShaderFile;

    cShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        cShaderFile.open(filename);
        std::stringstream cShaderStream;
        cShaderStream << cShaderFile.rdbuf();
        cShaderFile.close();
        computeCode = cShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n" << e.what() << std::endl;
    }
    return computeCode;
}

GLuint createShader(const char* vertexFilename, const char* fragmentFilename)
{
    CHECK_ERROR();

    // create the compute shader
    // Read the source code of the shader
    std::string vShaderCode = readShaderCode(vertexFilename);
    std::string fShaderCode = readShaderCode(fragmentFilename);

    const char* vertexShaderCode = vShaderCode.c_str();
    const char* fragmentShaderCode = fShaderCode.c_str();

    GLuint shaderProgram = glCreateProgram();
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vs, 1, &vertexShaderCode, NULL);
    glShaderSource(fs, 1, &fragmentShaderCode, NULL);

    glCompileShader(vs);
    int rvalue;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &rvalue);
    if (!rvalue) {
        fprintf(stderr, "Error in compiling the compute shader\n");
        GLchar* log = new GLchar[10240];
        GLsizei length;
        glGetShaderInfoLog(vs, 10239, &length, log);
        fprintf(stderr, "Compiler log:\n%s\n", log);
        delete[] log;
        exit(40);
    }
    glAttachShader(shaderProgram, vs);

    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &rvalue);
    if (!rvalue) {
        fprintf(stderr, "Error in compiling the compute shader\n");
        GLchar* log = new GLchar[10240];
        GLsizei length;
        glGetShaderInfoLog(fs, 10239, &length, log);
        fprintf(stderr, "Compiler log:\n%s\n", log);
        delete[] log;
        exit(40);
    }
    glAttachShader(shaderProgram, fs);


    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &rvalue);
    if (!rvalue) {
        fprintf(stderr, "Error in linking compute shader program\n");
        GLchar* log = new GLchar[10240];
        GLsizei length;
        glGetProgramInfoLog(shaderProgram, 10239, &length, log);
        fprintf(stderr, "Linker log:\n%s\n", log);
        delete[] log;
        exit(41);
    }
    glDeleteShader(vs);
    glDeleteShader(fs);
    return shaderProgram;
}