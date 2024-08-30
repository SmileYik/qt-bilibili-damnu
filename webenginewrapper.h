#ifndef WEBENGINEWRAPPER_H
#define WEBENGINEWRAPPER_H

#include <QObject>
#include <QWebEngineView>
#include <QCloseEvent>
#include <QApplication>
#include "setting.h"

class WebEngineWrapper : public QWebEngineView
{
    Q_OBJECT
public:
    WebEngineWrapper(QApplication* a);
    void display();
    void closeEvent(QCloseEvent *event) override;
private:
    Setting setting;
    QApplication* application;
};

#endif // WEBENGINEWRAPPER_H
