#include "IComponent.hpp"
#include "Component.hpp"
#include "Color.hpp"

namespace arcade
{
  Component::Component(Color const &color, std::string const &text,
      double posX, double posY, double width, double height)
    :m_color(color), m_text(text), m_x(posX), m_y(posY), m_width(width), m_height(height)
  {
  }

  Component::~Component()
  {
  }

  double Component::getX() const
  {
    return (m_x);
  }

  double Component::getY() const
  {
    return (m_y);
  }

  double Component::getWidth() const
  {
    return (m_width);
  }

  double Component::getHeight() const
  {
    return (m_height);
  }

  size_t Component::getBackgroundId() const
  {
    return (0);
  }

  Color Component::getBackgroundColor() const
  {
    return (m_color);
  }

  std::string const &Component::getText() const
  {
    return (m_text);
  }

  void Component::setClicked()
  {
  }
}
