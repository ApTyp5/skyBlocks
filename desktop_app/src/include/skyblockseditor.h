#ifndef SKYBLOCKSEDITOR_H
#define SKYBLOCKSEDITOR_H

#include "FigureFactory.h"

#include "drawsettings.h"
#include "ui_drawsettings.h"

#include <QGraphicsScene>
#include <QLabel>
#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class SkyBlocksEditor; }
QT_END_NAMESPACE

class SkyBlocksEditor : public QMainWindow
{
    Q_OBJECT

public:
    SkyBlocksEditor(QWidget *parent = nullptr);
    ~SkyBlocksEditor();

    void keyPressEvent(QKeyEvent *event);

    void Draw(QPainter &painter, const DrawData &drawData);
    void DrawAll();
public slots:
    void nextImagePage();
    void prevImagePage();

    void increaseImageScale();
    void reduceImageScale();
    void sendInformation();
    void setDrawSettings();
    void drawAlgorithm();

private:
    Ui::SkyBlocksEditor *ui;
    QLabel label;
    std::vector<QImage *> images;
    int currPage;
    int pagesCount;
    double scaleIndex;

    std::vector<DrawData *> *drawData;

    DrawSettings settings;

    QFont drawFont;

    QNetworkAccessManager networkManager;
    QNetworkReply *reply;

    FigureFactory blockFactory;
};
#endif // SKYBLOCKSEDITOR_H
