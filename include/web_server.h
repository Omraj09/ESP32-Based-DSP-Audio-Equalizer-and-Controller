#ifndef WEB_SERVER_H
#define WEB_SERVER_H

/**
 * @brief Initializes the asynchronous web server and Wi-Fi access point.
 * Designed to run as an independent FreeRTOS task.
 * * @param pvParameters Standard FreeRTOS task parameter pointer (usually NULL).
 */
void init_web_server(void *pvParameters);

#endif // WEB_SERVER_H
