#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

# include <string>
# include "Color.hpp"
# include "IComponent.hpp"

namespace arcade
{
  class Component: public IComponent
  {
    public:
      Component();
      virtual ~Component();
      virtual double getX() const;
      virtual double getY() const;
      virtual double getWidth() const;
      virtual double getHeight() const;
      virtual size_t getBackgroundId() const;
      virtual Color getBackgroundColor() const;
      virtual std::string const &getText() const;
      virtual void setClicked();
    private:
      Color a;
      std::string b;
  };
}
#endif
