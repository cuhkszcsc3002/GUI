/*/
#include "login.h"
#include "transfer.h"
#include "score.h"
#include "chessboard.h"
#include "invite.h"
/*/


#include <QApplication>
#include "GUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GUI GUI;
    GUI.init();
//    GUI.loginShow();
//    GUI.receiveInvite();
//    GUI.showMessage();
//    GUI.showGame();
//    GUI.gameFinish();
    GUI.takeCount();
    return a.exec();
}



/*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login log;
    Transfer trans;
    Score score;
    InviteReceive invite;
    ChessBoard chess;

    //chess.hide();
    //chess.show();
    invite.show();
    log.show();

    QObject::connect(&log, SIGNAL(ShowScore()), &score, SLOT(CheckReceived()));
    QObject::connect(&log, SIGNAL(ShowTransfer()), &trans, SLOT(ReceiveInvite()));
    QObject::connect(&trans, SIGNAL(ComfirmReceived()), &chess, SLOT(StartReceived()));
    QObject::connect(&trans, SIGNAL(ComfirmReceived()), &log, SLOT(StartReceived()));

    //a.exec();
    return a.exec();

}
/*/
