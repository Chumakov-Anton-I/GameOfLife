#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QTimer>
#include <QList>

class QPainter;
class QBitmap;
class Grid;

class Map : public QWidget
{
    Q_OBJECT
public:
    explicit Map(int size = 64, QWidget *parent = nullptr);
    ~Map();

    void setSize(int size);
    void setTimeout(int timeout);

    bool saveImage(const QString &fileName) const;
    bool loadImage(const QString &fileName);

signals:
    void scoreChanged(unsigned long score);

private:
    QTimer m_timer;
    int m_timeout;
    int m_size;     // grid size
    int m_cellSize;
    unsigned long m_score;
    Grid *m_grid;
    bool m_loadGrid;
    bool m_hover;

    QPoint m_trackedCell;

    QPixmap *m_pixmap;
    QPainter *m_painter;
    QColor m_bgColor;
    QColor m_aliveColor;
    QColor m_highLight;

    void updateGrid();

public slots:
    void onStart();
    void onStop();
    void onReset();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent *event);
};

#endif // MAP_H
