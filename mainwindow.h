#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pdfcanvas.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void openFile ();

private slots:
    void on_actionOpen_triggered();
    void scroll_value (int value);

private:
    Ui::MainWindow *ui;
    PdfCanvas* m_pdf;
};
#endif // MAINWINDOW_H
