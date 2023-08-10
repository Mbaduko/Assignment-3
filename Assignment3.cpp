#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include<vector>
using namespace std;

string Words[8] = {"paris", "london", "madrid", "amsterdam", "lisbon", "brussel", "berlin", "budapest"};
string Random_word ;
int guesses = 6;
int warnings = 3;
string current_word;
char entered_char;

// Function prototypes
void Randoming_word();
void initialising();
void printings();
bool is_letter(char b);
bool is_vowel(char b);
bool is_used(char c);
void case_sensitive(char enter);
bool find(char f);
int counting_unique_characters_in_random_word(string a);
bool lost();
bool wins();

int main()
{
    srand(time(0)); // Seed the random number generator

    Randoming_word();
    initialising();
    printings();

    for (int i = 0;; i++)
    {
        char enter;
        cout << "\nEnter your character:";
        cin >> enter;
        if (is_letter(enter))
        {
            if (!is_used(enter))
            {
                case_sensitive(enter);
                if (find(entered_char))
                {
                    printings();
                }
                else
                {
                    if (is_vowel(entered_char))
                    {
                        guesses -= 2;
                    }
                    else
                    {
                        guesses -= 1;
                    }
                }
            }
            else
            {
                if (warnings == 0)
                {
                    guesses -= 1;
                }
                else
                {
                    warnings -= 1;
                }
            }
        }
        else 
        {
            if (warnings != 0)
            {
                warnings-=1;
                cout<<"\n!!!!!!You entered a non_letter symbol";
            }
            else
            {
                guesses-=1;
                cout<<"\n!!!!!!You entered a non_letter symbol";
            }
            
            
        }
        

        if (wins())
        {
            cout << "\n\n\t***Congratulations you won!";
            cout << "\n\t\t***You got:" << guesses*counting_unique_characters_in_random_word(Random_word);
            cout << "/"<<6*counting_unique_characters_in_random_word(Random_word);
            break;
        }
        else if (lost())
        {
            cout << "\n\n\t***Oops you lost, guesses are over;";
            break;
        }
        cout<<"\n\t\tRemaining guesses are:"<<guesses;
        cout<<"\n\t\tRemainig warnings are:"<<warnings;
    }

    return 0;
}

void Randoming_word()
{
    Random_word = Words[rand() % 8];
}

void initialising()
{
    int word_size = Random_word.size();
    current_word = string(word_size, '-'); // Initialize current_word with underscores
}

void printings()
{
    cout << "\n\tCurrently you filled:" << current_word << endl;
}

bool is_letter(char b)
{
    char letters[52] = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd',
                        'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm'};
    for (int i = 0; i < 52; i++)
    {
        if (b == letters[i] || b == toupper(letters[i]))
        {
            return true;
        }
    }
    return false;
}

bool is_vowel(char b)
{
    string vowels = "aeiou";
    return vowels.find(tolower(b)) != string::npos;
}

bool is_used(char c)
{
    for (int i = 0; i < current_word.size(); i++)
    {
        if (c == current_word.at(i))
        {
            return true;
        }
    }
    return false;
}

void case_sensitive(char enter)
{
    entered_char=tolower(enter);
}

bool find(char f)
{
    bool check = false;
    for (int i = 0; i < Random_word.size(); i++)
    {
        if (Random_word.at(i) == f)
        {
            check = true;
            current_word[i] = f;
        }
    }
    return check;
}

bool lost()
{
    return (guesses == 0) ? true : false;
}

bool wins()
{
    return (guesses != 0 && current_word == Random_word);
}

int counting_unique_characters_in_random_word(string a)
{
    vector<char> count={'.'};
    for (char c:a)
    {
        for (int i = 0; i < count.size(); i++)
        {
            if (c!=count[i])
            {
                count.push_back(c);
                break;
            }
            
        }
        
    }
    return (count.size()-1); 
}