#include <fstream>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <thread>

using namespace std;

struct Node {
    const char c;
    const int freq;
    Node* const left;
    Node* const right;

    Node(const char c, const int freq, Node* const left, Node* const right) : c(c), freq(freq), left(left), right(right) {}

    ~Node() {
        delete left;
        delete right;
    }
};

struct comp {
    constexpr bool operator()(Node* const left, Node* const right) const {
        return left->freq > right->freq;
    }
};

/*ESKİ HALİ (RESERVE İLE YAZILAN)  
static void calculateFrequencies(const string& inputFile, unordered_map<char, int>& freq) {
    ifstream inFile(inputFile, ios::in);

    string fileContents;
    inFile.seekg(0, ios::end);
    fileContents.reserve(inFile.tellg());
    inFile.seekg(0, ios::beg);

    fileContents.assign((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());

    for (char c : fileContents) {
        freq[c]++;
    }

    inFile.close();
}
*/

// RESERVE YERİNE MALLOC KULLANMAMI İSTEMİŞTİNİZ SUNUMDA, BU KODU DEĞİŞTİRMEMİ İSTEDİĞİNİZ ŞEKİLDE YAZMAYA ÇALIŞTIM.
static void calculateFrequencies(const string& inputFile, unordered_map<char, int>& freq) {     
    ifstream inFile(inputFile, ios::in | ios::binary);

    if (inFile) {
        inFile.seekg(0, ios::end);
        size_t fileSize = inFile.tellg();
        inFile.seekg(0, ios::beg);

        char* fileContents = static_cast<char*>(malloc(fileSize));
        if (fileContents == nullptr) {
            cerr << "Bellek tahsis edilemedi!" << endl;
            inFile.close();
            return;
        }
        inFile.read(fileContents, fileSize);

        for (size_t i = 0; i < fileSize; i++) {
            freq[fileContents[i]]++;
        }
        inFile.close();
        free(fileContents);
    } 
}
static Node* buildHuffmanTree(const unordered_map<char, int>& freq) {
    priority_queue<Node*, vector<Node*>, comp> pq;
    for (const auto& pair : freq) {
        pq.push(new Node(pair.first, pair.second, nullptr, nullptr));
    }

    for (int size = pq.size(); size > 1; size = pq.size()) {
    for (int i = 0; i < size - 1; i += 2) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        Node* newNode = new Node('$', left->freq + right->freq, left, right);
        pq.push(newNode);
    }
}
 if (pq.empty()) {
        return nullptr; 
    }
    
    return pq.top();
}


static void encode(const Node* const root, const string str, vector<string>& huffmanCode ) {
    if (!root)
        return;

    if (!root->left && !root->right) {
        huffmanCode[root->c] = str;
    }
    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

void compressFile(const string& inputFile, const string& outputFile) {
    unordered_map<char, int> freq;
    calculateFrequencies(inputFile, freq);

    Node* root = buildHuffmanTree(freq);

    vector<string> huffmanCode(256);
    encode(root, "", huffmanCode);

    ifstream inFile(inputFile, ios::in);
    ofstream outFile(outputFile, ios::out);

     for (char c; inFile.get(c);) {
        outFile << huffmanCode[c];
    }

    inFile.close();
    outFile.close();

    delete root;

    cout << "Sıkıştırma işlemi "<< outputFile << " için tamamlandı." << endl;
}

int main() {
    const vector<string> inputFiles = { "input1.txt", "input2.txt", "input3.txt", "input4.txt", "input5.txt" };
    const vector<string> outputFiles = { "output1.txt", "output2.txt", "output3.txt", "output4.txt","output5.txt"};

    vector<thread> threads;
    for (int i = 0; i < inputFiles.size(); i++) {
        threads.emplace_back(compressFile, ref(inputFiles[i]), ref(outputFiles[i]));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
