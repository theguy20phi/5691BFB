#include <iostream>

#define TESTING

#define TEST(a) \
    void a() {

#define END_TEST \
        std::cout << "Test " << __FUNCTION__ << " succeeded!" << std::endl; \
    } 
    
#define IS_TRUE(a) \
    if(!a) { \
        std::cout << "Test " << __FUNCTION__ << " failed. See file " << __FILE__ << " line " << __LINE__ << " for context." << std::endl;  \
        return; \
    } 

#define IS_EQUAL(a, b) \
    if(a != b) { \
        std::cout << "Test " << __FUNCTION__ << " failed. See file " << __FILE__ << " line " << __LINE__ << " for context." << std::endl;  \
        return; \
    } 

void runTests();