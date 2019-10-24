#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopServices>
#include <QProcess>
#include <QUrl>

#include "database.hpp"

using namespace Warehouse;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool displayDetailById(int id);

private slots:
    void on_actionNew_triggered();

    void on_actionImport_triggered();

    void on_actionExport_triggered();

    void on_actionExit_triggered();

    void on_actionQt_triggered();

    void on_actionIndex_triggered();

    void on_buttonPrevious_clicked();

    void on_buttonNext_clicked();

    void on_buttonTips_clicked();

    void on_buttonAnswer_clicked();

    void on_buttonAdd_clicked();

    void on_buttonUpdate_clicked();

    void on_buttonDelete_clicked();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    Database *db;

    QString sql;

    int maxId;
    int currentId = 0;
};

#endif // MAINWINDOW_H
