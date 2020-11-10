#include "Shader.h"
#include "GL/glew.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"


/// <summary>
/// Constructs a shader object
/// </summary>
/// <param name="filepath">The filepath to the shader resource</param>
Shader::Shader(const std::string& filepath)
	: m_FilePath(filepath), m_RendererID(0)
{
    //Parses the data necessary for a shader
    ShaderProgramSource source = ParseShader(filepath);

    //Creats the shader in OpenGL and stores its id
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource, source.GeometrySource);
}

/// <summary>
/// Deletes the shader
/// </summary>
Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

/// <summary>
/// Parses the shader into different shader types. Allows for vertex and fragment shaders to be in the same file
/// </summary>
/// <param name="filePath">The file path to the shader resource</param>
/// <returns>A struct containing the parsed source code of each of the individual shader types</returns>
ShaderProgramSource Shader::ParseShader(const std::string& filePath) {
    std::ifstream stream(filePath);

    //Used for deciding what shader is being created at any given point
    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1,
        GEOMETRY = 2
    };

    std::string line;
    std::stringstream ss[3];

    ShaderType type = ShaderType::NONE;

    //Keeps looping until the file is empty
    while (getline(stream, line)) {
        //Changes the type of shader being created based on the text in the shader source
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
            else if (line.find("geometry") != std::string::npos) {
                type = ShaderType::GEOMETRY;
            }
        }
        else
        {
            //Adds the line to the shader
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str(), ss[2].str()};
}

/// <summary>
/// Compiles the shader source code into shaders that OpenGL know how to use
/// </summary>
/// <param name="type">The type of shader being compiled using OpenGL types</param>
/// <param name="source">The source code of the shader to compile</param>
/// <returns>The id of the shader</returns>
unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    //Creates the location of the shader
    unsigned int id = glCreateShader(type);
    //Sets up the string as a c str
    const char* src = source.c_str();
    //Sets the source code of the shader
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    //Gets the result of the compilation
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

    //Checks if the shader compiled properly
    if (result == GL_FALSE) {

        //Gets the length of the message
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

        //Gets the error message
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));

        std::cout << "Failed to compile " <<
            (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << " shader!" << std::endl;

        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));

        return 0;
    }

    //Returns the location of the compiled shader
    return id;
}

/// <summary>
/// Creates the shader object from the source code passed in
/// </summary>
/// <param name="vertexShader">Source code of the vertex shader</param>
/// <param name="fragmentShader">Source code of the fragment shader</param>
/// <param name="geometryShader">Source code of the geometry shader</param>
/// <returns>The id of the shader program</returns>
unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader)
{
    unsigned int program = glCreateProgram();
    //Compiles the vertex shader code
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    //Compiles the fragment shader code
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    //Attaches the vertex and frag shaders to the program
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));

    //Checks if the geometry shader exists for this shader
    if (geometryShader != "")
    {
        unsigned int gs = CompileShader(GL_GEOMETRY_SHADER, geometryShader);
        GLCall(glAttachShader(program, gs));
    }

    //Links the program
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    //Unnecessary to leave shaders in the code as they
    //have already been attached to the program
    GLCall(glDetachShader(program, vs));
    GLCall(glDetachShader(program, fs));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

/// <summary>
/// Binds this shader's program to be the one used
/// </summary>
void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

/// <summary>
/// UnBinds this shader's program
/// </summary>
void Shader::UnBind() const
{
    GLCall(glUseProgram(0));
}

/// <summary>
/// Sets the one int uniform of the specified names value to the specified value
/// </summary>
/// <param name="name">The name of the uniform</param>
/// <param name="value">The value to set the uniform equal</param>
void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocations(name), value));
}

/// <summary>
/// Sets the one float uniform of the specified names value to the specified value
/// </summary>
/// <param name="name">The name of the uniform</param>
/// <param name="value">The value to set the uniform equal</param>
void Shader::SetUniform1f(const std::string& name, float value)
{
    GLCall(glUniform1f(GetUniformLocations(name), value));
}

/// <summary>
/// Sets the for float values of the uniform of the specified name to the specified value
/// </summary>
/// <param name="name">Name of the uniform</param>
/// <param name="v0">First float value to store</param>
/// <param name="v1">Second float value to store</param>
/// <param name="v2">Third float value to store</param>
/// <param name="v3">Fourth float value to store</param>
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocations(name), v0, v1, v2, v3));
}

/// <summary>
/// Sets the for float values of the matrix uniform of the specified name to the specified value
/// </summary>
/// <param name="name">Name of the matrix uniform</param>
/// <param name="v0">First float value to store</param>
/// <param name="v1">Second float value to store</param>
/// <param name="v2">Third float value to store</param>
/// <param name="v3">Fourth float value to store</param>
void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocations(name), 1, GL_FALSE, &matrix[0][0]));
}

/// <summary>
/// Gets the location of the uniform in the shader program
/// </summary>
/// <param name="name">The name of the uniform to find</param>
/// <returns>The location of the specified uniform</returns>
int Shader::GetUniformLocations(const std::string& name) const
{
    //Checks if the uniform is already cached
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    {
        return m_UniformLocationCache[name];
    }

    //Gets the location
    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));

    //Makes sure the uniform exists
    if (location == -1)
    {
        std::cout << "Warning: uniform '" << name << "' doesn't exist" << std::endl;
    }

    //Adds the location to the cache
    m_UniformLocationCache[name] = location;
	return location;
}
