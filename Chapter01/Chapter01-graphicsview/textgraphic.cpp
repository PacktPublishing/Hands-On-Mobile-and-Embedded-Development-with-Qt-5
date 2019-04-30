#include "textgraphic.h"

TextGraphic::TextGraphic(const QString &text)
    : QGraphicsSimpleTextItem(text),
      simpleText(text)
{
}

void TextGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (scene()->collidingItems(this).isEmpty())
        QGraphicsSimpleTextItem::setText("BOOM!");
    else
        QGraphicsSimpleTextItem::setText(simpleText);

    QGraphicsSimpleTextItem::paint(painter,option,widget);
}
