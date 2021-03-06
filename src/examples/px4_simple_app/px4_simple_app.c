#include <px4_config.h>
#include <px4_tasks.h>
#include <px4_posix.h>
#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include <string.h>
#include <math.h>
#include <drivers/drv_hrt.h>

#include <uORB/uORB.h>
#include <uORB/topics/sel_solar_plane.h>

__EXPORT int px4_simple_app_main(int argc, char *argv[]);

int px4_simple_app_main(int argc, char *argv[])
{
   PX4_INFO("Hello Sky!");

    struct sel_solar_plane_s sel;
    memset(&sel, 0, sizeof(sel));

    orb_advert_t sel_pub = orb_advertise(ORB_ID(sel_solar_plane), &sel);
    sel.timestamp = hrt_absolute_time();
    sel.sel_bat_generating_capacity = 100.0;
    sel.sel_load_side_current_value = 100.0;
    sel.sel_load_side_voltage_value = 100.0;
    sel.sel_solar_cell_module_1_voltage = 100.0;
    sel.sel_solar_cell_module_2_voltage = 100.0;
    sel.sel_solar_cell_module_3_voltage = 100.0;
    sel.sel_solar_cell_module_1_current = 100.0;
    sel.sel_solar_cell_module_2_current = 100.0;
    sel.sel_solar_cell_module_3_current = 100.0;
    orb_publish(ORB_ID(sel_solar_plane), sel_pub, &sel);

    PX4_INFO("exiting");

    return 0;
}
