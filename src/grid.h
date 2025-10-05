#ifndef GRID_H
#define GRID_H

#include <QImage>

class Grid : public QImage
{
public:
    explicit Grid(int size);
    Grid(const QImage &image);
    ~Grid() {}

    bool isAlive(int i, int j) const;
    void setAlive(int i, int j, bool state);
    void flip(int i, int j);

    Grid copy() const { return Grid(QImage::copy()); }
    bool save(const QString &fileName) const;

private:
    enum ColorIndx { DEAD = 0, ALIVE };
};

#endif // GRID_H
