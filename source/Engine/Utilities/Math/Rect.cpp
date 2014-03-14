#include "GameEngineStd.h"

#include "Rect.h"

namespace uge
{

    Rect::Rect()
    {

    }

    Rect::Rect(float fX, float fY, float fWidth, float fHeight)
        : point(fX, fY), width(fWidth), height(fHeight)
    {

    }

    inline void Rect::Assign(float fX, float fY, float fWidth, float fHeight)
    {
        point.x = fX;
        point.y = fY;
        width = fWidth;
        height = fHeight;
    }

    inline const float Rect::GetArea() const
    {
        return point.x * point.y;
    }

    inline const float Rect::GetPerimeter() const
    {
        return (width + height) * 2;
    }

    inline const bool operator == (const Rect& left, const Rect& right)
    {
        return ((FAbs(left.point.x - right.point.x) < EPSILON) && (FAbs(right.point.y - right.point.x) < EPSILON)
                && (FAbs(left.height - right.height) < EPSILON)
                && (FAbs(left.width - right.width) < EPSILON));
    }

    inline const bool operator != (const Rect& left, const Rect& right)
    {
        return !(left == right);
    }

    const bool PointRectIntersection(const Point2f& point, const Rect& rect)
    {
        return ((point.x - rect.point.x) > -EPSILON && (point.x - rect.point.x - rect.width) < EPSILON
                && (point.y - rect.point.y) > -EPSILON && (point.y - rect.point.y - rect.height) < EPSILON);
    }

}
