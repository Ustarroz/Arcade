#ifndef GUI_HPP_
# define GUI_HPP_

# include "IGUI.hpp"
# include "IComponent.hpp"
# include "Component.hpp"

namespace arcade
{
  class GUI: public IGUI
  {
    public:
      GUI();
      virtual ~GUI();
      virtual std::size_t size() const;
      virtual IComponent &at(std::size_t);
    private:
      Component a;
  };
}

#endif
