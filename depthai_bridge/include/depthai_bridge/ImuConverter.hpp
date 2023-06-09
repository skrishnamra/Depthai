#pragma once

#include <ros/ros.h>

#include <boost/make_shared.hpp>
#include <depthai/depthai.hpp>
#include <depthai_bridge/depthaiUtility.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <unordered_map>

#include "sensor_msgs/Imu.h"

namespace dai {

namespace ros {

namespace ImuMsgs = sensor_msgs;
using ImuPtr = ImuMsgs::Imu::Ptr;

enum class ImuSyncMethod { COPY, LINEAR_INTERPOLATE_GYRO, LINEAR_INTERPOLATE_ACCEL };

class ImuConverter {
   public:
    ImuConverter(const std::string& frameName,
                 ImuSyncMethod syncMode = ImuSyncMethod::LINEAR_INTERPOLATE_ACCEL,
                 double linear_accel_cov = 0.0,
                 double angular_velocity_cov = 0.0);

    void toRosMsg(std::shared_ptr<dai::IMUData> inData, std::deque<ImuMsgs::Imu>& outImuMsg);

   private:
    void FillImuData_LinearInterpolation(std::vector<IMUPacket>& imuPackets, std::deque<ImuMsgs::Imu>& imuMsgs);
    ImuMsgs::Imu CreateUnitMessage(dai::IMUReportAccelerometer accel, dai::IMUReportGyroscope gyro);

    uint32_t _sequenceNum;
    double _linear_accel_cov, _angular_velocity_cov;
    const std::string _frameName = "";
    ImuSyncMethod _syncMode;
    std::chrono::time_point<std::chrono::steady_clock> _steadyBaseTime;
    ::ros::Time _rosBaseTime;
};

}  // namespace ros

namespace rosBridge = ros;

}  // namespace dai
