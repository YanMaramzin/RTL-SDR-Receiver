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

const int REAL=0;
const int IMAG=1;


//Функция для прямого преобразовния Фурье
void fft(fftw_complex *in, fftw_complex *out,int N)
{
     fftw_plan plan=fftw_plan_dft_1d(N,in,out,FFTW_FORWARD,FFTW_ESTIMATE);
     fftw_execute(plan);
     fftw_destroy_plan(plan);
     fftw_cleanup();
}

// Функция для обратного преобразовния Фурье
void ifft(fftw_complex *in, fftw_complex *out,int N)
{
    fftw_plan plan=fftw_plan_dft_1d(N,in,out,FFTW_BACKWARD,FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);
    fftw_cleanup();
    for(int i=0; i<N; ++i)
    {
        out[i][REAL]/=N;
        out[i][IMAG]/=N;
    }
}




enum class ReceiverType {
    soft, hw
};

struct AppContext {
    //read from .txt file
    ReceiverType rcvType;
    //...
};

//auto getContext(const std::string &fileName) {
//    //...
//    //...
//    return AppContext();
//}

void error() {
    throw std::runtime_error(" ////error description ");
}

auto rcvFactory(const AppContext &context) {
    std::unique_ptr<IReceiver> rcvPtr;

    switch (context.rcvType) {
        case ReceiverType::hw:
            rcvPtr = std::make_unique<ReceiverHWImpl>();
        case ReceiverType::soft:
            rcvPtr = std::make_unique<ReceiverSoftImpl>();
        default:
            error();
    }
    return rcvPtr;

}

using ComplexSignal = std::vector<Complex<uint8_t>>;

void ComplexForFFTW_Complex(fftw_complex* s,ComplexSignal& s1)
{
    for(size_t i=0;i<s1.size();i++)
    {
        s[i][0]=s1[i].real();
        s[i][1]=s1[i].imag();
    }
}
void FFTW_ComplexForComplex(fftw_complex* s,std::vector<Complex<double>>& s1,size_t size)
{
    for(size_t i=0;i<size;i++)
    {
        Complex<double> pr(s[i][0],s[i][1]);
        s1.push_back(pr);
    }
}

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
//еще какой-то класс Processor может делать это: (иначе в main`e     будет много кода)

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);
    QWidget w;
    w.resize(1500,1080);
    QCustomPlot *graphOne=new QCustomPlot(&w);
    QCustomPlot *graphSecond=new QCustomPlot(&w);
    QCustomPlot *graphThird =new QCustomPlot(&w);
    graphOne->resize(500,1080/2);
    graphSecond->resize(500,1080/2);
    graphThird->resize(1000,400);
    graphSecond->move(500,0);
    graphThird->move(0,600);

    ReceiverSettings settings;
    settings.rfSettings.centralFreq=88.4e6;
    settings.rfSettings.sampleFreq=2.4e6;
    settings.sync_mode=1;
    settings.fileName="Signal";
    settings.sampleCount=4096;
    settings.bytes_to_read=2048;
    settings.n_read=1024;
    settings.direct_sampling=1;
    ReceiverHWImpl rcv;

    ComplexSignal signal(settings.bytes_to_read);
    settings.outputBuffer = signal.data();

    rcv.set(settings);
    rcv.start();

      fftw_complex* sig=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*signal.size());
      fftw_complex* spec=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*signal.size());
      std::vector<Complex<double>> spect;
      ComplexForFFTW_Complex(sig,signal);
      fft(sig,spec,signal.size());
      FFTW_ComplexForComplex(spec,spect,signal.size());
      std::vector<double> specA;
      for(int i=0;i<spect.size();i++)
          specA.push_back(spect[i].abs());

      FilterMovingAverageNonRec fil;

     specA=fil.filtration(specA,50);

      QVector<Complex<uint8_t>> vec;
      vec.resize(signal.size());
      vec=QVector<Complex<uint8_t>>(signal.begin(), signal.end());
      QVector<Complex<double>> spectVecQ;
      spectVecQ.resize(signal.size());
      spectVecQ=QVector<Complex<double>>(spect.begin(), spect.end());


      //Просто для просмотра действительной и мнимой части пока
      // не сделан графический интерфейс
      QVector<double> yRe;
      QVector<double> xRe;
      QVector<double> yIm;
      QVector<double> xIm;
      QVector<double> specAbs;

      for(size_t i=0;i<vec.size();i++)
          yRe.push_back(vec[i].real());
      for(size_t i=0;i<yRe.size();i++)
          xRe.push_back(i);
      for(size_t i=0;i<vec.size();i++)
          yIm.push_back(vec[i].imag());
      for(size_t i=0;i<yIm.size();i++)
          xIm.push_back(i);
      for(size_t i=0;i<spect.size();i++)
      {
          specAbs.push_back(log(specA[i]));
      }

//      auto max =*std::max_element(specAbs.begin(), specAbs.end());

//      for(size_t i=0;i<spect.size();i++)
//      {
//          specAbs[i]=specAbs[i]/max;
//      }

      QVector<double> freqN;
      for(size_t i=0;i<spect.size();i++)
          freqN.push_back((i*settings.rfSettings.sampleFreq)/spect.size());

      graphOne->addGraph();
      graphOne->graph()->setData(xRe,yRe);
      graphOne->graph()->rescaleAxes();

      graphOne->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

      graphSecond->addGraph();
      graphSecond->graph()->setData(xIm,yIm);
      graphSecond->graph()->rescaleAxes();

      graphSecond->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

      graphThird->addGraph();
      graphThird->graph()->setData(freqN,specAbs);
      graphThird->graph()->rescaleAxes();

      graphThird->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

      w.show();
      rcv.stop();

//      sendResultToClient(settings, std::move(signal));



    return a.exec();

}
