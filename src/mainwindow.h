#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class QPushButton;
class QLineEdit;
class Map;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QPushButton *m_btnStart;
    QPushButton *m_btnStop;
    QPushButton *m_btnReset;
    QLineEdit   *m_scoreLabel;
    QPushButton *m_btnLoadImg;
    QPushButton *m_btnSaveImg;

    Map *m_map;

private slots:
    void showScore(unsigned long score);
    void loadImage();
    void saveImage();
};

#endif // MAINWINDOW_H
