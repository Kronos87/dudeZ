#ifndef UTIL_H_
#define UTIL_H_

#include <vector>

class Util {
    public:
        static int rndNo(int min, int max);
        static bool rndBool();
    
    template<typename T, typename A>
    static void cleanList( std::vector<T,A> &vec) {
        for (auto it = vec.begin(); it != vec.end(); ++it){
            delete *it;
        }
        
        vec.clear();
    }
};


#endif
