#pragma once
#include<bits/stdc++.h>
#include <boost/process.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/allocators/allocator.hpp>


size_t get_max(const std::vector<std::string>& sb);
std::pair<int, int> get_len_substr(size_t l, size_t len_data, int num_cores, int max_sz);
std::vector<int> f(const std::vector<std::string> & inpt);
