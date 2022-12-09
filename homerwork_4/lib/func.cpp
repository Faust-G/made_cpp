
#include "func.h"
#pragma pack(1)
[[gnu::always_inline]]
inline size_t get_max(const std::vector<std::string>& sb){
    size_t res = sb[0].size();
    for(int i = 1;i<sb.size();++i)
        res = std::max(res, sb[i].size());
    return res;
}
[[gnu::always_inline]]
inline std::pair<int, int> get_len_substr(size_t l, size_t len_data, int num_cores, int max_sz){
    int res = len_data, num_bt = 1;
    for(int i = 2; i <= num_cores; ++i){
        if((len_data + i - 1)/i >= max_sz) {
            res = (len_data + i - 1)/i;
            num_bt = i;
        }
    }
    return {res, num_bt};
}

std::vector<int> f(const std::vector<std::string> & inpt){
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
    // bp::system("lib/weather");
    struct shm_remove
    {
        shm_remove() { shared_memory_object::remove("MySharedMemory"); }
        ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
    } remover;

    managed_shared_memory shm(create_only, "MySharedMemory", 5e8);

    CharAllocator     charallocator  (shm.get_segment_manager());
    StringAllocator   stringallocator(shm.get_segment_manager());
    MyShmStringVector *myshmvector =
            shm.construct<MyShmStringVector>("myshmvector")(stringallocator);
    MyShmString mystring(charallocator);
    for(const auto& i : inpt){
        mystring = i;
        myshmvector->push_back(mystring);
    }
    // std::ifstream f("/home/slava/CLionProjects/sport/text.txt");
    // std::string data( (std::istreambuf_iterator<char>(f) ),
    //                   (std::istreambuf_iterator<char>()    ) );
   std::string data = "aa3aababaaa3aababaaa3aababa";
//    std::cerr<<data.size()<<'\n';
    mystring = std::move(data);
    myshmvector->push_back(mystring );
    // bp::system("g++ /home/slava/CLionProjects/sport/func.cpp -o /home/slava/CLionProjects/sport/func");
    const  int num_cores = (int)std::thread::hardware_concurrency();
    const size_t max_sz = get_max(inpt);
    auto [batch_len, num_batches] = get_len_substr(max_sz, mystring.size(), num_cores, max_sz);
//    std::cerr<<batch_len<<' '<< num_batches<<'\n';
    std::vector<bp::ipstream>stream;
    std::vector<bp::child> process;
    std::vector<int>sep;
    int l = 0,  ch = 0;
    while(true){
        stream.emplace_back();
        if(l + batch_len >= mystring.size()){
            process.emplace_back("lib/weather " + std::to_string(l) + " "
            + std::to_string(mystring.size()),
                                 bp::std_out > stream[ch++]);
            process.back().detach();
            break;
        }
        process.emplace_back("lib/weather " + std::to_string(l) + " " +
                                     std::to_string(l + batch_len), bp::std_out > stream[ch++]);
        process.back().detach();
        l+=batch_len;
        sep.emplace_back(l);
    }
    std::vector<int> res(inpt.size(), 0);
    for(auto& i : stream) {
        std::string res_i;
        getline(i, res_i);
//        std::cerr<<res_i<<'\n';
        ch = 0;
        std::string u;
        for(const char& j : res_i){
            if(j == ' '){
                res[ch++] += stoi(u);
                u = "";
            }
            else
                u+=j;
        }
    }
//    for(int i : res)
//        std::cout<<i<<' ';
    for(int i : sep){
        for(int sb = 0; sb<inpt.size();++sb){
            for(int j = i - (int)inpt[sb].size() + 1; j <= i + inpt[sb].size() - 1;++j){
                if(j<0 || j>= mystring.size())
                    continue;
                for(int k =0;k<inpt[sb].size();++k){
                    if(inpt[sb][k] != mystring[j + k])
                        break;
                    if(k == inpt[sb].size() - 1)
                        ++res[sb];
                }
            }
        }
    }
    for(int i : res)
        std::cout<<i<<' ';
    shm.destroy_ptr(myshmvector);
    return res;
}


