#ifndef GAME_INIT_H
#define GAME_INIT_H

#include <QtWidgets>
#include "chessboard.h"
#include "invite.h"
#include "item.h"
#include "login.h"
#include "score.h"
#include "transfer.h"
#include "reject.h"
#include "finish.h"

class GUI : public QWidget
{
    Q_OBJECT

private:
    login *log;
    score *scor;
    transfer *trans;
    reject *rej;
    inviteReceive *invite;
    finish *fini;
    chessBoard *chess;

private slots:
    //void restartReceive();

public:

    GUI(QWidget *parent = nullptr);
    ~GUI();

    void init();
    void loginShow();
    void receiveInvite();
    void showMessage();
    void showGame();
    void newClicked();  //not complete yet
    void updateNewMovel();  //not complete yet
    void gameFinish();
};

#endif // GAME_INIT_H
