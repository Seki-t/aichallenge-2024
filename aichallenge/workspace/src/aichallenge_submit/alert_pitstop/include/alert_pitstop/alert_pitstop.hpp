// Copyright 2023 Tier IV, Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef ALERT_PITSTOP__ALERT_PITSTOP_HPP_
#define ALERT_PITSTOP__ALERT_PITSTOP_HPP_

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/bool.hpp"
#include <fstream>
#include <chrono>

class AlertPistop : public rclcpp::Node {
 public:
  using PitstopCondition = std_msgs::msg::Int32;
  using PitstopAlert = std_msgs::msg::Bool;

 public:
  AlertPistop();

 private:
  rclcpp::Subscription<PitstopCondition>::SharedPtr sub_;
  rclcpp::Publisher<PitstopAlert>::SharedPtr pub_;
  std::ofstream log_file_;
};

#endif  // ALERT_PITSTOP__ALERT_PITSTOP_HPP_