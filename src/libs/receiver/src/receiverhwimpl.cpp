#include "receiverhwimpl.h"
#include <iostream>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <rtl-sdr.h>



ReceiverHWImpl::ReceiverHWImpl()
{
    open();
}


ReceiverHWImpl::~ReceiverHWImpl()
{
    rtlsdr_close(dev);
}

/**
 * @brief Метод для открытия свистка. Сначала вызывается метод
 * deviceSearch(), чтобы определить что это за свисток.
*/
void ReceiverHWImpl::open()
{
    dev_index = deviceSearch("0");
    int r = rtlsdr_open(&dev, (uint32_t)dev_index);
    if (r < 0) {
        std::cerr << "Failed to open rtlsdr device" << dev_index << "\n";
        exit(1);
    }
}

/**
 * @brief Метод для установки настроек приемника.
 * Данному методу на вход подается структура с настройками.
 * Здесь можно установить:
 * - центральную частоту
 * - частоту дискретизации
 * - усиление
 * - откорректровать центральную частоту
 * Также возможно включить режим автоматического контроля
 * усиления.
*/
void ReceiverHWImpl::set(const ReceiverSettings &settings)
{
    n_read = settings.n_read;

    if (settings.direct_sampling)
        setDirectSampling(settings.direct_sampling);

    setSampleRate(settings.rfSettings.sampleFreq);

    setCenterFreq(settings.rfSettings.centralFreq);

    if (0 == settings.rfSettings.gain) {
        setAutoGain();
    } else {
        auto gain = nearestGain(settings.rfSettings.gain);
        setGain(gain);
    }

    setPpm(settings.rfSettings.ppm_error);

    setAgcMode(settings.rfSettings.agcMode);
}

/**
 * @brief Метод для получения отсчетов I и Q. На вход методу подаются настройки приемника
 * и буфер, в который будут считанны I и Q.
 * Считывание идет следующим образом сначала идет I потом Q и так далее. I и Q представлют
 * собой uint8_t.
 * Минимальная величина буфера может быть 512. Максимальная 256 * 16384. В rtl-sdr.h
 * написано, что длина буфера должна быть кратна 16384 (URB size). Беря во внимание, что
 * минимальная длина буфера 512, то можно сказать, что длина буфера должна быть кратна 512.
 * ( С этим нужно разобраться подробнее)
 * Также важно заметить, что буфером является вектор, сотсоящий из элементов класса Complex.
 * Он содержит re и im. I считывается в re, а Q считывается в im. Из это понятно, что число
 * считанных байт будет в два раза больше, чем число считанных отсчетов. (bytesToRead = 2 * sampleCount)
*/

bool ReceiverHWImpl::getComplex(const ReceiverSettings &settings, ReceiverHWImpl::Buffer &out)
{
    set(settings);
    uint32_t size = settings.sampleCount;
    size = roundPowerTwo(size);
    out.resize(size);
    uint32_t bytesToRead = 2 * settings.sampleCount;
    bytesToRead = roundPowerTwo(bytesToRead);
    resetBuffer();
        auto result = rtlsdr_read_sync(dev, out.data(), bytesToRead, &n_read);

        if (result < 0)
            std::cerr << "WARNING: sync read failed." << std::endl;

    return result;
}

/**
 * @brief Метод для получения результата FFT. На вход методу подаются настройки приемника
 * и буфер, в который будут считанны значения, получившегося спектра.
 * В нем мы используем метод getComplex() для получения I и Q, чтобы в дальнейшем вычислить FFT.
*/

void ReceiverHWImpl::getSpectrum(const ReceiverSettings &settings, IReceiver::SpectBuff &out)
{
    IReceiver::Buffer signal;
    uint32_t size = settings.sampleCount;
    size = roundPowerTwo(size);
    signal.resize(size);
    getComplex(settings, signal);

    std::vector<Complex<float>> signalFloat;
    signalFloat.resize(size);
    for (int i = 0; i < signalFloat.size(); i++) {
        signalFloat[i].re = (static_cast<float>(signal[i].re) - 127.5f);
        signalFloat[i].im = (static_cast<float>(signal[i].im) - 127.5f);
    }

    IReceiver::SpectBuff signalDouble(signalFloat.begin(), signalFloat.end());

    for(int i = 0; i < signalDouble.size(); i++) {
        if (i % 2 == 0)
            signalDouble[i] = -signalDouble[i];
    }
    out.resize(size);

    fft(signalDouble, out, signalDouble.size());
}

/**
 * @brief Функция для поиска устройства.
 * Также она выводит название устройства, производителя и серию.
*/
int ReceiverHWImpl::deviceSearch(char const *s)
{
    int i, device_count, device, offset;
    char *s2;
    char vendor[256] = {0}, product[256] = {0}, serial[256] = {0};
    device_count = rtlsdr_get_device_count();
    if (!device_count) {
        std::cerr << "No supported devices found.\n";
        return -1;
    }
    std::cerr <<"Found "<< device_count << " device(s):\n";
    for (i = 0; i < device_count; i++) {
        if (rtlsdr_get_device_usb_strings(i, vendor, product, serial) == 0) {
            std::cerr << i << ": " << vendor << ", " << product << ", " << serial << "\n";
        } else {
            std::cerr << i <<  "Failed to query data\n";
        }
    }

    /* does string look like raw id number */
    device = (int)strtol(s, &s2, 0);
    if (s2[0] == '\0' && device >= 0 && device < device_count) {
        std::cerr << "Using device " << device << ": " << rtlsdr_get_device_name((uint32_t)device) << "\n";
        return device;
    }
    /* does string exact match a serial */
    for (i = 0; i < device_count; i++) {
        rtlsdr_get_device_usb_strings(i, vendor, product, serial);
        if (strcmp(s, serial) != 0) {
            continue;}
        device = i;
        std::cerr << "Using device " << device << ": " << rtlsdr_get_device_name((uint32_t)device) << "\n";
        return device;
    }
    /* does string prefix match a serial */
    for (i = 0; i < device_count; i++) {
        rtlsdr_get_device_usb_strings(i, vendor, product, serial);
        if (strncmp(s, serial, strlen(s)) != 0) {
            continue;}
        device = i;
        std::cerr << "Using device " << device << ": " << rtlsdr_get_device_name((uint32_t)device) << "\n";
        return device;
    }
    /* does string suffix match a serial */
    for (i = 0; i < device_count; i++) {
        rtlsdr_get_device_usb_strings(i, vendor, product, serial);
        offset = strlen(serial) - strlen(s);
        if (offset < 0) {
            continue;}
        if (strncmp(s, serial+offset, strlen(s)) != 0) {
            continue;}
        device = i;
        std::cerr << "Using device " << device << ": " << rtlsdr_get_device_name((uint32_t)device) << "\n";
        return device;
    }
    std::cerr << "No matching devices found.\n";
    return -1;
}

/**
 * @brief Метод для установки центральной частоты.
*/
int ReceiverHWImpl::setCenterFreq(uint32_t freq)
{
    int r;
    r = rtlsdr_set_center_freq(dev, freq);
    if (r < 0)
        std::cerr << "WARNING: Failed to set center freq.\n";
    else
        std::cerr << "Tuned to " << freq << " Hz.\n" ;
    return r;
}

/**
 * @brief Метод для установки частоты дискретизации приемника.
*/
int ReceiverHWImpl::setSampleRate(uint32_t samp_rate)
{
    int r;
    r = rtlsdr_set_sample_rate(dev, samp_rate);
    if (r < 0)
        std::cerr << "WARNING: Failed to set sample rate.\n";
    else
        std::cerr << "Sampling at " << samp_rate << "\n";
    return r;
}

/**
 * @brief Метод, который устанавливает автоматическое усисление
 * приемника.
*/
int ReceiverHWImpl::setAutoGain()
{
    int r;
    r = rtlsdr_set_tuner_gain_mode(dev, 0);
    if (r != 0)
        std::cerr << "WARNING: Failed to set tuner gain.\n";
    else
        std::cerr << "Tuner gain set to automatic.\n";
    return r;
}

/**
 * @brief Метод для поиска ближайшего усиления, которое
 * возможно установить для данного приемника.
*/

int ReceiverHWImpl::nearestGain(int gain)
{
    int i, r, err1, err2, count, nearest;
    std::vector<int> gains;
    r = rtlsdr_set_tuner_gain_mode(dev, 1);
    if (r < 0) {
        std::cerr << "WARNING: Failed to enable manual gain.\n";
        return r;
    }
    count = rtlsdr_get_tuner_gains(dev, nullptr);
    if (count <= 0) {
        return 0;
    }
    count = rtlsdr_get_tuner_gains(dev, gains.data());
    gains.resize(count);
    nearest = gains[0];
    for (i = 0; i < count; i++) {
        err1 = abs(gain - nearest);
        err2 = abs(gain - gains[i]);
        if (err2 < err1) {
            nearest = gains[i];
        }
    }
    return nearest;
}

/**
 * @brief Метод для установки усиления.
*/
int ReceiverHWImpl::setGain(int gain)
{
    int r;
    r = rtlsdr_set_tuner_gain_mode(dev, 1);
    if (r < 0) {
        std::cerr << "WARNING: Failed to enable manual gain.\n";
        return r;
    }

    r = rtlsdr_set_tuner_gain(dev, gain);
    if (r != 0)
        std::cerr << "WARNING: Failed to set tuner gain.\n";
    else
        std::cerr << "Tuner gain set to" << gain/10.0 <<"dB.\n";
    return r;
}

/**
 * @brief Метод для установки режима Direct Sampling
 * 0 - Откючение режима прямой выборки
 * 1 - Включение режима прямой выборки для вывода I
 * 2 - Включение режима прямой выборки для вывода Q
 * 3 - Включен режим прямой выборки
*/
int ReceiverHWImpl::setDirectSampling(int on)
{
    int r;
    r = rtlsdr_set_direct_sampling(dev, on);
    if (r != 0) {
        std::cerr << "WARNING: Failed to set direct sampling mode.\n";
        return r;
    }

    if (on == 0)
        std::cerr << "Direct sampling mode disabled.\n";
    if (on == 1)
        std::cerr << "Enabled direct sampling mode, input 1/I.\n";
    if (on == 2)
        std::cerr << "Enabled direct sampling mode, input 2/Q.\n";
    if (on == 3)
        std::cerr << "Enabled no-mod direct sampling mode.\n";

    return r;
}

int ReceiverHWImpl::setPpm(int ppm_error)
{
    int r;
    if (ppm_error == 0)
        return 0;
    r = rtlsdr_set_freq_correction(dev, ppm_error);
    if (r < 0)
        std::cerr << "WARNING: Failed to set ppm error.\n";
    else
        std::cerr << "Tuner error set to " << ppm_error << "ppm.\n";
    return r;
}

void ReceiverHWImpl::setOffsetTuningOn()
{
    rtlsdr_set_offset_tuning(dev, 1);
}

/**
 * @brief Функция для включения/выключения автоматического контроля усиления.
 * Он необходим для того, чтобы при большой мощности сигнала приемник
 * не ограничивал сигнал и можно было видеть его без искажений.
 * Например, без включения этого метода синусоиды при большой мощности
 * генератора приемник отсекал часть синусоиды сверху и снизу из-за этого часть
 * данных была неправильной.
*/
void ReceiverHWImpl::setAgcMode(int on)
{
    rtlsdr_set_agc_mode(dev, on);
    if (on)
        std::cerr << "AGC mode on\n";
    else
        std::cerr << "AGC mode off\n";
}

/**
 * @brief Метод для очиски буфера приемника. Необходимо вызывать каждый раз
 * перед чтением данных (асинхронным или синхронным)
*/

int ReceiverHWImpl::resetBuffer()
{
    int r;
    r = rtlsdr_reset_buffer(dev);
    if (r < 0)
        std::cerr << "WARNING: Failed to reset buffers.\n";
    return r;
}

/**
 * @brief Метод для округление до ближайшей степни двойки вверх.
 * Он необходим для того, чтобы можно было правильно считать данные.
*/

uint32_t ReceiverHWImpl::roundPowerTwo(uint32_t &size)
{
    auto result = size - 1;
    for(unsigned k = 0; k <= 4; ++k)
        result |= result >> (1 << k);
    ++result;
    return result;
}









