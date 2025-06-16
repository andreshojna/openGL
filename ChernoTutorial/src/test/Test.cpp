#include "Test.h"

#include <iostream>

#include "imgui/imgui.h"

namespace Test {

TestMenu::TestMenu(Test*& currentTestPtr)
    : m_CurrentTest{currentTestPtr} {}

void TestMenu::OnUpdate(float deltaTime) {}

void TestMenu::OnRender() {}

void TestMenu::OnImGuiRender() {
  for (auto& test: m_Tests) {
    if (ImGui::Button(test.first.c_str())) 
    m_CurrentTest = test.second();
  }
}

} // namespace Test