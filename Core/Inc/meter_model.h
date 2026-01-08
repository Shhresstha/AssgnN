#ifndef METER_MODEL_H
#define METER_MODEL_H

#include <stdint.h>

#define MAX_DEVICES        4
#define MAX_DATA_POINTS    4

typedef struct {
    const char *timestamp;
    const char *meter_datetime;
    double      total_m3;
    const char *status;
} meter_data_t;

typedef struct {
    const char     *media;
    const char     *meter;
    const char     *device_id;
    const char     *unit;
    uint8_t         data_count;
    meter_data_t    data[MAX_DATA_POINTS];
} device_reading_t;

typedef struct {
    const char         *gateway_id;
    const char         *date;
    const char         *device_type;
    uint16_t            interval_minutes;
    uint16_t            total_readings;
    uint8_t             device_count;
    device_reading_t    devices[MAX_DEVICES];
} gateway_payload_t;

#endif
