#pragma once

#include "MathUtil.h"
#include "Point.h"

namespace uge
{

    /**
     * @class Rect
     *  A rectangle.
     */
    struct Rect
    {
        /// Top-left point of the rectangle.
        math::Point2f point;
        /// Width of the rectangle.
        float width;
        /// Height of the rectangle.
        float height;

        /**
         * Constructor.
         */
        Rect();

        /**
         *  Constructor.
         * @param fX : upper left X coordinate of the rectangle.
         * @param fY : upper left Y coordiante of the rectangle.
         * @param fWidth : width of the rectangle.
         * @param fHeight : height of the rectangle.
         */
        Rect(float fX, float fY, float fWidth, float fHeight);

        /**
         *  Assigns a new values to the rectangle.
         * @param fX : upper left X coordinate of the rectangle.
         * @param fY : upper left Y coordiante of the rectangle.
         * @param fWidth : width of the rectangle.
         * @param fHeight : height of the rectangle.
         */
        void Assign(float fX, float fY, float fWidth, float fHeight);

        /**
         *  Calculates the area of the rectangle.
         * @return : the rectangle's area.
         */
        const float GetArea() const;

        /**
         *  Calculates the perimeter of the rectangle.
         * @return : the rectangle's perimeter.
         */
        const float GetPerimeter() const;
    };

    const bool operator == (const Rect& left, const Rect& right);
    const bool operator != (const Rect& left, const Rect& right);

    /**
     *  Checks if a Point is inside of a rectangle.
     * @param point : a point.
     * @param rect : a rectangle.
     * @return : true if the intersection of the point and the rectangle isn't nil,
     *           false otherwise.
     */
    const bool PointRectIntersection(const Point2f& point, const Rect& rect);

}
