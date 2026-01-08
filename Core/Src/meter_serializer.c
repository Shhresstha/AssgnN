#include "meter_model.h"
#include "json_writer.h"
#include <stdbool.h>

bool serialize_to_json(const gateway_payload_t *g,
                       char *out,
                       size_t out_size) {

    json_writer_t w;
    json_init(&w, out, out_size);

    if (!json_write(&w, "[{")) return false;

    json_write(&w,
        "\"gatewayId\":\"%s\","
        "\"date\":\"%s\","
        "\"deviceType\":\"%s\","
        "\"interval_minutes\":%u,"
        "\"total_readings\":%u,",
        g->gateway_id,
        g->date,
        g->device_type,
        g->interval_minutes,
        g->total_readings
    );

    json_write(&w, "\"values\":{");
    json_write(&w, "\"device_count\":%u,", g->device_count);
    json_write(&w, "\"readings\":[");

    for (uint8_t i = 0; i < g->device_count; i++) {
        device_reading_t *d = &g->devices[i];

        json_write(&w,
            "{"
            "\"media\":\"%s\","
            "\"meter\":\"%s\","
            "\"deviceId\":\"%s\","
            "\"unit\":\"%s\","
            "\"data\":[",
            d->media,
            d->meter,
            d->device_id,
            d->unit
        );

        for (uint8_t j = 0; j < d->data_count; j++) {
            meter_data_t *m = &d->data[j];

            json_write(&w,
                "{"
                "\"timestamp\":\"%s\","
                "\"meter_datetime\":\"%s\","
                "\"total_m3\":%.3f,"
                "\"status\":\"%s\""
                "}%s",
                m->timestamp,
                m->meter_datetime,
                m->total_m3,
                m->status,
                (j + 1 < d->data_count) ? "," : ""
            );
        }

        json_write(&w, "]}%s", (i + 1 < g->device_count) ? "," : "");
    }

    json_write(&w, "]}]}]");
    return true;
}
