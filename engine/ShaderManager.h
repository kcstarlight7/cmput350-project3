#pragma once

namespace ECSEngine {

class ShaderManager
{
public:
	ShaderManager() = default;
	~ShaderManager() = default;
	void RegisterShader(const std::string& shaderPath, const std::string& shaderName);
	sf::Shader* GetShader(const std::string& shaderName);
private:
	std::unordered_map<std::string, sf::Shader> mShaders;
};

} // namespace ECSEngine