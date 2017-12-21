#include <iostream>
#include <map>
#include <set>
#include <fstream>

using namespace std;

int main(int argc, const char * argv[]) {
    string word, line;
    ifstream stop_words_file, input_file;
    set<string> stop_words;
    map<string, int> frequency;
    multimap<int, string> descending;
    map<string, int>::iterator iter;
    multimap<int, string>::reverse_iterator rev_it;
    stop_words_file.open("stopwords.txt");
    while(stop_words_file >> line)
        stop_words.insert(line);
    stop_words_file.close();
    input_file.open("input.txt");
    while (input_file >> word){
        string fixed_word;
        for(int i = 0; i<word.length(); i++)
            if(isalpha(word[i]))
                fixed_word += tolower(word[i]);
        if(fixed_word.length() && stop_words.find(fixed_word)!=stop_words.end())
            frequency[fixed_word]++;
    }
    input_file.close();
    for(iter = frequency.begin(); iter!=frequency.end(); iter++)
        descending.insert(pair<int, string>(iter->second, iter->first));
    for(rev_it = descending.rbegin(); rev_it != descending.rend(); rev_it++)
        cout << (*rev_it).second << " " << (*rev_it).first << " " << (double)(*rev_it).first/stop_words.size()*100.0 << "%" << endl;
    return 0;
}
