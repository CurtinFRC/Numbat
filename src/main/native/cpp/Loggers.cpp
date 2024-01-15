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

void NTLogger::OnLogTick() {
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
}

DigitalLogger::DigitalLogger(std::string name, std::string path, int channel)
    : name(name), path(path), channel(channel) {
      _input = new frc::DigitalInput(channel);
    }

void DigitalLogger::OnLogTick() {
  auto value = _input->Get();

  std::cout << value << std::endl;
}

std::string DigitalLogger::GetName() {
  return this->name;
}

void VariableLogger::OnLogTick() {
  std::cout << "VariableLogger::OnLogTick() called" << std::endl;
}

std::string VariableLogger::GetName() {
  return this->name;
}

DoubleLogger::DoubleLogger(std::string name, std::string path, double *variable)
    : name(name), path(path), variable(variable) {}

void DoubleLogger::OnLogTick() {
  auto value = *variable;

  std::cout << value << std::endl;
}

std::string DoubleLogger::GetName() {
  return this->name;
}

EncoderLogger::EncoderLogger(std::string name, std::string path, frc::Encoder *encoder)
    : name(name), path(path), encoder(encoder) {}

void EncoderLogger::OnLogTick() {
  auto value = encoder->Get();

  std::cout << value << std::endl;
}

std::string EncoderLogger::GetName() {
  return this->name;
}

JoystickLogger::JoystickLogger(std::string name, std::string path, frc::Joystick *joystick)
    : name(name), path(path), joystick(joystick) {}

void JoystickLogger::OnLogTick() {
  auto value = joystick->GetRawAxis(0);

  std::cout << value << std::endl;
}

std::string JoystickLogger::GetName() {
  return this->name;
}

XboxControllerLogger::XboxControllerLogger(std::string name, std::string path, frc::XboxController *controller)
    : name(name), path(path), controller(controller) {}

void XboxControllerLogger::OnLogTick() {
  auto value = controller->GetRawAxis(0);

  std::cout << value << std::endl;
}

std::string XboxControllerLogger::GetName() {
  return this->name;
}

LimelightLogger::LimelightLogger(std::string name, std::string path, NT_Table table)
    : name(name), path(path), table(table), key("tv") {}

LimelightLogger::LimelightLogger(std::string name, std::string path, NT_Table table, std::string key)
    : name(name), path(path), table(table), key(key) {}

void LimelightLogger::OnLogTick() {
  auto value = table->first.GetEntry(key).GetDouble(0.0);

  std::cout << value << std::endl;
}

