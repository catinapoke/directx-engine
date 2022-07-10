#pragma once
#include "../InputDevice/SimpleMath.h"

struct SphericalCoords
{
    float radius;
    float v_angle;
    float h_angle;
};

inline DirectX::SimpleMath::Vector3 Spherical2Cartesian(SphericalCoords point)
{
    return {
        static_cast<float>(point.radius * sin(point.v_angle) * cos(point.h_angle)),
        static_cast<float>(point.radius * sin(point.v_angle) * sin(point.h_angle)),
        static_cast<float>(point.radius * cos(point.v_angle))
    };
}

inline SphericalCoords Cartesian2Spherical(DirectX::SimpleMath::Vector3 point)
{
    const double radius = sqrt(pow(point.x, 2) + pow(point.y, 2) + pow(point.z, 2));
    return {
        static_cast<float>(radius),
        static_cast<float>(acos(point.z / radius)),
        static_cast<float>(atan(point.y / point.x))
    };
}