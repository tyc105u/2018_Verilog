#include "mywindow.h"

int paste=0;

MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Example 2");
    resize(870, 480);
	setStyleSheet("background-color:#BDC3C7;");

    stroke.clear();
    lines.clear();
    painting = false;
	
    /* 清除按鈕 */
	clr_btn = new QPushButton("Clear",this);//建立名為Clear的按鈕
	//按鈕樣式//
	clr_btn->setStyleSheet("QPushButton{border: 2px solid #95A5A6;border-radius:10px;color:rgb(192,57,43);background-color:rgb(149,165,166)}");
    clr_btn->setFont(QFont("Courier", 25, QFont::Bold));//字型
	clr_btn->setGeometry(50, 370, 135, 80);//座標(50,370)的135×80大小按鈕
	//按下按鈕連動到ClearButton_clicked()函式//
    connect(clr_btn, SIGNAL(clicked()), this, SLOT(ClearButton_clicked()));
	
    /* 儲存按鈕 */
    conf_btn = new QPushButton("Save",this);
	conf_btn->setStyleSheet("QPushButton{border: 2px solid #95A5A6;border-radius:10px;color:rgb(22,160,133);background-color:rgb(149,165,166);}");
    conf_btn->setFont(QFont("Courier", 25, QFont::Bold));
    conf_btn->setGeometry(195, 370, 135, 80);
    connect(conf_btn, SIGNAL(clicked()), this, SLOT(ConfirmButton_clicked()));
}

/* HandWriting */
void MyWindow::mousePressEvent(QMouseEvent* event)
{
    if(event->x()>55 && event->y()>55 && event->x()<325 && event->y()<325)//range_on
    {    
        painting = true;
        stroke.push_back(event->pos());
    }
    update();
}

void MyWindow::mouseMoveEvent(QMouseEvent* event)
{
    if(event->x()>55 && event->y()>55 && event->x()<325 && event->y()<325 && painting)//50,30
            stroke.push_back(event->pos());
    update();
}

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

void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
	painter.setPen(Qt::blue);
	painter.setBrush(Qt::white);
	painter.drawRect(49, 49, 280, 280);
        painter.drawRect(487,49,280, 280);
	
	painter.setBrush(Qt::NoBrush);
	/* HandWriting */
    painter.setPen(QPen(Qt::black, 20));

    for(size_t i=0;i<lines.size();i++)
    {
        for(size_t j=0;j<lines[i].size();++j)
                painter.drawPoint(lines[i][j].x(),lines[i][j].y());
    }
    for(size_t i=0;i<stroke.size();++i)
        painter.drawPoint(stroke[i].x(), stroke[i].y());

    char img_str[15];  

if(paste==1)
{
        snprintf(img_str,sizeof(img_str),"saveImg.ppm");
        /*座標(49,49)大小280×280圖片*/
        painter.drawImage(487,49,QImage(img_str).scaled(280, 280, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
}
/*按鈕函式*/
void MyWindow::ClearButton_clicked()
{
	/*清除軌跡*/
    stroke.clear();
    lines.clear();
    painting = false;
    update();
    paste=0;
}

void MyWindow::ConfirmButton_clicked()
{
	/* 擷取軌跡 */
    QPixmap qpx;
    QImage img = qpx.grabWidget(this, 50, 50, 280, 280).scaled(28, 28, Qt::KeepAspectRatio, Qt::SmoothTransformation).toImage();
	
    img.save("saveImg.ppm","ppm");//儲存軌跡圖片
    update();
    paste=1;
}
