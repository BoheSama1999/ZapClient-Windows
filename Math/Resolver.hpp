#pragma once
#include <cmath>
#include "Vector3D.hpp"
#include "QAngle.hpp"

//visual studio cmath dont have these :(
#define M_E        2.71828182845904523536
#define M_LOG2E    1.44269504088896340736
#define M_LOG10E   0.434294481903251827651
#define M_LN2      0.693147180559945309417
#define M_LN10     2.30258509299404568402
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.785398163397448309616
#define M_1_PI     0.318309886183790671538
#define M_2_PI     0.636619772367581343076
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2    1.41421356237309504880
#define M_SQRT1_2  0.707106781186547524401

class Resolver {
public:
    static QAngle CalculateAngle(Vector3D from, Vector3D to) {
        Vector3D newDirection = to.Subtract(from);
        newDirection.Normalize();
        
        float pitch = -asinf(newDirection.z) * (180 / M_PI);
        float yaw = atan2f(newDirection.y, newDirection.x) * (180 / M_PI);

        return QAngle(pitch, yaw);
    }

    static Vector3D GetTargetPosition(const Vector3D& targetPosition, Vector3D targetVelocity, float time) {
        return targetPosition.Add((targetVelocity.Multiply(time))); // Subtract
    }

    static float GetTimeToTarget(Vector3D startPosition, Vector3D endPosition, float bulletSpeed) {
        float distance = (endPosition.Subtract(startPosition)).Magnitude();
        return distance / bulletSpeed; // * 1000
    }

    static float GetBasicBulletDrop(Vector3D startPosition, Vector3D endPosition, float bulletSpeed, float bulletDropRate) {
        float time = GetTimeToTarget(startPosition, endPosition, bulletSpeed);
        bulletDropRate *= 750.0f;
        return 0.5f * bulletDropRate * time * time;
    }

    static Vector3D GetTargetPosition(Vector3D startPosition, Vector3D endPosition, Vector3D targetVelocity, float bulletSpeed) {
        float time = GetTimeToTarget(startPosition, endPosition, bulletSpeed);
        return GetTargetPosition(endPosition, targetVelocity, time);
    }

    // Aim at moving target without bullet drop predicion
    static bool CalculateAimRotation(Vector3D startPosition, Vector3D endPosition, Vector3D targetVelocity, float bulletSpeed, QAngle& result) {
        endPosition = GetTargetPosition(startPosition, endPosition, targetVelocity, bulletSpeed);
        result = CalculateAngle(startPosition, endPosition);
        return true;
    }

    // Aim at moving target without bullet drop predicion
    static QAngle CalcAimRotation(Vector3D startPosition, Vector3D endPosition, Vector3D targetVelocity, float bulletSpeed, QAngle& result) {
        endPosition = GetTargetPosition(startPosition, endPosition, targetVelocity, bulletSpeed);
        result = CalculateAngle(startPosition, endPosition);
        return result;
    }

    // Aim at moving target without movement prediction
    static void CalculateAimRotationBasicDrop(Vector3D startPosition, Vector3D endPosition, Vector3D targetVelocity, float bulletSpeed, float bulletScale, QAngle& result) {
        endPosition.z += GetBasicBulletDrop(startPosition, endPosition, bulletSpeed, bulletScale);
        result = CalculateAngle(startPosition, endPosition);
    }

    static bool CalculateAimRotationNew(Vector3D start, Vector3D targetPosition, Vector3D targetVelocity, float bulletSpeed, float bulletScale, int steps, QAngle& result) {
        const float gravity = 750.0f / bulletScale;

        float angle = 0;
        float time = 0.0;
        float timeStep = 1.0f / steps;

        for(int i = 0; i < steps; i++) {
            Vector3D predictedPosition = GetTargetPosition(targetPosition, targetVelocity, time);
            if (!OptimalAngle(start, predictedPosition, bulletSpeed, gravity, angle))
                continue;

            Vector3D direction = predictedPosition.Subtract(start);
            float horizontalDistance = direction.Magnitude2D();
            float travelTime = horizontalDistance / (bulletSpeed * cosf(angle));
            if (travelTime <= time){
                result.x = -angle  * (180 / M_PI);
                result.y = atan2f(direction.y, direction.x)  * (180 / M_PI); //180
                return true;
            }
            time += timeStep;
        }

        targetPosition = GetTargetPosition(start, targetPosition, targetVelocity, bulletSpeed);
        result = CalculateAngle(start, targetPosition);
        return true;
    }

    static bool CalculatePrediction(Vector3D start, Vector3D targetPosition, Vector3D targetVelocity, float bulletSpeed, float bulletScale, int steps, QAngle& result) {
        const float gravity = 750.0f / bulletScale;

        float angle = 0;
        float time = 0.0;
        float timeStep = 1.0f / steps;

        for(int i = 0; i < steps; i++) {
            Vector3D predictedPosition = GetTargetPosition(targetPosition, targetVelocity, time);
            if (!OptimalAngle(start, predictedPosition, bulletSpeed, gravity, angle))
                continue;

            Vector3D direction = predictedPosition.Subtract(start);
            float horizontalDistance = direction.Magnitude2D();
            float travelTime = horizontalDistance / (bulletSpeed * cosf(angle));
            if (travelTime <= time){
                result.x = -angle  * (180 / M_PI);
                result.y = atan2f(direction.y, direction.x)  * (180 / M_PI); //180
            }
            time += timeStep;
        }

        targetPosition = GetTargetPosition(start, targetPosition, targetVelocity, bulletSpeed);
        result = CalculateAngle(start, targetPosition);
        return true;
    }

    static float GetTimeToTarget(const Vector3D start, const Vector3D end, const float speed, const float gravity) {
        float horizontalDistance = start.Distance2D(end);
        float heightDifference = end.z - start.z;
        return (speed * sqrtf(2 * sinf(M_PI / 4) / gravity)) + (sqrtf(2 * sinf(M_PI / 4) * (sinf(M_PI / 4) - 2 * heightDifference) / gravity));
    }

    static bool OptimalAngle(const Vector3D start, const Vector3D end, const float speed, const float gravity, float& angle) {
        float horizontalDistance = start.Distance2D(end);
        float heightDifference = end.z - start.z;
        
        float root = powf(speed, 4) - gravity * (gravity * powf(horizontalDistance, 2) + 2 * heightDifference * powf(speed, 2));
        if (root < 0.0)
            return false;

        float term1 = powf(speed, 2) - sqrt(root);
        float term2 = gravity * horizontalDistance;

        angle = atanf(term1 / term2);
        return true;
    }
};
