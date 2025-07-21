#include "pch.h"
#include "Framework/Renderer.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"
#include "Interface/IRenderableObject.h"
#include "Game/RenderableObjects/UIRenderableObject .h"
#include "Game/Particle/Particle.h"
#include "Game/Particle/ParticleEmitter.h"
#include "Game/ShadowMap/CascadedShadowMap.h"
#include "Game/Buffers.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Renderer::Renderer()
{
	m_commonResources = CommonResources::GetInstance();
	m_device          = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	m_context         = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	m_commonStates    = CommonResources::GetInstance()->GetCommonStates();


	m_particleConstBuffer = std::make_unique<ConstantBuffer<ParticleConstBuffer>>();
	m_particleConstBuffer->Initialize(m_commonResources->GetDeviceResources()->GetD3DDevice());


	// === UI ===

	// ���_�V�F�[�_�[���擾����
	m_uiVertexShader = Resources::GetInstance()->GetShaderResources()->GetVertexShader(VS_ID::UI_VS);
	// �W�I���g���V�F�[�_�[���擾����
	m_uiGeometryShader = Resources::GetInstance()->GetShaderResources()->GetGeometryShader(GS_ID::UI_GS);
	// �C���v�b�g���C�A�E�g���擾����
	m_uiInputLayout = Resources::GetInstance()->GetShaderResources()->GetUIinputLayout();
	
	// �萔�o�b�t�@�̏�����
	m_uiConstBufferData.windowSize = { 1280.0f ,720.0f };
	m_uiConstBufferData.useTexture = 1.0f;
	m_uiConstBufferData.time = { 0.0f ,0.0f ,0.0f ,0.0f };

	m_uiConstBuffer = std::make_unique<ConstantBuffer<UIConstBuffer>>();
	m_uiConstBuffer->Initialize(m_device);

	// �V�F�[�_�[�Ƀf�[�^��n�����߂�UI�̃o�[�e�b�N�X�o�b�t�@�̍쐬
	D3D11_BUFFER_DESC desc = {};
	ZeroMemory(&desc, sizeof(desc));
	desc.ByteWidth = sizeof(UIVertexBuffer);
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	m_device->CreateBuffer(&desc, nullptr, &m_uiVertexBuffer);

	// === �p�[�e�B�N�� ===

	// ���_�V�F�[�_�[���擾����
	m_particleVertexShader   = Resources::GetInstance()->GetShaderResources()->GetVertexShader(VS_ID::Particle_VS);
	// �W�I���g���V�F�[�_�[���擾����
	m_particleGeometryShader = Resources::GetInstance()->GetShaderResources()->GetGeometryShader(GS_ID::Particle_GS);
	// �C���v�b�g���C�A�E�g���擾����
	m_particleiInputLayout   = Resources::GetInstance()->GetShaderResources()->GetParticleInputLayout();


	// �V�F�[�_�[�Ƀf�[�^��n�����߂�UI�̃o�[�e�b�N�X�o�b�t�@�̍쐬
	 desc = {};
	ZeroMemory(&desc, sizeof(desc));
	// �T�C�Y�͕K�v�Ȓ��_���ɂ���
	desc.ByteWidth = sizeof(DirectX::VertexPositionColorTexture) * 300; 
	// ���t���[������������Ȃ�DYNAMIC���g��
	desc.Usage = D3D11_USAGE_DYNAMIC;
	// �o�C���h�t���O��VertexBuffer
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// CPU���珑�����݂ł���悤�ɂ���
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	// �o�b�t�@�쐬
	m_device->CreateBuffer(&desc, nullptr, &m_particleVertexBuffer);

	// �A�^�b�`�̋�����������
	m_isActiveAttach = false;

	m_shadowMap = std::make_unique<CascadedShadowMap>();
	m_shadowMap->Initialize();
}


/// <summary>
/// �`�揈�����s��
/// </summary>
void Renderer::Render()
{
	DirectX::SimpleMath::Matrix viewMatrix       = m_commonResources->GetViewMatrix();
	DirectX::SimpleMath::Matrix projectionMatrix = m_commonResources->GetProjectionMatrix();

	// ���f����`�悷��
	this->ModelRender(viewMatrix, projectionMatrix);
	// �p�[�e�B�N���`��
	this->ParticleRender(viewMatrix, projectionMatrix);
	// UI�̕`��
	this->UIRender();
}

/// <summary>
/// ���f�����A�^�b�`����
/// </summary>
/// <param name="object">�I�u�W�F�N�g</param>
/// <param name="renderableObject">�`��I�u�W�F�N�g</param>
void Renderer::Attach(IObject* object, IRenderableObject* renderableObject)
{
	// �A�^�b�`��������ĂȂ���΃X�L�b�v
	if (!m_isActiveAttach) return;

	// �L�[�̒ǉ�
	m_objectKeys.push_back(object);

	// �`��I�u�W�F�N�g�̒ǉ�
	m_modelRenderableObjects[object] = renderableObject;
}

/// <summary>
/// UI���A�^�b�`����
/// </summary>
/// <param name="object">UI�I�u�W�F�N�g</param>
/// <param name="renderableObject">UI�`��I�u�W�F�N�g</param>
void Renderer::Attach(IObject* object, UIRenderableObject* renderableObject)
{
	// �A�^�b�`��������ĂȂ���΃X�L�b�v
	if (!m_isActiveAttach) return;

	// �L�[�̒ǉ�
	m_UIObjectKeys.push_back(object);

	// �`��I�u�W�F�N�g�̒ǉ�
	m_UIRenderableObjects[object] = renderableObject;
}

/// <summary>
/// �A�^�b�`���J�n
/// </summary>
void Renderer::Begin()
{
	// �A�^�b�`�̋���
	m_isActiveAttach = true;
	
	// ���݂̃I�u�W�F�N�g�̐����擾����
	m_objectNumber = m_objectKeys.size();
	// ���݂�UI�I�u�W�F�N�g�̐����擾����
	m_uiObjectNumber = m_UIObjectKeys.size();
	// ���݂̃G�t�F�N�g�̐����擾����
	particleEmitterNumber = m_particleEmitter.size();

}

/// <summary>
/// �A�^�b�`�I��
/// </summary>
void Renderer::End()
{
	// �O�̃V�[���̃I�u�W�F�N�g��j��
	for (int i = 0; i < m_objectNumber; ++i)
	{
		// �擪�̃I�u�W�F�N�g�擾
		IObject* obj = m_objectKeys.front();
		// �����_���u���}�b�v����폜
		m_modelRenderableObjects.erase(obj);    
		// �x�N�^����擪�폜
		m_objectKeys.erase(m_objectKeys.begin());
	}

	// �O�̃V�[����UI�I�u�W�F�N�g��j��
	for (int i = 0; i < m_uiObjectNumber; i++)
	{
		// �擪�̃I�u�W�F�N�g�擾
		IObject* obj = m_UIObjectKeys.front();  
		// �����_���u���}�b�v����폜
		m_UIRenderableObjects.erase(obj);    
		// �x�N�^����擪�폜
		m_UIObjectKeys.erase(m_UIObjectKeys.begin()); 
	}

	// �O�̃V�[���̃G�t�F�N�g��j��
	for (int i = 0; i < particleEmitterNumber; i++)
	{
		// �擪�̃G�t�F�N�g��j������
		m_particleEmitter.erase(m_particleEmitter.begin());
	}

	// ���݂̃I�u�W�F�N�g�̐����擾����
	m_objectNumber = m_objectKeys.size();
	// ���݂�UI�I�u�W�F�N�g�̐����擾����
	m_uiObjectNumber = m_UIObjectKeys.size();
	// ���݂̃G�t�F�N�g�̐����擾����
	particleEmitterNumber = m_particleEmitter.size();
}

/// <summary>
/// �I�u�W�F�N�g�̍폜
/// </summary>
void Renderer::Reset()
{

}


/// <summary>
/// ���f����`�悷��
/// </summary>
/// <param name="viewMatrix">�r���[�s��</param>
/// <param name="projectionMatrix">�ˉe�s��</param>
void Renderer::ModelRender(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	// �V���h�E�}�b�v�̕`��
	m_shadowMap->Begin();
	for (int i = 0; i < m_objectNumber; ++i)
	{
		IObject* object = m_objectKeys[i];
		IRenderableObject* renderable = m_modelRenderableObjects[object];

		bool active = this->IsHierarchyActive(object);

		if (active && renderable->GetIsActive())
		{
			if (object->GetObjectID() != IObject::ObjectID::BALLOON)
			m_shadowMap->Draw(renderable->GetModel(), m_context, m_commonStates, object->GetTransform());
		}
	}
	m_shadowMap->End();

	for (int i = 0; i < m_objectNumber; ++i)
	{
		IObject* object = m_objectKeys[i];
		IRenderableObject* renderable = m_modelRenderableObjects[object];

		bool active = this->IsHierarchyActive(object);

		if (active && renderable->GetIsActive())
		{
			renderable->Render(m_context, m_commonStates, viewMatrix, projectionMatrix, m_shadowMap->GetShadowShaderResourceView());
		}
	}
}



/// <summary>
/// �p�[�e�B�N����`�悷��
/// </summary>
/// <param name="viewMatrix">�r���[�s��</param>
/// <param name="projectionMatrix">�ˉe�s��</param>
void Renderer::ParticleRender(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;

	ParticleConstBuffer particleConstBuffer = {};
	particleConstBuffer.projectionMatrix = projectionMatrix.Transpose();
	particleConstBuffer.viewMatrix = viewMatrix.Transpose();
	// �r���{�[�h�s������
	m_billboardMatrix = viewMatrix.Invert();
	m_billboardMatrix._41 = 0.0f;
	m_billboardMatrix._42 = 0.0f;
	m_billboardMatrix._43 = 0.0f;
	particleConstBuffer.billboardMatrix = m_billboardMatrix.Transpose();
	particleConstBuffer.worldMatrix = world.Transpose();
	particleConstBuffer.time = DirectX::SimpleMath::Vector4::Zero;

	// �萔�o�b�t�@�̍X�V
	m_particleConstBuffer->Update(m_context, particleConstBuffer);

	//	�V�F�[�_�[�ɒ萔�o�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_particleConstBuffer->GetBuffer() };
	m_context->VSSetConstantBuffers(0, 1, cb);
	m_context->GSSetConstantBuffers(0, 1, cb);
	m_context->PSSetConstantBuffers(0, 1, cb);

	//	�������`��w��		��ԃA���t�@����
	ID3D11BlendState* blendstate = m_commonStates->NonPremultiplied();
	//	�������菈��
	m_context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	m_context->OMSetDepthStencilState(m_commonStates->DepthRead(), 0);

	//	�J�����O�͂Ȃ�
	m_context->RSSetState(m_commonStates->CullNone());

	//	�C���v�b�g���C�A�E�g�̓o�^
	m_context->IASetInputLayout(m_particleiInputLayout);

	// �v���~�e�B�u�g�|���W�[��ݒ�
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	// ���_�V�F�[�_�[�̐ݒ�
	m_context->VSSetShader(m_particleVertexShader, nullptr, 0);
	// �W�I���g���V�F�[�_�[�̐ݒ�
	m_context->GSSetShader(m_particleGeometryShader, nullptr, 0);

	
	for (int i = 0; i < particleEmitterNumber; ++i)
	{
		ParticleEmitter* emitter = m_particleEmitter[i];

		if (!emitter->GetIsActive() || emitter->GetInputDatas().empty())
			continue;

		particleConstBuffer.worldMatrix = DirectX::SimpleMath::Matrix::Identity;
		m_particleConstBuffer->UpdateIfNeeded(m_context, particleConstBuffer);

		ID3D11ShaderResourceView* srv = emitter->GetTexture();
		m_context->PSSetShaderResources(0, 1, &srv);

		ID3D11SamplerState* sampler[1] = { m_commonStates->LinearWrap() };
		m_context->PSSetSamplers(0, 1, sampler);

		m_context->PSSetShader(emitter->GetPixelShader(), nullptr, 0);

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		m_context->Map(m_particleVertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

		memcpy(mappedResource.pData, emitter->GetInputDatas().data(),
			sizeof(DirectX::VertexPositionColorTexture) * emitter->GetInputDatas().size());

		m_context->Unmap(m_particleVertexBuffer.Get(), 0);

		UINT stride = sizeof(DirectX::VertexPositionColorTexture);
		UINT offset = 0;
		ID3D11Buffer* buffer = m_particleVertexBuffer.Get();
		m_context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);

		m_context->Draw(static_cast<UINT>(emitter->GetInputDatas().size()), 0);

		m_context->PSSetShader(nullptr, nullptr, 0);
		ID3D11ShaderResourceView* nullsrv[] = { nullptr };
		m_context->PSSetShaderResources(0, 1, nullsrv);
	}

	//	�V�F�[�_�̓o�^���������Ă���
	m_context->VSSetShader(nullptr, nullptr, 0);
	m_context->GSSetShader(nullptr, nullptr, 0);
}

/// <summary>
/// UI��`�悷��
/// </summary>
void Renderer::UIRender()
{
	// �o�ߎ��Ԃ��X�V
	float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();
	m_uiConstBufferData.time.x += elapsedTime;

	// �萔�o�b�t�@��ݒ�
	m_uiConstBuffer->Update(m_context, m_uiConstBufferData);

	//	�V�F�[�_�[�ɒ萔�o�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_uiConstBuffer->GetBuffer() };
	m_context->VSSetConstantBuffers(0, 1, cb);
	m_context->GSSetConstantBuffers(0, 1, cb);
	m_context->PSSetConstantBuffers(0, 1, cb);

	//	�������`��w��		��ԃA���t�@����
	ID3D11BlendState* blendstate = m_commonStates->NonPremultiplied();
	//	�������菈��
	m_context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);
	//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	m_context->OMSetDepthStencilState(m_commonStates->DepthRead(), 0);
	//	�J�����O�͂Ȃ�
	m_context->RSSetState(m_commonStates->CullNone());
	// ���̓��C�A�E�g��ݒ�
	m_context->IASetInputLayout(m_uiInputLayout);
	// �v���~�e�B�u�g�|���W�[��ݒ� (�|�C���g���X�g)
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	// ���_�V�F�[�_�[�̐ݒ�
	m_context->VSSetShader(m_uiVertexShader, nullptr, 0);
	// �W�I���g���V�F�[�_�[�̐ݒ�
	m_context->GSSetShader(m_uiGeometryShader, nullptr, 0);

	for (int i = 0; i < m_uiObjectNumber; ++i)
	{
		IObject* object = m_UIObjectKeys[i];
		UIRenderableObject* renderable = m_UIRenderableObjects[object];

		if (!object->GetIsActive() || !renderable->GetIsActive())
			continue;

		UIVertexBuffer buffer = renderable->GetVertexBufferData();
		m_context->UpdateSubresource(m_uiVertexBuffer.Get(), 0, NULL, &buffer, 0, 0);

		ID3D11Buffer* buffers[] = { m_uiVertexBuffer.Get() };
		UINT stride[] = { sizeof(UIVertexBuffer) };
		UINT offset[] = { 0 };
		m_context->IASetVertexBuffers(0, 1, buffers, stride, offset);

		m_context->PSSetShader(renderable->GetPixelShader(), nullptr, 0);

		std::vector<ID3D11ShaderResourceView*> tex = {
			renderable->GetTexture(),
			renderable->GetRuleTexture(),
		};
		m_context->PSSetShaderResources(0, (UINT)tex.size(), tex.data());

		m_context->Draw(1, 0);

		m_context->PSSetShader(nullptr, nullptr, 0);
		ID3D11ShaderResourceView* nullsrv[] = { nullptr };
		m_context->PSSetShaderResources(0, 1, nullsrv);
	}

	// ���\�[�X�̉��
	ID3D11ShaderResourceView* nullsrv[] = { nullptr };
	m_context->PSSetShaderResources(0, 0, nullsrv);
	m_context->PSSetShaderResources(0, 1, nullsrv);

	// ���_�V�F�[�_�[�̉��
	m_context->VSSetShader(nullptr, nullptr, 0);
	// �W�I���g���V�F�[�_�[�̉��
	m_context->GSSetShader(nullptr, nullptr, 0);

}


bool Renderer::IsHierarchyActive(IObject* object)
{
	while (object != nullptr && object != Root::GetInstance())
	{
		if (!object->GetIsActive())
			return false;

		object = object->GetParent();
	}

	// Root �܂œ��B������ARoot ���̂��`�F�b�N�i�K�v�ł���΁j
	return Root::GetInstance()->GetIsActive();
}