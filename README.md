# Data-Encryption
Trying to implement the 'Run Lenght Algorithm' to compress data, but it expanded the data instead and turned into an encryption algorithm

## Usage
To run the project get the source and use **visual studio** and compile it as a **c++** project

### Some important functions and structs in the code

* struct Block;
````c++
  struct Block {
	  char ltr;
	  int frequency;
  };
````
A structure that holds a letter read from file and its frequency of consecutive occurance

* readFile
````c++
  vector<char> readFile(string&);
````
Takes a file name of file to encrypt as parameter and returns a vector of all the character in the file

* RLAc
````c++
  vector<Block> RLAc(vector<char>&);
````
RLAc -> Run Length Algorithm compress. 
Takes the vector of characters returned from the read file function and counts the frequency of occurance of a letter that repeates it self consecultivey
and store its value and the letter in the block which is then returned as a vector

* writeFile
````c++
  int writeFile(string&, vector<Block>&);
````
Writes the vector of blocks returned from RLAc function and writes them to a file, which then becomes encrypted.

* RLAu
````c++
  void RLAu(string&);
````
RLAu -> Run Length Algorithm uncompress.
Read the individual data of **Block** type from file and extracts the letter and frequency then uses this information to rewrite the original data in the decrypted file.
Takes the filename of the encrypted file and the new decrypted file will have a '3' appended to its end.

## Issues
- Some of the functions present in the code are depreciated and just left for a short while.
- The program requires commenting out of the unused function at a time. When encrypting comment out the decryption function and vice versa.
