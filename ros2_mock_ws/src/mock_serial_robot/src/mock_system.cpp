#include "mock_serial_robot/mock_system.hpp"
#include "pluginlib/class_list_macros.hpp"

namespace mock_serial_robot
{

hardware_interface::CallbackReturn MockSystem::on_init(
  const hardware_interface::HardwareInfo & info)
{
  if (hardware_interface::SystemInterface::on_init(info) !=
      hardware_interface::CallbackReturn::SUCCESS)
  {
    return hardware_interface::CallbackReturn::ERROR;
  }

  // Init states and commands
  position_state_ = 0.0;
  command_ = 0.0;

  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn MockSystem::on_configure(
  const rclcpp_lifecycle::State &)
{
  driver_.connect();
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn MockSystem::on_activate(
  const rclcpp_lifecycle::State &)
{
  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn MockSystem::on_deactivate(
  const rclcpp_lifecycle::State &)
{
  return hardware_interface::CallbackReturn::SUCCESS;
}

std::vector<hardware_interface::StateInterface>
MockSystem::export_state_interfaces()
{
  std::vector<hardware_interface::StateInterface> state_interfaces;

  state_interfaces.emplace_back(
    info_.joints[0].name,
    hardware_interface::HW_IF_POSITION,
    &position_state_);

  return state_interfaces;
}

std::vector<hardware_interface::CommandInterface>
MockSystem::export_command_interfaces()
{
  std::vector<hardware_interface::CommandInterface> command_interfaces;

  command_interfaces.emplace_back(
    info_.joints[0].name,
    hardware_interface::HW_IF_POSITION,
    &command_);

  return command_interfaces;
}

hardware_interface::return_type MockSystem::read(
  const rclcpp::Time &,
  const rclcpp::Duration &)
{
  position_state_ = driver_.readPosition();
  return hardware_interface::return_type::OK;
}

hardware_interface::return_type MockSystem::write(
  const rclcpp::Time &,
  const rclcpp::Duration &)
{
  driver_.sendCommand(command_);
  return hardware_interface::return_type::OK;
}

}  // namespace mock_serial_robot

PLUGINLIB_EXPORT_CLASS(
  mock_serial_robot::MockSystem,
  hardware_interface::SystemInterface)

