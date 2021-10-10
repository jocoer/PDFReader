#ifndef PDFCANVAS_H
#define PDFCANVAS_H

#include <QWidget>
#include <poppler-qt5.h>
#include <QScrollArea>
#include <QLabel>
#include <QMap>
#include <QThread>
#include <QMutex>

class PdfCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit PdfCanvas(QWidget *parent = nullptr);
    ~PdfCanvas();
    bool setDoc (QString fileName);
    void paintEvent(QPaintEvent *event);

    int getPageHeight (int pageNum);
    int getPageNums ();

    void renderPage ();
    QImage getPage (int pageNum);

    void wheelEvent(QWheelEvent *event);
public slots:
    void setPage (int scrvalue);
signals:
    void indexChanged (int value);
private:
    Poppler::Document* m_doc;
    QScrollArea* m_scrollarea;
    double m_multiple;

    int m_page_nums;
    int m_page_height;

    int m_curIndex;
    int m_curPageY;

    QMap <int, QImage> m_pageCache;
};

#endif // PDFCANVAS_H
