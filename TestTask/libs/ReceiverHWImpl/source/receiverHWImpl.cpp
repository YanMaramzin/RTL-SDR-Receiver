#include "receiverHWImpl.h"
#include <iostream>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

ReceiverHWImpl::ReceiverHWImpl()
{
    filename=NULL;
    gain = 0;
    ppm_error = 0;
    sync_mode = 0;
    direct_sampling = 0;
    dithering = 1;
    dev_index = 0;
    dev_given = 0;
    dev=nullptr;
    do_exit=0;

}



void ReceiverHWImpl::set(const ReceiverSettings &settings)
{
    sync_mode=settings.sync_mode;
    bytes_to_read=settings.bytes_to_read;
    out_block_size=settings.sampleCount;
    n_read=settings.n_read;
    filename=settings.fileName;
    outputBuffer=settings.outputBuffer;
    dev_index = verbose_device_search("0");
    dev_given = 1;


    if (!dithering) {
        fprintf(stderr, "Disabling dithering...  ");
        r = rtlsdr_set_dithering(dev, dithering);
        if (r) {
            fprintf(stderr, "failure\n");
        } else {
            fprintf(stderr, "success\n");
        }
    }

    if (direct_sampling) {
        verbose_direct_sampling(dev, direct_sampling);
    }

    r = rtlsdr_open(&dev, (uint32_t)dev_index);
    if (r < 0) {
        fprintf(stderr, "Failed to open rtlsdr device #%d.\n", dev_index);
        exit(1);
    }
    /* Set the sample rate */
    verbose_set_sample_rate(dev, settings.rfSettings.sampleFreq);

    /* Set the frequency */
    verbose_set_frequency(dev, settings.rfSettings.centralFreq);

    if (0 == gain) {
        /* Enable automatic gain */
        verbose_auto_gain(dev);
    } else {
        /* Enable manual gain */
        gain = nearest_gain(dev, gain);
        verbose_gain_set(dev, gain);
    }

    verbose_ppm_set(dev, ppm_error);

}


void ReceiverHWImpl::start(){

        file = fopen(filename, "wb");
        if (!file)
        {
            fprintf(stderr, "Failed to open %s\n", filename);
        }
        /* Reset endpoint before we start reading from it (mandatory) */
        verbose_reset_buffer(dev);
        if (sync_mode) {
            fprintf(stderr, "Reading samples in sync mode...\n");
            while (!do_exit) {
                r = rtlsdr_read_sync(dev, outputBuffer, out_block_size, &n_read);
                if (r < 0) {
                    fprintf(stderr, "WARNING: sync read failed.\n");
                    break;
                }

                if ((bytes_to_read > 0) && (bytes_to_read <(uint32_t)n_read)) {
                    n_read = bytes_to_read;
                    do_exit = 1;
                }

                if (fwrite(outputBuffer, 1, n_read, file) != (size_t)n_read) {
                    fprintf(stderr, "Short write, samples lost, exiting!\n");
                    break;
                }

//                if ((uint32_t)n_read < out_block_size) {
//                    fprintf(stderr, "Short read, samples lost, exiting!\n");
//                    break;
//                }

                if (bytes_to_read > 0)
                    bytes_to_read -= n_read;
                }

            }
//        else {
//                fprintf(stderr, "Reading samples in async mode...\n");
//                r = rtlsdr_read_async(dev,rtlsdr_callback, (void *)file,
//                              0, out_block_size);
//            }
}




void ReceiverHWImpl::stop(){
        if (do_exit)
            fprintf(stderr, "\nUser cancel, exiting...\n");
        else
            fprintf(stderr, "\nLibrary error %d, exiting...\n", r);
        if (file != stdout)
            fclose(file);
        rtlsdr_close(dev);
}










