#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;


/*This function reads the file that contains the cipher text 
puts the file into a string and returns a string*/
string read_ciphertext(string filename) {

  //variable that takes in the file 
    ifstream fin(filename); 
  
//statement that checks if it exist, if not it will return a message 
    if (!fin) {
        cout << "Error: cannot open file " << filename << endl;
        exit(1);
    }
  
/* The string variable ciphertext takes in two parameters,
one that reads the file all the way to the end and the other 
that returns it to the variable*/
    string ciphertext((istreambuf_iterator<char>(fin)), (istreambuf_iterator<char>()));
  
  //closes file
    fin.close();
    return ciphertext;
}
// A function that displays the encrypted text 
string encryptedText(string filename){
  ifstream file(filename); //taking file as inputstream
   string str;
   if(file) {

     //reading file and storing it in string variable
      ostringstream x;

     //reading file and storing it in string variable
      x << file.rdbuf(); 

     //storing the string in str
      str = x.str();
   }

  return str;
}

/* A funtion takes a string (has the ciphertext) then collects, 
calculates and displays the frequency of each letter in the 
cipher text using the map data structure */
map<char, int> get_frequency(string ciphertext) {

  //map takes in a char and int variable
    map<char, int> frequency;
    int count = 0;
  
  /*Advanced for loop that looks through the cipher text and 
  counts the frequency of each letter*/
    for (char c : ciphertext) {
      
      // counts how many characters in the file 
      count++;
        if (isalpha(c)) {
            c = toupper(c);
            frequency[c]++;
        }
    }
    
    cout << "\n\nFrequency of letters in the ciphertext:\n" << endl;

  /*Advanced for loop that displays the frequency of a 
  character and how many it occurs and its percentage*/
    for (auto p : frequency) {
      double percentage = (double)p.second / count * 100;
        cout << p.first << ": " << p.second << " ["<< round(percentage) <<"%]"<<endl;
    }
    return frequency;
}

/* A vector function that takes a map variable containing a character 
and an int to sort the letters by frequency in descending order*/
vector<char> sort_by_frequency(map<char, int> freq) {

  // A vector that contains a pair that takes an int and char
    vector<pair<int, char>> pairs;

  //An advanced for loop that add the pairs at the end of the vector
    for (auto p : freq) {
        pairs.push_back({p.second, p.first});
    }

//sort function arranging the pairs vector from begining to end  
    sort(pairs.rbegin(), pairs.rend());

  //a vector that takes in characters 
    vector<char> sorted_letters;
  
/*An advanced for loop that takes in pairs and puts them into 
  the vector sorted_letters by int*/
    for (auto p : pairs) {
        sorted_letters.push_back(p.second);
    }
    return sorted_letters;
}

/* A void function that allows the user to guess and 
replace a letter in the encrypted text*/
void make_guess(map<char, char>& mapping) {
    char letter, replacement;
    cout << "\nEnter your guess in the format 'letter = replacement': \n";
    cout<< "\nIf you want to exit please enter '! = !' \n ";
    cin >> letter >> replacement >> replacement;
  
  //makes letter & replacement uppercase after user input 
    letter = toupper(letter); 
    replacement = toupper(replacement);

  //if statement that checks if the user input is valid and replaces the letter in the map
    if (isalpha(letter) && isalpha(replacement)) {
        mapping[letter] = replacement;
        cout << "\n Updated mapping: " << letter << " -> " << replacement << endl<<endl;

    }
      else if(letter == '!'){
        cout<<"Exiting program...\n";
        cout<< "GoodBye!\n";
        exit(1);
        
      }
      // if user input is invalid it waill prompt user to try again
    else {
        cout << "Invalid input. Try again." << endl;
    }
}

/*A string function that takes a map variable(that takes in two 
character variable) and a string variable*/
string decrypt(string ciphertext, map<char, char> mapping) {
    string plaintext = ciphertext;
    for (int i = 0; i < plaintext.length(); i++) {
        char c = plaintext[i];

      //if statement that checks if the character is a letter
        if (isalpha(c)) {
            c = toupper(c);

          //if statement that checks if the character is in the map
            if (mapping.count(c)) {

              //plaintext turns into mapping 
                plaintext[i] = mapping[c];
            }
              //if it is not in the map it will replace the character with a '*'
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
  cout<< "Please select an input file:"<<endl;
  cout<< "ciphertext.txt"<<endl;
  cout<< "ciphertext2.txt\n"<<endl;
  
  cin >> filename;
  
  //while loop just in case user inputs a file that doesnt exist
  while(filename != "ciphertext.txt" && filename != "ciphertext2.txt"){
      cout<<"File not found, try again"<<endl;
      cin >> filename;
  }
  if(filename == "ciphertext.txt"||filename == "ciphertext2.txt"){

    //string ciphertext becomes the file that the user input 
    string ciphertext = read_ciphertext(filename);


    /*map variable the takes character(key) and int(value) and 
    passes it into the get_frequency function which takes 
    the string ciphertext */
    map<char, int> frequency = get_frequency(ciphertext);


    /* vector variable that takes in characters and passes it into 
    the sort_by_frequency function which takes in the map frequency*/
    vector<char> sorted_letters = sort_by_frequency(frequency);

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
    cout<<endl<< encryptedText(filename)<<endl;
  
     // Display the decrypted plaintext with "*" in its place 
     display_plaintext(plaintext);
  
     // Make guesses and update the mapping interactively
  while (true) {
         make_guess(mapping);
         plaintext = decrypt(ciphertext, mapping);
    // displays encrypted text while the user is guessing 
         cout<< encryptedText(filename)<<endl;
    
         display_plaintext(plaintext);
    

  }
  }


     return 0;
}