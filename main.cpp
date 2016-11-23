#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <algorithm>

namespace std {
    template<>
    struct less<std::pair<char,size_t>> {
	bool operator()(const std::pair<char,size_t> & pr1, const std::pair<char,size_t> & pr2) {
	    return pr1.second < pr2.second;
	}
    };
}

class solution {
public:
    std::pair<size_t,size_t> lengthOfLongestSubstring(const std::string & s) {
	std::unordered_map<char,size_t> dict;
	size_t begin = 0, curr = begin;
	std::pair<size_t,size_t> idx;
	while (curr < s.size()) {
	    if (dict.find(s[curr]) == dict.end()) {
		dict[s[curr]] = curr;
		curr++;
	    }
	    else
		break;
	}
	idx.first = begin;
	idx.second = curr-1;

	while (curr < s.size()) {
	    size_t toErase = dict[s[curr]];
	    auto it = dict.begin();
	    while (it != dict.end()) {
		if (it->second <= toErase)
		    it = dict.erase(it);
		else
		    it++;
	    }
	    
	    dict[s[curr]] = curr;
	    curr++;
	    while (curr < s.size()) {
		if (dict.find(s[curr]) == dict.end()) {
		    dict[s[curr]] = curr;
		    curr++;
		}
		else
		    break;
	    }
	    auto it_min = std::min_element(dict.begin(), dict.end(), std::less<std::pair<char,size_t>>());
	    auto it_max = std::max_element(dict.begin(), dict.end(), std::less<std::pair<char,size_t>>());
	    if (it_max->second-it_min->second > idx.second-idx.first) {
		idx.first = it_min->second;
		idx.second = it_max->second;
	    }
	}
	
	return idx;
    }
};

int main() {
    std::string s{"abcabcbb"};
    // std::string s{"bbbbb"};
    // std::string s{"pwwkew"};
    
    solution soln;
    auto maxPr = soln.lengthOfLongestSubstring(s);
    std::cout << "The longest substring without repeating characters is:\n"
	      << "(" << maxPr.first << "," << maxPr.second << ")" << std::endl;
    std::cout << s.substr(maxPr.first, maxPr.second-maxPr.first+1) << std::endl;
}
