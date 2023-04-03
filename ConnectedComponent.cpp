#include <iostream>
#include "ConnectedComponent.h"
namespace srkyud001
{

    ConnectedComponent::ConnectedComponent() {}
    ConnectedComponent::~ConnectedComponent() {}
    // copy c
    ConnectedComponent::ConnectedComponent(const ConnectedComponent &cc)
    {
        if (cc.comp != this->comp)
        {
            comp = cc.comp;
            num_pixels = cc.num_pixels;
            coord = cc.coord;
        }
    }
    // move c
    ConnectedComponent::ConnectedComponent(ConnectedComponent &&rhs)
    {

        comp = std::move(rhs.comp);
        num_pixels = std::move(rhs.num_pixels);
        coord = coord;
        rhs.coord.clear();
    }
    // copy a
    ConnectedComponent &ConnectedComponent::operator=(const ConnectedComponent &&rhs)
    {
        if (this != &rhs)
        {
            this->comp = rhs.comp;
            this->coord = rhs.coord;
            this->num_pixels = rhs.num_pixels;

            if (this->comp != -1)
            {
                this->comp = -1;
            }
        }

        return *this;
    }
    // move a
    ConnectedComponent &ConnectedComponent::operator=(ConnectedComponent &&rhs)
    {
        if (this != &rhs)
        {
            comp = std::move(rhs.comp);
            num_pixels = std::move(rhs.num_pixels);
            coord = coord;
            rhs.coord.clear();
            rhs.comp = -1;
            rhs.num_pixels = 0;
        }
        return *this;
    }

}