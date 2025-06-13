#include "SkyBox.hlsli"


PS_Input main(VS_Input input)
{
    // 出力構造体を初期化
    PS_Input output = (PS_Input) 0;
    
    // オブジェクト空間 (OS) からワールド空間 (WS) へ変換
    float4 position = mul(float4(input.positionOS, 1.0f), matWorld);
    
     // ビュー行列の平行移動成分をゼロにする
    matrix SetMatView = matView;
    SetMatView._41 = 0;
    SetMatView._42 = 0;
    SetMatView._43 = 0;
    
    // ワールド空間からビュー空間へ変換
    position = mul(position, SetMatView);
    // ビュー空間からクリップ空間 (CS) へ変換
    position = mul(position, matProj);
    
    // 深度値を最大化して常に奥に描画
    position.z = position.w;
    
    // 出力変数に座標とテクスチャ座標を格納
    output.positionCS = position;
    output.texcoord = input.positionOS.xyz;
    
    // ピクセルシェーダーに渡す
    return output;
}