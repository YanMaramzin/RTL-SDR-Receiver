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

    QHBoxLayout *hLayout1 = new QHBoxLayout(this);
    hLayout1->addWidget(frame);
    hLayout1->addLayout(vLayout1);
    hLayout1->addLayout(vLayout2);

    begin();

    connect(start,SIGNAL(clicked(bool)),
    this,SLOT(startReceiver()));
    connect(stop,SIGNAL(clicked(bool)),
    this,SLOT(stopReceiver()));
}


void Window::begin(){
    spectr->setMinimumSize(1000,500);
    real->yAxis->setLabel("A");
    real->xAxis->setLabel("samples");
    imag->yAxis->setLabel("A");
    imag->xAxis->setLabel("samples");
    spectr->yAxis->setLabel("A");
    spectr->xAxis->setLabel("frequency, Hz");

    this->resize(1000,1000);
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);

}


void Window::startReceiver(){
    ReceiverSettings settings;
    settings.rfSettings.centralFreq=centFreqEdit->text().toDouble();
    settings.rfSettings.sampleFreq=sampleFreqEdit->text().toDouble();
    settings.bytes_to_read=bytes_to_readEdit->text().toDouble();
    settings.sampleCount=sampleCountEdit->text().toDouble();
    settings.fileName="Signal.bin";
    std::vector<Complex<uint8_t>> signal(settings.bytes_to_read);
    settings.outputBuffer=signal.data();

    rcv.set(settings);
    rcv.start();
//    rcv.stop();
    std::vector<Complex<double>> signalDouble(signal.begin(),signal.end());

   Complex<double> mean;
   for(auto& sample: signalDouble)
   {
       mean += sample;
   }
   mean.re= mean.re/signalDouble.size();
   mean.im= mean.im/signalDouble.size();

   for(int i=0; i<signalDouble.size();i++)
   {
       signalDouble[i].re-=mean.re;
       signalDouble[i].im-=mean.im;
   }

   std::vector<Complex<double>> spect(signalDouble.size());



    fft(signalDouble,spect,signalDouble.size());
    std::vector<double> specA;
    specA.reserve(spect.size());

    fftShift(spect);

    for(int i=0;i<spect.size();i++)
        specA.push_back(spect[i].abs());


//    FilterMovingAverageNonRec fil;

//    specA=fil.filtration(specA,10);

    QVector<double> specAbs;
    for(size_t i=0;i<spect.size();i++)
    {
        specAbs.push_back(10*log(specA[i]));
    }

    QVector<double> freqN;
    double s=(double)settings.rfSettings.centralFreq-(double)settings.rfSettings.sampleFreq/2;
    freqN.push_back(s);
    for(int i=0;i<specAbs.size();i++)
    {
      freqN.push_back(s+(i*(double)settings.rfSettings.sampleFreq/specAbs.size()));
      std::cout<<freqN[i]<<std::endl;
    }
    QVector<double> sample;
    QVector<double> yRe;
    QVector<double> yIm;
    for(int i=0;i<specAbs.size();i++)
    {
      sample.push_back(i);
      yRe.push_back(spect[i].real());
      yIm.push_back(spect[i].imag());
    }

    grapInit(real,sample,yRe);
    grapInit(imag,sample,yIm);
    grapInit(spectr,freqN,specAbs);
}

void Window::stopReceiver(){
    rcv.stop();
}

void grapInit(QCustomPlot *graph,QVector<double> &x,QVector<double> &y)
{
    graph->replot();
    graph->addGraph();
    graph->graph()->setData(x,y);
    graph->graph()->rescaleAxes();
    graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}
