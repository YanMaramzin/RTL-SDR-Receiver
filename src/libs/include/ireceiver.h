#pragma once

#include <cstdint>
#include "complex.h"
#include <vector>


/**
* @brief Структура, которой находятся настройки приемника,
* связанные с железом.
*/
struct RfSettings
{
  uint32_t centralFreq;
  uint32_t sampleFreq;
  int gain {0};
  int ppm_error {0};
  int agcMode {0};
};

/**
* @brief Структура, которой находятся все настройки приемника
*/
struct ReceiverSettings
{
    RfSettings rfSettings;
    uint32_t sampleCount;
    int n_read;
    int sync_mode {1};
    int direct_sampling {0};
    int dithering {1};
};

//struct Info
//{

//};


class IReceiver
{
public:    
    using Buffer = std::vector<Complex<uint8_t>>;
    using SpectBuff = std::vector<Complex<double>>;
    virtual ~IReceiver() = default;    

    virtual bool getComplex(const ReceiverSettings &, Buffer &) = 0;
    virtual void getSpectrum(const ReceiverSettings &, SpectBuff &) = 0;
};


