#ifndef ITEM_H
#define ITEM_H

#pragma once
#include <QPoint>

class Item
{
public:
    Item(void);
    Item(QPoint pt,bool bBlack);        //constructor
    ~Item(void);

    bool operator==(const Item &t1)const        //overload == opeartor
    {
        return ((m_pt == t1.m_pt) && (m_bBlack == t1.m_bBlack));
    }

    QPoint m_pt;
    bool m_bBlack;

private:


};


#endif // ITEM_H
