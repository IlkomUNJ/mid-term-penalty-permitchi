#ifndef POLYGONPOINTS_H
#define POLYGONPOINTS_H

#include <QPoint>
#include <QVector>

struct polygonPoints {
    int x_min = std::numeric_limits<int>::max();
    int x_max = std::numeric_limits<int>::min();
    int y_min = std::numeric_limits<int>::max();
    int y_max = std::numeric_limits<int>::min();
};

/**
 * @brief Calculates the bounding box (min/max X and Y) for a list of QPoints.
 * @param points The vector of QPoints.
 * @return A polygonPoints structure containing the min/max coordinates.
 */
polygonPoints calculatepolygonPoints(const QVector<QPoint>& point);

#endif // POLYGONPOINTS_H
