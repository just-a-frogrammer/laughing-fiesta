#include <iostream>
#include <fstream>
#include <vector>

//Variables
const int numb_of_forbidden_words = 2;
std::string forbidden_words[ numb_of_forbidden_words ] = {"shit", "fuck"};
std::string not_moderated_text, single_line;
std::ifstream file_to_moderate("txt_to_moderate.txt");
std::vector<int> forbidden_words_starting_points;

//function for detecting bad words
std::vector<int> finding_forbidden(const std::string &txt, const std::string &forbidden_word) {
    std::vector<int> forbidden_words_starting_points;

    for (int strt_letter_index = 0; strt_letter_index <= txt.length() - forbidden_word.length(); strt_letter_index++) {
        std::string text_word = txt.substr(strt_letter_index, forbidden_word.length());
        
        if (text_word == forbidden_word) {
            forbidden_words_starting_points.push_back(strt_letter_index);
        }
    }

    return forbidden_words_starting_points;
}

//function for ##### forbidden words
std::string hash_bad_words(std::vector<int> starting_points, std::string &txt, std::string &forbidden_word){
    std::string moderated_text;
    moderated_text = txt;

    for (int strt_point = 0; strt_point < starting_points.size(); strt_point++){
        for (int hashed_letter = 0; hashed_letter < forbidden_word.size(); hashed_letter++){
            moderated_text[starting_points[strt_point] + hashed_letter] = '#';
        }
    }

    return moderated_text;
}

int main(){

    //using while to iterate thru every line of file
    while (std::getline(file_to_moderate, single_line)) {
    
    //adding every line to variable and separating with " " to avoid getting forbidden words from two allowed words
    not_moderated_text += " " + single_line;

    }

    //not moderated text
    std::cout << "Not moderated text: \n" << not_moderated_text << "\n";

    //finding and saving forbidden words
    for (int forbidden_word_index = 0; forbidden_word_index < numb_of_forbidden_words; forbidden_word_index++) {
        std::vector<int> positions = finding_forbidden(not_moderated_text, forbidden_words[forbidden_word_index]);
        forbidden_words_starting_points.insert(forbidden_words_starting_points.end(), positions.begin(), positions.end());
    }

    //printing positions of founded words
    std::cout << "\nPositions of bad words:\n";
    for (int position_index = 0; position_index < forbidden_words_starting_points.size(); position_index++){
        std::cout << forbidden_words_starting_points[position_index] << "\n";
    }

    //moderating text
    std::string moderated_text;
    moderated_text = not_moderated_text;
    for (int bad_word_index = 0; bad_word_index < numb_of_forbidden_words; bad_word_index++){
        moderated_text = hash_bad_words(forbidden_words_starting_points, moderated_text, forbidden_words[bad_word_index]);
    }

    //moderated text
    std::cout << "\nModerated text: \n" << moderated_text;

    // Close the file
    file_to_moderate.close();

}