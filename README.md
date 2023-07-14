# RTL-SDR

Данная библиотека основывается на вот этом репозитории [keernerd](https://github.com/keenerd/rtl-sdr), но она давно не обновлялась, поэтому лучше изучить следующий репоизиторий от [osmocom](https://github.com/osmocom/rtl-sdr).

Они по большей части идентичны, но в последней чуть больше реализовано и исправлены некоторые недочеты.

## Что необходимо для корректной работы

Для начала работы необходимо установить необходимые библиотеки и произвести некоторые манипуляции. Можно воспользоваться данной [статьей](https://blog.radiotech.kz/radio/bystryj-start-s-rtl-sdr-v-linux/) в ней вполне неплохо описано, что нужно делать.

## Возможности библиотеки

На данный момент библиотека предоставляет такие возможности:

- настройка устройства
- получение отсчетов I и Q
- получение спектра c помощью ffw3

Ниже будет приведен список функций, которые хотелось бы реализовать для улучшения работы с rtl-sdr и возможно добавления поддержки других устройств.

## TODO

- Реализовать асинхронное чтение данных (можно реализовать на подобии [rtl-sdr-scanner-cpp](https://github.com/shajen/rtl-sdr-scanner-cpp/tree/master)).
- Проверить работу с несколькими устройствами. Если не работает, то необходимо реализовать.
- Хотелось бы добавить структру, которая содержит инфрматицию об sdr приемнике.
- Хотелосб бы добавить эмуляцию приемника, который бы генерировал зашумленную 
зашумленную синусоиду.
- Возможно хотелось бы улучшить FFT на основе [rtl-power-fftw](https://github.com/AD-Vega/rtl-power-fftw/tree/master).
- Добавить поддержку других устройств (HackRF, KrakenSDR и др.)

## Полезные ссылки по RTL-SDR

### Репозитории, на которых можно основываться для улучшения

- [keernerd](https://github.com/keenerd/rtl-sdr)
- [osmocom](https://github.com/osmocom/rtl-sdr)
- [rtl-power-fftw](https://github.com/AD-Vega/rtl-power-fftw/tree/master). В нем реализована улучшенная версия rtl_power из [keernerd](https://github.com/keenerd/rtl-sdr) или [osmocom](https://github.com/osmocom/rtl-sdr). В нем используется fftw3 для более удобного вычисления FFT.
- [rtl-sdr-scanner-cpp](https://github.com/shajen/rtl-sdr-scanner-cpp/tree/master). Можно использовать для улучшения библиотеки и добавления в асинхронного чтения.
- [SDRPlusPlus](https://github.com/AlexandreRouma/SDRPlusPlus/tree/master). Возможно здесь можго найти что-то полезное.

### Ссылки для дополнительной информации

- https://www.aaronscher.com/wireless_com_SDR/RTL_SDR_AM_spectrum_demod.html
- https://www.rtl-sdr.com/
- https://rtl-sdr.com/wp-content/uploads/2013/04/R820T_datasheet-Non_R-20111130_unlocked.
pdf
- http://superkuh.com/rtlsdr.html#ltescanner
- https://eax.me/r820t2-module/
- https://www.rtl-sdr.com/wp-content/uploads/2018/02/RTL-SDR-Blog-V3-Datasheet.pdf

Возможно данные материалы окажутся полезными при доработке библиотеки.