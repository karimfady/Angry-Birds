

#include "birdieblast.h"
#include "ui_birdieblast.h"
using namespace std;
BirdieBlast::BirdieBlast(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BirdieBlast)
{
    ui->setupUi(this);


}
BirdieBlast::BirdieBlast(int c)
{
    //Message Box
       msgBox.setText("Do you want to start the game?");
       msgBox.setIcon(QMessageBox::Information);
       QPushButton *button1 = msgBox.addButton("Yes", QMessageBox::AcceptRole);
          QPushButton *button2 = msgBox.addButton("No", QMessageBox::RejectRole);
       int x= msgBox.exec();
  if (x == QMessageBox::AcceptRole) {

       msgBox1.setText("keys used are W,A,S and D");
          msgBox1.setIcon(QMessageBox::Information);
           msgBox1.setStandardButtons(QMessageBox::Ok);
          msgBox1.exec();

      this->setFocusPolicy(Qt::StrongFocus);
      scene = new QGraphicsScene(0,0,1600,900);
      backgroundPic=QPixmap(":/background birdieblast.jpeg");
      backgroundPic=backgroundPic.scaledToHeight(900);
      backgroundItem=new QGraphicsPixmapItem;
      backgroundItem->setPixmap(backgroundPic);
      scene->addItem(backgroundItem);


       //bird
          birdPic=QPixmap(":/angrybird.png");
          birdPic.setMask(birdPic.createMaskFromColor(Qt::transparent));
          birdItem=new QGraphicsPixmapItem;
          birdPic=birdPic.scaledToHeight(40);
          birdPic=birdPic.scaledToWidth(40);
          birdItem->setPixmap(birdPic);
          birdMove=new QPushButton;
          birdMove->setIcon(QIcon(birdPic));
          birdMove->setIconSize(birdPic.size());
          birdMove->setStyleSheet("background-color: transparent; border: none; color: white;");
          scene->addWidget(birdMove);
          birdMove->hide();

          levelItem=new QGraphicsTextItem;
          QFont font = levelItem->font();
          font.setBold(true);
          font.setPointSize(25);
          levelItem->setFont(font);
          levelItem->setPos(10,10);
          levelItem->setDefaultTextColor(Qt::black);
          levelItem->setPlainText("Level: 1");
             scene->addItem(levelItem);

             winLoss=new QGraphicsTextItem;
              font = winLoss->font();
             font.setBold(true);
             font.setPointSize(20);
             winLoss->setFont(font);
             winLoss->setPos(250,450);
             winLoss->setDefaultTextColor(Qt::black);
             winLoss->setPlainText("");
             scene->addItem(winLoss);

             shotsRemText=new QGraphicsTextItem;
             font =shotsRemText->font();
             font.setBold(true);
             font.setPointSize(25);
            shotsRemText->setFont(font);
             shotsRemText->setPos(1100,10);
             shotsRemText->setDefaultTextColor(Qt::black);
             shotsRemText->setPlainText("Remaining Shots: ");
             scene->addItem(shotsRemText);

            //Shooter
             shooterPic=QPixmap(":/shooter-removebg.png");
             shooterPic.setMask(shooterPic.createMaskFromColor(Qt::transparent));
             shooterItem=new QGraphicsPixmapItem;
             shooterPic=shooterPic.scaledToHeight(70);
             shooterPic=shooterPic.scaledToWidth(150);
             shooterItem->setPos(100,665);
             shooterItem->setPixmap(shooterPic);
             scene->addItem(shooterItem);

             //Shooter Wheel
                 wheelPic=QPixmap(":/shooter wheel.png");
                 wheelPic.setMask(wheelPic.createMaskFromColor(Qt::transparent));
                 wheelItem=new QGraphicsPixmapItem;
                 wheelPic=wheelPic.scaledToHeight(80);
                 wheelPic=wheelPic.scaledToWidth(80);
                 wheelItem->setPos(100,700);
                 wheelItem->setPixmap(wheelPic);
                 scene->addItem(wheelItem);


               //force bar
               forcePic=QPixmap(":/merged colors for force bar.jpeg");
               forceItem=new QGraphicsPixmapItem;
               //orcePic=forcePic.scaledToHeight(175);
               forcePic=forcePic.scaledToWidth(35);
               forcePic = forcePic.scaled(birdPic.width(), 175);
               forceItem->setPos(1297.5,460);
               forceItem->setPixmap(forcePic);
               scene->addItem(forceItem);

               //Cursor
               cursor=new QGraphicsRectItem;
                cursor->setRect(1295,635,45,7);
               cursor->setBrush(QColor("black"));
               scene->addItem(cursor);

              changeLevel(1);

              view = new QGraphicsView(scene, this);
              view->setGeometry(0,0,1600,900);


      y=cursor->y();
      //
      } else if (x == QMessageBox::RejectRole) {
        exit;
      }

}



void BirdieBlast::levelConstructor(){
    numOfTargets = 0;
    shots = 0;
    if(!targetItems.empty())
      for(int i=0;i<targetItems.size();i++)
    {
        targetItems[i]->hide();
    }
    if(!obstacleItems.empty())
      for(int i=0;i<obstacleItems.size();i++)
    {
        obstacleItems[i]->hide();
    }
    targetItems.clear();
    explosionItems.clear();
    obstacleItems.clear();
    correctShots=0;
}


void  BirdieBlast::changeLevel(int L){
    QString x;
    QString stringNo;
    switch(L){
    case 1: //2 shots
    levelConstructor();
    maxShots=2;
    shotsRem=maxShots;
    stringNo = QString::number(shotsRem);
    x="Remaining Shots: "+stringNo;
    shotsRemText->setPlainText(x);
    explosionItem = new QGraphicsPixmapItem;
    explosion = explosion.scaledToHeight(100);
    explosion = explosion.scaledToWidth(100);
    explosionItem->setPos(975, 725);
    explosionItem->setPixmap(explosion);
    explosionItem->hide();
    explosionItems.push_back(explosionItem);
    scene->addItem(explosionItems[numOfTargets]);

    targetItem = new QGraphicsPixmapItem;
    target = target.scaledToHeight(50);
    target = target.scaledToWidth(50);
    targetItem->setPos(1000, 725);
    targetItem->setPixmap(target);
    targetItems.push_back(targetItem);
    scene->addItem(targetItems[numOfTargets]);
    numOfTargets++;

    break;


    case 2: // 2 shots
        levelConstructor();
         maxShots=2;
         shotsRem=maxShots;
        correctShots=0;
        Obstacle=QPixmap(":/wall.jpeg");
        ObstacleItem=new QGraphicsPixmapItem;
        Obstacle=Obstacle.scaledToWidth(100);
        Obstacle=Obstacle.scaledToHeight(150);
        ObstacleItem->setPos(900,625);
        ObstacleItem->setPixmap(Obstacle);
        obstacleItems.push_back(ObstacleItem);
        scene->addItem(obstacleItems[0]);

        explosionItem=new QGraphicsPixmapItem;
        explosion=explosion.scaledToHeight(100);
        explosion=explosion.scaledToWidth(100);
        explosionItem->setPos(950,575);
        explosionItem->setPixmap(explosion);
        explosionItem->hide();
        explosionItems.push_back(explosionItem);
        scene->addItem(explosionItems[numOfTargets]);

        targetItem=new QGraphicsPixmapItem;
        target=target.scaledToHeight(50);
        target=target.scaledToWidth(50);
        targetItem->setPos(975,575);
        targetItem->setPixmap(target);
        targetItems.push_back(targetItem);
        scene->addItem(targetItems[numOfTargets]);
        numOfTargets++;
         break;

    case 3: //2 shots
         levelConstructor();
          maxShots=2;
          shotsRem=maxShots;
         Obstacle=QPixmap((":/tower.png"));
         ObstacleItem=new QGraphicsPixmapItem;
         Obstacle=Obstacle.scaledToWidth(100);
         Obstacle=Obstacle.scaledToHeight(200);
         ObstacleItem->setPos(850,585);
         ObstacleItem->setPixmap(Obstacle);
         obstacleItems.push_back(ObstacleItem);
         scene->addItem(obstacleItems[0]);

         explosionItem=new QGraphicsPixmapItem;
         explosion=explosion.scaledToHeight(100);
         explosion=explosion.scaledToWidth(100);
         explosionItem->setPos(900,545);
         explosionItem->setPixmap(explosion);
         explosionItem->hide();
         explosionItems.push_back(explosionItem);
         scene->addItem(explosionItems[numOfTargets]);

         targetItem=new QGraphicsPixmapItem;
         target=target.scaledToHeight(50);
         target=target.scaledToWidth(50);
         targetItem->setPos(910,545);
         targetItem->setPixmap(target);
         targetItems.push_back(targetItem);
         scene->addItem(targetItems[numOfTargets]);
         numOfTargets++;
          break;

    case 4:// 3 shots

        levelConstructor();
         maxShots=3;
         shotsRem=maxShots;
         Obstacle=QPixmap((":/tower.png"));
         ObstacleItem=new QGraphicsPixmapItem;
         Obstacle=Obstacle.scaledToWidth(100);
         Obstacle=Obstacle.scaledToHeight(200);
         ObstacleItem->setPos(900,585);
         ObstacleItem->setPixmap(Obstacle);
         obstacleItems.push_back(ObstacleItem);
         scene->addItem(obstacleItems[0]);

         explosionItem=new QGraphicsPixmapItem;
         explosion=explosion.scaledToHeight(100);
         explosion=explosion.scaledToWidth(100);
         explosionItem->setPos(910,545);
         explosionItem->setPixmap(explosion);
         explosionItem->hide();
         explosionItems.push_back(explosionItem);
         scene->addItem(explosionItems[numOfTargets]);

         targetItem=new QGraphicsPixmapItem;
         target=target.scaledToHeight(50);
         target=target.scaledToWidth(50);
         targetItem->setPos(960,545);
         targetItem->setPixmap(target);
         targetItems.push_back(targetItem);
         scene->addItem(targetItems[numOfTargets]);
         numOfTargets++;

         explosionItem=new QGraphicsPixmapItem;
         explosion=explosion.scaledToHeight(100);
         explosion=explosion.scaledToWidth(100);
         explosionItem->setPos(1000,725);
         explosionItem->setPixmap(explosion);
         explosionItem->hide();
         explosionItems.push_back(explosionItem);
         scene->addItem(explosionItems[numOfTargets]);

         targetItem=new QGraphicsPixmapItem;
         target=target.scaledToHeight(50);
         target=target.scaledToWidth(50);
         targetItem->setPos(1050,725);
         targetItem->setPixmap(target);
         targetItems.push_back(targetItem);
         scene->addItem(targetItems[numOfTargets]);
         numOfTargets++;

          break;

    case 5: //same as case 4 but 1 shot

         levelConstructor();
          maxShots=1;
          shotsRem=maxShots;
         Obstacle=QPixmap((":/tower.png"));
         ObstacleItem=new QGraphicsPixmapItem;
         Obstacle=Obstacle.scaledToWidth(100);
         Obstacle=Obstacle.scaledToHeight(200);
         ObstacleItem->setPos(900,585);
         ObstacleItem->setPixmap(Obstacle);
         obstacleItems.push_back(ObstacleItem);
         scene->addItem(obstacleItems[0]);

         explosionItem=new QGraphicsPixmapItem;
         explosion=explosion.scaledToHeight(100);
         explosion=explosion.scaledToWidth(100);
         explosionItem->setPos(910,545);
         explosionItem->setPixmap(explosion);
         explosionItem->hide();
         explosionItems.push_back(explosionItem);
         scene->addItem(explosionItems[numOfTargets]);

         targetItem=new QGraphicsPixmapItem;
         target=target.scaledToHeight(50);
         target=target.scaledToWidth(50);
         targetItem->setPos(960,545);
         targetItem->setPixmap(target);
         targetItems.push_back(targetItem);
         scene->addItem(targetItems[numOfTargets]);
         numOfTargets++;

         explosionItem=new QGraphicsPixmapItem;
         explosion=explosion.scaledToHeight(100);
         explosion=explosion.scaledToWidth(100);
         explosionItem->setPos(1000,725);
         explosionItem->setPixmap(explosion);
         explosionItem->hide();
         explosionItems.push_back(explosionItem);
         scene->addItem(explosionItems[numOfTargets]);

         targetItem=new QGraphicsPixmapItem;
         target=target.scaledToHeight(50);
         target=target.scaledToWidth(50);
         targetItem->setPos(1050,725);
         targetItem->setPixmap(target);
         targetItems.push_back(targetItem);
         scene->addItem(targetItems[numOfTargets]);
         numOfTargets++;

         break;

             case 6: //3 shots
         levelConstructor();
          maxShots=3;
          shotsRem=maxShots;
          Obstacle=QPixmap((":tower.png"));
          ObstacleItem=new QGraphicsPixmapItem;
          Obstacle=Obstacle.scaledToWidth(100);
          Obstacle=Obstacle.scaledToHeight(200);
          ObstacleItem->setPos(500,585);
          ObstacleItem->setPixmap(Obstacle);
          obstacleItems.push_back(ObstacleItem);
          scene->addItem(obstacleItems[0]);

          Obstacle=QPixmap(":wall.jpeg");
          ObstacleItem=new QGraphicsPixmapItem;
          Obstacle=Obstacle.scaledToWidth(100);
          Obstacle=Obstacle.scaledToHeight(100);
          ObstacleItem->setPos(900,675);
          ObstacleItem->setPixmap(Obstacle);
          obstacleItems.push_back(ObstacleItem);
          scene->addItem(obstacleItems[1]);

          Obstacle=QPixmap((":/tower.png"));
          ObstacleItem=new QGraphicsPixmapItem;
          Obstacle=Obstacle.scaledToWidth(100);
          Obstacle=Obstacle.scaledToHeight(200);
          ObstacleItem->setPos(867,485);
          ObstacleItem->setPixmap(Obstacle);
          obstacleItems.push_back(ObstacleItem);
          scene->addItem(obstacleItems[2]);

          explosionItem=new QGraphicsPixmapItem;
          explosion=explosion.scaledToHeight(100);
          explosion=explosion.scaledToWidth(100);
          explosionItem->setPos(880,445);
          explosionItem->setPixmap(explosion);
          explosionItem->hide();
          explosionItems.push_back(explosionItem);
          scene->addItem(explosionItems[numOfTargets]);

          targetItem=new QGraphicsPixmapItem;
          target=target.scaledToHeight(50);
          target=target.scaledToWidth(50);
          targetItem->setPos(930,445);
          targetItem->setPixmap(target);
          targetItems.push_back(targetItem);
          scene->addItem(targetItems[numOfTargets]);
          numOfTargets++;

          explosionItem=new QGraphicsPixmapItem;
          explosion=explosion.scaledToHeight(100);
          explosion=explosion.scaledToWidth(100);
          explosionItem->setPos(510,545);
          explosionItem->setPixmap(explosion);
          explosionItem->hide();
          explosionItems.push_back(explosionItem);
          scene->addItem(explosionItems[numOfTargets]);

          targetItem=new QGraphicsPixmapItem;
          target=target.scaledToHeight(50);
          target=target.scaledToWidth(50);
          targetItem->setPos(560,545);
          targetItem->setPixmap(target);
          targetItems.push_back(targetItem);
          scene->addItem(targetItems[numOfTargets]);
          numOfTargets++;
         break;

          case 7: //3 shots
         levelConstructor();
          maxShots=3;
          shotsRem=maxShots;
         Obstacle=QPixmap((":tower.png"));
         ObstacleItem=new QGraphicsPixmapItem;
         Obstacle=Obstacle.scaledToWidth(100);
         Obstacle=Obstacle.scaledToHeight(200);
         ObstacleItem->setPos(500,585);
         ObstacleItem->setPixmap(Obstacle);
         obstacleItems.push_back(ObstacleItem);
         scene->addItem(obstacleItems[0]);

         Obstacle=QPixmap(":wall.jpeg");
         ObstacleItem=new QGraphicsPixmapItem;
         Obstacle=Obstacle.scaledToWidth(100);
         Obstacle=Obstacle.scaledToHeight(100);
         ObstacleItem->setPos(900,675);
         ObstacleItem->setPixmap(Obstacle);
         obstacleItems.push_back(ObstacleItem);
         scene->addItem(obstacleItems[1]);

         Obstacle=QPixmap((":/tower.png"));
         ObstacleItem=new QGraphicsPixmapItem;
         Obstacle=Obstacle.scaledToWidth(100);
         Obstacle=Obstacle.scaledToHeight(200);
         ObstacleItem->setPos(867,485);
         ObstacleItem->setPixmap(Obstacle);
         obstacleItems.push_back(ObstacleItem);
         scene->addItem(obstacleItems[2]);

         explosionItem=new QGraphicsPixmapItem;
         explosion=explosion.scaledToHeight(100);
         explosion=explosion.scaledToWidth(100);
         explosionItem->setPos(880,445);
         explosionItem->setPixmap(explosion);
         explosionItem->hide();
         explosionItems.push_back(explosionItem);
         scene->addItem(explosionItems[numOfTargets]);

         targetItem=new QGraphicsPixmapItem;
         target=target.scaledToHeight(50);
         target=target.scaledToWidth(50);
         targetItem->setPos(930,445);
         targetItem->setPixmap(target);
         targetItems.push_back(targetItem);
         scene->addItem(targetItems[numOfTargets]);
         numOfTargets++;


         explosionItem=new QGraphicsPixmapItem;
         explosion=explosion.scaledToHeight(100);
         explosion=explosion.scaledToWidth(100);
         explosionItem->setPos(510,545);
         explosionItem->setPixmap(explosion);
         explosionItem->hide();
         explosionItems.push_back(explosionItem);
         scene->addItem(explosionItems[numOfTargets]);

         targetItem=new QGraphicsPixmapItem;
         target=target.scaledToHeight(50);
         target=target.scaledToWidth(50);
         targetItem->setPos(560,545);
         targetItem->setPixmap(target);
         targetItems.push_back(targetItem);
         scene->addItem(targetItems[numOfTargets]);
         numOfTargets++;

         explosionItem=new QGraphicsPixmapItem;
         explosion=explosion.scaledToHeight(100);
         explosion=explosion.scaledToWidth(100);
         explosionItem->setPos(1000,725);
         explosionItem->setPixmap(explosion);
         explosionItem->hide();
         explosionItems.push_back(explosionItem);
         scene->addItem(explosionItems[numOfTargets]);

         targetItem=new QGraphicsPixmapItem;
         target=target.scaledToHeight(50);
         target=target.scaledToWidth(50);
         targetItem->setPos(1050,725);
         targetItem->setPixmap(target);
         targetItems.push_back(targetItem);
         scene->addItem(targetItems[numOfTargets]);
         numOfTargets++;

         break;

          case 8: //same as level 6 but 2 tries only
         levelConstructor();
          maxShots=2;
          shotsRem=maxShots;
         Obstacle=QPixmap((":tower.png"));
         ObstacleItem=new QGraphicsPixmapItem;
         Obstacle=Obstacle.scaledToWidth(100);
         Obstacle=Obstacle.scaledToHeight(200);
         ObstacleItem->setPos(500,585);
         ObstacleItem->setPixmap(Obstacle);
         obstacleItems.push_back(ObstacleItem);
         scene->addItem(obstacleItems[0]);

         Obstacle=QPixmap(":wall.jpeg");
         ObstacleItem=new QGraphicsPixmapItem;
         Obstacle=Obstacle.scaledToWidth(100);
         Obstacle=Obstacle.scaledToHeight(100);
         ObstacleItem->setPos(900,675);
         ObstacleItem->setPixmap(Obstacle);
         obstacleItems.push_back(ObstacleItem);
         scene->addItem(obstacleItems[1]);

         Obstacle=QPixmap((":/tower.png"));
         ObstacleItem=new QGraphicsPixmapItem;
         Obstacle=Obstacle.scaledToWidth(100);
         Obstacle=Obstacle.scaledToHeight(200);
         ObstacleItem->setPos(867,485);
         ObstacleItem->setPixmap(Obstacle);
         obstacleItems.push_back(ObstacleItem);
         scene->addItem(obstacleItems[2]);

         explosionItem=new QGraphicsPixmapItem;
         explosion=explosion.scaledToHeight(100);
         explosion=explosion.scaledToWidth(100);
         explosionItem->setPos(880,445);
         explosionItem->setPixmap(explosion);
         explosionItem->hide();
         explosionItems.push_back(explosionItem);
         scene->addItem(explosionItems[numOfTargets]);

         targetItem=new QGraphicsPixmapItem;
         target=target.scaledToHeight(50);
         target=target.scaledToWidth(50);
         targetItem->setPos(930,445);
         targetItem->setPixmap(target);
         targetItems.push_back(targetItem);
         scene->addItem(targetItems[numOfTargets]);
         numOfTargets++;


         explosionItem=new QGraphicsPixmapItem;
         explosion=explosion.scaledToHeight(100);
         explosion=explosion.scaledToWidth(100);
         explosionItem->setPos(510,545);
         explosionItem->setPixmap(explosion);
         explosionItem->hide();
         explosionItems.push_back(explosionItem);
         scene->addItem(explosionItems[numOfTargets]);

         targetItem=new QGraphicsPixmapItem;
         target=target.scaledToHeight(50);
         target=target.scaledToWidth(50);
         targetItem->setPos(560,545);
         targetItem->setPixmap(target);
         targetItems.push_back(targetItem);
         scene->addItem(targetItems[numOfTargets]);
         numOfTargets++;

         explosionItem=new QGraphicsPixmapItem;
         explosion=explosion.scaledToHeight(100);
         explosion=explosion.scaledToWidth(100);
         explosionItem->setPos(1000,725);
         explosionItem->setPixmap(explosion);
         explosionItem->hide();
         explosionItems.push_back(explosionItem);
         scene->addItem(explosionItems[numOfTargets]);

         targetItem=new QGraphicsPixmapItem;
         target=target.scaledToHeight(50);
         target=target.scaledToWidth(50);
         targetItem->setPos(1050,725);
         targetItem->setPixmap(target);
         targetItems.push_back(targetItem);
         scene->addItem(targetItems[numOfTargets]);
         numOfTargets++;

         break;

          case 9: //3 shots
         levelConstructor();
         maxShots=3;
         shotsRem=maxShots;
         Obstacle=QPixmap((":tower.png"));
         ObstacleItem=new QGraphicsPixmapItem;
         Obstacle=Obstacle.scaledToWidth(100);
         Obstacle=Obstacle.scaledToHeight(200);
         ObstacleItem->setPos(500,585);
         ObstacleItem->setPixmap(Obstacle);
         obstacleItems.push_back(ObstacleItem);
         scene->addItem(obstacleItems[0]);

         Obstacle=QPixmap(":wall.jpeg");
         ObstacleItem=new QGraphicsPixmapItem;
         Obstacle=Obstacle.scaledToWidth(100);
         Obstacle=Obstacle.scaledToHeight(100);
         ObstacleItem->setPos(900,675);
         ObstacleItem->setPixmap(Obstacle);
         obstacleItems.push_back(ObstacleItem);
         scene->addItem(obstacleItems[1]);

         Obstacle=QPixmap((":/tower.png"));
         ObstacleItem=new QGraphicsPixmapItem;
         Obstacle=Obstacle.scaledToWidth(100);
         Obstacle=Obstacle.scaledToHeight(200);
         ObstacleItem->setPos(867,485);
         ObstacleItem->setPixmap(Obstacle);
         obstacleItems.push_back(ObstacleItem);
         scene->addItem(obstacleItems[2]);

         explosionItem=new QGraphicsPixmapItem;
         explosion=explosion.scaledToHeight(100);
         explosion=explosion.scaledToWidth(100);
         explosionItem->setPos(880,445);
         explosionItem->setPixmap(explosion);
         explosionItem->hide();
         explosionItems.push_back(explosionItem);
         scene->addItem(explosionItems[numOfTargets]);

         targetItem=new QGraphicsPixmapItem;
         target=target.scaledToHeight(50);
         target=target.scaledToWidth(50);
         targetItem->setPos(930,445);
         targetItem->setPixmap(target);
         targetItems.push_back(targetItem);
         scene->addItem(targetItems[numOfTargets]);
         numOfTargets++;

         explosionItem=new QGraphicsPixmapItem;
         explosion=explosion.scaledToHeight(100);
         explosion=explosion.scaledToWidth(100);
         explosionItem->setPos(705,725);
         explosionItem->setPixmap(explosion);
         explosionItem->hide();
         explosionItems.push_back(explosionItem);
         scene->addItem(explosionItems[numOfTargets]);

         targetItem=new QGraphicsPixmapItem;
         target=target.scaledToHeight(50);
         target=target.scaledToWidth(50);
         targetItem->setPos(755,725);
         targetItem->setPixmap(target);
         targetItems.push_back(targetItem);
         scene->addItem(targetItems[numOfTargets]);
         numOfTargets++;


         explosionItem=new QGraphicsPixmapItem;
         explosion=explosion.scaledToHeight(100);
         explosion=explosion.scaledToWidth(100);
         explosionItem->setPos(510,545);
         explosionItem->setPixmap(explosion);
         explosionItem->hide();
         explosionItems.push_back(explosionItem);
         scene->addItem(explosionItems[numOfTargets]);

         targetItem=new QGraphicsPixmapItem;
         target=target.scaledToHeight(50);
         target=target.scaledToWidth(50);
         targetItem->setPos(560,545);
         targetItem->setPixmap(target);
         targetItems.push_back(targetItem);
         scene->addItem(targetItems[numOfTargets]);
         numOfTargets++;

         explosionItem=new QGraphicsPixmapItem;
         explosion=explosion.scaledToHeight(100);
         explosion=explosion.scaledToWidth(100);
         explosionItem->setPos(1005,725);
         explosionItem->setPixmap(explosion);
         explosionItem->hide();
         explosionItems.push_back(explosionItem);
         scene->addItem(explosionItems[numOfTargets]);

         targetItem=new QGraphicsPixmapItem;
         target=target.scaledToHeight(50);
         target=target.scaledToWidth(50);
         targetItem->setPos(1055,725);
         targetItem->setPixmap(target);
         targetItems.push_back(targetItem);
         scene->addItem(targetItems[numOfTargets]);
         numOfTargets++;

         break;
          case 10: //same as case 9 but 2 shots
         levelConstructor();
          maxShots=2;
          shotsRem=maxShots;
         Obstacle=QPixmap((":tower.png"));
         ObstacleItem=new QGraphicsPixmapItem;
         Obstacle=Obstacle.scaledToWidth(100);
         Obstacle=Obstacle.scaledToHeight(200);
         ObstacleItem->setPos(500,585);
         ObstacleItem->setPixmap(Obstacle);
         obstacleItems.push_back(ObstacleItem);
         scene->addItem(obstacleItems[0]);

         Obstacle=QPixmap(":wall.jpeg");
         ObstacleItem=new QGraphicsPixmapItem;
         Obstacle=Obstacle.scaledToWidth(100);
         Obstacle=Obstacle.scaledToHeight(100);
         ObstacleItem->setPos(900,675);
         ObstacleItem->setPixmap(Obstacle);
         obstacleItems.push_back(ObstacleItem);
         scene->addItem(obstacleItems[1]);

         Obstacle=QPixmap((":/tower.png"));
         ObstacleItem=new QGraphicsPixmapItem;
         Obstacle=Obstacle.scaledToWidth(100);
         Obstacle=Obstacle.scaledToHeight(200);
         ObstacleItem->setPos(867,485);
         ObstacleItem->setPixmap(Obstacle);
         obstacleItems.push_back(ObstacleItem);
         scene->addItem(obstacleItems[2]);

         explosionItem=new QGraphicsPixmapItem;
         explosion=explosion.scaledToHeight(100);
         explosion=explosion.scaledToWidth(100);
         explosionItem->setPos(880,445);
         explosionItem->setPixmap(explosion);
         explosionItem->hide();
         explosionItems.push_back(explosionItem);
         scene->addItem(explosionItems[numOfTargets]);

         targetItem=new QGraphicsPixmapItem;
         target=target.scaledToHeight(50);
         target=target.scaledToWidth(50);
         targetItem->setPos(930,445);
         targetItem->setPixmap(target);
         targetItems.push_back(targetItem);
         scene->addItem(targetItems[numOfTargets]);
         numOfTargets++;

         explosionItem=new QGraphicsPixmapItem;
         explosion=explosion.scaledToHeight(100);
         explosion=explosion.scaledToWidth(100);
         explosionItem->setPos(705,725);
         explosionItem->setPixmap(explosion);
         explosionItem->hide();
         explosionItems.push_back(explosionItem);
         scene->addItem(explosionItems[numOfTargets]);

         targetItem=new QGraphicsPixmapItem;
         target=target.scaledToHeight(50);
         target=target.scaledToWidth(50);
         targetItem->setPos(755,725);
         targetItem->setPixmap(target);
         targetItems.push_back(targetItem);
         scene->addItem(targetItems[numOfTargets]);
         numOfTargets++;


         explosionItem=new QGraphicsPixmapItem;
         explosion=explosion.scaledToHeight(100);
         explosion=explosion.scaledToWidth(100);
         explosionItem->setPos(510,545);
         explosionItem->setPixmap(explosion);
         explosionItem->hide();
         explosionItems.push_back(explosionItem);
         scene->addItem(explosionItems[numOfTargets]);

         targetItem=new QGraphicsPixmapItem;
         target=target.scaledToHeight(50);
         target=target.scaledToWidth(50);
         targetItem->setPos(560,545);
         targetItem->setPixmap(target);
         targetItems.push_back(targetItem);
         scene->addItem(targetItems[numOfTargets]);
         numOfTargets++;

         explosionItem=new QGraphicsPixmapItem;
         explosion=explosion.scaledToHeight(100);
         explosion=explosion.scaledToWidth(100);
         explosionItem->setPos(1005,725);
         explosionItem->setPixmap(explosion);
         explosionItem->hide();
         explosionItems.push_back(explosionItem);
         scene->addItem(explosionItems[numOfTargets]);

         targetItem=new QGraphicsPixmapItem;
         target=target.scaledToHeight(50);
         target=target.scaledToWidth(50);
         targetItem->setPos(1055,725);
         targetItem->setPixmap(target);
         targetItems.push_back(targetItem);
         scene->addItem(targetItems[numOfTargets]);
         numOfTargets++;

         break;

    case 11:
        levelConstructor();
        winLoss->setPlainText("You have completed all the levels of the game, more levels are coming in the next semester ;)");
         break;
    }
}
QPoint BirdieBlast::projectile(int t){
    double angleRadians = qDegreesToRadians(angle);
    double vx=vinit*cos(angleRadians);
    double vy=vinit*sin(angleRadians);
    int X,Y;
    X=birdInitialPosition.x()+(vx*t);
    Y=birdInitialPosition.y()-(vy*t-(0.5*9.81*t*t));
    QPoint p(X,Y);
    return p;
}

void BirdieBlast::fillPath(){
    if(path.size()!=0){
        for(int i=0;i<path.size();i++)
            pathItems[i]->hide();
            pathItems.clear();
            path.clear();
    }
    angle=360-rotation;
    int cursorPos;
    cursorPos=abs(cursor->y());
    vinit=((cursorPos/10)*4)+45;
    for(int i=0;i<40;i++){
        path.push_back(projectile(i));
        if(path[i].y()>720)
        {
            birdFinalIndex=i;
            break;
        }
    }


}


void BirdieBlast::keyPressEvent(QKeyEvent *event){
  if(event->key()==Qt::Key_D)
     {
      if(cursor->y()>=y-170)
      cursor->setPos(x(),cursor->y()-10);
      fillPath();
      for(int i=0;i<path.size();i++)
      {
          //birdItem->setPos(path[i]);
          QGraphicsEllipseItem* pathItem = new QGraphicsEllipseItem(path[i].x(), path[i].y(), 5, 5);
          pathItem->setBrush(QBrush(Qt::white));
          pathItems.push_back(pathItem);
          scene->addItem(pathItem);
      }
  }
  if(event->key()==Qt::Key_A)
     {
      if(cursor->y()<y)
      cursor->setPos(x(),cursor->y()+10);
      fillPath();
      for(int i=0;i<path.size();i++)
      {
          //birdItem->setPos(path[i]);
          QGraphicsEllipseItem* pathItem = new QGraphicsEllipseItem(path[i].x(), path[i].y(), 5, 5);
          pathItem->setBrush(QBrush(Qt::white));
          pathItems.push_back(pathItem);
          scene->addItem(pathItem);
      }
  }
  if(event->key()==Qt::Key_W)
     {
   if(rotation<=360&&rotation>280)
   {
       QPointF center = shooterItem->boundingRect().center();
       shooterItem->setTransformOriginPoint(center.x()-35,center.y());
       shooterItem->setRotation(rotation-10);
       rotation=rotation-10;
       fillPath();
       for(int i=0;i<path.size();i++)
       {
           QGraphicsEllipseItem* pathItem = new QGraphicsEllipseItem(path[i].x(), path[i].y(), 5, 5);
           pathItem->setBrush(QBrush(Qt::white));
           pathItems.push_back(pathItem);
           scene->addItem(pathItem);
       }
   }
   QPointF localRightSideCenter(shooterItem->pixmap().width()+xOffset, shooterItem->pixmap().height() / 2 + yOffset);
   QPointF sceneRightSideCenter = shooterItem->mapToScene(localRightSideCenter);
   birdInitialPosition=sceneRightSideCenter;
   fillPath();
   for(int i=0;i<path.size();i++)
   {
       QGraphicsEllipseItem* pathItem = new QGraphicsEllipseItem(path[i].x(), path[i].y(), 5, 5);
       pathItem->setBrush(QBrush(Qt::white));
       pathItems.push_back(pathItem);
       scene->addItem(pathItem);
   }
}

  if(event->key()==Qt::Key_S)
     {
      if(rotation<360&&rotation>=280)
      {
          shooterItem->setRotation(rotation+10);
          rotation=rotation+10;
      }
      QPointF localRightSideCenter(shooterItem->pixmap().width()+xOffset, shooterItem->pixmap().height() / 2 + yOffset);
      QPointF sceneRightSideCenter = shooterItem->mapToScene(localRightSideCenter);
      birdInitialPosition=sceneRightSideCenter;
      fillPath();
      for(int i=0;i<path.size();i++)
      {
          QGraphicsEllipseItem* pathItem = new QGraphicsEllipseItem(path[i].x(), path[i].y(), 5, 5);
          pathItem->setBrush(QBrush(Qt::white));
          pathItems.push_back(pathItem);
          scene->addItem(pathItem);
      }
  }
  if(event->key()==Qt::Key_Space)
     {
     birdItem->hide();
      qDebug()<<"Level: "<<level<<" Num of targets: "<<numOfTargets<<" Path size: "<<path.size();
      if(path.size()!=0){//1
              scene->addItem(birdItem);
          for(int i=0;i<path.size();i++)
              pathItems[i]->hide();
              pathItems.clear();
              path.clear();
      }


      for(int i=0;i<=birdFinalIndex;i++){//4
          birdItem->setPos(path[i]);
          for(int j=0;j<numOfTargets;j++){//5
          if(((birdItem->x()+40)>=targetItems[j]->x())&&(birdItem->x()<=(targetItems[j]->x()+50)))
          {//3
          if(((birdItem->y()+40)>=targetItems[j]->y())&&(birdItem->y()<=(targetItems[j]->y()+50)))
                {//2
              if(targetItems[j]->isVisible()){//
              targetItems[j]->hide();
              explosionItems[j]->show();
                   QTimer *timer = new QTimer();
                    timer->setSingleShot(true);
                     QObject::connect(timer, &QTimer::timeout, [=]() {
                     explosionItems[j]->hide();
                     QCoreApplication::processEvents();
                     });
                       timer->start(2000);
              correctShots++;
              }//
                }//2
          }//3
         }//5
      }//4
//  }//1

      shotsRem--;
      QString x;
      QString stringNo = QString::number(shotsRem);
      x="Shots Remaining: "+stringNo;
      shotsRemText->setPlainText(x);
        if(shotsRem==0){
             winLoss->setPlainText("You Lost, TRY AGAIN");
          QTimer *timer = new QTimer();
           timer->setSingleShot(true);
            QObject::connect(timer, &QTimer::timeout, [=]() {
                  changeLevel(level);
                  winLoss->setPlainText(" ");
            QCoreApplication::processEvents();
            });
              timer->start(3000);
     }

 if(correctShots==numOfTargets){
     level++;
     winLoss->setPlainText("              You won, off to the next level!");
     QString stringNo = QString::number(shotsRem);
     x="Shots Remaining: "+stringNo;
     shotsRemText->setPlainText(x);
     QTimer *timer = new QTimer();
      timer->setSingleShot(true);
       QObject::connect(timer, &QTimer::timeout, [=]() {
           QString x;
           QString stringNo = QString::number(level);
           x="Level: "+stringNo;
           levelItem->setPlainText(x);
           winLoss->setPlainText(" ");
           changeLevel(level);
           stringNo = QString::number(shotsRem);
           x="Shots Remaining: "+stringNo;
           shotsRemText->setPlainText(x);

       QCoreApplication::processEvents();
       });
         timer->start(3000);
  }



   }


}


BirdieBlast::~BirdieBlast()
{
    delete ui;
}


