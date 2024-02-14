#pragma once
#include <string>
#include <cmath>

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
	float Size2D()
	{
		// sqrtf 제곱근 구해주는 함수
		return std::sqrtf((X * X) + (Y * Y));
	}

	// 나 자신이 길이 1짜리로 변경되는 것.
	void Normalize2D()
	{
		float Size = Size2D();
		X /= Size;
		Y /= Size;
		Z = 0.0f;
		W = 0.0f;
	}

	// 나는 변화하지 않고 길이 1짜리로 변한 나와 방향이 같은 벡터를 리턴하는 함수
	float4 Normalize2DReturn()
	{
		float4 Result = *this;
		Result.Normalize2D();
		return Result;
	}

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
		return std::lround(X);
	}

	int iY() const
	{
		return std::lround(Y);
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
		return std::lround(hY());
	}

	int ihX() const
	{
		return std::lround(hX());
	}

	float4& operator=(const float4& _Other)
	{
		X = _Other.X;
		Y = _Other.Y;
		Z = _Other.Z;
		W = _Other.W;
		return *this;
	}


	float4 operator+(const float4& _Other) const
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

	float4 operator-()
	{
		float4 Result;
		Result.X = -X;
		Result.Y = -Y;
		Result.Z = -Z;
		return Result;
	}

	float4 operator-(const float4& _Other) const
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
	static const Color8Bit Magenta;

	static const Color8Bit BlackA;
	static const Color8Bit RedA;
	static const Color8Bit GreenA;
	static const Color8Bit BlueA;
	static const Color8Bit WhiteA;
	static const Color8Bit MagentaA;


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

	Color8Bit()
	{

	}

	Color8Bit(
		unsigned char _R,
		unsigned char _G,
		unsigned char _B,
		unsigned char _A
	)
		:R(_R), G(_G), B(_B), A(_A)
	{

	}


	bool operator==(Color8Bit _Color)
	{
		return Color == _Color.Color;
	}

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

