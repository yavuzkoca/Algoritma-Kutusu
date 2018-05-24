#include <fstream>
#include <iostream>
#include <string>
#include <map> 
#include <set>
bool lower( std::string &word ){ for( int i = 0; i < word[i] != '\0'; word[i] = word[i] < 'a' ? word[i] + 'a' - 'A' : word[i], ++i); return true; }
int main(){
	std::string word;
	std::set< std::string > sw;
	std::map< std::string,int > freq;
	std::multimap< int,std::string > rfreq;
	for( std::ifstream stopWords("stopwords.txt"); !stopWords.eof() && stopWords >> word && lower(word); ) sw.insert(word);
	for( std::ifstream input("input.txt"); !input.eof() && input >> word && lower(word); ) if( sw.find(word) != sw.end() ){ ++freq[word]; ++freq[std::string("COUNTER")]; }
	for( std::map< std::string,int >::iterator iter = freq.begin(); iter != freq.end(); ++iter ) rfreq.insert( std::pair< int,std::string >(iter->second,iter->first) );
	for( std::multimap< int,std::string >::reverse_iterator iter = ++rfreq.rbegin(); iter != rfreq.rend(); ++iter )
		std::cout << iter->second << " " << iter->first << " %" << (iter->first + 0.0) * 100 / freq[std::string("COUNTER")] << std::endl;
	return 0;
}