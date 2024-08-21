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

#include "alert_pitstop/alert_pitstop.hpp"

AlertPistop::AlertPistop() : Node("alert_pitstop_node") {
  // logging data
  auto now = std::chrono::system_clock::now();
  std::time_t end_time = std::chrono::system_clock::to_time_t(now);

  log_file_.open("/aichallenge/workspace/condition.log", std::ios::app);
  if (log_file_.is_open()) {
    log_file_ << "Current Time and Date: " << std::ctime(&end_time) << std::endl;
  } else {
    RCLCPP_ERROR(this->get_logger(), "Failed to open log file");
  }

  pub_ = this->create_publisher<PitstopAlert>("output", 1);

  sub_ = this->create_subscription<PitstopCondition>(
    "/aichallenge/pitstop/condition", 1,
    [this](const std::shared_ptr<PitstopCondition> msg) {
        PitstopAlert alert;
        // メッセージの 'data' フィールドの値を取得
        int data = msg->data;
        int threshold = 1000;
        bool flag = 0;
        // 'data' が閾値を超えたらalertをTrueに
        if (data > threshold) {
          flag = 1;
        } else {
          flag = 0;
        }
        // 'data' の値をログファイルに出力
        if (log_file_.is_open()) {
          log_file_ << "Received message with data: " << data << std::endl;
          log_file_ << "Received message with alert: " << flag << std::endl;
        } else {
          RCLCPP_ERROR(this->get_logger(), "Log file is not open");
        }
        alert.data = flag;
        pub_->publish(alert);
    }
  );
}

int main(int argc, char const* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<AlertPistop>());
  rclcpp::shutdown();
  return 0;
}
