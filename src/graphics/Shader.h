#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

/// <summary>
/// Struct that stores the source code of the different shader types
/// </summary>
struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
	std::string GeometrySource;
};

class Shader
{
private:
	//File path of the shader
	std::string m_FilePath;
	unsigned int m_RendererID;

	//A cache that saves time looking for uniforms in shaders
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	ShaderProgramSource ParseShader(const std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader);
	int GetUniformLocations(const std::string& name) const;
};