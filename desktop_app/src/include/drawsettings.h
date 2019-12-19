#ifndef DRAWSETTINGS_H
#define DRAWSETTINGS_H
#pragma once

#include <QDialog>
#include <QJsonObject>

enum ListSizes {
    A0V = 0, A0H, A1V, A1H, A2V, A2H,
    A3V, A3H, A4V, A4H, A5V, A5H
};

const std::vector<QSize>listSizes = {
    QSize(841, 1189), QSize(1189, 841),
    QSize(594, 841), QSize(841, 594),
    QSize(420, 594), QSize(594, 420),
    QSize(297, 420), QSize(420, 297),
    QSize(210, 297), QSize(297, 210),
    QSize(148, 210), QSize(210, 148)
};

const QStringList listSizesStrings = {
    "A0 Вертикальный",
    "A0 Горизонтальный",
    "A1 Вертикальный",
    "A1 Горизонтальный",
    "A2 Вертикальный",
    "A2 Горизонтальный",
    "A3 Вертикальный",
    "A3 Горизонтальный",
    "A4 Вертикальный",
    "A4 Горизонтальный",
    "A5 Вертикальный",
    "A5 Горизонтальный",
};

struct DrawSettings {
    unsigned int xp;
    unsigned int yp;
    unsigned int xm;
    unsigned int ym;
    unsigned int bs;
    ListSizes size;

    QFont font;

    DrawSettings() : xp(0), yp(0), xm(0), ym(0), bs(5),
        size(A4V), font("freeMono", 8) {}

    QJsonObject ToJson();
};

namespace Ui {
class DrawSettingsDialog;
}

class DrawSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DrawSettingsDialog(const DrawSettings &s, QWidget *parent = nullptr);
    ~DrawSettingsDialog();

    DrawSettings getSettings() const;

private:
    Ui::DrawSettingsDialog *ui;
};

#endif // DRAWSETTINGS_H
