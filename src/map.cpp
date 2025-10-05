#include "map.h"
#include "grid.h"

#include <QPainter>
#include <QMouseEvent>
#include <QBitArray>

Map::Map(int size, QWidget *parent)
    : QWidget{parent}, m_timeout{10}, m_size{size}, m_cellSize{6},
    m_grid{nullptr}, m_loadGrid{false}, m_pixmap{nullptr},
    m_bgColor{Qt::black}, m_aliveColor{Qt::yellow}
{
    m_painter = new QPainter;
    onReset();
    connect(&m_timer, &QTimer::timeout, this, QOverload<>::of(&Map::update));
}

Map::~Map()
{
    delete m_painter;
    delete m_grid;
    delete m_pixmap;
}

void Map::setSize(int size)
{
    m_size = size;
    onReset();
}

void Map::setTimeout(int timeout)
{
    bool active = m_timer.isActive();   // save timer status
    m_timer.stop();
    m_timeout = timeout;
    if (active)
        m_timer.start(m_timeout);   // restore timer status
}

bool Map::saveImage(const QString &fileName) const
{
    return m_grid->save(fileName);
}

bool Map::loadImage(const QString &fileName)
{
    m_timer.stop();
    QImage src(fileName);
    if (src.format() == QImage::Format_Invalid)
        return false;

    delete m_grid;
    int sz = qMin(src.width(), src.height());
    if (sz > 128)   m_size = 128;
    else            m_size = sz;
    m_grid = new Grid(src.copy(0, 0, m_size, m_size).convertToFormat(QImage::Format_Mono));
    resize(m_size*m_cellSize, m_size*m_cellSize);
    setMinimumSize(size());

    delete m_pixmap;
    m_pixmap = new QPixmap(size());
    m_pixmap->fill(m_bgColor);

    m_score = 0ul;
    emit scoreChanged(m_score);
    update();
    return true;
}

void Map::updateGrid()
{
    if (!m_timer.isActive()) return;    // do nothing if timer is inactive
    QBitArray moores(8);
    Grid newGrid = m_grid->copy();
    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            // skip cells on borders
            /*if (i == 0 || i == m_size - 1 || j == 0 || j == m_size - 1)
                continue;*/
            int ip = i - 1, in = i + 1, jp = j - 1, jn = j + 1;
            if (i == 0)          ip = m_size - 1;
            if (i == m_size - 1) in = 0;
            if (j == 0)          jp = m_size - 1;
            if (j == m_size - 1) jn = 0;
            // Moore's neighborhood
            moores[0] = newGrid.isAlive(ip, jp);
            moores[1] = newGrid.isAlive(i,  jp);
            moores[2] = newGrid.isAlive(in, jp);
            moores[3] = newGrid.isAlive(ip,  j);
            moores[4] = newGrid.isAlive(in,  j);
            moores[5] = newGrid.isAlive(ip, jn);
            moores[6] = newGrid.isAlive(i,  jn);
            moores[7] = newGrid.isAlive(in, jn);
            int count = moores.count(true); // look for alive cells
            if (count == 3) {
                if (!newGrid.isAlive(i, j))
                    m_grid->setAlive(i, j, true);
            }
            else if (count < 2 || count > 3)
                m_grid->setAlive(i, j, false);
        }
    }
    ++m_score;
    emit scoreChanged(m_score);
}

void Map::onStart()
{
    m_timer.start(m_timeout);
}

void Map::onStop()
{
    m_timer.stop();
}

void Map::onReset()
{
    m_timer.stop();
    delete m_grid;
    delete m_pixmap;

    m_grid = new Grid(m_size);
    resize(m_size*m_cellSize, m_size*m_cellSize);
    setMinimumSize(size());

    m_pixmap = new QPixmap(size());
    m_pixmap->fill(m_bgColor);

    m_score = 0ul;
    emit scoreChanged(m_score);
    update();   // don't forget redraw widget
}

void Map::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    updateGrid();
    m_painter->begin(m_pixmap);
    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            QRect rct(i*m_cellSize, j*m_cellSize, m_cellSize, m_cellSize);
            if (m_grid->isAlive(i, j))
                m_painter->fillRect(rct, m_aliveColor);
            else
                m_painter->fillRect(rct, m_bgColor);
        }
    }
    m_painter->end();
    m_painter->begin(this);
    m_painter->drawPixmap(m_pixmap->rect(), *m_pixmap);
    m_painter->end();
}

void Map::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;
    bool timerState = m_timer.isActive();   // memorise timer state
    m_timer.stop();
    QPoint pos = event->pos();
    int x = pos.x() / m_cellSize;
    int y = pos.y() / m_cellSize;
    m_grid->flip(x, y);
    if (timerState) // restore timer if it was active
        m_timer.start(m_timeout);
    else
        update();
}
