#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <QRectF>
#include <QPainter>
#include <QColor>
#include <QEvent>
#include <QPoint>
#include <QMessageBox>
#include <QMouseEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "stones.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();
    ui->menuBar->hide();

    m_bIsBlackTurn = true;
    isJump = false;
    this->resize(1050, 990);            //the size of the window
    this->grabKeyboard();

    phyLocation = new QPoint(INIT_POSX, INIT_POSY);
    logLocation = new QPoint(0, 0);

    leftBoundAxis = new QPoint(-9, 0);
    rightBoundAxis = new QPoint(9, 0);
    upBoundAxis = new QPoint(0, -9);
    downBoundAxis = new QPoint(0, 9);


    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor("#B1723C"));
    this->setPalette(palette);
    centralWidget()->setMouseTracking(true);
    setMouseTracking(true);

    /**/
    Stone.push_back("0,0,1");
    Stone.push_back("10,10,2");
    Stone.push_back("9,-9,3");
    Stone.push_back("9,-10,1");
//    Stone.push_back("0,0,1");
//    Stone.push_back("0,0,1");
//    Stone.push_back("0,0,1");
//    Stone.push_back("0,0,1");

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    DrawChessboard();		//draw chess board
    DrawItems();			//draw chess stone
    //DrawItemWithMouse();

    drawLocatorWithKeyboard();  //draw the locator
    update();
}



void MainWindow::DrawChessboard()
{
    QPainter painter(this);             //construct base of the chessboard
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

    QPen pen = painter.pen();           //set the color of chessboard boundary
    pen.setColor(QColor("#8D5822"));
    pen.setWidth(7);
    painter.setPen(pen);

    QBrush brush;                       //set the background colcor of the chessboard
    brush.setColor(QColor("#EEC085"));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);            //draw the chessboard background color
    painter.drawRect(35, 35, 932, 932); //draw the boundary of the chess board


    pen.setColor(Qt::black);            //set the colot of the lines
    pen.setWidth(1);
    painter.setPen(pen);
    for (int i=0; i<19; i++)            //draw lines of the chessboard, 19 lines in total
    {
        painter.drawLine(50 + i*50, 50, 50 + i*50, 950);
        painter.drawLine(50, 50 + i*50, 950, 50 + i*50);
    }


    brush.setColor(Qt::black);          //draw five balck point on the chessboard
    painter.setBrush(brush);
    painter.drawRect(245, 245, 10, 10); //left up corner
    painter.drawRect(745, 245, 10, 10); //right up corner
    painter.drawRect(245, 745, 10, 10); //left down corner
    painter.drawRect(745, 745, 10, 10); //right down corner
    painter.drawRect(495, 495, 10, 10); //middle corner


    /* The coordinate indicator of the X axis and Y axis */
    QRect textVertical, textHorizontal1, textHorizontal2, textHorizontal3, textHorizontal4, textHorizontal5, textHorizontal6,
            textHorizontal7, textHorizontal8, textHorizontal9, textHorizontal10, textHorizontal11, textHorizontal12,
            textHorizontal13, textHorizontal14, textHorizontal15, textHorizontal16, textHorizontal17, textHorizontal18,
            textHorizontal19;
    QString verticalAxis, horizontalAxis1, horizontalAxis2, horizontalAxis3, horizontalAxis4, horizontalAxis5, horizontalAxis6,
            horizontalAxis7, horizontalAxis8, horizontalAxis9, horizontalAxis10, horizontalAxis11, horizontalAxis12,
            horizontalAxis13, horizontalAxis14, horizontalAxis15, horizontalAxis16, horizontalAxis17, horizontalAxis18,
            horizontalAxis19;

    textVertical.setRect(980, 42, 60, 950); textHorizontal1.setRect(45, 970, 30, 20); textHorizontal2.setRect(95, 970, 30, 20);
    textHorizontal3.setRect(145, 970, 30, 20); textHorizontal4.setRect(195, 970, 30, 20); textHorizontal5.setRect(245, 970, 30, 20);
    textHorizontal6.setRect(295, 970, 30, 20); textHorizontal7.setRect(345, 970, 30, 20); textHorizontal8.setRect(395, 970, 30, 20);
    textHorizontal9.setRect(445, 970, 30, 20); textHorizontal10.setRect(495, 970, 30, 20); textHorizontal11.setRect(545, 970, 30, 20);
    textHorizontal12.setRect(595, 970, 30, 20); textHorizontal13.setRect(645, 970, 30, 20); textHorizontal14.setRect(695, 970, 30, 20);
    textHorizontal15.setRect(745, 970, 30, 20); textHorizontal16.setRect(795, 970, 30, 20); textHorizontal17.setRect(845, 970, 30, 20);
    textHorizontal18.setRect(895, 970, 30, 20); textHorizontal19.setRect(945, 970, 30, 20);
    verticalAxis.sprintf("%d \n\n\n%d \n\n\n%d \n\n\n%d \n\n\n%d \n\n\n%d \n\n\n%d \n\n\n%d \n\n\n%d \n\n\n%d \n\n%d \n\n\n%d "
                         "\n\n\n%d \n\n\n%d \n\n\n%d \n\n\n%d \n\n\n%d \n\n\n%d \n\n\n%d",
                         upBoundAxis->y()+0, upBoundAxis->y()+1, upBoundAxis->y()+2, upBoundAxis->y()+3, upBoundAxis->y()+4,
                         upBoundAxis->y()+5, upBoundAxis->y()+6, upBoundAxis->y()+7, upBoundAxis->y()+8, upBoundAxis->y()+9,
                         upBoundAxis->y()+10, upBoundAxis->y()+11, upBoundAxis->y()+12, upBoundAxis->y()+13, upBoundAxis->y()+14,
                         upBoundAxis->y()+15, upBoundAxis->y()+16, upBoundAxis->y()+17, upBoundAxis->y()+18);

    horizontalAxis1.sprintf("%d", leftBoundAxis->x()+0); horizontalAxis2.sprintf("%d", leftBoundAxis->x()+1);
    horizontalAxis3.sprintf("%d", leftBoundAxis->x()+2); horizontalAxis4.sprintf("%d", leftBoundAxis->x()+3);
    horizontalAxis5.sprintf("%d", leftBoundAxis->x()+4); horizontalAxis6.sprintf("%d", leftBoundAxis->x()+5);
    horizontalAxis7.sprintf("%d", leftBoundAxis->x()+6); horizontalAxis8.sprintf("%d", leftBoundAxis->x()+7);
    horizontalAxis9.sprintf("%d", leftBoundAxis->x()+8); horizontalAxis10.sprintf("%d", leftBoundAxis->x()+9);
    horizontalAxis11.sprintf("%d", leftBoundAxis->x()+10); horizontalAxis12.sprintf("%d", leftBoundAxis->x()+11);
    horizontalAxis13.sprintf("%d", leftBoundAxis->x()+12); horizontalAxis14.sprintf("%d", leftBoundAxis->x()+13);
    horizontalAxis15.sprintf("%d", leftBoundAxis->x()+14); horizontalAxis16.sprintf("%d", leftBoundAxis->x()+15);
    horizontalAxis17.sprintf("%d", leftBoundAxis->x()+16); horizontalAxis18.sprintf("%d", leftBoundAxis->x()+17);
    horizontalAxis19.sprintf("%d", leftBoundAxis->x()+18);


    painter.drawText(textVertical, Qt::AlignTop, verticalAxis, nullptr);
    painter.drawText(textHorizontal1, Qt::AlignTop, horizontalAxis1, nullptr);
    painter.drawText(textHorizontal2, Qt::AlignTop, horizontalAxis2, nullptr);
    painter.drawText(textHorizontal3, Qt::AlignTop, horizontalAxis3, nullptr);
    painter.drawText(textHorizontal4, Qt::AlignTop, horizontalAxis4, nullptr);
    painter.drawText(textHorizontal5, Qt::AlignTop, horizontalAxis5, nullptr);
    painter.drawText(textHorizontal6, Qt::AlignTop, horizontalAxis6, nullptr);
    painter.drawText(textHorizontal7, Qt::AlignTop, horizontalAxis7, nullptr);
    painter.drawText(textHorizontal8, Qt::AlignTop, horizontalAxis8, nullptr);
    painter.drawText(textHorizontal9, Qt::AlignTop, horizontalAxis9, nullptr);
    painter.drawText(textHorizontal10, Qt::AlignTop, horizontalAxis10, nullptr);
    painter.drawText(textHorizontal11, Qt::AlignTop, horizontalAxis11, nullptr);
    painter.drawText(textHorizontal12, Qt::AlignTop, horizontalAxis12, nullptr);
    painter.drawText(textHorizontal13, Qt::AlignTop, horizontalAxis13, nullptr);
    painter.drawText(textHorizontal14, Qt::AlignTop, horizontalAxis14, nullptr);
    painter.drawText(textHorizontal15, Qt::AlignTop, horizontalAxis15, nullptr);
    painter.drawText(textHorizontal16, Qt::AlignTop, horizontalAxis16, nullptr);
    painter.drawText(textHorizontal17, Qt::AlignTop, horizontalAxis17, nullptr);
    painter.drawText(textHorizontal18, Qt::AlignTop, horizontalAxis18, nullptr);
    painter.drawText(textHorizontal19, Qt::AlignTop, horizontalAxis19, nullptr);
}


void MainWindow::DrawItems()
{
    QPainter painter(this);
    QPen pen = painter.pen();
    pen.setColor(Qt::transparent);
    painter.setPen(pen);

    for (int i=0; i<Stone.size(); i++)
    {
        /*get the exact location*/

        unsigned int first, second, third;
        first = Stone[i].find(',');
        second = Stone[i].find(',', first+1);

        string strX = Stone[i].substr(0, first);
        string strY = Stone[i].substr(first+1, second);
        string strPlay = Stone[i].substr(second+1, Stone.size());

        int x = atoi(strX.c_str());
        int y = atoi(strY.c_str());
        int player = atoi(strPlay.c_str());

        /*draw the chess stones one by one*/
        if( leftBoundAxis->x() <= x && x <= rightBoundAxis->x() && upBoundAxis->y() <= y && y <= downBoundAxis->y())
        {
            switch (player)
            {
            case 1 :
                painter.setBrush(Qt::red);
                break;
            case 2 :
                painter.setBrush(Qt::yellow);
                break;
            case 3 :
                painter.setBrush(Qt::blue);
                break;
            default:
                break;
            }

            if(i == Stone.size()-1 && isJump == false)
            {
                leftBoundAxis->setX(x-9);
                rightBoundAxis->setX(x+9);
                upBoundAxis->setY(y-9);
                downBoundAxis->setY(y+9);
                logLocation->setX(x);
                logLocation->setY(y);
                phyLocation->setX(INIT_POSX);
                phyLocation->setY(INIT_POSY);

                isJump = true;

//                pen.setColor(Qt::white);
//                pen.setWidth(50);
//                painter.setPen(pen);
//                painter.drawLine(40 + abs(leftBoundAxis->x()-x)*50, 50 + abs(upBoundAxis->y()-y)*50, 60 + abs(leftBoundAxis->x()-x)*50, 50 + abs(upBoundAxis->y()-y)*50);
//                painter.drawLine(50 + abs(leftBoundAxis->x()-x)*50, 40 + abs(upBoundAxis->y()-y)*50, 50 + abs(leftBoundAxis->x()-x)*50, 60 + abs(upBoundAxis->y()-y)*50);

                //cout<<"end player x: "<<x<<" y: "<<y<<" Player:"<<strPlay<<endl;
            }
            drawStoneAtPoint(painter, x, y);
        }
        //cout<<"x: "<<x<<" y: "<<y<<" Player:"<<strPlay<<endl;
    }
}


void MainWindow::drawStoneAtPoint(QPainter& painter, int logX, int logY)
{
    int phyX = 50 + abs(leftBoundAxis->x()-logX)*50;
    int phyY = 50 + abs(upBoundAxis->y()-logY)*50;
    //cout<<"x: "<<phyX<<" y: "<<phyY<<endl;
    QPoint ptCenter(phyX, phyY);
    painter.drawEllipse(phyX-25, phyY-25, 50, 50);

//    pen.setColor(Qt::white);
//    pen.setWidth(50);
//    painter.setPen(QPen(QColor(Qt::white)));
//    painter.drawLine(phyX-10, phyY, phyX+10, phyY);
//    painter.drawLine(phyX, phyY-10, phyX, phyY+10);


}


void MainWindow::DrawItemWithMouse()            //this function determine the colour of the mouse
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::transparent)));

    if (m_bIsBlackTurn)
        painter.setBrush(Qt::black);
    else
        painter.setBrush(Qt::white);

    //QPoint pt;
    //pt.setX( (QCursor::pos().x() ) / RECT_WIDTH);
    //pt.setY( (QCursor::pos().y() ) / RECT_HEIGHT);

    //DrawChessAtPoint(painter,pt);

    //painter.drawEllipse(mapFromGlobal(QCursor::pos()), RECT_WIDTH / 2, RECT_HEIGHT / 2);    //mapFromGlobal() -- translate global coordinate to widget coordinate

}


void MainWindow::drawLocatorWithKeyboard()
{
    QPainter painter(this);
    QPen pen = painter.pen();

    pen.setColor(Qt::red);
    pen.setWidth(3);
    painter.setPen(pen);

    painter.drawLine(phyLocation->x()-25, phyLocation->y()-25, phyLocation->x()-10, phyLocation->y()-25);
    painter.drawLine(phyLocation->x()+10, phyLocation->y()-25, phyLocation->x()+25, phyLocation->y()-25);
    painter.drawLine(phyLocation->x()+25, phyLocation->y()-25, phyLocation->x()+25, phyLocation->y()-10);
    painter.drawLine(phyLocation->x()+25, phyLocation->y()+10, phyLocation->x()+25, phyLocation->y()+25);
    painter.drawLine(phyLocation->x()+10, phyLocation->y()+25, phyLocation->x()+25, phyLocation->y()+25);
    painter.drawLine(phyLocation->x()-25, phyLocation->y()+25, phyLocation->x()-10, phyLocation->y()+25);
    painter.drawLine(phyLocation->x()-25, phyLocation->y()+25, phyLocation->x()-25, phyLocation->y()+10);
    painter.drawLine(phyLocation->x()-25, phyLocation->y()-10, phyLocation->x()-25, phyLocation->y()-25);

    QString msg;
    msg.sprintf("physical locator: %d, %d. logical locator: %d, %d.  left:%d, right:%d, up:%d, down:%d",
                phyLocation->x(), phyLocation->y(), logLocation->x(), logLocation->y(),
                leftBoundAxis->x(), rightBoundAxis->x(), upBoundAxis->y(), downBoundAxis->y());
    setWindowTitle(msg);
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left)      //dealing with the case that player press "A" key
    {
        logLocation->setX(logLocation->x() - 1);
        if(phyLocation->x() > 50)
            phyLocation->setX(phyLocation->x() - 50);
        else if (phyLocation->x() == 50)
        {
            leftBoundAxis->setX(leftBoundAxis->x()-1);
            rightBoundAxis->setX(rightBoundAxis->x()-1);
        }

    }
    else if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right)    //dealing with the case that player press "B" key
    {
        logLocation->setX(logLocation->x() + 1);
        if(phyLocation->x() < 950)
            phyLocation->setX(phyLocation->x() + 50);
        else if (phyLocation->x() == 950)
        {
            leftBoundAxis->setX(leftBoundAxis->x()+1);
            rightBoundAxis->setX(rightBoundAxis->x()+1);
        }
    }
    else if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up)   //dealing with the case that player press "W" key
    {
        logLocation->setY(logLocation->y() - 1);
        if(phyLocation->y() > 50)
            phyLocation->setY(phyLocation->y() - 50);
        else if (phyLocation->y() == 50)
        {
            upBoundAxis->setY(upBoundAxis->y()-1);
            downBoundAxis->setY(downBoundAxis->y()-1);
        }
    }
    else if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down) //dealing with the case that player press "S" key
    {
        logLocation->setY(logLocation->y() + 1);
        if(phyLocation->y() < 950)
            phyLocation->setY(phyLocation->y() + 50);
        else if (phyLocation->y() == 950)
        {
            upBoundAxis->setY(upBoundAxis->y()+1);
            downBoundAxis->setY(downBoundAxis->y()+1);
        }
    }
    else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        bool isRepeat = false;
        string strX, strY;
        for (int i=0; i<Stone.size(); i++)
        {
            unsigned int first, second;
            first = Stone[i].find(',');
            second = Stone[i].find(',', first+1);

            strX = Stone[i].substr(0, first);
            strY = Stone[i].substr(first+1, second);

            int x = atoi(strX.c_str());
            int y = atoi(strY.c_str());

            if (logLocation->x() == x && logLocation->y() == y)
                isRepeat = true;
        }
        if (isRepeat == false)
        {
            string stoneInfo;
            stringstream ssX, ssY;
            ssX<<logLocation->x();
            ssY<<logLocation->y();
            stoneInfo.append(ssX.str());
            stoneInfo.append(",");
            stoneInfo.append(ssY.str());
            stoneInfo.append(",2");


            /*need to check with network*/
            Stone.append(stoneInfo);
            isJump = false;
            //cout << "info: "<< stoneInfo<<endl;
        }
    }
}

//void MainWindow::mousePressEvent(QMouseEvent * e)
//{
//    //求鼠标点击处的棋子点pt
//    QPoint pt;
//    pt.setX( (e->pos().x() ) / RECT_WIDTH);
//    pt.setY( (e->pos().y() ) / RECT_HEIGHT);

//    //如果已存在棋子，就什么也不做
//    for (int i = 0; i<m_items.size(); i++)
//    {
//        Item item = m_items[i];
//        if (item.m_pt == pt)
//        {
//            //已有棋子
//            return;
//        }
//    }
//    //不存在棋子，就下一个
//    Item item(pt,m_bIsBlackTurn);
//    m_items.append(item);

//    //统计4个方向是否五子连
//    int nLeft =			CountNearItem(item,QPoint(-1,0));
//    int nLeftUp =		CountNearItem(item,QPoint(-1,-1));
//    int nUp =			CountNearItem(item,QPoint(0,-1));
//    int nRightUp =		CountNearItem(item,QPoint(1,-1));
//    int nRight =		CountNearItem(item,QPoint(1,0));
//    int nRightDown =	CountNearItem(item,QPoint(1,1));
//    int nDown =			CountNearItem(item,QPoint(0,1));
//    int nLeftDown =		CountNearItem(item,QPoint(-1,1));
//    if ( (nLeft + nRight) >= 4 ||
//         (nLeftUp + nRightDown) >= 4 ||
//         (nUp + nDown) >= 4 ||
//         (nRightUp + nLeftDown) >= 4 )
//    {
//        QString str = m_bIsBlackTurn?"Black win!":"White win!";     //if is black turn, print"black win!"
//        QMessageBox::information(nullptr, "GAME OVER", str, QMessageBox::Yes, QMessageBox::Yes);       //second: title. third: text
//        m_items.clear();
//        m_bIsBlackTurn = true;          //make balck is always the first
//        //NewGame();
//        return;
//    }
//    //该另一方下棋了
//    m_bIsBlackTurn = !m_bIsBlackTurn;
//}

//int MainWindow::CountNearItem(Item item,QPoint ptDirection)
//{
//    int nCount = 0;
//    item.m_pt += ptDirection;

//    while (m_items.contains(item))
//    {
//        nCount++;
//        item.m_pt += ptDirection;
//    }
//    return nCount;
//}


