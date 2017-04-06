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
      explicit Component(Color const &, std::string const &, double, double, double, double);
      virtual ~Component();
      virtual double getX() const;
      virtual double getY() const;
      virtual double getWidth() const;
      virtual double getHeight() const;
      virtual bool hasSprite() const;
      virtual size_t getBackgroundId() const;
      virtual Color getBackgroundColor() const;
      virtual Color getTextColor() const;
      virtual std::string const &getText() const;
      virtual void setClicked();
    private:
      Color m_color;
      std::string m_text;
      double m_x;
      double m_y;
      double m_width;
      double m_height;
  };
}
#endif
