#include <px4_config.h>
#include <px4_tasks.h>
#include <px4_posix.h>
#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include <string.h>
#include <math.h>
#include <drivers/drv_hrt.h>
#include <mathlib/mathlib.h>

#include <uORB/uORB.h>
#include <uORB/topics/sel_solar_plane.h>
#include <uORB/topics/vehicle_attitude_setpoint.h>
#include <uORB/topics/vehicle_attitude.h>

#include <uORB/topics/actuator_controls.h>
#include <uORB/topics/actuator_direct.h>
#include <uORB/topics/vehicle_rates_setpoint.h>

__EXPORT int px4_simple_app_main(int argc, char *argv[]);

int px4_simple_app_main(int argc, char *argv[])
{
   PX4_INFO("Hello Sky!");

    struct sel_solar_plane_s sel;
    memset(&sel, 0, sizeof(sel));
/*
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
*/
    /* subscribe to sensor_combined topic */
    int sensor_sub_fd = orb_subscribe(ORB_ID(vehicle_attitude));
    /* limit the update rate to 5 Hz */
    struct vehicle_attitude_s att;
    matrix::Eulerf euler;
    /* copy sensors raw data into local buffer */
    orb_copy(ORB_ID(vehicle_attitude), sensor_sub_fd, &att);
    struct vehicle_attitude_setpoint_s att_set;
    orb_advert_t att_set_pub = orb_advertise(ORB_ID(vehicle_attitude_setpoint), &att_set);
    for(int j= 0;j<1000;j++){
    orb_copy(ORB_ID(vehicle_attitude), sensor_sub_fd, &att);
    //euler = matrix::Quatf(att.q);
    att_set.timestamp = hrt_absolute_time();
    att_set.roll_body = 90;
    att_set.pitch_body = 0.0;
    att_set.yaw_body = 0.0;
    /* copy sensors raw data into local buffer */
    orb_copy(ORB_ID(vehicle_attitude), sensor_sub_fd, &att);
    PX4_INFO("Loop2");

    orb_publish(ORB_ID(vehicle_attitude_setpoint), att_set_pub, &att_set);
    usleep(500);
    }
    PX4_INFO("Loop2");


    PX4_INFO("exiting");

    return 0;
}
