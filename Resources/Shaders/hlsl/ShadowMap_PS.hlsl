
// シャドウマップのピクセルシェーダ入力用
struct PS_SM_Input
{
    float4 Position : SV_Position;
};

float4 main(PS_SM_Input input) : SV_TARGET
{
	// Z値を出力する
    return input.Position.z;
}