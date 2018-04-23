#ifndef __ahrs_H
#define __ahrs_H

void get_euler_angle(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz, float *pitch, float *roll, float *yaw);
#endif
