#include "item.h"

Item::Item(void)
{}

Item::Item(QPoint pt,bool bBlack)       //constructor
{
    m_pt = pt;
    m_bBlack = bBlack;
}


Item::~Item(void)
{}
