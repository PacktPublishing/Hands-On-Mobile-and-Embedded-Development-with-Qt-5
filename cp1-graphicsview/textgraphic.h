#ifndef TEXTGRAPHIC_H
#define TEXTGRAPHIC_H

#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsItem>
#include <QPainter>

class TextGraphic :public QGraphicsSimpleTextItem
{
public:
    TextGraphic(const QString &text);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QString simpleText;
};

#endif // TEXTGRAPHIC_H