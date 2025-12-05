#pragma once
#include <mutex>
#include <cstdint>

class MockDriver {
public:
  MockDriver() : position_(0.0), command_(0.0) {}

  bool connect() {
    connected_ = true;
    return true;
  }

  bool isConnected() const { return connected_; }

  // Simulate reading motor feedback
  double readPosition() {
    std::lock_guard<std::mutex> lock(mutex_);
    // simple simulation: position moves toward command
    position_ = position_ + 0.05 * (command_ - position_);
    return position_;
  }

  // Simulate writing to serial
  void sendCommand(double cmd) {
    std::lock_guard<std::mutex> lock(mutex_);
    command_ = cmd;
  }

private:
  bool connected_{false};
  double position_;
  double command_;
  std::mutex mutex_;
};

