#pragma once
#include <string>

struct float4
{
	// F구조체의 

public:
	static const float4 Zero;
	static const float4 Left;
	static const float4 Right;
	static const float4 Up;
	static const float4 Down;

	union
	{
		struct
		{
			float X; // 2D
			float Y; // 2D
			float Z;
			float W;
		};

		struct
		{
			float R; // 2D
			float G; // 2D
			float B;
			float A;
		};
	};

	// 생성자를 한번 만들게 되면 리스트 이니셜라이저가 동작하지 않아서
	// 내가 생성하는 방식을 다 정의해야 합니다.
	float4()
		: X(0.0f), Y(0.0f), Z(0.0f), W(1.0f)
	{

	}

	float4(long _X, long _Y)
		: X(static_cast<float>(_X)), Y(static_cast<float>(_Y)), Z(0.0f), W(1.0f)
	{

	}


	float4(int _X, int _Y)
		: X(static_cast<float>(_X)), Y(static_cast<float>(_Y)), Z(0.0f), W(1.0f)
	{

	}

	float4(float _X, float _Y)
		: X(_X), Y(_Y), Z(0.0f), W(1.0f)
	{

	}

	float4(int _X, int _Y, int _Z, int _W)
		: X(static_cast<float>(_X)), Y(static_cast<float>(_Y)), Z(static_cast<float>(_Z)), W(static_cast<float>(_W))
	{

	}

	float4(float _X, float _Y, float _Z, float _W)
		: X(_X), Y(_Y), Z(_Z), W(_W)
	{

	}


public:
	std::string ToString()
	{
		return "[X : " + std::to_string(X) + " Y : " + std::to_string(Y) + " Z : " + std::to_string(Z) + " W : " + std::to_string(W) + "]";
	}

	float4 Half2D()
	{
		return { hX(), hY() };
	}

	int iX() const
	{
		return static_cast<int>(X);
	}

	int iY() const
	{
		return static_cast<int>(Y);
	}


	float hX() const
	{
		return X * 0.5f;
	}

	float hY() const
	{
		return Y * 0.5f;
	}


	int ihY() const
	{
		return static_cast<int>(hY());
	}

	int ihX() const
	{
		return static_cast<int>(hX());
	}

	float4 operator+(const float4& _Other)
	{
		float4 Result = *this;
		Result.X += _Other.X;
		Result.Y += _Other.Y;
		Result.Z += _Other.Z;
		return Result;
	}

	float4& operator+=(const float4& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		Z += _Other.Z;

		return *this;
	}

	float4 operator*(float _Value) const
	{
		float4 Result = *this;
		Result.X *= _Value;
		Result.Y *= _Value;
		Result.Z *= _Value;
		return Result;
	}

	float4& operator*=(float _Value)
	{
		X *= _Value;
		Y *= _Value;
		Z *= _Value;

		return *this;
	}

	float4 operator*(const float4& _Other) const
	{
		float4 Result = *this;
		Result.X *= _Other.X;
		Result.Y *= _Other.Y;
		Result.Z *= _Other.Z;
		return Result;
	}

	float4& operator*=(const float4& _Other)
	{
		X *= _Other.X;
		Y *= _Other.Y;
		Z *= _Other.Z;

		return *this;
	}

	float4 operator-(const float4& _Other)
	{
		float4 Result = *this;
		Result.X -= _Other.X;
		Result.Y -= _Other.Y;
		Result.Z -= _Other.Z;
		return Result;
	}

	float4& operator-=(const float4& _Other)
	{
		X -= _Other.X;
		Y -= _Other.Y;
		Z -= _Other.Z;

		return *this;
	}
};

using FVector = float4;
using FColor = float4;

class Color8Bit
{
	// 현실에서의 색상은
	// 물감으로 치면 다섞으면 어두운색
	// 빛으로 치면 다섞으면 흰색
	// 컴퓨터는 빛의 삼원색을 사용합니다.
public:
	static const Color8Bit Black;
	static const Color8Bit Red;
	static const Color8Bit Green;
	static const Color8Bit Blue;
	static const Color8Bit White;

	union
	{
		struct
		{
			unsigned char R;
			unsigned char G;
			unsigned char B;
			unsigned char A;
		};

		unsigned char Arr1D[4] = { 0,0,0,255 };
		unsigned int Color;
	};

	Color8Bit ZeroAlphaColor() const
	{
		return Color8Bit{ R,G,B,0 };
	}
};

// 설명 :
class EngineMath
{
public:
	// constrcuter destructer
	EngineMath();
	~EngineMath();

	// delete Function
	EngineMath(const EngineMath& _Other) = delete;
	EngineMath(EngineMath&& _Other) noexcept = delete;
	EngineMath& operator=(const EngineMath& _Other) = delete;
	EngineMath& operator=(EngineMath&& _Other) noexcept = delete;

protected:

private:

};

