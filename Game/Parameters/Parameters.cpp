#include "pch.h"
#include <windows.h>
#include <commdlg.h>
#include "Game/Parameters/Parameters.h"
#include "Game/Parameters/ParameterKeys.h"
#include <iostream>
#include <fstream>
#include <imgui/imgui.h>


/// <summary>
/// �R���X�g���N�^
/// </summary>
Parameters::Parameters()
    :
    m_parameters{}
{
}

/// <summary>
/// JOSN�f�[�^�����[�h����
/// </summary>
/// <param name="filepath">�t�@�C���p�X</param>
void Parameters::LoadFromJson(const std::string& filepath)
{
    std::ifstream file(filepath);
    if (!file) return;

    json j;
    file >> j;

    m_parameters.clear();

    for (auto& [categoryName, paramGroup] : j.items())
    {
        for (auto& [paramKey, value] : paramGroup.items())
        {
            if (value.is_boolean())
            {
                m_parameters[categoryName][paramKey] = value.get<bool>();
            }
            else if (value.is_number_float())
            {
                m_parameters[categoryName][paramKey] = value.get<float>();
            }
            else if (value.is_number_integer())
            {
                m_parameters[categoryName][paramKey] = value.get<int>();
            }
            else if (value.is_string())
            {
                m_parameters[categoryName][paramKey] = value.get<std::string>();
            }
            else if (value.is_array())
            {
                if (value.size() == 3)
                {
                    m_parameters[categoryName][paramKey] = DirectX::SimpleMath::Vector3(
                        value[0].get<float>(), value[1].get<float>(), value[2].get<float>()
                    );
                }
                else if (value.size() == 4)
                {
                    m_parameters[categoryName][paramKey] = DirectX::SimpleMath::Vector4(
                        value[0].get<float>(), value[1].get<float>(), value[2].get<float>(), value[3].get<float>()
                    );
                }
            }
        }
    }
}

/// <summary>
/// JSON�Ƀp�����[�^��ۑ�
/// </summary>
/// <param name="filepath">�t�@�C���p�X</param>
void Parameters::SaveToJson(const std::string& filepath)
{
    json j;

    for (const auto& [categoryName, paramGroup] : m_parameters)
    {
        for (const auto& [paramKey, paramValue] : paramGroup)
        {
            if (std::holds_alternative<bool>(paramValue))
            {
                j[categoryName][paramKey] = std::get<bool>(paramValue);
            }
            else if (std::holds_alternative<float>(paramValue))
            {
                j[categoryName][paramKey] = std::get<float>(paramValue);
            }
            else if (std::holds_alternative<int>(paramValue))
            {
                j[categoryName][paramKey] = std::get<int>(paramValue);
            }
            else if (std::holds_alternative<std::string>(paramValue))
            {
                j[categoryName][paramKey] = std::get<std::string>(paramValue);
            }
            else if (std::holds_alternative<DirectX::SimpleMath::Vector3>(paramValue))
            {
                const auto& v = std::get<DirectX::SimpleMath::Vector3>(paramValue);
                j[categoryName][paramKey] = { v.x, v.y, v.z };
            }
            else if (std::holds_alternative<DirectX::SimpleMath::Vector4>(paramValue))
            {
                const auto& v = std::get<DirectX::SimpleMath::Vector4>(paramValue);
                j[categoryName][paramKey] = { v.x, v.y, v.z, v.w };
            }
        }
    }

    std::ofstream out(filepath);
    out << j.dump(4);
}


/// <summary>
/// �t�@�C�����J��
/// </summary>
/// <returns>�t�@�C���p�X</returns>
std::string Parameters::OpenFile() const
{
    // �t�@�C�����o�b�t�@
    char fileName[MAX_PATH] = "";

    // �t�@�C���_�C�A���O�\���̂�������
    OPENFILENAMEA ofn = {};
    // �\���̃T�C�Y
    ofn.lStructSize = sizeof(ofn);
    // ���ʂƂ��đI�����ꂽ�t�@�C���p�X������o�b�t�@
    ofn.lpstrFile = fileName;
    // �o�b�t�@�̃T�C�Y
    ofn.nMaxFile = MAX_PATH;

    // �t�@�C���I�����̃t�B���^�[
    ofn.lpstrFilter = "JSON Files\0*.json\0All Files\0*.*\0";
    // �ŏ��̃t�B���^�[���f�t�H���g
    ofn.nFilterIndex = 1;
    // �e�E�B���h�E
    ofn.hwndOwner = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST |  // �p�X�����݂���K�v����
        OFN_FILEMUSTEXIST;          // �t�@�C�������݂���K�v����

    // �t�@�C�����J���_�C�A���O��\�����A�I�����ꂽ�ꍇ�̂݃t�@�C���p�X��Ԃ�
    if (GetOpenFileNameA(&ofn)) {
        return fileName;
    }

    // �L�����Z����G���[���͋󕶎����Ԃ�
    return "";
}


/// <summary>
/// �t�@�C���̕ۑ�����w��
/// </summary>
/// <returns>�t�@�C���p�X</returns>
std::string Parameters::SaveFile() const
{
    char filename[MAX_PATH] = "params.json";
    OPENFILENAMEA ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "JSON Files\0*.json\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

    if (GetSaveFileNameA(&ofn)) {
        return filename;
    }
    return "";
}

/// <summary>
/// �p�����[�^���擾���� int
/// </summary>
/// <param name="key">�L�[</param>
/// <returns>int�l</returns>
int Parameters::GetParameter(const ParametersID& id, const ParameterKeysI& key) const
{
    // enum -> string �ɕϊ�
    std::string idStr = std::string(magic_enum::enum_name(id));
    std::string keyStr = std::string(magic_enum::enum_name(key));

    // �܂��J�e�S��(id)������
    auto catIt = m_parameters.find(idStr);
    if (catIt != m_parameters.end())
    {
        // ���̒��̃L�[������
        auto paramIt = catIt->second.find(keyStr);
        if (paramIt != catIt->second.end() && std::holds_alternative<int>(paramIt->second))
        {
            return std::get<int>(paramIt->second);
        }
    }

    // ���s���F���S�ȃf�t�H���g
    return 0;
}

/// <summary>
/// �p�����[�^���擾���� float
/// </summary>
/// <param name="key">�L�[</param>
/// <returns>float�l</returns>
float Parameters::GetParameter(const ParametersID& id, const ParameterKeysF& key) const
{
    std::string idStr = std::string(magic_enum::enum_name(id));
    std::string keyStr = std::string(magic_enum::enum_name(key));

    auto catIt = m_parameters.find(idStr);
    if (catIt != m_parameters.end())
    {
        auto paramIt = catIt->second.find(keyStr);
        if (paramIt != catIt->second.end() && std::holds_alternative<float>(paramIt->second))
        {
            return std::get<float>(paramIt->second);
        }
    }

    return 0.0f;
}

/// <summary>
/// �p�����[�^���擾���� bool
/// </summary>
/// <param name="key">�L�[</param>
/// <returns>bool�l</returns>
bool Parameters::GetParameter(const ParametersID& id, const ParameterKeysB& key) const
{
    std::string idStr = std::string(magic_enum::enum_name(id));
    std::string keyStr = std::string(magic_enum::enum_name(key));

    auto catIt = m_parameters.find(idStr);
    if (catIt != m_parameters.end())
    {
        auto paramIt = catIt->second.find(keyStr);
        if (paramIt != catIt->second.end() && std::holds_alternative<bool>(paramIt->second))
        {
            return std::get<bool>(paramIt->second);
        }
    }

    return false;
}

/// <summary>
/// �p�����[�^���擾���� string
/// </summary>
/// <param name="key">�L�[</param>
/// <returns>string�l</returns>
std::string Parameters::GetParameter(const ParametersID& id, const ParameterKeysS& key) const
{
    std::string idStr = std::string(magic_enum::enum_name(id));
    std::string keyStr = std::string(magic_enum::enum_name(key));

    auto catIt = m_parameters.find(idStr);
    if (catIt != m_parameters.end())
    {
        auto paramIt = catIt->second.find(keyStr);
        if (paramIt != catIt->second.end() && std::holds_alternative<std::string>(paramIt->second))
        {
            return std::get<std::string>(paramIt->second);
        }
    }

    return "";
}

/// <summary>
/// �p�����[�^���擾���� Vector3
/// </summary>
/// <param name="key">�L�[</param>
/// <returns>Vector3�l</returns>
DirectX::SimpleMath::Vector3 Parameters::GetParameter(const ParametersID& id, const ParameterKeysV3& key) const
{
    std::string idStr = std::string(magic_enum::enum_name(id));
    std::string keyStr = std::string(magic_enum::enum_name(key));

    auto catIt = m_parameters.find(idStr);
    if (catIt != m_parameters.end())
    {
        auto paramIt = catIt->second.find(keyStr);
        if (paramIt != catIt->second.end() && std::holds_alternative<DirectX::SimpleMath::Vector3>(paramIt->second))
        {
            return std::get<DirectX::SimpleMath::Vector3>(paramIt->second);
        }
    }

    return DirectX::SimpleMath::Vector3::Zero;
}

/// <summary>
/// �p�����[�^���擾���� Vector4
/// </summary>
/// <param name="key">�L�[</param>
/// <returns>Vector4�l</returns>
DirectX::SimpleMath::Vector4 Parameters::GetParameter(const ParametersID& id, const ParameterKeysV4& key) const
{
    std::string idStr = std::string(magic_enum::enum_name(id));
    std::string keyStr = std::string(magic_enum::enum_name(key));

    auto catIt = m_parameters.find(idStr);
    if (catIt != m_parameters.end())
    {
        auto paramIt = catIt->second.find(keyStr);
        if (paramIt != catIt->second.end() && std::holds_alternative<DirectX::SimpleMath::Vector4>(paramIt->second))
        {
            return std::get<DirectX::SimpleMath::Vector4>(paramIt->second);
        }
    }

    return DirectX::SimpleMath::Vector4::Zero;
}


/// <summary>
/// �f�o�b�O�E�B���h�E
/// </summary>
void Parameters::ShowImGuiEditor() 
{

    // UI�ێ��p
    static int selectedCategoryIndex = 0;
    static char newCategoryName[64] = "";

    // �����J�e�S���ꗗ��vector�ɂ���
    std::vector<std::string> categoryList;
    for (auto& [catName, _] : m_parameters) {
        categoryList.push_back(catName);
    }


    ImGui::Begin("Parameter Editor", nullptr, ImGuiWindowFlags_MenuBar);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::Button("Load")) 
        {
            const std::string path = this->OpenFile();
            if (!path.empty()) LoadFromJson(path);
        }
        ImGui::SameLine();
        if (ImGui::Button("Save"))
        {
            const std::string path = this->SaveFile();
            if (!path.empty()) SaveToJson(path);
        }

        ImGui::EndMenuBar();
    }

    // �^�u�J�n
    if (ImGui::BeginTabBar("ParameterTabs")) {

        // -------- View�^�u
        if (ImGui::BeginTabItem("View")) {
            if (!categoryList.empty()) {
                // �J�e�S���I��
                std::vector<const char*> catItems;
                for (const auto& str : categoryList) catItems.push_back(str.c_str());

                ImGui::Combo("Category", &selectedCategoryIndex, catItems.data(), catItems.size());

                // �I���J�e�S���̃p�����[�^��\��
                const auto& selectedCategory = categoryList[selectedCategoryIndex];
                for (auto& [paramName, paramValue] : m_parameters[selectedCategory]) {
                    if (std::holds_alternative<float>(paramValue))
                        ImGui::Text("%s : %.2f", paramName.c_str(), std::get<float>(paramValue));
                    else if (std::holds_alternative<int>(paramValue))
                        ImGui::Text("%s : %d", paramName.c_str(), std::get<int>(paramValue));
                    else if (std::holds_alternative<DirectX::SimpleMath::Vector3>(paramValue)) {
                        auto v = std::get<DirectX::SimpleMath::Vector3>(paramValue);
                        ImGui::Text("%s : (%.2f, %.2f, %.2f)", paramName.c_str(), v.x, v.y, v.z);
                    }
                }
            }
            ImGui::EndTabItem();
        }

        // -------- Edit�^�u
        if (ImGui::BeginTabItem("Edit")) {
            if (!categoryList.empty()) {
                std::vector<const char*> catItems;
                for (const auto& str : categoryList) catItems.push_back(str.c_str());

                ImGui::Combo("Category", &selectedCategoryIndex, catItems.data(), catItems.size());

                const auto& selectedCategory = categoryList[selectedCategoryIndex];
                for (auto& [paramName, paramValue] : m_parameters[selectedCategory]) {
                    if (std::holds_alternative<float>(paramValue)) {
                        float v = std::get<float>(paramValue);
                        if (ImGui::SliderFloat(paramName.c_str(), &v, -1000.0f, 1000.0f)) paramValue = v;
                    }
                    else if (std::holds_alternative<int>(paramValue)) {
                        int v = std::get<int>(paramValue);
                        if (ImGui::SliderInt(paramName.c_str(), &v, -1000, 1000)) paramValue = v;
                    }
                    else if (std::holds_alternative<DirectX::SimpleMath::Vector3>(paramValue)) {
                        auto v = std::get<DirectX::SimpleMath::Vector3>(paramValue);
                        if (ImGui::SliderFloat3(paramName.c_str(), &v.x, -1000.0f, 1000.0f)) paramValue = v;
                    }
                }
            }
            ImGui::EndTabItem();
        }

        // --- UI�p�ێ��ϐ�
        static bool isNewCategory = false;
        static int selectedCategoryIndex = 0;
        static char newCategoryName[64] = "";

        static char newParamName[64] = "";
        static int newTypeIndex = 0;
        static float floatVal = 0.0f;
        static int intVal = 0;
        static DirectX::SimpleMath::Vector3 vec3Val(0, 0, 0);

        // --- �����J�e�S�����X�g
        std::vector<std::string> categoryList;
        for (auto& [catName, _] : m_parameters) {
            categoryList.push_back(catName);
        }

        // --- �`��J�n
        if (ImGui::BeginTabItem("Add"))
        {
            // �V�K�J�e�S�����ǂ����I��
            ImGui::Checkbox("New Category", &isNewCategory);

            // �V�K�J�e�S��
            if (isNewCategory) {
                ImGui::InputText("New Category Name", newCategoryName, sizeof(newCategoryName));
            }
            // �����J�e�S��
            else if (!categoryList.empty()) {
                std::vector<const char*> catItems;
                for (const auto& str : categoryList) catItems.push_back(str.c_str());

                ImGui::Combo("Select Existing Category", &selectedCategoryIndex, catItems.data(), catItems.size());
            }

            // �p�����[�^���ƌ^�E�l����
            ImGui::InputText("Parameter Name", newParamName, sizeof(newParamName));
            const char* types[] = { "float", "int", "Vector3" };
            ImGui::Combo("Type", &newTypeIndex, types, IM_ARRAYSIZE(types));

            if (newTypeIndex == 0) ImGui::InputFloat("Value (float)", &floatVal);
            else if (newTypeIndex == 1) ImGui::InputInt("Value (int)", &intVal);
            else if (newTypeIndex == 2) ImGui::InputFloat3("Value (Vector3)", &vec3Val.x);

            // Add�{�^����������ǉ�
            if (ImGui::Button("Add Parameter"))
            {
                std::string category;
                if (isNewCategory && strlen(newCategoryName) > 0) {
                    category = std::string(newCategoryName);
                }
                else if (!isNewCategory && !categoryList.empty()) {
                    category = categoryList[selectedCategoryIndex];
                }

                if (!category.empty() && strlen(newParamName) > 0)
                {
                    std::string param(newParamName);

                    if (newTypeIndex == 0)
                        m_parameters[category][param] = floatVal;
                    else if (newTypeIndex == 1)
                        m_parameters[category][param] = intVal;
                    else if (newTypeIndex == 2)
                        m_parameters[category][param] = vec3Val;

                    // ���̓��Z�b�g
                    std::memset(newCategoryName, 0, sizeof(newCategoryName));
                    std::memset(newParamName, 0, sizeof(newParamName));
                }
            }

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}


