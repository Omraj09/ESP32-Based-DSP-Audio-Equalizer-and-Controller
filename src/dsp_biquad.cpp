#include <math.h>
#include "dsp_biquad.h"

// Standard audio sample rate for A2DP
const float SAMPLE_RATE = 44100.0f; 

// Update coefficients for a Peaking EQ Filter
void update_filter_coefficients(float frequency, float gain_db) {
    // Quality factor (Q) determines the bandwidth of the EQ curve. 
    // 0.707 is a standard, musically pleasing bandwidth.
    float Q = 0.707f; 

    // Convert gain from dB to linear amplitude
    float A = pow(10.0f, gain_db / 40.0f);
    
    // Calculate angular frequency
    float w0 = 2.0f * M_PI * frequency / SAMPLE_RATE;
    float alpha = sin(w0) / (2.0f * Q);

    // Calculate intermediate a0 coefficient
    float a0 = 1.0f + (alpha / A);

    // Update global Biquad coefficients
    b0 = (1.0f + alpha * A) / a0;
    b1 = (-2.0f * cos(w0)) / a0;
    b2 = (1.0f - alpha * A) / a0;
    
    // Note: a1 and a2 are negated in the difference equation calculation 
    // in the process_audio_sample function, so they remain positive here.
    a1 = (-2.0f * cos(w0)) / a0;
    a2 = (1.0f - (alpha / A)) / a0;
}
