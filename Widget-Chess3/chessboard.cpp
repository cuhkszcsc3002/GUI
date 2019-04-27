#include <QRectF>
#include <QPainter>
#include <QColor>
#include <QEvent>
#include <QPoint>
#include <QMessageBox>
#include <QMouseEvent>
#include "chessboard.h"
//#include "ui_mainwindow.h"


ChessBoard::ChessBoard(QWidget *parent) : QMainWindow(parent)//, ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    //ui->mainToolBar->hide();
    //ui->menuBar->hide();

    resize((CHESS_COLUMES + 1)*RECT_WIDTH  ,(CHESS_ROWS + 1)*RECT_HEIGHT);

    m_bIsBlackTurn = true;

    int mouseX = mapFromGlobal(QCursor::pos()).x();
    int mouseY = mapFromGlobal(QCursor::pos()).y();
    QString msg;
    msg.sprintf("move: %d, %d", mouseX, mouseY);
    setWindowTitle(msg);
}

ChessBoard::~ChessBoard()
{
    delete ui;
}

void ChessBoard::startReceived()
{
    this->show();
}

void ChessBoard::paintEvent(QPaintEvent *e)
{
    DrawChessboard();		//鐢绘鐩?
    DrawItems();			//鐢绘瀛?
    DrawItemWithMouse();	//鐢婚紶鏍囷紙褰撳墠鏂圭殑妫嬪瓙褰㈢姸锛?

    update();
}

void ChessBoard::DrawChessboard()
{
    QPainter painter(this);         //construct the painter
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    painter.setBrush(QColor("#EEC085"));                //background color of the rectangle
    painter.setPen(QPen(QColor(Qt::black),2));          //color: black. font: 2


    int mouseX = mapFromGlobal(QCursor::pos()).x();                 //get the position of mouse, unit is pix
    int mouseY = mapFromGlobal(QCursor::pos()).y();

    int leftBound = mouseX, rightBound = mouseX, upBound = mouseY, lowBound = mouseY, numOfColume, numOfRow;
    for (int i = 0; i<m_items.size(); i++)                          //find the four bound of the chess board, need to translate the unit from index to pix
    {
        Item item = m_items[i];
        if(item.m_pt.x()*50 + 25 > rightBound)
            rightBound = item.m_pt.x()*50 + 25;
        if(item.m_pt.x()*50 + 25 < leftBound)
            leftBound = item.m_pt.x()*50 + 25;
        if(item.m_pt.y()*50 + 25 < upBound)
            upBound = item.m_pt.y()*50 + 25;
        if(item.m_pt.y()*50 + 25 > lowBound)
            lowBound = item.m_pt.y()*50 + 25;
    }

    numOfColume = (rightBound - leftBound) / 50;
    numOfRow = (lowBound - upBound) / 50;
    leftBound = (leftBound / 50) * 50;
    upBound = (upBound / 50) * 50;
    for(int i = 0; i < numOfColume+6; i++)                  //draw rectangle to represent the chess board
    {
        for(int j = 0; j < numOfRow+6; j++)
        {
            painter.drawRect(leftBound+(i)*RECT_WIDTH-150, upBound+(j)*RECT_HEIGHT-150, RECT_WIDTH, RECT_HEIGHT);
        }
    }

    int ptx = 0, pty = 0;
    if(m_items.isEmpty() == false)
    {
        ptx = m_items[m_items.size()-1].m_pt.x();
        pty = m_items[m_items.size()-1].m_pt.y();
    }
    QString msg;
    //msg.sprintf("move: %d, %d.      leftBound: %d,  upBound: %d", mouseX, mouseY, leftBound, upBound);
    msg.sprintf("mouse: %d, %d.      point: %d, %d", mouseX, mouseY, ptx, pty);
    setWindowTitle(msg);
    /*/
    for(int i = 0; i < CHESS_COLUMES; i++)
    {
        for (int j = 0; j < CHESS_ROWS; j++)
        {
            painter.drawRect( (i)*RECT_WIDTH, (j)*RECT_HEIGHT, RECT_WIDTH, RECT_HEIGHT);        //draw many many little rectangles, these rectangles form the chess board
        }   //first two is the coordinate of upper left corner. second two is width and heigth. Add 0.5 will make the chess land into the cross
    }
    /*/
}

void ChessBoard::DrawItems()
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::transparent)));

    for (int i = 0; i<m_items.size(); i++)          //put all the chess that in the vector onto the chess board
    {
        Item item = m_items[i];
        if (item.m_bBlack)                          //if the value is true, set the point as black, else set the point as white
            painter.setBrush(Qt::black);
        else
            painter.setBrush(Qt::white);
        DrawChessAtPoint(painter,item.m_pt);        //draw the chess
    }
}

void ChessBoard::DrawChessAtPoint(QPainter& painter,QPoint& pt)
{
    //painter.drawRect( (pt.x()+0.5)*RECT_WIDTH,(pt.y()+0.5)*RECT_HEIGHT,RECT_WIDTH,RECT_HEIGHT);

    QPoint ptCenter((pt.x()+0.5)*RECT_WIDTH, (pt.y()+0.5)*RECT_HEIGHT);         //the center of the chess
    //painter.drawEllipse(ptCenter, RECT_WIDTH/2, RECT_HEIGHT/2);               //draw a circle with half radius
    painter.drawEllipse((pt.x())*RECT_WIDTH+5, (pt.y())*RECT_HEIGHT+5, 40, 40); //draw a circle with radius is 40 pix
}

void ChessBoard::DrawItemWithMouse()            //this function determine the colour of the mouse
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

    painter.drawEllipse(mapFromGlobal(QCursor::pos()), RECT_WIDTH / 2, RECT_HEIGHT / 2);    //mapFromGlobal() -- translate global coordinate to widget coordinate

}

void ChessBoard::mousePressEvent(QMouseEvent * e)
{
    //姹傞紶鏍囩偣鍑诲鐨勬瀛愮偣pt
    QPoint pt;
    pt.setX( (e->pos().x() ) / RECT_WIDTH);
    pt.setY( (e->pos().y() ) / RECT_HEIGHT);

    //濡傛灉宸插瓨鍦ㄦ瀛愶紝灏变粈涔堜篃涓嶅仛
    for (int i = 0; i<m_items.size(); i++)
    {
        Item item = m_items[i];
        if (item.m_pt == pt)
        {
            //宸叉湁妫嬪瓙
            return;
        }
    }
    //涓嶅瓨鍦ㄦ瀛愶紝灏变笅涓€涓?
    Item item(pt,m_bIsBlackTurn);
    m_items.append(item);

    //缁熻4涓柟鍚戞槸鍚︿簲瀛愯繛
    int nLeft =			CountNearItem(item,QPoint(-1,0));
    int nLeftUp =		CountNearItem(item,QPoint(-1,-1));
    int nUp =			CountNearItem(item,QPoint(0,-1));
    int nRightUp =		CountNearItem(item,QPoint(1,-1));
    int nRight =		CountNearItem(item,QPoint(1,0));
    int nRightDown =	CountNearItem(item,QPoint(1,1));
    int nDown =			CountNearItem(item,QPoint(0,1));
    int nLeftDown =		CountNearItem(item,QPoint(-1,1));
    if ( (nLeft + nRight) >= 4 ||
         (nLeftUp + nRightDown) >= 4 ||
         (nUp + nDown) >= 4 ||
         (nRightUp + nLeftDown) >= 4 )
    {
        QString str = m_bIsBlackTurn?"Black win!":"White win!";     //if is black turn, print"black win!"
        QMessageBox::information(NULL, "GAME OVER", str, QMessageBox::Yes, QMessageBox::Yes);       //second: title. third: text
        m_items.clear();
        m_bIsBlackTurn = true;          //make balck is always the first
        //NewGame();
        return;
    }
    //璇ュ彟涓€鏂逛笅妫嬩簡
    m_bIsBlackTurn = !m_bIsBlackTurn;
}

void ChessBoard::mouseMoveEvent(QMouseEvent *e)
{
    for(int i = 0; i<10; i++)
    {
        for(int j = 0; j<10; j++)
        {

        }
    }
}


int ChessBoard::CountNearItem(Item item,QPoint ptDirection)
{
    int nCount = 0;
    item.m_pt += ptDirection;

    while (m_items.contains(item))
    {
        nCount++;
        item.m_pt += ptDirection;
    }
    return nCount;
}


/*/
//bool MainWindow::FindItem(Item item)
//{
//	bool bFind = false;
//	for (int i = 0; i<m_items.size(); i++)
//	{
//		Item item = m_items[i];
//		if (item.m_pt == pt)
//		{
//			bFind = true;
//			break;
//		}
//	}
//	return bFind;
//}
/*/
