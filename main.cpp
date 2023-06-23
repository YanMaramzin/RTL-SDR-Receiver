#include <iostream>
#include "receiverHWImpl.h"
#include <QApplication>
#include "qcustomplot.h"
#include <vector>
#include <memory>
#include <QVector>
#include "Complex.h"
#include <algorithm>
#include "Filter.h"
#include "fft.h"
#include <QLineEdit>
#include "window.h"

using ComplexSignal = std::vector<Complex<uint8_t>>;

struct ResultMessage {
    ResultMessage(const RfSettings &settings, ComplexSignal &&signal):
    settings(settings), signal(std::move(signal)) {}
    RfSettings settings;
    ComplexSignal signal;
};

void sendResultToClient( const ReceiverSettings& inputSettings, ComplexSignal&& signal){

    ResultMessage message(inputSettings.rfSettings, std::move(signal));
    std::cout<<"Центральная частота:"<<message.settings.centralFreq<<"\n";
    std::cout<<"Частота дискретизации:"<<message.settings.sampleFreq<<"\n";
    std::cout<<"Размер "<<message.signal.size()<<"\n";
    for(size_t i=0;i<message.signal.size();i++)
        std::cout<<message.signal[i].real()+0<<" "<<message.signal[i].imag()+0<<"\n";
}



int main(int argc, char *argv[])
{
    QApplication a(argc,argv);
//    QWidget w;
    Window w;
//    w.setMinimumSize(1000,1000);



//    QCustomPlot *graphOne=new QCustomPlot(&w);
//    QCustomPlot *graphSecond=new QCustomPlot(&w);
//    QCustomPlot *graphThird=new QCustomPlot(&w);
//    graphThird->resize(500,500);
//    QLabel* centerFreqLabel=new QLabel("&Центральная частота");
//    QLineEdit* centerFreqEdit=new QLineEdit(&w);

//    QGridLayout* grid=new QGridLayout(&w);
//    grid->addWidget(graphThird,0,0);
//    grid->addWidget(centerFreqLabel,0,1);
//    grid->addWidget(centerFreqEdit,1,1);

//    ReceiverSettings settings;
//    settings.rfSettings.centralFreq=88.4e6;
//    settings.rfSettings.sampleFreq=2.4e6;
//    settings.sync_mode=1;
//    settings.fileName="Signal.bin";
//    settings.sampleCount=512;
//    settings.bytes_to_read=256;
//    settings.n_read=1;
//    settings.direct_sampling=0;
//    ReceiverHWImpl rcv;
//    ComplexSignal signal(settings.bytes_to_read);
//    settings.outputBuffer=signal.data();

//    rcv.set(settings);
//    rcv.start();
//    std::vector<Complex<double>> signalDouble(signal.begin(),signal.end());



//    Complex<float> mean;
//    for(auto& sample: signalDouble){
//        mean += sample;
//    }
//    mean.re= mean.re/signalDouble.size();
//    mean.im= mean.im/signalDouble.size();

//    for(auto& sample: signalDouble){
//        sample -=(127.4f) * (1.0f / 128.0f);
//    }
//    for(int i=0;i<signalDouble.size();i++)
//    {
//        signalDouble[i]-=(127.4) ;
//        signalDouble[i]*=(1.0 / 128.0);
//    }


//        std::vector<Complex<double>> spect(signalDouble.size());

//        fft(signalDouble,spect,signalDouble.size());
//        std::vector<double> specA;
//        specA.reserve(spect.size());

//        fftShift(spect);

//        for(int i=0;i<spect.size();i++)
//            specA.push_back(spect[i].abs());


//        FilterMovingAverageNonRec fil;

//        specA=fil.filtration(specA,10);

//        QVector<double> specAbs;
//        for(size_t i=0;i<spect.size();i++)
//        {
//            specAbs.push_back(10*log(specA[i]));
//        }


//        QVector<double> freqN;
//        for(int i=0;i<specAbs.size();i++)
//        {
//          double s;
//          s=(double)settings.rfSettings.centralFreq+(i*(double)settings.rfSettings.sampleFreq/specAbs.size());
//          freqN.push_back(s);
//        }



//    QVector<Complex<uint8_t>> vec;
//    vec.resize(signal.size());
//    vec=QVector<Complex<uint8_t>>(signal.begin(), signal.end());
//    QVector<Complex<double>> spectVecQ;

//    QVector<double> yRe;
//    QVector<double> xRe;
//    QVector<double> yIm;
//    QVector<double> xIm;
//    QVector<double> specAbs;

//    for(size_t i=0;i<vec.size();i++)
//        yRe.push_back(vec[i].real());
//    for(size_t i=0;i<yRe.size();i++)
//        xRe.push_back(i);
//    for(size_t i=0;i<vec.size();i++)
//        yIm.push_back(vec[i].imag());
//    for(size_t i=0;i<vec.size();i++)
//        xIm.push_back(i);
//    for(size_t i=0;i<spect.size();i++)
//    {
//        specAbs.push_back(10*log(specA[i]));
//    }

//    QVector<double> freqN;
//    for(int i=0;i<specAbs.size();i++)
//    {
//      double s;
//      s=(double)settings.rfSettings.centralFreq+(i*(double)settings.rfSettings.sampleFreq/specAbs.size());
//      freqN.push_back(s);
//    }


//    graphOne->addGraph();
//    graphOne->graph()->setData(freqN,specAbs);
//    graphOne->graph()->rescaleAxes();

//    graphOne->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);


//    graphThird->addGraph();
//    graphThird->graph()->setData(freqN,specAbs);
//    graphThird->graph()->rescaleAxes();

//    graphThird->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

//    rcv.stop();
    w.show();
    return a.exec();
}

