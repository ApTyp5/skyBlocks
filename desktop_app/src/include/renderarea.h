#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <array>

#include <QFrame>
#include <QPen>
#include <QScrollArea>

class RenderArea
{
public:
    explicit RenderArea();
    ~RenderArea() = default;

    void setFigures(QPoint *figure, size_t size);

    void draw();

public slots:
    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);

private:
    QScrollArea scrollArea;

    QPen pen;
    QBrush brush;
    QPixmap pixmap;
    QPoint figure[4];
};

#endif // RENDERAREA_H
