#include "pch.h"
#include <windows.h>
#include <commdlg.h>
#include "Game/Parameters/Parameters.h"
#include "Game/Parameters/ParameterKeys.h"
#include <iostream>
#include <fstream>
#include <imgui/imgui.h>


/// <summary>
/// コンストラクタ
/// </summary>
Parameters::Parameters()
    :
    m_parameters{}
{
}

/// <summary>
/// JOSNデータをロードする
/// </summary>
/// <param name="filepath">ファイルパス</param>
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
/// JSONにパラメータを保存
/// </summary>
/// <param name="filepath">ファイルパス</param>
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
/// ファイルを開く
/// </summary>
/// <returns>ファイルパス</returns>
std::string Parameters::OpenFile() const
{
    // ファイル名バッファ
    char fileName[MAX_PATH] = "";

    // ファイルダイアログ構造体を初期化
    OPENFILENAMEA ofn = {};
    // 構造体サイズ
    ofn.lStructSize = sizeof(ofn);
    // 結果として選択されたファイルパスが入るバッファ
    ofn.lpstrFile = fileName;
    // バッファのサイズ
    ofn.nMaxFile = MAX_PATH;

    // ファイル選択時のフィルター
    ofn.lpstrFilter = "JSON Files\0*.json\0All Files\0*.*\0";
    // 最初のフィルターをデフォルト
    ofn.nFilterIndex = 1;
    // 親ウィンドウ
    ofn.hwndOwner = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST |  // パスが存在する必要あり
        OFN_FILEMUSTEXIST;          // ファイルが存在する必要あり

    // ファイルを開くダイアログを表示し、選択された場合のみファイルパスを返す
    if (GetOpenFileNameA(&ofn)) {
        return fileName;
    }

    // キャンセルやエラー時は空文字列を返す
    return "";
}


/// <summary>
/// ファイルの保存先を指定
/// </summary>
/// <returns>ファイルパス</returns>
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
/// パラメータを取得する int
/// </summary>
/// <param name="key">キー</param>
/// <returns>int値</returns>
int Parameters::GetParameter(const ParametersID& id, const ParameterKeysI& key) const
{
    // enum -> string に変換
    std::string idStr = std::string(magic_enum::enum_name(id));
    std::string keyStr = std::string(magic_enum::enum_name(key));

    // まずカテゴリ(id)を検索
    auto catIt = m_parameters.find(idStr);
    if (catIt != m_parameters.end())
    {
        // その中のキーを検索
        auto paramIt = catIt->second.find(keyStr);
        if (paramIt != catIt->second.end() && std::holds_alternative<int>(paramIt->second))
        {
            return std::get<int>(paramIt->second);
        }
    }

    // 失敗時：安全なデフォルト
    return 0;
}

/// <summary>
/// パラメータを取得する float
/// </summary>
/// <param name="key">キー</param>
/// <returns>float値</returns>
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
/// パラメータを取得する bool
/// </summary>
/// <param name="key">キー</param>
/// <returns>bool値</returns>
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
/// パラメータを取得する string
/// </summary>
/// <param name="key">キー</param>
/// <returns>string値</returns>
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
/// パラメータを取得する Vector3
/// </summary>
/// <param name="key">キー</param>
/// <returns>Vector3値</returns>
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
/// パラメータを取得する Vector4
/// </summary>
/// <param name="key">キー</param>
/// <returns>Vector4値</returns>
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
/// デバッグウィンドウ
/// </summary>
void Parameters::ShowImGuiEditor() 
{

    // UI保持用
    static int selectedCategoryIndex = 0;
    static char newCategoryName[64] = "";

    // 既存カテゴリ一覧をvectorにする
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

    // タブ開始
    if (ImGui::BeginTabBar("ParameterTabs")) {

        // -------- Viewタブ
        if (ImGui::BeginTabItem("View")) {
            if (!categoryList.empty()) {
                // カテゴリ選択
                std::vector<const char*> catItems;
                for (const auto& str : categoryList) catItems.push_back(str.c_str());

                ImGui::Combo("Category", &selectedCategoryIndex, catItems.data(), catItems.size());

                // 選択カテゴリのパラメータを表示
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

        // -------- Editタブ
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

        // --- UI用保持変数
        static bool isNewCategory = false;
        static int selectedCategoryIndex = 0;
        static char newCategoryName[64] = "";

        static char newParamName[64] = "";
        static int newTypeIndex = 0;
        static float floatVal = 0.0f;
        static int intVal = 0;
        static DirectX::SimpleMath::Vector3 vec3Val(0, 0, 0);

        // --- 既存カテゴリリスト
        std::vector<std::string> categoryList;
        for (auto& [catName, _] : m_parameters) {
            categoryList.push_back(catName);
        }

        // --- 描画開始
        if (ImGui::BeginTabItem("Add"))
        {
            // 新規カテゴリかどうか選ぶ
            ImGui::Checkbox("New Category", &isNewCategory);

            // 新規カテゴリ
            if (isNewCategory) {
                ImGui::InputText("New Category Name", newCategoryName, sizeof(newCategoryName));
            }
            // 既存カテゴリ
            else if (!categoryList.empty()) {
                std::vector<const char*> catItems;
                for (const auto& str : categoryList) catItems.push_back(str.c_str());

                ImGui::Combo("Select Existing Category", &selectedCategoryIndex, catItems.data(), catItems.size());
            }

            // パラメータ名と型・値入力
            ImGui::InputText("Parameter Name", newParamName, sizeof(newParamName));
            const char* types[] = { "float", "int", "Vector3" };
            ImGui::Combo("Type", &newTypeIndex, types, IM_ARRAYSIZE(types));

            if (newTypeIndex == 0) ImGui::InputFloat("Value (float)", &floatVal);
            else if (newTypeIndex == 1) ImGui::InputInt("Value (int)", &intVal);
            else if (newTypeIndex == 2) ImGui::InputFloat3("Value (Vector3)", &vec3Val.x);

            // Addボタン押したら追加
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

                    // 入力リセット
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


