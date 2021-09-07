//Run Length Algorithm

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//structure to be stored in the file
struct Block {
	char ltr;
	int frequency;
};

vector<char> readFile(string&);
int writeFile(string&, vector<Block>&);
float percent(string&);
vector<Block> RLAc(vector<char>&);
void RLAuBAD(string&, vector<Block>&);
void display(vector<Block>&);
void RLAu(string&);

int main()
{
	string filename = "sample.txt.comp"; //"img.jfif"; //"sample.txt"
	vector<char> raw_data;
	vector<Block> compressed_data;

	/*raw_data = readFile(filename);
	compressed_data = RLAc(raw_data);
	writeFile(filename, compressed_data);*/
	//RLAu(filename, compressed_data);

	RLAu(filename);

	//display(compressed_data);

	/*cout << "Compression Percent: " << percent(filename) << "%" << endl;
	cout << "File Compressed Successfuly" << endl;*/

	cout << sizeof(Block) << endl;

	return 0;
}

//compress data
vector<Block> RLAc(vector<char>& raw_data) {
	char current, next;
	current = raw_data[0];
	int frq = 1;

	vector<Block> blocks;
	Block block;

	for (unsigned int i = 1; i < raw_data.size(); i++) {
		next = raw_data[i];
		if (current == next) {
			frq++;
		}
		else {
			block.frequency = frq;
			block.ltr = current;

			blocks.push_back(block);

			frq = 1;
			current = next;
		}

		if (i == raw_data.size() - 1) {
			frq -= 1;
			block.frequency = frq;
			block.ltr = current;

			blocks.push_back(block);
		}
	}

	return blocks;
}

//uncompress data
void RLAu(string& filename) {
	ifstream ogFile(filename, ios::binary);
	ofstream file(filename + "3", ios::binary);
	Block block[1];
	char ltr[1];

	while (!ogFile.eof()) {
		ogFile.read((char*)block, sizeof(block));

		ltr[0] = block[0].ltr;
		for (int i = 0; i < block[0].frequency; i++) {
			file.write(ltr, sizeof(ltr));
		}
	}

	ogFile.close();
	file.close();
}

//not working as expected, it requires the read block of the original file
void RLAuBAD(string& filename, vector<Block>& blocks) {
	ofstream file(filename+"2", ios::binary);
	char ltr[1];

	for (int i = 0; i < blocks.size(); i++) {
		for (int j = 0; j < blocks[i].frequency; j++) {
			ltr[0] = blocks[i].ltr;
			file.write(ltr, sizeof(ltr));
		}
	}

	file.close();
}

//write compressed data to file .comp - compressed file type
int writeFile(string& filename, vector<Block>& data) {
	ofstream file;
	Block block[1];
	file.open(filename+".comp", ios::binary);

	if (!file.is_open()) {
		cerr << "ERROR: Could not create file: " << filename+".comp" << endl;
		return -1;
	}
	else {
		for (unsigned int i = 0; i < data.size(); i++) {
			block[0] = data[i];
			file.write((char*)block, sizeof(block));
		}
	}

	file.close();
	return 0;
}

//read raw data from file
vector<char> readFile(string& filename) {
	vector<char> data;
	char ltr[1];
	ifstream file;
	file.open(filename, ios::binary);

	if (!file.is_open()) {
		cerr << "ERROR: Could not open file: " << filename << endl;
	}
	else {
		while (!file.eof()) {
			file.read(ltr, sizeof(ltr));
			data.push_back(ltr[0]);
		}
	}

	file.close();
	return data;
}

//compression percent
float percent(string& filename) {
	ifstream raw_file(filename), comp_file(filename + ".comp");
	int raw_size, comp_size;

	raw_file.seekg(0, ios::end);
	raw_size = raw_file.tellg();

	comp_file.seekg(0, ios::end);
	comp_size = comp_file.tellg();

	raw_file.close();
	comp_file.close();

	cout << "Original file: " << raw_size << endl;
	cout << "Compressed file: " << comp_size << endl;

	return comp_size * 100.0f / raw_size;
}

//display content of block structure vector
void display(vector<Block>& blocks) {
	ofstream file("display.txt");
	for (unsigned int i = 0; i < blocks.size(); i++) {
		file << blocks[i].ltr << " " << blocks[i].frequency << endl;
	}
	file.close();
}