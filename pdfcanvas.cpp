#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include "pdfcanvas.h"

PdfCanvas::PdfCanvas(QWidget *parent) : QWidget(parent)
{
    m_doc = nullptr;
    m_curIndex = 0;
    m_curPageY = 0;
    m_multiple = 2.0;

}

PdfCanvas::~PdfCanvas()
{
    delete m_scrollarea;
    delete m_doc;
}

bool PdfCanvas::setDoc(QString fileName)
{
    Poppler::Document* old_doc = m_doc;
    m_doc = Poppler::Document::load(fileName);
    if (m_doc)
    {
        delete old_doc;
        m_pageCache.clear();
        qDebug() << "set ok";
        update();
        return true;
    }
    else
    {
        qDebug() << "doc load failure";
        return false;
    }
}

void PdfCanvas::renderPage()
{
    if (!m_doc)
    {
        return;
    }
    QSize size = this->size();
    int drawHeight = size.height();
    qDebug() << size;

    QPainter* painter = new QPainter(this);

    int drawX;
    int drawY;
    QImage img;
    QImage img_copy;
    int i = 0;
    while (drawHeight > 0)
    {
        if (i > 0)
            m_curPageY = 0;
        i++;
        img_copy = getPage (m_curIndex++);
        img = img_copy.copy (0, m_curPageY, img_copy.width(), img_copy.height() - m_curPageY);
        if (img.isNull())
        {
            qDebug() << "null image";
        }

        drawX = (size.width() - img.width()) / 2;
        drawY = size.height() - drawHeight;


        painter->drawImage(drawX, drawY, img);
        drawHeight -= (img.height() + 8);
    }
    painter->end();
}

QImage PdfCanvas::getPage(int pageNum)
{
    QImage img;
    if (m_pageCache.contains(pageNum))
    {
        img = m_pageCache.value(pageNum);
    }
    else
    {
        Poppler::Page* pdfPage = nullptr;
        pdfPage = m_doc->page(pageNum);
        img = pdfPage->renderToImage(75 * m_multiple, 75 * m_multiple);
        m_pageCache.insert(pageNum, img);
        delete pdfPage;
    }
    return img;
}

void PdfCanvas::wheelEvent(QWheelEvent *event)
{
    int n = 0;
    int distance = event->delta() / 120 * -1;
    if (distance > 0)
    {
        n = 25;
    }
    else
    {
        n = -25;
    }
    emit indexChanged(n);
}

void PdfCanvas::setPage(int scrvalue)
{
    qDebug() << scrvalue;
    m_curIndex = scrvalue / m_page_height;
    m_curPageY = scrvalue % m_page_height;
    qDebug() << "index: " << m_curIndex << "Y: " << m_curPageY;
    update ();
}


void PdfCanvas::paintEvent(QPaintEvent *event)
{
    renderPage();
}

int PdfCanvas::getPageHeight(int pageNum)
{
    if (!m_doc)
    {
        return -1;
    }
    Poppler::Page* pdfPage = m_doc->page(pageNum);
    m_page_height = pdfPage->pageSize().height();
    return m_page_height;
}

int PdfCanvas::getPageNums()
{
    if (!m_doc)
    {
        return -1;
    }
    m_page_nums = m_doc->numPages();
    return m_page_nums;
}
