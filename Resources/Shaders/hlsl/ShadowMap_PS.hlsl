
// �V���h�E�}�b�v�̃s�N�Z���V�F�[�_���͗p
struct PS_SM_Input
{
    float4 Position : SV_Position;
};

float4 main(PS_SM_Input input) : SV_TARGET
{
	// Z�l���o�͂���
    return input.Position.z;
}