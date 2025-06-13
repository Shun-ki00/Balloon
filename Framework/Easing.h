// ============================================
// 
// ファイル名: Easing.h
// 概要: イージング関数の集まり
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include <iostream>
#include <DirectXMath.h>

namespace easing
{
	/*
		参考：
		https://easings.net/ja
	*/

	
	//EaseInSine
	inline float EaseInSine(float t)
	{
		return 1.0f - cosf((t * DirectX::XM_PI) / 2.0f);
	}

	//EaseOutSine
	inline float EaseOutSine(float t)
	{
		return sinf((t * DirectX::XM_PI) / 2.0f);
	}

	//EaseInOutSine
	inline float EaseInOutSine(float t)
	{
		return -(cosf(DirectX::XM_PI * t) - 1) / 2;
	}

	//EaseInQuad
	inline float EaseInQuad(float t)
	{
		return t * t;
	}

	//EaseOutQuad
	inline float EaseOutQuad(float t)
	{
		return 1.0f - (1.0f - t) * (1.0f - t);
	}

	//EaseInOutQuad
	inline float EaseInOutQuad(float t)
	{
		return t < 0.5f ? 2.0f * t * t : 1.0f - pow(-2.0f * t + 2.0f, 2.0f) / 2.0f;
	}

	//EaseInCubic
	inline float EaseInCubic(float t)
	{
		return t * t * t;
	}

	//EaseOutCubic
	inline float EaseOutCubic(float t)
	{
		return 1.0f - pow(1.0f - t, 3.0f);
	}

	//EaseInOutCubic
	inline float EaseInOutCubic(float t)
	{
		return t < 0.5f ? 4.0f * t * t * t : 1.0f - pow(-2.0f * t + 2.0f, 3.0f) / 2.0f;
	}

	//EaseInQuart
	inline float EaseInQuart(float t)
	{
		return t * t * t * t;
	}

	//EaseOutQuart
	inline float EaseOutQuart(float t)
	{
		return 1.0f - pow(1.0f - t, 4.0f);
	}

	//EaseInOutQuart
	inline float EaseInOutQuart(float t)
	{
		return t < 0.5f ? 8.0f * t * t * t * t : 1.0f - pow(-2.0f * t + 2.0f, 4.0f) / 2.0f;
	}

	//EaseInQuint
	inline float EaseInQuint(float t)
	{
		return t * t * t * t * t;
	}

	//EaseOutQuint
	inline float EaseOutQuint(float t)
	{
		return 1.0f - pow(1.0f - t, 5.0f);
	}

	//EaseInOutQuint
	inline float EaseInOutQuint(float t)
	{
		return t < 0.5f ? 16.0f * t * t * t * t * t : 1.0f - pow(-2.0f * t + 2.0f, 5.0f) / 2.0f;
	}

	//EaseInExpo
	inline float EaseInExpo(float t)
	{
		return t ==  0.0f ? 0.0f : pow(2.0f, 10.0f * t - 10.0f);
	}

	//EaseOutExpo
	inline float EaseOutExpo(float t)
	{
		return t == 1.0f ? 1.0f : 1.0f - pow(2.0f, -10.0f * t);
	}

	//EaseInOutExpo
	inline float EaseInOutExpo(float t)
	{
		return t == 0.0f
			? 0.0f
			: t == 1.0f
			? 1.0f
			: t < 0.5f ? pow(2.0f, 20.0f * t - 10.0f) / 2.0f
			: (2.0f - pow(2.0f, -20.0f * t + 10.0f)) / 2.0f;
	}

	//EaseInCirc
	inline float EaseInCirc(float t)
	{
		return 1.0f - sqrt(1.0f - pow(t, 2.0f));
	}

	//EaseOutCirc
	inline float EaseOutCirc(float t)
	{
		return sqrt(1.0f - pow(t - 1.0f, 2.0f));
	}

	//EaseInOutCirc
	inline float EaseInOutCirc(float t)
	{
		return t < 0.5f
			? (1.0f - sqrt(1.0f - pow(2.0f * t, 2.0f))) / 2.0f
			: (sqrt(1.0f - pow(-2.0f * t + 2.0f, 2.0f)) + 1.0f) / 2.0f;
	}

	//EaseInBack
	inline float EaseInBack(float t)
	{
		const float c1 = 1.70158f;
		const float c3 = c1 + 1.0f;

		return c3 * t * t * t - c1 * t * t;
	}

	//EaseOutBack
	inline float EaseOutBack(float t)
	{
		const float c1 = 1.70158f;
		const float c3 = c1 + 1.0f;

		return 1.0f + c3 * pow(t - 1.0f, 3.0f) + c1 * pow(t - 1, 2.0f);
	}

	//EaseInOutBack
	inline float EaseInOutBack(float t)
	{
		const float c1 = 1.70158;
		const float c2 = c1 * 1.525;

		return t < 0.5
			? (pow(2.0f * t, 2.0f) * ((c2 + 1.0f) * 2.0f * t - c2)) / 2.0f
			: (pow(2.0f * t - 2.0f, 2.0f) * ((c2 + 1.0f) * (t * 2.0f - 2.0f) + c2) + 2.0f) / 2.0f;
	}

	//EaseInElastic
	inline float EaseInElastic(float t)
	{
		const float c4 = (2.0f * DirectX::XM_PI) / 3.0f;

		return t == 0
			? 0.0f
			: t == 1.0f
			? 1.0f
			: -pow(2.0f, 10.0f * t - 10.0f) * sin((t * 10.0f - 10.75f) * c4);
	}

	//EaseOutElastic
	inline float EaseOutElastic(float t)
	{
		const float c4 = (2.0f * DirectX::XM_PI) / 3.0f;

		return t == 0.0f
			? 0.0f
			: t == 1.0f
			? 1.0f
			: pow(2.0f, -10.0f * t) * sin((t * 10.0f - 0.75f) * c4) + 1.0f;
	}

	//EaseInOutElastic
	inline float EaseInOutElastic(float t)
	{
		const float c5 = (2.0f * DirectX::XM_PI) / 4.5f;

		return t == 0.0f
			? 0.0f
			: t == 1.0f
			? 1.0f
			: t < 0.5f
			? -(pow(2.0f, 20.0f * t - 10.0f) * sin((20.0f * t - 11.125f) * c5)) / 2.0f
			:  (pow(2.0f, -20.0f * t + 10.0f) * sin((20.0f * t - 11.125f) * c5)) / 2.0f + 1.0f;
	}

	// EaseOutBounce
	inline float EaseOutBounce(float t)
	{
		const float n1 = 7.625f;
		const float d1 = 2.75f;

		if (t < (1.f / d1))
		{
			return n1 * t * t;
		}
		else if (t < (2.f / d1))
		{
			return n1 * (t -= 1.5f / d1) * t + 0.75f;
		}
		else if (t < (2.5f / d1))
		{
			return n1 * (t -= 2.25f / d1) * t + 0.9375f;
		}
		else
		{
			return n1 * (t -= 2.625f / d1) * t + 0.984375f;
		}
	}

	//EaseInBounce
	inline float EaseInBounce(float t)
	{
		return 1.0f - EaseOutBounce(1.0f - t);
	}

	//EaseInOutBounce
	inline float EaseInOutBounce(float t)
	{
		return t < 0.5f
			? (1.0f - EaseOutBounce(1.0f - 2.0f * t)) / 2.0f
			: (1.0f + EaseOutBounce(2.0f * t - 1.0f)) / 2.0f;
	}
}