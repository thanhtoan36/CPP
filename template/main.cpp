#include "function_template.h"

int main()
{
    Circle c1{0.5};
    Circle c2{0.6};
    std::cout << mymax<Circle>(c1,c2) << "\n";
    return 0;
}