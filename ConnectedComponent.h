#ifndef ConnectedComponent_h
#define ConnectedComponent_h
#include <vector>
#include <utility>
namespace srkyud001
{

    class ConnectedComponent
    {
    private:
    public:
        int num_pixels;
        int comp = -1;
        std::vector<std::pair<int, int>> coord;
        ConnectedComponent();
        ~ConnectedComponent();

        ConnectedComponent(const ConnectedComponent &cc); // copy c
        ConnectedComponent(ConnectedComponent &&rhs);     // move c

        ConnectedComponent &operator=(const ConnectedComponent &&rhs); // copy a
        ConnectedComponent &operator=(ConnectedComponent &&rhs);       // move a
    };

}

#endif