// ============================================
// 
// ファイル名: ShaderResources.cpp
// 概要: シェーダーのリソースを管理するクラス（シングルトン）
// 
// 製作者 : 清水駿希
// 
// ============================================

#include "pch.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/Resources.h"
#include <Framework/Microsoft/ReadData.h>
#include <VertexTypes.h>


const std::vector<D3D11_INPUT_ELEMENT_DESC> ShaderResources::UI_INPUT_LAYOUT =
{
	// セマンティック名 インデックス フォーマット         入力スロット    オフセット                                                                                                                                         データ種別        インスタンスステップ率
	{ "SV_Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  0,  D3D11_INPUT_PER_VERTEX_DATA, 0 }, // position
	{ "NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 16,  D3D11_INPUT_PER_VERTEX_DATA, 0 }, // rotate
	{ "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,       0, 28,  D3D11_INPUT_PER_VERTEX_DATA, 0 }, // size
	{ "TEXCOORD",    1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 36,  D3D11_INPUT_PER_VERTEX_DATA, 0 }, // rect
	{ "COLOR",       0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 52,  D3D11_INPUT_PER_VERTEX_DATA, 0 }, // color
	{ "TEXCOORD",    2, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 68,  D3D11_INPUT_PER_VERTEX_DATA, 0 }, // rule
};
const std::vector<D3D11_INPUT_ELEMENT_DESC> ShaderResources::SEA_INPUT_LAYOUT =
{
	{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,                                    D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,    0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


/// <summary>
/// コンストラクタ
/// </summary>
ShaderResources::ShaderResources()
	:
	m_UIinputLayout{},
	m_SeaInputLayout{},
	m_PBRLitInputLayout{},
	m_particleInputLayout{}
{
}


/// <summary>
/// シェーダーのリソースをロードする
/// </summary>
/// <param name="data">Jsonデータ</param>
void ShaderResources::LoadResource(const nlohmann::json& data)
{
	// デバイス
	ID3D11Device1* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	// モデルの各ディレクトリを取得する
	const std::wstring directory = Resources::GetDirectoryFromJSON(data, "ShaderDirectory");

	std::vector<uint8_t> blob;

	// 頂点シェーダー
	if (data["Shaders"].contains("VS")) {
		for (const auto& [key, value] : data["Shaders"]["VS"].items()) {
			std::wstring path = directory + L"/" + Resources::ConvertToWString(value);

			// シェーダーをロードする
			blob = DX::ReadData(path.c_str());
			DX::ThrowIfFailed(
				device->CreateVertexShader(blob.data(), blob.size(), nullptr, 
					m_vertexShaders[key].ReleaseAndGetAddressOf())
			);
		}
	}
	// ハルシェーダー
	if (data["Shaders"].contains("HS")) {
		for (const auto& [key, value] : data["Shaders"]["HS"].items()) {
			std::wstring path = directory + L"/" + Resources::ConvertToWString(value);

			// シェーダーをロードする
			blob = DX::ReadData(path.c_str());
			DX::ThrowIfFailed(
				device->CreateHullShader(blob.data(), blob.size(), nullptr,
					m_hullShaders[key].ReleaseAndGetAddressOf())
			);
		}
	}
	// ドメインシェーダー
	if (data["Shaders"].contains("DS")) {
		for (const auto& [key, value] : data["Shaders"]["DS"].items()) {
			std::wstring path = directory + L"/" + Resources::ConvertToWString(value);

			// シェーダーをロードする
			blob = DX::ReadData(path.c_str());
			DX::ThrowIfFailed(
				device->CreateDomainShader(blob.data(), blob.size(), nullptr,
					m_domainShaders[key].ReleaseAndGetAddressOf())
			);
		}
	}
	// ジオメトリシェーダー
	if (data["Shaders"].contains("GS")) {
		for (const auto& [key, value] : data["Shaders"]["GS"].items()) {
			std::wstring path = directory + L"/" + Resources::ConvertToWString(value);

			// シェーダーをロードする
			blob = DX::ReadData(path.c_str());
			DX::ThrowIfFailed(
				device->CreateGeometryShader(blob.data(), blob.size(), nullptr,
					m_geometryShaders[key].ReleaseAndGetAddressOf())
			);
		}
	}
	// ピクセルシェーダー
	if (data["Shaders"].contains("PS")) {
		for (const auto& [key, value] : data["Shaders"]["PS"].items()) {
			std::wstring path = directory + L"/" + Resources::ConvertToWString(value);

			// シェーダーをロードする
			blob = DX::ReadData(path.c_str());
			DX::ThrowIfFailed(
				device->CreatePixelShader(blob.data(), blob.size(), nullptr,
					m_pixelShaders[key].ReleaseAndGetAddressOf())
			);
		}
	}


	// 入力レイアウトの構築（必要なものだけ）
	if (m_vertexShaders.contains("UI_VS")) {
		blob = DX::ReadData((directory + L"/UI_VS.cso").c_str());
		device->CreateInputLayout(UI_INPUT_LAYOUT.data(),
			(UINT)UI_INPUT_LAYOUT.size(),
			blob.data(), blob.size(),
			m_UIinputLayout.GetAddressOf());
	}

	if (m_vertexShaders.contains("Sea_VS")) {
		blob = DX::ReadData((directory + L"/Sea_VS.cso").c_str());
		device->CreateInputLayout(
			DirectX::VertexPositionTexture::InputElements,
			DirectX::VertexPositionTexture::InputElementCount,
			blob.data(), blob.size(),
			m_SeaInputLayout.GetAddressOf());
	}

	if (m_vertexShaders.contains("PBRLit_VS")) {
		blob = DX::ReadData((directory + L"/PBRLit_VS.cso").c_str());
		device->CreateInputLayout(
			DirectX::VertexPositionNormalTangentColorTexture::InputElements,
			DirectX::VertexPositionNormalTangentColorTexture::InputElementCount,
			blob.data(), blob.size(),
			m_PBRLitInputLayout.GetAddressOf());
	}

	if (m_vertexShaders.contains("Particle_VS")) {
		blob = DX::ReadData((directory + L"/Particle_VS.cso").c_str());
		device->CreateInputLayout(
			DirectX::VertexPositionColorTexture::InputElements,
			DirectX::VertexPositionColorTexture::InputElementCount,
			blob.data(), blob.size(),
			m_particleInputLayout.GetAddressOf());
	}
}

/// <summary>
/// 頂点シェーダーを取得する
/// </summary>
/// <param name="id">頂点シェーダーID</param>
/// <returns>頂点シェーダー</returns>
ID3D11VertexShader* ShaderResources::GetVertexShader(VS_ID id)
{
	std::string key = std::string(magic_enum::enum_name(id));
	auto it = m_vertexShaders.find(key);
	return (it != m_vertexShaders.end()) ? it->second.Get() : nullptr;
}

/// <summary>
/// ハルシェーダーを取得する
/// </summary>
/// <param name="id">ハルシェーダーID</param>
/// <returns>ハルシェーダー</returns>
ID3D11HullShader* ShaderResources::GetHullShader(HS_ID id)
{
	std::string key = std::string(magic_enum::enum_name(id));
	auto it = m_hullShaders.find(key);
	return (it != m_hullShaders.end()) ? it->second.Get() : nullptr;
}

/// <summary>
/// ドメインシェーダーを取得する
/// </summary>
/// <param name="id">ドメインシェーダーID</param>
/// <returns>ドメインシェーダー</returns>
ID3D11DomainShader* ShaderResources::GetDomainShader(DS_ID id)
{
	std::string key = std::string(magic_enum::enum_name(id));
	auto it = m_domainShaders.find(key);
	return (it != m_domainShaders.end()) ? it->second.Get() : nullptr;
}

/// <summary>
/// ジオメトリシェーダーを取得する
/// </summary>
/// <param name="id">ジオメトリシェーダーID</param>
/// <returns>ジオメトリシェーダー</returns>
ID3D11GeometryShader* ShaderResources::GetGeometryShader(GS_ID id)
{
	std::string key = std::string(magic_enum::enum_name(id));
	auto it = m_geometryShaders.find(key);
	return (it != m_geometryShaders.end()) ? it->second.Get() : nullptr;
}

/// <summary>
/// ピクセルシェーダーを取得する
/// </summary>
/// <param name="id">ピクセルシェーダーID</param>
/// <returns>ピクセルシェーダー</returns>
ID3D11PixelShader* ShaderResources::GetPixelShader(PS_ID id)
{
	std::string key = std::string(magic_enum::enum_name(id));
	auto it = m_pixelShaders.find(key);
	return (it != m_pixelShaders.end()) ? it->second.Get() : nullptr;
}
