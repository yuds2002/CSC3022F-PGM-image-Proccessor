#ifndef ConnectedComponent_h
#define ConnectedComponent_h
#include <vector>
#include <utility>
namespace srkyud001{

    class ConnectedComponent
    {
    private:
        int num_pixels;
        int comp;
        std::vector< std::pair<int,int> > coord;
    public:
        ConnectedComponent(/* args */);
        ~ConnectedComponent();
    };

    
}

#endif