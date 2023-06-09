#pragma once
#include <Arduino.h>
#include <esp_wifi.h>
#include <esp_wifi_types.h>
#include <esp_system.h>
#include <esp_event.h>
#include <esp_event_loop.h>
#include "mac_address.h"
#include "ieee_802_11_mac_header.h"

// Must be defined elsewhere!
void handle_packet(void* buffer, wifi_promiscuous_pkt_type_t type);

// This is a copy of what the example code I followed used.
wifi_country_t wifi_country = {
  .cc = "CN",
  .schan = 1,
  .nchan = 13
};

static esp_err_t handle_event_loop(void* ctx, system_event_t* event) {
  return ESP_OK;
}

// This is also almost a copy from the demo I used.
inline void setup_wifi_sniffer() {
  tcpip_adapter_init();
  ESP_ERROR_CHECK(esp_event_loop_init(handle_event_loop, NULL));

  wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&config));
  ESP_ERROR_CHECK(esp_wifi_set_country(&wifi_country));
  ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_NULL));
  ESP_ERROR_CHECK(esp_wifi_start());

  esp_wifi_set_promiscuous(true);
  esp_wifi_set_promiscuous_rx_cb(&handle_packet);
}

inline void set_channel(uint8_t channel) {
  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
}
