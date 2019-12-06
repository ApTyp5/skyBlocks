#include "renderarea.h"
#include <QDebug>
#include <QImage>
#include <QPainter>

RenderArea::RenderArea()
{
    pen = QPen(Qt::black, 1);
    brush = QBrush(Qt::NoBrush);
}

void RenderArea::setFigures(QPoint *figure, size_t size) {
    for(size_t i = 0; i < size; i++)
        this->figure[i] = figure[i];
}

void RenderArea::setPen(const QPen &pen) {
    this->pen = pen;
}

void RenderArea::setBrush(const QBrush &brush) {
    this->brush = brush;
}

void RenderArea::draw() {

}
