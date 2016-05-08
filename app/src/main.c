#include <pebble.h>
#include "windows/routes.h"
#include "windows/predictions.h"
#include "layers/splash.h"
#include "modules/bluetooth.h"

static void app_init(void);
static void app_deinit(void);
void inbox_received_callback(DictionaryIterator *iterator, void *context);

int main(void) {
  app_init();
  app_event_loop();
  app_deinit();

  return 0;
}

static void app_init(void) {
  bluetooth_initialize(inbox_received_callback);
  routes_window_init();
  splash_show("TORONTO TRANSIT\nBY @chesterbr");
}

static void app_deinit(void) {
  splash_destroy();
  routes_window_deinit();
}

void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  routes_window_inbox_received(iterator, context);
  predictions_window_inbox_received(iterator, context);
  splash_layer_inbox_received(iterator, context);
}

