#include <iostream>
#include "receiverHWImpl.h"
#include "receiverSoftImpl.h"
#include <QApplication>
#include "qcustomplot.h"
#include <vector>
#include <memory>
#include <QVector>
#include "Complex.h"
#include "fftw3.h"
#include <algorithm>
#include "Filter.h"
#include "fft.h"
#include "window.h"
#include <thread>
#include "WavReader.h"
enum class ReceiverType {
    soft, hw
};

void error() {
    throw std::runtime_error(" ////error description ");
}

//using ComplexSignal = std::vector<Complex<uint8_t>>;
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

template<typename T>
T meanComplex(std::vector<T> &vec){
        T mean;
        for(auto& sample: vec){
            mean += sample;
        }
        mean.re= mean.re/vec.size();
        mean.im= mean.im/vec.size();

}

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);
    Window w(0);

    ReceiverSettings settings;
    settings.rfSettings.centralFreq=425e6;
    settings.rfSettings.sampleFreq=2.4e6;
    settings.sync_mode=1;
    settings.fileName="Signal.bin";
    settings.sampleCount=512*100;
    settings.bytes_to_read=256*100;
    settings.n_read=1;
    settings.direct_sampling=0;
    ReceiverHWImpl rcv;

    ComplexSignal signal(settings.bytes_to_read);
//    w.startReceiver(rcv);



    settings.outputBuffer = signal.data();

    rcv.set(settings);
    rcv.start();

    std::vector<Complex<double>> signalDouble(signal.begin(), signal.end());



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

    std::vector<Complex<double>> spect(signalDouble.size());

    fft((fftw_complex*)signalDouble.data(),(fftw_complex*)spect.data(),signalDouble.size());
//    fftShift(spect);

    std::vector<double> specA;
    specA.reserve(spect.size());

    for(int i=0;i<spect.size();i++)
        specA.push_back(spect[i].abs());

    FilterMovingAverageNonRec fil;

    specA=fil.filtration(specA,50);

//    QVector<Complex<uint8_t>> vec;
//    vec.resize(signal.size());
//    vec=QVector<Complex<uint8_t>>(signal.begin(), signal.end());
//    QVector<Complex<double>> spectVecQ;

//    QVector<double> yRe;
//    QVector<double> xRe;
//    QVector<double> yIm;
//    QVector<double> xIm;
    QVector<double> specAbs;

//    for(size_t i=0;i<vec.size();i++)
//        yRe.push_back(vec[i].real());
//    for(size_t i=0;i<yRe.size();i++)
//        xRe.push_back(i);
//    for(size_t i=0;i<vec.size();i++)
//        yIm.push_back(vec[i].imag());
//    for(size_t i=0;i<vec.size();i++)
//        xIm.push_back(i);
    for(size_t i=0;i<spect.size();i++)
    {
        specAbs.push_back(10*log(specA[i]));
    }

    QVector<double> freqN;
    for(int i=0;i<specAbs.size();i++)
    {
      double s;
      s=(double)settings.rfSettings.centralFreq+(i*(double)settings.rfSettings.sampleFreq/specAbs.size());
      freqN.push_back(s);
    }

    w.startReceiver(freqN,specAbs);
    rcv.stop();



//    graphOne->addGraph();
//    graphOne->graph()->setData(xRe,yRe);
//    graphOne->graph()->rescaleAxes();

//    graphOne->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

//    graphSecond->addGraph();
//    graphSecond->graph()->setData(xIm,yIm);
//    graphSecond->graph()->rescaleAxes();

//    graphSecond->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

//    graphThird->addGraph();
//    graphThird->graph()->setData(freqN,specAbs);
//    graphThird->graph()->rescaleAxes();

//    graphThird->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
//    rcv.stop();

    w.show();

    return a.exec();
}
