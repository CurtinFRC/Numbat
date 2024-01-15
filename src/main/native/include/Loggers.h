// Copyright (c) 2023-2024 CurtinFRC
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#pragma once

#include <networktables/NetworkTable.h>
#include <frc/DigitalInput.h>
#include <frc/Encoder.h>
#include <frc/Joystick.h>
#include <frc/XboxController.h>
#include <networktables/NetworkTableValue.h>

#include <memory>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include <iostream>

namespace loggers {
using NT_Table = std::shared_ptr<std::pair<nt::NetworkTable, nt::Value>>;

class Logger {
 public:
  virtual void OnLogTick() = 0;
  virtual std::string GetName() = 0;

 private:
};

class NTLogger : public Logger {
 public:
  NTLogger(std::string name, std::string path, std::vector<NT_Table> tables);

  ~NTLogger();

  void OnLogTick();

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
  
    void OnLogTick();
  
    std::string GetName();
  
  private:
    std::string name;
    std::string path;
    int channel;

    frc::DigitalInput *_input;
};

class VariableLogger : public Logger {
  public:  
    void OnLogTick();
  
    std::string GetName();
  
  private:
    std::string name;
    std::string path;

    void *variable;
};

class DoubleLogger : public VariableLogger {
  public:
    DoubleLogger(std::string name, std::string path, double *variable);

    void OnLogTick() override;

    std::string GetName() override;
  
  private:
    std::string name;
    std::string path;
    double *variable;
};

class IntLogger : public VariableLogger {
  public:
    IntLogger(std::string name, std::string path, int *variable);
  
    void OnLogTick() override;
  
    std::string GetName() override;
  
  private:
    std::string name;
    std::string path;
    int *variable;
};

class BoolLogger : public VariableLogger {
  public:
    BoolLogger(std::string name, std::string path, bool *variable);
  
    void OnLogTick() override;
  
    std::string GetName() override;
  
  private:
    std::string name;
    std::string path;
    bool *variable;
};

class StringLogger : public VariableLogger {
  public:
    StringLogger(std::string name, std::string path, std::string *variable);
  
    void OnLogTick() override;
  
    std::string GetName() override;
  
  private:
    std::string name;
    std::string path;
    std::string *variable;
};

class EncoderLogger : public Logger {
  public:
    EncoderLogger(std::string name, std::string path, frc::Encoder *encoder);
  
    void OnLogTick();
  
    std::string GetName();
  
  private:
    std::string name;
    std::string path;
    frc::Encoder *encoder;
};

class JoystickLogger : public Logger {
  public:
    JoystickLogger(std::string name, std::string path, frc::Joystick *joystick);
  
    void OnLogTick();
  
    std::string GetName();
  
  private:
    std::string name;
    std::string path;
    frc::Joystick *joystick;
};

class XboxControllerLogger : public Logger {
  public:
    XboxControllerLogger(std::string name, std::string path, frc::XboxController *controller);
  
    void OnLogTick();
  
    std::string GetName();
  
  private:
    std::string name;
    std::string path;
    frc::XboxController *controller;
};

class LimelightLogger : public Logger {
  public:
    LimelightLogger(std::string name, std::string path, NT_Table table);
    LimelightLogger(std::string name, std::string path, NT_Table table, std::string key);

    void OnLogTick();

    std::string GetName();

  private:
    std::string name;
    std::string path;
    NT_Table table;
    std::string key;
};
}  // namespace loggers

