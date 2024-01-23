// Copyright (c) 2023-2024 CurtinFRC
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#pragma once

#include <frc/DigitalInput.h>
#include <frc/Encoder.h>
#include <frc/Joystick.h>
#include <frc/XboxController.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableValue.h>

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <utility>
#include <vector>

namespace loggers {

using NT_Table = std::shared_ptr<std::pair<nt::NetworkTable, nt::Value>>;

class Logger {
 public:
  // make the OnLogTick() return multiple types
  virtual std::vector<std::pair<std::string, double>> OnLogTick() = 0;

  virtual std::string GetName() = 0;

 private:
};

class NTLogger : public Logger {
 public:
  NTLogger(std::string name, std::string path, std::vector<NT_Table> tables);

  ~NTLogger();

  virtual std::vector<std::pair<std::string, double>> OnLogTick();

  std::string GetName();
  std::vector<NT_Table> GetTables();

 private:
  std::string name;
  std::vector<NT_Table> tables;
  std::vector<std::thread*> threads;
};

class JsonLogger : public Logger {};

class WPILogger : public Logger {};

class DigitalLogger : public Logger {
 public:
  DigitalLogger(std::string name, std::string path, int channel);

  std::vector<std::pair<std::string, double>> OnLogTick() override;

  std::string GetName();

 private:
  std::string name;
  std::string path;
  int channel;

  frc::DigitalInput* _input;
};

class VariableLogger : public Logger {
 public:
  std::vector<std::pair<std::string, double>> OnLogTick();

  std::string GetName();

 private:
  std::string name;
  std::string path;

  void* variable;
};

class DoubleLogger : public VariableLogger {
 public:
  DoubleLogger(std::string name, std::string path, double* variable);

  std::vector<std::pair<std::string, double>> OnLogTick();

  std::string GetName() override;

 private:
  std::string name;
  std::string path;
  double* variable;
};

class IntLogger : public VariableLogger {
 public:
  IntLogger(std::string name, std::string path, int* variable);

  std::vector<std::pair<std::string, double>> OnLogTick();

  std::string GetName() override;

 private:
  std::string name;
  std::string path;
  int* variable;
};

class BoolLogger : public VariableLogger {
 public:
  BoolLogger(std::string name, std::string path, bool* variable);

  std::vector<std::pair<std::string, double>> OnLogTick();

  std::string GetName() override;

 private:
  std::string name;
  std::string path;
  bool* variable;
};

class EncoderLogger : public Logger {
 public:
  EncoderLogger(std::string name, std::string path, frc::Encoder* encoder);

  std::vector<std::pair<std::string, double>> OnLogTick();

  std::string GetName();

 private:
  std::string name;
  std::string path;
  frc::Encoder* encoder;
};

class JoystickLogger : public Logger {
 public:
  JoystickLogger(std::string name, std::string path, frc::Joystick* joystick);

  std::vector<std::pair<std::string, double>> OnLogTick();

  std::string GetName();

 private:
  std::string name;
  std::string path;
  frc::Joystick* joystick;
};

class XboxControllerLogger : public Logger {
 public:
  XboxControllerLogger(std::string name, std::string path,
                       frc::XboxController* controller);

  std::vector<std::pair<std::string, double>> OnLogTick();

  std::string GetName();

 private:
  std::string name;
  std::string path;
  frc::XboxController* controller;
};

class LimelightLogger {
 public:
  LimelightLogger(std::string name, std::string path,
                  std::shared_ptr<nt::NetworkTable> table);

  std::pair<std::vector<std::pair<std::string, double>>,
            std::vector<std::pair<std::string, std::vector<double>>>>
  OnLogTick();

  std::string GetName();

 private:
  std::string name;
  std::string path;
  std::shared_ptr<nt::NetworkTable> table;
  std::string key;
};
}  // namespace loggers
