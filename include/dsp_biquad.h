#ifndef DSP_BIQUAD_H
#define DSP_BIQUAD_H

#include <stdint.h>

// Extern declarations prevent multiple definition errors during linking.
// The actual memory is allocated in dsp_biquad.cpp.
extern float b0, b1, b2, a1, a2;
extern float z1_L, z2_L;
extern float z1_R, z2_R;

/**
 * @brief Processes a single raw 16-bit PCM audio sample through the IIR Biquad filter.
 * * @param input The raw audio sample from the Bluetooth A2DP stream.
 * @param channel 0 for Left Channel, 1 for Right Channel.
 * @return int16_t The equalized audio sample to be sent to the I2S DAC.
 */
int16_t process_audio_sample(int16_t input, int channel);

/**
 * @brief Calculates and updates the global Biquad filter coefficients dynamically.
 * * @param frequency The center frequency of the EQ band in Hz.
 * @param gain_db The boost or cut amount in decibels.
 */
void update_filter_coefficients(float frequency, float gain_db);

#endif // DSP_BIQUAD_H
