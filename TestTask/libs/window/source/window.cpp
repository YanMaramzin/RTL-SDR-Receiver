#include "window.h"


Window::Window(QWidget *parent):QWidget(parent)
{

    setWindowTitle("Receiver");
    frame=new QFrame(this);
    centFreqLabel=new QLabel("Введите центральную частоту:",this);
    centFreqEdit=new QLineEdit("88.4e6",this);

    sampleFreqLabel=new QLabel("Введите частоту дискретизации:",this);
    sampleFreqEdit=new QLineEdit("2.4e6",this);

    bytes_to_readLabel=new QLabel("Введите количество считываемых байтов:",this);
    bytes_to_readEdit=new QLineEdit("512",this);

    sampleCountLabel=new QLabel("Введите число отсчетов:",this);
    sampleCountEdit=new QLineEdit("1024",this);

    set=new QPushButton("Задать параметры приемника");
    start=new QPushButton("Старт");
    stop=new QPushButton("Стоп");

    //Графики
    real=new QCustomPlot(this);

    imag=new QCustomPlot(this);
    spectr=new QCustomPlot(this);

    QVBoxLayout *vLayout1=new QVBoxLayout;
    vLayout1->addWidget(real);
    vLayout1->addWidget(imag);
    vLayout1->addWidget(spectr);

    QHBoxLayout *hLayout=new QHBoxLayout();
    hLayout->addWidget(set);
    hLayout->addWidget(start);
    hLayout->addWidget(stop);

    QVBoxLayout *vLayout2=new QVBoxLayout();
    vLayout2->addWidget(centFreqLabel);
    vLayout2->addWidget(centFreqEdit);
    vLayout2->addWidget(sampleFreqLabel);
    vLayout2->addWidget(sampleFreqEdit);
    vLayout2->addWidget(bytes_to_readLabel);
    vLayout2->addWidget(bytes_to_readEdit);
    vLayout2->addWidget(sampleCountLabel);
    vLayout2->addWidget(sampleCountEdit);
    vLayout2->addLayout(hLayout);
    vLayout2->addStretch();


//    QGridLayout* prgdLayout=new QGridLayout;
//    prgdLayout->addLayout(vLayout1,0,0,1,1);
//    prgdLayout->addLayout(hLayout,1,1,1,1);
//    prgdLayout->addLayout(vLayout2,0,1,1,1);

    QHBoxLayout *hLayout1 = new QHBoxLayout(this);
    hLayout1->addWidget(frame);
    hLayout1->addLayout(vLayout1);
    hLayout1->addLayout(vLayout2);



    begin();

    connect(set,SIGNAL(clicked(bool)),
    this,SLOT(setReceiverParameters()));
    connect(start,SIGNAL(clicked(bool)),
    this,SLOT(startReceiver()));
    connect(stop,SIGNAL(returnPressed()),
    this,SLOT(stopReceiver()));
}


void Window::begin(){
    real->setMinimumSize(500,200);
    real->yAxis->setLabel("A");
    real->xAxis->setLabel("samples");
    imag->yAxis->setLabel("A");
    imag->xAxis->setLabel("samples");
    spectr->yAxis->setLabel("A");
    spectr->xAxis->setLabel("frequency, Hz");

    this->resize(700,700);
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);

}

void Window::calc(){

}

void Window::setReceiverParameters(){
//    ReceiverSettings settings;
//    settings.rfSettings.centralFreq=centFreqEdit->text().toDouble();
//    settings.rfSettings.sampleFreq=sampleFreqEdit->text().toDouble();
//    settings.bytes_to_read=bytes_to_readEdit->text().toDouble();
//    settings.sampleCount=sampleCountEdit->text().toDouble();
}


void Window::startReceiver(QVector<double> &f,QVector<double> &y){
//    ReceiverSettings settings;
//    settings.rfSettings.centralFreq=centFreqEdit->text().toDouble();
//    settings.rfSettings.sampleFreq=sampleFreqEdit->text().toDouble();
//    settings.bytes_to_read=bytes_to_readEdit->text().toDouble();
//    settings.sampleCount=sampleCountEdit->text().toDouble();
//    settings.fileName="Signal.bin";

//    rcv.set(settings);
//    rcv.start();
//    rcv.stop();
//      QVector<double> xRe;
//      QVector<double> yRe;
//      grapInit(real,xRe,yRe);

//      QVector<double> xIm;
//      QVector<double> yIm;
//      grapInit(imag,xIm,yIm);



      QVector<double> freq;
      QVector<double> Amp;
      grapInit(spectr,f,y);
}

void Window::stopReceiver(){
//    rcv.stop();
}

QVector<double> soz(QVector<Complex<double>> &vec){
     QVector<double> x;
     for(size_t i=0;i<vec.size();i++)
         x.push_back(vec[i].real());
     return x;
}

void grapInit(QCustomPlot *graph,QVector<double> &x,QVector<double> &y)
{
    graph->replot();
    graph->addGraph();
    graph->graph()->setData(x,y);
    graph->graph()->rescaleAxes();
    graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

