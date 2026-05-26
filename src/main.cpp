#include <Arduino.h>
#include "BluetoothA2DPSink.h"
#include "dsp_biquad.h"
#include "web_server.h"

BluetoothA2DPSink a2dp_sink;

// FreeRTOS Task Handles
TaskHandle_t WebServerTask;

// DSP Callback: This intercepts the raw I2S data from Bluetooth before it hits the DAC
void read_data_stream(const uint8_t *data, uint32_t length) {
    int16_t *pcm_data = (int16_t *)data;
    uint32_t sample_count = length / 2; // 16-bit audio

    for (uint32_t i = 0; i < sample_count; i += 2) {
        // Apply DSP to Left Channel
        pcm_data[i] = process_audio_sample(pcm_data[i], 0); 
        // Apply DSP to Right Channel
        pcm_data[i+1] = process_audio_sample(pcm_data[i+1], 1); 
    }
}

void setup() {
    Serial.begin(115200);

    // Initialize Web Server on Core 0
    xTaskCreatePinnedToCore(
        init_web_server,    // Task function
        "WebServerTask",    // Name of task
        4096,               // Stack size
        NULL,               // Parameter
        1,                  // Priority
        &WebServerTask,     // Task handle
        0                   // Pin to Core 0
    );

    // Initialize I2S Output Configuration
    i2s_pin_config_t my_pin_config = {
        .bck_io_num = 26,   // Bit Clock
        .ws_io_num = 25,    // Word Select (L/R Clock)
        .data_out_num = 22, // Data Out
        .data_in_num = I2S_PIN_NO_CHANGE
    };

    a2dp_sink.set_pin_config(my_pin_config);
    a2dp_sink.set_stream_reader(read_data_stream, false); 
    a2dp_sink.start("ESP32_DSP_Audio"); 
    
    Serial.println("System Initialized. A2DP Sink active.");
}

void loop() {
    // Empty: FreeRTOS handles the tasks in the background
    vTaskDelay(1000 / portTICK_PERIOD_MS); 
}
