#include <QtGui/QWidget>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QMouseEvent>
#include <QPaintEvent>

class MyWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MyWindow(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent*);

private:
    //HandWriting
    QVector<QPoint> stroke;
    QVector<QVector<QPoint> >lines;
    bool painting;

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

};
