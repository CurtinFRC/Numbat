// Copyright (c) 2023-2024 CurtinFRC
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#include "Loggers.h"

using namespace loggers;

NTLogger::NTLogger(std::string name, std::string path,
                   std::vector<NT_Table> tables)
    : name(name), tables(tables) {
  for (NT_Table table : this->tables) {
    std::thread thread = std::thread([table]() {
      for (std::string key : table->first.GetKeys()) {
        table->first.GetEntry(key).SetDefaultValue((table->second));
      }
    });
    threads.push_back(&thread);
  }
}

NTLogger::~NTLogger() {
  for (std::thread* thread : this->threads) {
    thread->join();
  }
}

std::string NTLogger::GetName() {
  return this->name;
}

std::vector<NT_Table> NTLogger::GetTables() {
  return this->tables;
}

std::vector<std::pair<std::string, double>> NTLogger::OnLogTick() {
  int i = 0;
  for (NT_Table table : this->tables) {
    std::thread thread = std::thread([table]() {
      for (std::string key : table->first.GetKeys()) {
        table->first.GetEntry(key).SetDefaultValue((table->second));
      }
    });
    threads.at(i)->join();
    threads.emplace(this->threads.begin() + i, &thread);

    i++;
  }

  return std::vector<std::pair<std::string, double>>();
}

DigitalLogger::DigitalLogger(std::string name, std::string path, int channel)
    : name(name), path(path), channel(channel) {
  _input = new frc::DigitalInput(channel);
}

std::vector<std::pair<std::string, double>> DigitalLogger::OnLogTick() {
  std::vector<std::pair<std::string, double>> values;

  values[0] = std::pair<std::string, double>("value", _input->Get() ? 1 : 0);

  return values;
}

std::string DigitalLogger::GetName() {
  return this->name;
}

std::vector<std::pair<std::string, double>> VariableLogger::OnLogTick() {
  std::cout << "VariableLogger::OnLogTick() called" << std::endl;
  return std::vector<std::pair<std::string, double>>();
}

std::string VariableLogger::GetName() {
  return this->name;
}

DoubleLogger::DoubleLogger(std::string name, std::string path, double* variable)
    : name(name), path(path), variable(variable) {}

std::vector<std::pair<std::string, double>> DoubleLogger::OnLogTick() {
  double value = *variable;

  std::vector<std::pair<std::string, double>> values;

  values[0] = std::pair<std::string, double>("value", value);

  return values;
}

std::string DoubleLogger::GetName() {
  return this->name;
}

IntLogger::IntLogger(std::string name, std::string path, int* variable)
    : name(name), path(path), variable(variable) {}

std::vector<std::pair<std::string, double>> IntLogger::OnLogTick() {
  int value = *variable;

  std::vector<std::pair<std::string, double>> values;

  values[0] =
      std::pair<std::string, double>("value", static_cast<double>(value));

  return values;
}

std::string IntLogger::GetName() {
  return this->name;
}

BoolLogger::BoolLogger(std::string name, std::string path, bool* variable)
    : name(name), path(path), variable(variable) {}

std::vector<std::pair<std::string, double>> BoolLogger::OnLogTick() {
  bool value = *variable;

  std::vector<std::pair<std::string, double>> values;

  values[0] = std::pair<std::string, double>("value", value ? 1 : 0);

  return values;
}

std::string BoolLogger::GetName() {
  return this->name;
}

EncoderLogger::EncoderLogger(std::string name, std::string path,
                             frc::Encoder* encoder)
    : name(name), path(path), encoder(encoder) {}

std::vector<std::pair<std::string, double>> EncoderLogger::OnLogTick() {
  std::vector<std::pair<std::string, double>> values;

  values[0] =
      std::pair<std::string, double>("distance", encoder->GetDistance());
  values[1] = std::pair<std::string, double>("rate", encoder->GetRate());
  values[2] = std::pair<std::string, double>("raw", encoder->GetRaw());
  values[3] =
      std::pair<std::string, double>("direction", encoder->GetDirection());
  values[4] = std::pair<std::string, double>("stopped", encoder->GetStopped());

  return values;
}

std::string EncoderLogger::GetName() {
  return this->name;
}

JoystickLogger::JoystickLogger(std::string name, std::string path,
                               frc::Joystick* joystick)
    : name(name), path(path), joystick(joystick) {}

std::vector<std::pair<std::string, double>> JoystickLogger::OnLogTick() {
  std::vector<std::pair<std::string, double>> values;

  values[0] = std::pair<std::string, double>("x", joystick->GetX());
  values[1] = std::pair<std::string, double>("y", joystick->GetY());
  values[2] = std::pair<std::string, double>("z", joystick->GetZ());

  values[3] = std::pair<std::string, double>("twist", joystick->GetTwist());
  values[4] =
      std::pair<std::string, double>("throttle", joystick->GetThrottle());

  values[5] = std::pair<std::string, double>("trigger", joystick->GetTrigger());

  values[6] = std::pair<std::string, double>("top", joystick->GetTop());

  values[7] =
      std::pair<std::string, double>("button1", joystick->GetRawButton(1));
  values[8] =
      std::pair<std::string, double>("button2", joystick->GetRawButton(2));
  values[9] =
      std::pair<std::string, double>("button3", joystick->GetRawButton(3));
  values[10] =
      std::pair<std::string, double>("button4", joystick->GetRawButton(4));
  values[11] =
      std::pair<std::string, double>("button5", joystick->GetRawButton(5));
  values[12] =
      std::pair<std::string, double>("button6", joystick->GetRawButton(6));
  values[13] =
      std::pair<std::string, double>("button7", joystick->GetRawButton(7));
  values[14] =
      std::pair<std::string, double>("button8", joystick->GetRawButton(8));
  values[15] =
      std::pair<std::string, double>("button9", joystick->GetRawButton(9));
  values[16] =
      std::pair<std::string, double>("button10", joystick->GetRawButton(10));
  values[17] =
      std::pair<std::string, double>("button11", joystick->GetRawButton(11));
  values[18] =
      std::pair<std::string, double>("button12", joystick->GetRawButton(12));

  return values;
}

std::string JoystickLogger::GetName() {
  return this->name;
}

XboxControllerLogger::XboxControllerLogger(std::string name, std::string path,
                                           frc::XboxController* controller)
    : name(name), path(path), controller(controller) {}

std::vector<std::pair<std::string, double>> XboxControllerLogger::OnLogTick() {
  std::vector<std::pair<std::string, double>> values;

  values[0] = std::pair<std::string, double>("leftX", controller->GetLeftX());
  values[1] = std::pair<std::string, double>("leftY", controller->GetLeftY());

  values[2] = std::pair<std::string, double>("rightX", controller->GetRightX());
  values[3] = std::pair<std::string, double>("rightY", controller->GetRightY());

  values[4] = std::pair<std::string, double>("leftTrigger",
                                             controller->GetLeftTriggerAxis());
  values[5] = std::pair<std::string, double>("rightTrigger",
                                             controller->GetRightTriggerAxis());

  values[6] = std::pair<std::string, double>("a", controller->GetAButton());
  values[7] = std::pair<std::string, double>("b", controller->GetBButton());
  values[8] = std::pair<std::string, double>("x", controller->GetXButton());
  values[9] = std::pair<std::string, double>("y", controller->GetYButton());

  values[10] =
      std::pair<std::string, double>("back", controller->GetBackButton());
  values[11] =
      std::pair<std::string, double>("start", controller->GetStartButton());

  values[12] =
      std::pair<std::string, double>("leftBumper", controller->GetLeftBumper());
  values[13] = std::pair<std::string, double>("rightBumper",
                                              controller->GetRightBumper());

  values[14] = std::pair<std::string, double>("leftStickButton",
                                              controller->GetLeftStickButton());
  values[15] = std::pair<std::string, double>(
      "rightStickButton", controller->GetRightStickButton());

  return values;
}

std::string XboxControllerLogger::GetName() {
  return this->name;
}

LimelightLogger::LimelightLogger(std::string name, std::string path,
                                 std::shared_ptr<nt::NetworkTable> table)
    : name(name), path(path), table(table) {}

std::pair<std::vector<std::pair<std::string, double>>,
          std::vector<std::pair<std::string, std::vector<double>>>>
LimelightLogger::OnLogTick() {
  std::pair<std::vector<std::pair<std::string, double>>,
            std::vector<std::pair<std::string, std::vector<double>>>>
      values;

  values.first[0] = std::pair<std::string, double>(
      "tv", table->GetEntry("tv").GetDouble(0.0));
  values.first[1] = std::pair<std::string, double>(
      "tx", table->GetEntry("tx").GetDouble(0.0));
  values.first[2] = std::pair<std::string, double>(
      "ty", table->GetEntry("ty").GetDouble(0.0));
  values.first[3] = std::pair<std::string, double>(
      "ta", table->GetEntry("ta").GetDouble(0.0));
  values.first[4] = std::pair<std::string, double>(
      "tl", table->GetEntry("tl").GetDouble(0.0));
  values.first[5] = std::pair<std::string, double>(
      "cl", table->GetEntry("cl").GetDouble(0.0));
  values.first[6] = std::pair<std::string, double>(
      "tshort", table->GetEntry("tshort").GetDouble(0.0));
  values.first[7] = std::pair<std::string, double>(
      "tlong", table->GetEntry("tlong").GetDouble(0.0));
  values.first[8] = std::pair<std::string, double>(
      "thor", table->GetEntry("thor").GetDouble(0.0));
  values.first[9] = std::pair<std::string, double>(
      "tvert", table->GetEntry("tvert").GetDouble(0.0));
  values.first[10] = std::pair<std::string, double>(
      "getpipe", table->GetEntry("getpipe").GetDouble(0.0));
  values.first[11] = std::pair<std::string, double>(
      "json", table->GetEntry("json").GetDouble(0.0));
  values.first[12] = std::pair<std::string, double>(
      "tclass", table->GetEntry("tclass").GetDouble(0.0));
  values.first[13] = std::pair<std::string, double>(
      "tc", table->GetEntry("tc").GetDouble(0.0));

  values.second[14] = std::pair<std::string, std::vector<double>>(
      "botpose", table->GetNumberArray("botpose", std::vector<double>(6)));
  values.second[15] = std::pair<std::string, std::vector<double>>(
      "botpose_wpiblue",
      table->GetNumberArray("botpose_wpiblue", std::vector<double>(6)));
  values.second[16] = std::pair<std::string, std::vector<double>>(
      "botpose_wpired",
      table->GetNumberArray("botpose_wpired", std::vector<double>(6)));
  values.second[17] = std::pair<std::string, std::vector<double>>(
      "camerapose_targetspace",
      table->GetNumberArray("camerapose_targetspace", std::vector<double>(6)));
  values.second[18] = std::pair<std::string, std::vector<double>>(
      "targetpose_cameraspace",
      table->GetNumberArray("targetpose_cameraspace", std::vector<double>(6)));
  values.second[19] = std::pair<std::string, std::vector<double>>(
      "targetpose_robotspace",
      table->GetNumberArray("targetpose_robotspace", std::vector<double>(6)));
  values.second[20] = std::pair<std::string, std::vector<double>>(
      "botpose_targetspace",
      table->GetNumberArray("botpose_targetspace", std::vector<double>(6)));
  values.second[21] = std::pair<std::string, std::vector<double>>(
      "camerapose_robotspace",
      table->GetNumberArray("camerapose_robotspace", std::vector<double>(6)));
  values.second[22] = std::pair<std::string, std::vector<double>>(
      "tid", table->GetNumberArray("tid", std::vector<double>(6)));

  return values;
}
std::string LimelightLogger::GetName() {
  return this->name;
}
