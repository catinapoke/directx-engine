#pragma once
#include <cmath>
#include "../InputDevice/SimpleMath.h"

#define M_PI 3.14159265358979323846
#define RAD2DEG (180 / M_PI)
#define DEG2RAD (M_PI / 180.0)

typedef DirectX::SimpleMath::Vector4 Vector4;
typedef DirectX::SimpleMath::Vector3 Vector3;
typedef DirectX::SimpleMath::Vector2 Vector2;
typedef DirectX::SimpleMath::Matrix Matrix;
typedef DirectX::SimpleMath::Quaternion Quaternion;

inline float CircleFloat(float value, float low, float hi)
{
    return value - (hi - low) * std::trunc((value - low) / (hi - low));
}

inline DirectX::SimpleMath::Vector3 CircleRotation(Vector3 rotation)
{
    rotation.x = CircleFloat(rotation.x, -M_PI, M_PI);
    rotation.y = CircleFloat(rotation.y, -M_PI, M_PI);
    rotation.z = CircleFloat(rotation.z, -M_PI, M_PI);
    return rotation;
}

template <typename T, typename Compare>
constexpr const T& clamp(const T& v, const T& lo, const T& hi, Compare comp) {
    return comp(v, lo) ? lo : comp(hi, v) ? hi : v;
}

template <typename T>
constexpr const T& clamp(const T& v, const T& lo, const T& hi) {
    return clamp(v, lo, hi, std::less<>());
}

// Has errors, need testing
inline Vector3 EulerBetweenVectors(Vector3 one, Vector3 two)
{
    return {
        static_cast<float>(acos(Vector2(one.y, one.z).Dot({ two.y, two.z })) * RAD2DEG),
        static_cast<float>(acos(Vector2(one.x, one.z).Dot({ two.x, two.z })) * RAD2DEG),
        static_cast<float>(acos(Vector2(one.x, one.y).Dot({ two.x, two.y })) * RAD2DEG)
    };
}