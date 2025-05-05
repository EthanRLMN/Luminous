#pragma once

class ModelComponent 
{
public:
    inline void SetModelPath(const std::string& a_path) { m_modelPath = a_path; }
    [[nodiscard]] inline const std::string& GetModelPath() const { return m_modelPath; }


private:
    std::string m_modelPath { };
};
