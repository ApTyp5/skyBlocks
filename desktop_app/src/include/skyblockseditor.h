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
public slots:
    void sendInformation();
    void setDrawSettings();
    void putMessage();

private:
    Ui::SkyBlocksEditor *ui;
    QLabel label;
    std::vector<QImage *> images;
    int currPage;
    double scaleIndex;

    DrawSettings settings;

    QFont drawFont;

    QNetworkAccessManager networkManager;
    QNetworkReply *reply;

    FigureFactory blockFactory;
};
#endif // SKYBLOCKSEDITOR_H
