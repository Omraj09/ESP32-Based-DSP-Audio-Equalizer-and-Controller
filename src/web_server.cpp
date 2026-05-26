#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "web_server.h"
#include "dsp_biquad.h"

AsyncWebServer server(80);

void init_web_server(void *pvParameters) {
    WiFi.softAP("ESP32_Audio_Config", "12345678");

    server.on("/update_eq", HTTP_GET, [](AsyncWebServerRequest *request){
        if (request->hasParam("freq") && request->hasParam("gain")) {
            String freq_str = request->getParam("freq")->value();
            String gain_str = request->getParam("gain")->value();
            
            update_filter_coefficients(freq_str.toFloat(), gain_str.toFloat());
            request->send(200, "text/plain", "EQ Updated");
        } else {
            request->send(400, "text/plain", "Bad Request");
        }
    });

    server.begin();
    
    for(;;) {
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Yield to other Core 0 tasks
    }
}
