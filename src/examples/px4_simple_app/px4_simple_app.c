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

#include <uORB/topics/manual_control_setpoint.h>
#include <uORB/topics/actuator_direct.h>
#include <drivers/drv_rc_input.h>


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
    px4_pollfd_struct_t fds[] = {
        { .fd = sensor_sub_fd,   .events = POLLIN },
        /* there could be more file descriptors here, in the form like:
         * { .fd = other_sub_fd,   .events = POLLIN },
         */
    };
    orb_set_interval(sensor_sub_fd, 10);
    /* copy sensors raw data into local buffer */
    //struct vehicle_attitude_setpoint_s att_set;
    //struct manual_control_setpoint_s mcs;
    struct rc_input_values rc = {};
    //orb_advert_t att_set_pub = orb_advertise(ORB_ID(vehicle_attitude_setpoint), &att_set);
    //orb_advert_t mcs_pub = orb_advertise(ORB_ID(manual_control_setpoint), &mcs);
    orb_advert_t _rc_pub = orb_advertise(ORB_ID(input_rc), &rc);


    for(int j= 0;j<10000;j++){
        int poll_ret = px4_poll(fds, 1, 100);
        int error_counter = 0;

        /* handle the poll result */
        if (poll_ret == 0) {
            /* this means none of our providers is giving us data */
            PX4_ERR("Got no data within");

        } else if (poll_ret < 0) {
            /* this is seriously bad - should be an emergency */
            if (error_counter < 10 || error_counter % 50 == 0) {
                /* use a counter to prevent flooding (and slowing us down) */
                PX4_ERR("ERROR return value from poll(): %d", poll_ret);
            }

            error_counter++;

        } else {

    if (fds[0].revents & POLLIN) {

    struct vehicle_attitude_s att;
    rc.timestamp = hrt_absolute_time();

    rc.timestamp_last_signal = rc.timestamp;

    rc.channel_count = 8;

    rc.rc_failsafe = false;

    rc.rc_lost = false;

    rc.rc_lost_frame_count = 0;

    rc.rc_total_frame_count = 1;

    rc.rc_ppm_frame_length = 0;

    rc.input_source = RC_INPUT_SOURCE_MAVLINK;

    rc.rssi = RC_INPUT_RSSI_MAX;

    /* channels */
    rc.values[0] = j;

    rc.values[1] = j;

    rc.values[2] = j;

    rc.values[3] = j;

    rc.values[4] = j;

    rc.values[5] = j;

    rc.values[6] = j;

    rc.values[7] = j;
    orb_publish(ORB_ID(input_rc), _rc_pub, &rc);
    orb_copy(ORB_ID(vehicle_attitude), sensor_sub_fd, &att);
    //euler = matrix::Quatf(att.q);
    //att_set.timestamp = hrt_absolute_time();

    //att_set.roll_body = -10.0f;
    //att_set.pitch_body = 0.0;
    //att_set.yaw_body = 0.0;
    //mcs.x = -1.0;
    //mcs.y = 0.0f;
    //mcs.z = 0.0;
    /* copy sensors raw data into local buffer */
    //orb_publish(ORB_ID(vehicle_attitude_setpoint), att_set_pub, &att_set);
    //orb_publish(ORB_ID(manual_control_setpoint), mcs_pub, &mcs);

    PX4_INFO("roll\t%8.4f\t%8.4f\t%8.4f\t%8.4f",(double)att.q[0],(double)att.q[1],(double)att.q[2],(double)att.q[3]);
}
}
}
    PX4_INFO("exiting");
    return 0;
}

