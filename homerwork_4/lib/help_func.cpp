#include<bits/stdc++.h>
#include <boost/process.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#pragma pack(1)
int main(int argc, char *argv[])
{
    // std::cout<<"this is help_func";
    namespace bp = boost::process;
    using namespace boost::interprocess;
    typedef allocator<char, managed_shared_memory::segment_manager>
            CharAllocator;
    typedef basic_string<char, std::char_traits<char>, CharAllocator>
            MyShmString;
    typedef allocator<MyShmString, managed_shared_memory::segment_manager>
            StringAllocator;
    typedef vector<MyShmString, StringAllocator>
            MyShmStringVector;
    managed_shared_memory shm(open_only, "MySharedMemory");
    CharAllocator     charallocator  (shm.get_segment_manager());
    StringAllocator   stringallocator(shm.get_segment_manager());

    MyShmStringVector *myshmvector =
            shm.find<MyShmStringVector>("myshmvector").first;
//    for (const auto &elem : *myshmvector) { std::cout << elem.size() << " "; };
    const auto& data = *(myshmvector->end() - 1);
//    std::cout<<argv[1]<<' '<<argv[2]<<"...";
    int l = atoi(argv[1]), r = atoi(argv[2]);
    for(auto it = myshmvector->begin();it != myshmvector->end() - 1; ++it) {
        int res = 0;
        const auto& str_x = *it;
        for (int j = l; j < r - str_x.size() + 1; ++j) {//r+1-?
            for (int k = 0; k < str_x.size(); ++k) {
                if (str_x[k] != data[j + k])
                    break;
                if (k == str_x.size() - 1)
                    ++res;
            }
        }
        std::cout<<res<<' ';
    }
}