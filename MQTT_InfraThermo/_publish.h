#include <MqttConnector.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
bool mlx_initialised = false;
void init_mlx() {
  if (!mlx_initialised) {
    mlx_initialised = true;
    mlx.begin();
  }
}

MqttConnector::prepare_data_hook_t on_prepare_data =
[&](JsonObject * root) -> void {
    init_mlx();

    JsonObject& data = (*root)["d"];
    JsonObject& info = (*root)["info"];

    data["myName"] = DEVICE_NAME;
    data["millis"] = millis();
    data["temp"] = mlx.readObjectTempC();
};
