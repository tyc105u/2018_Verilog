#include "mywindow.h"

/*設計視窗內容*/
MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Example 1");//標題
    resize(300, 300);//視窗大小
	setStyleSheet("background-color:#BDC3C7;");//背景顏色
	
	/*初始化滑鼠軌跡*/
    stroke.clear();
    lines.clear();
    painting = false;
}
/*滑鼠軌跡*/
/*按下滑鼠*/
void MyWindow::mousePressEvent(QMouseEvent* event)
{
    if(event->x()>10 && event->y()>10 && event->x()<290 && event->y()<290)/*設置範圍*/
    {    
        painting = true;
        stroke.push_back(event->pos());
    }
    update();
}
/*移動滑鼠*/
void MyWindow::mouseMoveEvent(QMouseEvent* event)
{
    if(event->x()>10 && event->y()>10 && event->x()<290 && event->y()<290 && painting)/*在範圍內且為按住狀態*/
            stroke.push_back(event->pos());
    update();
}
/*釋放滑鼠*/
void MyWindow::mouseReleaseEvent(QMouseEvent*)
{
    if(painting)
    {
        painting = false;
        lines.push_back(stroke);
        stroke.clear();  
    }
    update();
}
/*利用paintEvent繪畫*/
void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
	painter.setPen(Qt::blue);//設置畫筆
	painter.setBrush(Qt::white);//填滿顏色
	painter.drawRect(10, 10, 280, 280);//座標(10,10)的280×280矩形
	
	painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(Qt::black, 20));
	/* 畫出滑鼠軌跡 */
    for(size_t i=0;i<lines.size();i++)
    {
        for(size_t j=0;j<lines[i].size();++j)
                painter.drawPoint(lines[i][j].x(),lines[i][j].y());
    }
    for(size_t i=0;i<stroke.size();++i)
        painter.drawPoint(stroke[i].x(), stroke[i].y());
}
