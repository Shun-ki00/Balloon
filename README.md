# 「BALLOON」（開発中）

## 実行形式
最新版の実行ファイルはこちらからダウンロードできます： [Download BALLOON v1.0.0](https://github.com/Shun-ki00/Balloon/releases/latest)

## ゲーム概要
プレイヤーと敵は複数風船をつけていて、相手の風船をアタックして割る！  
全ての風船を割り、敵を落としたら勝ち！！

## 操作方法
- 移動：↑ / ↓
- 回転：← / →
- 風船膨らませ：ホールド Space
- アタック（風船割り）：Z

## 動作環境
・OS：Windows 10 / 11  
・GPU : Direct3D 11対応グラフィックカード  
・開発環境：Visual Studio 2022  
・ビルド対象：x64  

## 使用ライブラリ
・Direct3D 11  
・DirectXTK  
・Windows SDK  
・Dear ImGui 

## 使用デザインパターン
 - シングルトン
 - ファクトリー
 - ステート
 - コンポジット
 - オブザーバー
 - ステアリングビヘイビア
 - プール
 - ビジター

## 敵の挙動
 - ビヘイビアーツリー
 - ステアリングビヘイビアー
 - ステート

## 公開中の関連技術

本プロジェクト「BALLOON」の開発に関連し、以下の技術を検証・応用・公開しています。

- [D3D11TK_Physically-basedRendering](https://github.com/Shun-ki00/D3D11TK_Physically-basedRendering)  
  Direct3D 11 における PBR（物理ベースレンダリング）の実装

- [Multi-threadRendering](https://github.com/Shun-ki00/Multi-threadRendering)  
  D3D11 のマルチスレッド描画パイプライン実験用プロジェクト。描画最適化に応用。

- [D3D11TK_ImGizmo](https://github.com/Shun-ki00/D3D11TK_ImGizmo)  
  DirectX + Dear ImGui での Gizmo 表示ライブラリ。エディタ機能で使用。

- [D3D11TK_ImGuiSample](https://github.com/Shun-ki00/D3D11TK_ImGuiSample)  
  ImGui ベースのツールUIの実装例。デバッグUI構築の参考。
  
- [D3D11TK_InlineHLSL_Skybox](https://github.com/Shun-ki00/D3D11TK_InlineHLSL_Skybox)  
  HLSLコードのインライン化とスカイボックスの描画実験。

- [D3D11TK_Sea](https://github.com/Shun-ki00/D3D11TK_Sea)  
  海面の表現。波・反射の表現など。

- [D3D11TK_ParticleEditor](https://github.com/Shun-ki00/D3D11TK_ParticleEditor)  
  GUI上でパーティクル設定を行うエディタツール。演出制御に利用。



