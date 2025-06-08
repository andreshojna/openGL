#pragma once

namespace Test {

class Test {
public:
  Test() {}
  virtual ~Test() {}

private:
  virtual void OnUpdate(float deltaTime) {}
  virtual void OnRender() {}
  virtual void OnImGuiRender() {}
};

} // namespace Test