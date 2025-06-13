#pragma once

// ビヘイビアツリーの結果型
enum class Result { SUCCESS, FAILURE, RUNNING };

class IBehaviorNode
{
public:
	// デストラクタ
	virtual ~IBehaviorNode() = default;
	// 実行する
	virtual Result Tick() = 0;
	// 名前を取得する
	virtual std::string GetName() const = 0;
};