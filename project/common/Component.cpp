#include "IComponent.hpp"
#include "Component.hpp"
#include "Color.hpp"

namespace arcade
{
  Component::Component()
  {
    a = Color();
    b = "lmao";
  }

  Component::~Component()
  {
  }

  double Component::getX() const
  {
    return (0);
  }

  double Component::getY() const
  {
    return (0);
  }

  double Component::getWidth() const
  {
    return (0);
  }

  double Component::getHeight() const
  {
    return (0);
  }

  size_t Component::getBackgroundId() const
  {
    return (0);
  }

  Color Component::getBackgroundColor() const
  {
    return (a);
  }

  std::string const &Component::getText() const
  {
    return (b);
  }

  void Component::setClicked()
  {
  }
}
