#include "mainwindow.h"
#include "map.h"

#include <QBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}
{
    auto *topFrame = new QHBoxLayout;
    topFrame->setContentsMargins(2, 2, 2, 2);
    setLayout(topFrame);

    auto *cmdFrame = new QVBoxLayout;
    cmdFrame->setContentsMargins(2, 2, 2, 2);
    topFrame->addLayout(cmdFrame);

    m_map = new Map(128);
    topFrame->addWidget(m_map);

    m_btnStart = new QPushButton(tr("Start"));
    m_btnStop  = new QPushButton(tr("Stop"));
    m_btnReset = new QPushButton(tr("Reset"));
    m_scoreLabel = new QLineEdit;
    m_scoreLabel->setReadOnly(true);
    m_btnLoadImg = new QPushButton(tr("Load image.."));
    m_btnSaveImg = new QPushButton(tr("Save image.."));

    cmdFrame->addWidget(m_btnStart);
    cmdFrame->addWidget(m_btnStop);
    cmdFrame->addWidget(m_btnReset);
    cmdFrame->addWidget(m_scoreLabel);
    cmdFrame->addStretch(1);
    cmdFrame->addWidget(m_btnLoadImg);
    cmdFrame->addWidget(m_btnSaveImg);

    connect(m_btnStart, &QPushButton::clicked, m_map, &Map::onStart);
    connect(m_btnStop,  &QPushButton::clicked, m_map, &Map::onStop);
    connect(m_btnReset, &QPushButton::clicked, m_map, &Map::onReset);
    connect(m_map, &Map::scoreChanged, this, &MainWindow::showScore);
    connect(m_btnLoadImg, &QPushButton::clicked, this, &MainWindow::loadImage);
    connect(m_btnSaveImg, &QPushButton::clicked, this, &MainWindow::saveImage);
}

void MainWindow::showScore(unsigned long score)
{
    m_scoreLabel->setText(QString("Score: %1").arg(score));
}

void MainWindow::loadImage()
{
    QString fname = QFileDialog::getOpenFileName(this, tr("Open image"),
                                                 QString(),
                                                 tr("Images (*.jpg *.jpeg *.bmp *.png *.ppm)"));
    if (fname.isEmpty())    return;
    if (!m_map->loadImage(fname))
        QMessageBox::warning(this, tr("Warning"), tr("Cannot load image"));
}

void MainWindow::saveImage()
{
    m_map->onStop();
    QString fname = QFileDialog::getSaveFileName(this, tr("Save image as"),
                                                 QString(),
                                                 tr("Images (*.ppm)"));
    if (fname.isEmpty())    return;
    if (!fname.endsWith(".ppm", Qt::CaseInsensitive))
        fname += ".ppm";
    if (!m_map->saveImage(fname))
        QMessageBox::warning(this, tr("Warning"), tr("Cannot save file"));
}
