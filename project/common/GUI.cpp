#include "GUI.hpp"
#include "IComponent.hpp"
#include "Component.hpp"

namespace arcade
{
  GUI::GUI()
  {
  }

  GUI::~GUI()
  {
  }

  std::size_t GUI::size() const
  {
    return (m_comps.size());
  }

  IComponent &GUI::at(std::size_t n)
  {
    return (m_comps[n % m_comps.size()]);
  }

  void GUI::addComponent(const Component &c)
  {
    m_comps.push_back(c);
  }

  Component & GUI::getComponent(size_t pos)
  {
    return (m_comps[pos % m_comps.size()]);
  }
}
