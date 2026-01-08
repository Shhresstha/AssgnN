#include "meter_model.h"
#include <stdio.h>

bool serialize_to_json(const GatewayPayload*, char*, size_t);

int main(void) {
    GatewayPayload gateway = {
        .gatewayId = "gateway_1234",
        .date = "1970-01-01",
        .deviceType = "stromleser",
        .intervalMinutes = 15,
        .totalReadings = 1,
        .deviceCount = 1
    };

    gateway.devices[0] = (DeviceReading){
        .media = "water",
        .meter = "waterstarm",
        .deviceId = "stromleser_50898527",
        .unit = "m3",
        .dataCount = 1,
        .data = {{
            "1970-01-01 00:00",
            "1970-01-01 00:00",
            107.752,
            "OK"
        }}
    };

    char json_buffer[1024];
    serialize_to_json(&gateway, json_buffer, sizeof(json_buffer));

    // In real STM32 firmware, output via UART / SWO / logging
    printf("%s\n", json_buffer);

    while (1) {}
}
