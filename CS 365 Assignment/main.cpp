#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

// A function to read the ciphertext from a file
string read_ciphertext(string filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Error: cannot open file " << filename << endl;
        exit(1);
    }
    string ciphertext((istreambuf_iterator<char>(fin)), (istreambuf_iterator<char>()));
    fin.close();
    return ciphertext;
}
// A function that displays the encrypted text 
string encryptedText(string filename){
  ifstream file(filename); //taking file as inputstream
   string str;
   if(file) {
      ostringstream x;
      x << file.rdbuf(); // reading data
      str = x.str();
   }

  return str;
}

// ... (the rest of the code remains the same)
// A function to calculate and display the frequency of letters in the ciphertext
map<char, int> get_frequency(string ciphertext) {
    map<char, int> freq;
    for (char c : ciphertext) {
        if (isalpha(c)) {
            c = toupper(c);
            freq[c]++;
        }
    }
    cout << "\n\nFrequency of letters in the ciphertext:\n" << endl;
    for (auto p : freq) {
        cout << p.first << ": " << p.second << endl;
    }
    return freq;
}

// A function to sort the letters by frequency in descending order
vector<char> sort_by_frequency(map<char, int> freq) {
    vector<pair<int, char> > pairs;
    for (auto p : freq) {
        pairs.push_back({p.second, p.first});
    }
    sort(pairs.rbegin(), pairs.rend());
    vector<char> sorted_letters;
    for (auto p : pairs) {
        sorted_letters.push_back(p.second);
    }
    return sorted_letters;
}

// A function to make a guess and update the mapping
void make_guess(map<char, char>& mapping) {
    char letter, replacement;
    cout << "\nEnter your guess in the format 'letter = replacement': ";
    cin >> letter >> replacement >> replacement;
    letter = toupper(letter);
    replacement = toupper(replacement);
    if (isalpha(letter) && isalpha(replacement)) {
        mapping[letter] = replacement;
        cout << "\n Updated mapping: " << letter << " -> " << replacement << endl<<endl;

    }
    else {
        cout << "Invalid input. Try again." << endl;
    }
}

// A function to decrypt the ciphertext using the mapping
string decrypt(string ciphertext, map<char, char> mapping) {
    string plaintext = ciphertext;
    for (int i = 0; i < plaintext.length(); i++) {
        char c = plaintext[i];
        if (isalpha(c)) {
            c = toupper(c);
            if (mapping.count(c)) {
                plaintext[i] = mapping[c];
            }
            else {
                plaintext[i] = '*';
            }
        }
    }
    return plaintext;
}

// A function to display the decrypted plaintext
void display_plaintext(string plaintext) {
    cout << "\nDecrypted plaintext:\n" << endl;
    cout << plaintext << endl;
}

int main() {
  string filename;
  cout << "Welcome to the Decryptor!!\n"<<endl;
  cout<< "Which please input file"<<endl;
  cin >> filename;
  if(filename == "ciphertext.txt"||filename == "ciphertext2.txt"){

    // Read the ciphertext from a file
    string ciphertext = read_ciphertext(filename);

    // Calculate and display the frequency of letters in the ciphertext
    map<char, int> freq = get_frequency(ciphertext);

    // Sort the letters by frequency in descending order
    vector<char> sorted_letters = sort_by_frequency(freq);

    // Initialize the mapping with some initial guesses
    map<char, char> mapping;

     // Map 'E' with the most frequent letter in the ciphertext
     mapping[sorted_letters[0]] = 'E';

     // Map 'T' with the second most frequent letter in the ciphertext
     mapping[sorted_letters[1]] = 'T';

     // Map 'A' with the third most frequent letter in the ciphertext
     mapping[sorted_letters[2]] = 'A';

     // Decrypt the ciphertext using the initial mapping
     string plaintext = decrypt(ciphertext, mapping);
     
     // Displays encrypted text
    cout<< encryptedText(filename)<<endl;
  
     // Display the decrypted plaintext
     display_plaintext(plaintext);
  
     // Make guesses and update the mapping interactively
  while (true) {
         make_guess(mapping);
         plaintext = decrypt(ciphertext, mapping);
    // displays encrypted text while the user is guessing 
         cout<< encryptedText(filename)<<endl;
    
         display_plaintext(plaintext);
    

  }}
  else{
    cout<<"File not found, try again"<<endl;
    cin >> filename;
  }

     return 0;
}