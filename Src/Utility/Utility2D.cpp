#include "Utility2D.h"
#include <cmath>

double Utility2D::Magnitude(const Vector2& v)
{
    return sqrt((v.x * v.x) + (v.y * v.y));
}

int Utility2D::SqrMagnitude(const Vector2& v)
{
    return v.x * v.x + v.y * v.y;
}

double Utility2D::Distance(const Vector2& v1, const Vector2& v2)
{
    return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
}

Vector2 Utility2D::WorldToMapPos(const Vector2& worldPos, const Vector2& mapSize)
{
    Vector2 mapPos = worldPos;
    mapPos.x = static_cast<int>(worldPos.x / mapSize.x);
    mapPos.y = static_cast<int>(worldPos.y / mapSize.y);
    return mapPos;
}

Vector2 Utility2D::MapToWorldPos(const Vector2& mapPos, const Vector2& mapSize)
{
    Vector2 worldPos = mapPos;
    worldPos.x = static_cast<int>(mapPos.x * mapSize.x);
    worldPos.y = static_cast<int>(mapPos.y * mapSize.y);
    return worldPos;
}

bool Utility2D::IsHitCircles(const Vector2& circlePos1, const float radius1, const Vector2& circlePos2, const float radius2)
{
    // ���S�_�Ԃ�X�EY�������v�Z
    float dx = circlePos1.x - circlePos2.x;  // X�����̍�
    float dy = circlePos1.y - circlePos2.y;  // Y�����̍�

    // ���S�ԋ�����2��
    float distanceSq = dx * dx + dy * dy;

    // ���a�̘a��2��
    float radiusSum = radius1 + radius2;
    float radiusSumSq = radiusSum * radiusSum;

    // ������2�� <= ���a�̘a��2�� �� �Փ�
    return distanceSq <= radiusSumSq;
}
