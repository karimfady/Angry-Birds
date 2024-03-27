#ifndef BIRDIEBLAST_H
#define BIRDIEBLAST_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <cmath>
#include <QGraphicsItem>
#include <QPropertyAnimation>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <vector>
#include <QDebug>
#include <QTimer>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <QPointF>
#include <QThread>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include "bird.h"

using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class BirdieBlast; }
QT_END_NAMESPACE

class BirdieBlast : public QMainWindow, public bird
{
    Q_OBJECT

public:
    //Message Box
    QMessageBox msgBox;
     QMessageBox msgBox1;
    //Scene and view
    QGraphicsScene *scene;
    QGraphicsPixmapItem *backgroundItem;
    QPixmap backgroundPic;

    QGraphicsPixmapItem *birdItem;
    QPixmap birdPic;
    QPushButton *birdMove;
    vector <QGraphicsPixmapItem*> lives;
    QGraphicsPixmapItem* livesItem;
    QPropertyAnimation *animation;

    QGraphicsPixmapItem *wheelItem;
    QPixmap wheelPic;

    QGraphicsPixmapItem *shooterItem;
    QPixmap shooterPic;

    QGraphicsPixmapItem *forceItem;
    QPixmap forcePic;

    //Projectile Part
    int rotation=360;
    int vinitial=0;
    int shots=0;
    int angle=0;
    int vinit;
    QPointF birdInitialPosition;
    QPointF birdFinalPosition;
    int birdFinalIndex;
    qreal yOffset = -27.5;
    qreal xOffset = -10.0;
    vector <QPoint> path;
    vector <QGraphicsEllipseItem*> pathItems;
    QPoint projectile(int t);

    //Handling Levels
    void fillPath();
    void levelConstructor();
    void changeLevel(int L);
    int maxShots=0;
    int shotsRem=10;
    int level=1;
    int correctShots=0;

    QGraphicsView *view;
    BirdieBlast(QWidget *parent = nullptr);
    BirdieBlast(int c);

    QGraphicsRectItem *cursor;
    void keyPressEvent(QKeyEvent *event)override;

    //Target
    QPixmap target=QPixmap(":/woodTarget.jpeg");
    QPixmap Obstacle;
     QGraphicsPixmapItem* targetItem;
     QGraphicsPixmapItem* ObstacleItem;
     vector <QGraphicsPixmapItem*> targetItems;
     vector <QGraphicsPixmapItem*> obstacleItems;
     int numOfTargets=0;

     //Explosion
     QGraphicsPixmapItem* explosionItem;
     vector <QGraphicsPixmapItem*> explosionItems;
     QPixmap explosion=QPixmap(":/explosion.png");

     //Text Items
     QGraphicsTextItem *levelItem;
     QGraphicsTextItem *winLoss;
     QGraphicsTextItem *shotsRemText;


int y;
    ~BirdieBlast();

private:
    Ui::BirdieBlast *ui;
};
#endif // BIRDIEBLAST_H
