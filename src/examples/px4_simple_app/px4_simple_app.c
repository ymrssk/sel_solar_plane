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

    struct sel_solar_plane_s ssp;
    memset(&ssp, 0, sizeof(ssp));
    for(int j= 0;j<10;j++){
    orb_advert_t sel_pub = orb_advertise(ORB_ID(sel_solar_plane), &ssp);
    ssp.timestamp = hrt_absolute_time();
    ssp.battery_voltage  = 10.0;
    ssp.battery_current = 10.0;
    ssp.battery_power  = 10.0;
    ssp.battery_remaining = 10.0;
    ssp.sap_voltage  = 10.0;
    ssp.sap_current = 10.0;
    ssp.sap_power  = 10.0;
    ssp.sap_str1_voltage = 10.0;
    ssp.sap_str1_current  = 10.0;
    ssp.sap_str1_power = 10.0;
    ssp.sap_str2_voltage = 10.0;
    ssp.sap_str2_current  = 10.0;
    ssp.sap_str2_power = 10.0;
    ssp.sap_str3_voltage = 10.0;
    ssp.sap_str3_current  = 10.0;
    ssp.sap_str3_power = 10.0;
    ssp.load_current = 10.0;
    ssp.load_voltage = 10.0;
    ssp.load_power  = 10.0;
    ssp.component_status = 10.0;
    orb_publish(ORB_ID(sel_solar_plane), sel_pub, &ssp);
    sleep(1000000);
    }

/*
    int sensor_sub_fd = orb_subscribe(ORB_ID(vehicle_attitude));
    px4_pollfd_struct_t fds[] = {
        { .fd = sensor_sub_fd,   .events = POLLIN },
    };
    orb_set_interval(sensor_sub_fd, 10);

    struct rc_input_values rc = {};

    orb_advert_t _rc_pub = orb_advertise(ORB_ID(input_rc), &rc);


    for(int j= 0;j<10000;j++){
        int poll_ret = px4_poll(fds, 1, 100);
        int error_counter = 0;

        if (poll_ret == 0) {
            PX4_ERR("Got no data within");

        } else if (poll_ret < 0) {
            if (error_counter < 10 || error_counter % 50 == 0) {
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

    PX4_INFO("roll\t%8.4f\t%8.4f\t%8.4f\t%8.4f",(double)att.q[0],(double)att.q[1],(double)att.q[2],(double)att.q[3]);
}
}
}*/
    PX4_INFO("exiting");
    return 0;
}

