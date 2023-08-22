#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include<vector>
using namespace std;

string Words[10] = { "Hello",
        "world",
        "apple",
        "banana",
        "cat",
        "dog",
        "sun",
        "moon",
        "happy",
        "smile"};
string Random_word ;
int guesses = 6;
int warnings = 3;
string current_word;
char entered_char;

// Function prototypes
void Randoming_word();
void initialising();
void introduction();
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
    introduction();

    for (int i =0;; i++)
    {
        cout<<"\n==================================================================\n";
        char enter;
        cout << "\nEnter a letter you guess is in the secret word:";
        cin >> enter;
        if (is_letter(enter))
        {
            case_sensitive(enter);
            if (!is_used(enter))
            {
                if (find(entered_char))
                {
                    printings();
                }
                else
                {
                    if (is_vowel(entered_char))
                    {
                      cout<<"\n!!!this is a vowel and not in secret word, so you're lossing two guesses";
                        guesses -= 2;
                    }
                    else
                    {
                      cout<<"!!!This letter is not in secret word , so you're lossing a guess";
                        guesses -= 1;
                    }
                }
            }
            else
            {
                if (is_vowel(entered_char))
                {
                  cout<<"\n!!!this is a vowel and has been guessed, so you're lossing two guesses";
                    guesses -= 2;
                }
                else
                {
                    if (warnings == 0)
                    {
                       cout<<"!!!This letter has been guessed , so you're lossing a guess";
                        guesses -= 1;
                    }
                    else
                    {
                      cout<<"!!!This letter has been guessed , so you're lossing a warning";
                        warnings -= 1;
                    }
                }
            }
        }
        else 
        {
            if (warnings != 0)
            {
                warnings-=1;
                cout<<"\n!!!!!!You entered a non_letter symbol, you're lossing warning";
            }
            else
            {
                guesses-=1;
                cout<<"\n!!!!!!You entered a non_letter symbol, you're lossing a guess";
            }
            
            
        }

        if(guesses<0)
           guesses=0;
        

        if (wins())
        {
            cout << "\n\n\t***Congratulations you won!";
            cout << "\n\t\t***You got:" << guesses*counting_unique_characters_in_random_word(Random_word);
            cout << "/"<<6*counting_unique_characters_in_random_word(Random_word);
            break;
        }
        else if (lost())
        {
            cout << "\n\n\t***Oops you lost, guesses are over";
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

void introduction()
{
    cout<<"\n\t\t\t\t\t**************\n";
    cout<<"\t\t\t\t\t*HANGMAN GAME*\n";
    cout<<"\t\t\t\t\t**************\n";
    cout<<"\n\tThe Secret word has the same length as:\t"<<current_word;
    cout<<"\n\n\tTry to guess the word character by character\n";
    cout<<"\n\t\t\tINSTRUCTIONS";
    cout<<"\n\t\t\t************";
    cout<<"\n\t1.You have 6 guesses and 3 warnings, \n\tincase guesses finished before you guessed a secret word it will be your loss";
    cout<<"\n\n\t2.If you  inputs a vowel (a,e,i,o,u), not in secret word or already guessed you would lose 2 guesses.";
    cout<<"\n\n\t3.If you input a consonant not in secret word or already guessed you should lose wrning if any, or a guess";
    cout<<"\n\n\t4.Non letter symbols are not allowed if entered you would lose warning if any or a guess\n";
    cout<<"\n\t\t\t\tGood luck!  Let start our game\n";
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
