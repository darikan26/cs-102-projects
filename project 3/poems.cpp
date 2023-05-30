/**
 * CS-102 Project 03: Generates non-sensical Japanese poetry.
 * @file poems.cpp
 * @author(s) Derya Arikan
 * @date Monday, February 12th
 */

/* ------- Do not change anything in this section (below) ------- */

#include <iostream>
#include <string>

using namespace std;

int ROWS = 9;
int COLS = 5;
int SIZE = 4;

string HIRAGANA[9][5] = {{ "a",   "i",   "u",  "e",  "o"},
                         {"ka",  "ki",  "ku", "ke", "ko"},
                         {"sa", "shi",  "su", "se", "so"},
                         {"ta", "chi", "tsu", "te", "to"},
                         {"na",  "ni",  "nu", "ne", "no"},
                         {"ha",  "hi",  "hu", "he", "ho"},
                         {"ma",  "mi",  "mu", "me", "mo"},
                         {"ra",  "ri",  "ru", "re", "ro"},
                         {"ya",  "wa",  "yu",  "n", "yo"}
                        };

const int A = 125;
const int C = 11;
const int MOD = 1024;

const int SYL_IN_WORD_MAX = 5;
const int NUM_LINES_MAX = 15;
const int NUM_SYLS_MAX = 40;

/* ------- Do not change anything in this section (above) ------- */

/// @brief generates new seed from integer input seed, and replaces
///        the old one at its address location.
/// @param seed some integer input
void generate_prnd(int &seed) {
    seed = (A * seed + C) % MOD;
}

/// @brief generates a word of approptiate length by choosing a 
///        'random' row and column.
/// @param w determines the number of syllables the word will have.
/// @param seed some 'random' integer.
/// @return the word string
string generate_word(int w, int &seed) {
    string word;
    for ( int i = 0; i < w; i++ ) {
        int r, c = 0;
        generate_prnd(seed);
        r = seed % 9;
        generate_prnd(seed);
        c = seed % 5;
        word = word + HIRAGANA[r][c];
    }
    return word;
}

/// @brief generates a line of the poem with some number of words, given a 
///        syllable count. 
/// @param syl the number of syllables the line must contain
/// @param seed some 'random' integer
/// @return the line string
string generate_line(int syl, int &seed) {

    string line;
    int syl_left = syl;

    // while we still have syllables left
    while ( syl_left > 0 ) {
        // generate random number for syllable count of word btwn 1-5
        generate_prnd(seed);
        int syl_in_word = seed % SYL_IN_WORD_MAX + 1;

        // recalculate how many syllables we have left
        syl_left = syl_left - syl_in_word;

        if ( syl_left > 0 ) {
            line = line + generate_word(syl_in_word, seed) + ' ';
        } // there are more syllables left. re-enter loop to generate another word.
        if ( syl_left == 0 ) {
            line = line + generate_word(syl_in_word, seed);
            return line;
        } // if 0 syllables, generate the word, do not print space after, return.
        if ( syl_left < 0 ) {
            line = line + generate_word(( syl_left + syl_in_word ) , seed);
            return line;
        } // if - number of syllables, random syl_in_word is too much. generate word using the syllable count remaining.
    }   
}

/// @brief given an array of integers, determines the largest integer in it.
/// @param a array of integers.
/// @param n size of array a.
/// @return the largest integer in array a.
int max_length(string* a, int n) {
    int max = 0;
    for ( int i = 0; i < n; i++ ) {
        if ( a[i].length() > max ) {
            max = a[i].length();
        }
    }
    return max;
}

/// @brief formats the array a according to whether it will be 
///        capitalized or not, and whether it will be printed
///        vertically or horizontally.
/// @param c is 1 if line beginnings will be capitalized, 0 if not.
/// @param v is 1 if vertical print, and 0 if horizontal.
/// @param a the array that will undergo formatting.
/// @param n the size of array a. 
void settings(int c, int v, string* a, int n) {

    // if lapslock is off, first letters of a should be capitalized.
    if ( c == 1 ) {
        for ( int i = 0; i < n; i++ ) {
            a[i][0] = toupper( a[i][0] );
        }
    } // if lapslock is on, the capitalization is already correct.

    // if vertical = true, (denoted by v=1), then necessary spaces will be added.
    if ( v == 1 ) {
        // get the length of longest line in array
        int max = max_length(a, n);
        // add the right number of spaces to every other line
        for ( int i = 0; i < n; i++ ) {
            while ( a[i].length() < max ) {
                a[i] = a[i] + ' ';
            }
        }
    }

}

/// @brief displays the array a either vertically or horizontally.
/// @param v is 0 for horizontal, 1 for vertical display.
/// @param a array of strings that is being printed.
/// @param n length of array a.
void display (int v, string* a, int n) {
    if ( v == 1 ) {
        int max = max_length(a, n);
        for ( int i = 0; i < max; i++ ) {
            for ( int j = n-1; j >= 0; j-- ) {
                cout << a[j][i];
            } 
            cout << '\n';
        } 
    } // vertical print

    if ( v == 0 ) {
        for ( int i = 0; i < n; i++ ) {
            cout << a[i] << '\n';
        }
    } // horizontal print
}

// Controls operation of program
int main() {
    int seed = 0; // input line 1
    cin >> seed;

    int num_lines = 0; // input line 2
    cin >> num_lines;

    int* syllable_per_line = new int[num_lines];
    for( int i = 0; i < num_lines; i++ ) {  
        cin >> syllable_per_line[i];
    } // process input line 2

    string* array_of_lines = new string[num_lines];
    for ( int i = 0; i < num_lines; i++ ) {
        array_of_lines[i] = generate_line(syllable_per_line[i], seed);
    } // generate poem, line by line. 

    int capitalize, vertical = 0; // input line 3
    cin >> capitalize >> vertical;

    settings(capitalize, vertical, array_of_lines, num_lines);
    display(vertical, array_of_lines, num_lines);

    return 0;
}
