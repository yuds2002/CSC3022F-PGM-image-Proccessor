#ifndef ConnectedComponent_h
#define ConnectedComponent_h
#include <vector>
#include <utility>
namespace srkyud001{

    class ConnectedComponent
    {
    private:
        
    public:
        int num_pixels;
        int comp=-1;
        std::vector< std::pair<int,int> > coord;
        ConnectedComponent(){
            ++comp;
        }
        ~ConnectedComponent(){
            //std::cout<<comp<<std::endl;
            //std::cout<<"cc destructor"<<std::endl;
        }
    };
    

    
}

#endif