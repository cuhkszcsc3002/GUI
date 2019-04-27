#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QMainWindow>
#include <QMap>
#include "item.h"

namespace Ui {
class MainWindow;
}


#define CHESS_ROWS		15
#define CHESS_COLUMES	15
#define RECT_WIDTH		50
#define RECT_HEIGHT		50

class ChessBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChessBoard(QWidget *parent = nullptr);
    ~ChessBoard();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    void DrawChessboard();
    void DrawItems();
    void DrawItemWithMouse();

    void DrawChessAtPoint(QPainter& painter,QPoint& pt);

    int CountNearItem(Item item,QPoint ptDirection);	//缁熻鏌愪釜鏂瑰悜(鍏?涓柟鍚?涓婄殑鐩歌繛涓暟锛岀敤QPoint琛ㄧず缁熻鏂瑰悜锛屽(1,1)琛ㄧず鍙充笅鏂?锛?1,0锛夎〃绀哄悜宸?
    //bool FindItem(Item item);

    Ui::MainWindow *ui;

    QVector<Item> m_items;
    bool m_bIsBlackTurn;	//褰撳墠璇ラ粦妫嬩笅

private slots:
    void startReceived();

};

#endif // CHESSBOARD_H
