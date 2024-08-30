#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "setting.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_checkBoxUrlView_clicked(bool checked);

    void on_pushButtonApply_clicked();

private:
    Ui::MainWindow *ui;
    Setting setting;
};
#endif // MAINWINDOW_H
