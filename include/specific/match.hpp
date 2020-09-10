#pragma once

#include "main.h"

enum class Color { Red, Blue };

class Routine {
  public:
  struct Info {
    Color color;
    std::string name;
    std::string description;
    std::string setup;
  };
  Routine(const std::function<void()> &iRoutine, const Info &iInfo);
  void execute();
  Info getInfo() const;

  private:
  std::function<void()> routine;
  const Info info;
};

class Match {
  public:
  Match(const std::array<Routine, 12> &iRoutines);
  void update();
  Routine getRoutine() const;
  Color getColor() const;
  void setRoutine(int iIndex);
  void setColor(const Color &iColor);

  private:
  pros::ADIPotentiometer routineSelector{5};
  pros::ADIPotentiometer colorSelector{6};
  std::array<Routine, 12> routines;
  int index{0};
  Color color;
};
