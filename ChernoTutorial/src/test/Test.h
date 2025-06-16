#pragma once

#include <functional>
#include <string>
#include <vector>

#include <iostream>

namespace Test {

class Test {
public:
  Test() {}
  virtual ~Test() {}

  virtual void OnUpdate(float deltaTime) {}
  virtual void OnRender() {}
  virtual void OnImGuiRender() {}

private:
};

class TestMenu : public Test {
public:
  TestMenu(Test*& currentTestPtr);
  ~TestMenu() {}

  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;

  template<typename T, typename... Args>
  void RegisterTest(const std::string& name, Args&&... args) {
  std::cout << "Registering test " << name << std::endl;
  m_Tests.push_back(std::make_pair(name, [=](){ return new T(std::forward<Args>(args)...); }));
}

private:
  /**
   * @brief Vector to tests. We do not use a Test* at pair->second because we want to 
   * create and delete Tests dynamically; we don't want to hold the instance.
   * So, we use as second parameter a function that returns a Test*
   */
  std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;;

  /** Reference to a Test pointer (instead of using Test** to modify that pointer) */
  Test*& m_CurrentTest;
};

} // namespace Test