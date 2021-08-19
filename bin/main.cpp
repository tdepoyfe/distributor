//
// main.cpp
//

#include <iostream>
#include "distributor.hpp"

int main(int argc, char* argv[])
{
    try
    {
        // Check command line arguments.
        if (argc != 5)
        {
            std::cerr << "Usage: distributor <up_address> <up_port> "
                         "<self_address> <self_port>\n";
            return 1;
        }
        
        // Initialize the service.
        distributor::distributor d(argv[1], argv[2], argv[3], argv[4]);

        // Run the service until stopped.
        d.run();
    }
    catch (std::exception* e)
    {
        std::cerr << "exception: " << e->what() << "\n";

        return 2;
    }

    return 0;
}
