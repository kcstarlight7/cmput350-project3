#pragma once

#include <SFML/Graphics.hpp>

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

void ShaderManager::RegisterShader(const std::string& shaderPath, const std::string& shaderName) {
    mShaders[shaderName] = sf::Shader(std::filesystem::path{shaderPath}, sf::Shader::Type::Fragment);
};

sf::Shader* ShaderManager::GetShader(const std::string& shaderName) { return &mShaders[shaderName]; }

} // namespace ECSEngine