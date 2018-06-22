#include <string>
#include <iostream>
#include <iomanip>
#include <exception>

#include "../Griday.hpp"

int
main(int argc, char* argv[])
try {
    using namespace std;

    if (argc < 2)
        {
        cerr << "./visit \".grid files\"" << endl;
        return 1;
        }

    bool onlyIn = false;
    //if (argc == 3)
    //   onlyIn = false;

    cout << setw(80) << setfill('=') << "" << setfill(' ') << endl;
    cout << "VISIT MAKER STARTS" << endl;
    cout << setw(80) << setfill('=') << "" << setfill(' ') << endl;
    cout << endl;

    EnergyGrid energyGrid;
    for (int i = 1; i < argc; ++i)
        {
        string filename = argv[i];

        cout << setw(10) << "File:" << setw(40) << filename << endl;
        auto pos = filename.find_last_of(".");

        energyGrid.read(argv[i]);
        energyGrid.writeVisitInput(filename.substr(0, pos), onlyIn);
        }

    return 0;
    }
catch (GridayException& e)
    {
    std::cerr << e.what() << std::endl;
    }
catch (std::exception& e)
    {
    std::cerr << e.what() << std::endl;
    }
