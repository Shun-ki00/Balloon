#include "UI.hlsli"

// 定数
static const uint VERTEX_COUNT = 4;

// 頂点オフセット
static const float4 VERTEX_OFFSET[VERTEX_COUNT] =
{
    float4(-0.5f,  0.5f, 0.0f, 1.0f), // 左上
    float4( 0.5f,  0.5f, 0.0f, 1.0f), // 右上
    float4(-0.5f, -0.5f, 0.0f, 1.0f), // 左下
    float4(0.5f , -0.5f, 0.0f, 1.0f)  // 右下
};

// 射影変換行列
matrix GetProjection(float2 screenSize)
{
    return matrix(
        4.0f / screenSize.x, 0.0f, 0.0f, 0.0f,
        0.0f, -4.0f / screenSize.y, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 1.0f
    );
}

// 回転行列
matrix GetRotateMatrix(float angle)
{
    return matrix(
        cos(angle), -sin(angle), 0.0f, 0.0f,
        sin(angle), cos(angle), 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

// ジオメトリシェーダー
[maxvertexcount(VERTEX_COUNT)]
void main(
    point GS_INPUT input[1],
    inout TriangleStream<PS_INPUT> output
)
{
    // 行列計算
    matrix rot = GetRotateMatrix(input[0].rotate.z);
    matrix proj = GetProjection(windowSize);
    
    // 回転のXY成分スケールに使用
    float2 scale = float2(input[0].rotate.x, input[0].rotate.y);

    for (uint i = 0; i < VERTEX_COUNT; i++)
    {
        PS_INPUT element = (PS_INPUT) 0;

        // サイズに基づくオフセット計算
        float4 offset = VERTEX_OFFSET[i] * float4(scale.x * input[0].size.x, scale.y * input[0].size.y, 0.0f, 1.0f);

        // 中心を基準に回転
        offset.xy -= VERTEX_OFFSET[3].xy * float2(scale.x * input[0].size.x, scale.y * input[0].size.y);
        offset = mul(offset, rot);
        offset.xy += VERTEX_OFFSET[3].xy * float2(scale.x * input[0].size.x, scale.y * input[0].size.y);

        // 射影変換適用
        float4 p = input[0].position + offset;
        p = mul(p, proj);
        element.position = p;

        // UV座標の計算
        element.uv.x = 1 - (i + 1) % 2;
        element.uv.y = i >= 2 ? 0 : 1;

        // その他の属性をコピー
        element.color = input[0].color;
        element.rect  = input[0].rect;
        element.rule  = input[0].rule;

        output.Append(element);
    }

    output.RestartStrip();
}