#include "UI.hlsli"

// 頂点シェーダー
GS_INPUT main(VS_INPUT input)
{
    GS_INPUT output = (GS_INPUT)0;
    
    // 頂点位置を2Dスクリーン空間に変換
    output.position = float4(input.position.xy, 0.0f, 1.0f);
    
    // 頂点カラーを設定
    output.color = input.color;
    
    // X成分を回転角度として利用
    output.rotate = input.rotate;
    
    // テクスチャサイズを設定
    output.size = input.size;
    
    // 矩形情報を渡す
    output.rect = input.rect;

    // ルール画像設定情報を渡す
    output.rule = input.rule;

    return output;
}