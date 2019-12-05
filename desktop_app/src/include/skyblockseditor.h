#ifndef SKYBLOCKSEDITOR_H
#define SKYBLOCKSEDITOR_H

#include "BlockFactory.h"

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class SkyBlocksEditor; }
QT_END_NAMESPACE

class SkyBlocksEditor : public QMainWindow
{
    Q_OBJECT

public:
    SkyBlocksEditor(QWidget *parent = nullptr);
    ~SkyBlocksEditor();

public slots:
    void sendInformation();
    void putMessage();

private:
    Ui::SkyBlocksEditor *ui;
    QNetworkAccessManager networkManager;
    QNetworkReply *reply;

    BlockFactory blockFactory;
};
#endif // SKYBLOCKSEDITOR_H
