#ifndef GUI_HPP_
# define GUI_HPP_

# include <vector>
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
      void addComponent(const Component &c);
      Component & getComponent(size_t pos);
    private:
      std::vector<Component> m_comps;
  };
}

#endif
