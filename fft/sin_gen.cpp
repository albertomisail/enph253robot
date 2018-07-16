#include <math.h>
#include <iostream>

using namespace std;

int main() {
    //ios_base::sync_with_stdio(0), cin.tie(0);
    for(int i = 0;i<256;++i) {
        std::cout << (int) (127*sin(2*3.1415926535*i/1024) + 0.5) << ",";
    }
    std::cout << std::endl;
    return 0;
}
