#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <string>
#include "item.h"

namespace Ui {
class MainWindow;
}


#define CHESS_ROWS		15
#define CHESS_COLUMES	15
#define RECT_WIDTH		50
#define RECT_HEIGHT		50

#define INIT_POSX 500
#define INIT_POSY 500

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QPoint *phyLocation;        //physical location of the locator
    QPoint *logLocation;        //logical location of the locator

    QPoint *leftBoundAxis;      //the logical axis value of left boundary
    QPoint *rightBoundAxis;     //the logical axis value of right boundary
    QPoint *upBoundAxis;        //the logical axis value of up boundary
    QPoint *downBoundAxis;      //the logical axis value of down boundary

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);

private:

    /*
     * Fucntion: void DrawChessboard()
     *
     * useage: drawChessboard()
     *
     * The size of the chessboard is 900 x 900 pix. Chessbaord has a line in each 50 pix.
     * The left boundary must be at x=50 pix, right boundary must be at x=950 pix.
     * The up boundary must be at y=50 pix, down boundary must be at y=950 pix. And the
     * center of the chessboard must be at (500, 500). Initially, center is at (0,0) e.i.
     * the 10th line. Thus left boundary is at x=-9, e.i. the 1st line and right is
     * x=9, e.i. the 19th line. Same rule is apply to the up boundary and down boundary
     *
     */
    void DrawChessboard();

    /*
     * Fucntion: void DrawItems()
     *
     * useage:
     *
     */
    void DrawItems();

    /*
     * Fucntion: void DrawItemWithMouse()
     *
     * useage:
     *
     */
    void DrawItemWithMouse();

    /*
     * Fucntion: void drawLocatorWithKeyboard()
     *
     * useage:
     *
     */
    void drawLocatorWithKeyboard();

    /*
     * Fucntion: void drawStoneAtPoint(QPainter& painter, int logX, int logY)
     *
     * useage: drawChessboard(painter, x, y)
     *
     * This function will draw a single chess stone onto the chessborad at
     * the location provided.
     */
    void drawStoneAtPoint(QPainter& painter, int x, int y);


    int CountNearItem(Item item,QPoint ptDirection);	//统计某个方向(共8个方向)上的相连个数，用QPoint表示统计方向，如(1,1)表示右下方,（-1,0）表示向左
    //bool FindItem(Item item);

private:
    Ui::MainWindow *ui;

    QVector<Item> m_items;   
    bool m_bIsBlackTurn;	//当前该黑棋下


    /* test stones*/
    QVector<std::string> Stone;
    bool isJump;


};

#endif // MAINWINDOW_H
