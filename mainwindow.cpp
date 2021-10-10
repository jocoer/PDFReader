#include <QFileDialog>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pdf = new PdfCanvas;
    ui->gridLayout->addWidget(m_pdf);

    connect (ui->verticalScrollBar, SIGNAL (valueChanged(int)), m_pdf, SLOT (setPage(int)));
    connect (m_pdf, &PdfCanvas::indexChanged, this, &MainWindow::scroll_value);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QString FileName = QFileDialog::getOpenFileName(this, tr("Open PDF file"),
                                                    "../", tr ("PDF files (*.pdf)"));
    if (FileName.isEmpty())
    {
        return;
    }
    if (m_pdf->setDoc(FileName))
    {
        ui->verticalScrollBar->setMaximum(m_pdf->getPageHeight(0) * m_pdf->getPageNums());
        ui->verticalScrollBar->setValue(0);
        ui->verticalScrollBar->setMinimum(0);
    }
}


void MainWindow::on_actionOpen_triggered()
{
    openFile();
}

void MainWindow::scroll_value(int value)
{
    int v = ui->verticalScrollBar->value();
    ui->verticalScrollBar->setValue(v + value);
}
