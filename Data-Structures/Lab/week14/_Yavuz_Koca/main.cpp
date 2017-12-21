#include<bits/stdc++.h>
int main(){
    std::set <std::string> wordSet;
    std::map <std::string, int> freq;
    std::multimap<int, std::string, std::greater <int> > multiMap;
    std::string str;
    for(std::ifstream stopWords("stopwords.txt"); !stopWords.eof() && stopWords >> str; wordSet.insert(str));
    for(std::ifstream input("input.txt");!input.eof() && input >> str;){
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        str.erase( std::remove_if(str.begin(), str.end(), &ispunct), str.end());
        if(wordSet.find(str) != wordSet.end() && freq[str]++);
    }
    for(std::map<std::string, int >::const_iterator it = freq.begin(); it != freq.end(); multiMap.insert(make_pair(it->second, it->first)), ++it);
    for(std::multimap<int, std::string >::const_iterator it = multiMap.begin(); it != multiMap.end(); std::cout << it->second << " " << it->first << " %" << ((double) (it->first)/(double)wordSet.size())*100.0 << "\n", ++it);
    return 0;
}
