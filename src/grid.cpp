#include "grid.h"

Grid::Grid(int size)
    : QImage(size, size, QImage::Format_Mono)
{
    setColor(DEAD, qRgb(0, 0, 0));
    setColor(ALIVE, qRgb(255, 255, 0));
    fill(DEAD);
}

Grid::Grid(const QImage &image)
{
    setColor(DEAD, qRgb(0, 0, 0));
    setColor(ALIVE, qRgb(255, 255, 0));
}

bool Grid::isAlive(int i, int j) const
{
    if (pixel(i, j) == color(DEAD))
        return false;
    return true;
}

void Grid::setAlive(int i, int j, bool state)
{
    if (!state) setPixel(i, j, DEAD);
    else        setPixel(i, j, ALIVE);
}

void Grid::flip(int i, int j)
{
    if (pixel(i, j) == color(DEAD))
        setPixel(i, j, ALIVE);
    else
        setPixel(i, j, DEAD);
}

bool Grid::save(const QString &fileName) const
{
    return QImage::save(fileName, nullptr, 100);
}
