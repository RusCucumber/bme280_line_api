#include "mods.h"

int main(void)
{
    init();
    get_sensor_data();
    read_config();
    set_config();
    mqtt_pub();
    finit();
        
    return 0;
}
