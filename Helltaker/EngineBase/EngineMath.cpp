#include "EngineMath.h"

const float UEngineMath::PI = 3.14159265358979323846264338327950288419716939937510f;
const float UEngineMath::PI2 = UEngineMath::PI * 2.0f;
const float UEngineMath::DToR = UEngineMath::PI / 180.0f;
const float UEngineMath::RToD = 180.0f / UEngineMath::PI;


const float4 float4::Zero = { 0.0f, 0.0f, 0.0f, 0.0f };
const float4 float4::Left = { -1.0f, 0.0f, 0.0f, 0.0f };
const float4 float4::Right = { 1.0f, 0.0f, 0.0f, 0.0f };
const float4 float4::Up = { 0.0f, -1.0f, 0.0f, 0.0f };
const float4 float4::Down = { 0.0f, 1.0f, 0.0f, 0.0f };

const Color8Bit Color8Bit::Black = { 0, 0, 0, 255 };
const Color8Bit Color8Bit::Red = { 255, 0, 0, 255 };
const Color8Bit Color8Bit::Green = { 0, 255, 0, 255 };
const Color8Bit Color8Bit::Blue = { 0, 0, 255, 255 };
const Color8Bit Color8Bit::Yellow = { 255, 255, 0, 255 };
const Color8Bit Color8Bit::White = { 255, 255, 255, 255 };
const Color8Bit Color8Bit::Magenta = { 255, 0, 255, 255 };
const Color8Bit Color8Bit::Orange = { 255, 170, 46, 255 };


const Color8Bit Color8Bit::BlackA = { 0, 0, 0, 0 };
const Color8Bit Color8Bit::RedA = { 255, 0, 0, 0 };
const Color8Bit Color8Bit::GreenA = { 0, 255, 0, 0 };
const Color8Bit Color8Bit::BlueA = { 0, 0, 255, 0 };
const Color8Bit Color8Bit::YellowA = { 255, 255, 0, 0 };
const Color8Bit Color8Bit::WhiteA = { 255, 255, 255, 0 };
const Color8Bit Color8Bit::MagentaA = { 255, 0, 255, 0 };
const Color8Bit Color8Bit::OrangeA = { 255, 170, 46, 0 };
UEngineMath::UEngineMath()
{
}

UEngineMath::~UEngineMath()
{
}

