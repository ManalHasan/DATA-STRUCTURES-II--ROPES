#ifndef ROPE_HPP
#define ROPE_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>

struct RopeNode
{
    std::string data;
    int weight;
    RopeNode *left;
    RopeNode *right;

    RopeNode(const std::string &data) : data(data), weight(data.length()), left(nullptr), right(nullptr) {}
};

class Rope
{
private:
    RopeNode *root;
    std::vector<RopeNode*> history;
    int len;

    std::pair<RopeNode *, RopeNode *> split(RopeNode *&root, int index);
    int getHeight(RopeNode *&node);
    RopeNode *rotateLeft(RopeNode *&x);
    RopeNode *rotateRight(RopeNode *&x);
    int getBalance(RopeNode *&node);
    RopeNode *balance(RopeNode *&n);
    RopeNode *append(RopeNode *&leftRoot, RopeNode *&rightRoot);
    void updateWeight(RopeNode *&newNode);
    void printRope(RopeNode *&node);
    RopeNode *Del(int low, int high);
    int Length(RopeNode *node);
    RopeNode *concatenate(RopeNode *root2, RopeNode *root, RopeNode *root1, int n1);
    void searchhelper(RopeNode *&node, std::vector<int> indexes, std::string &s);
    void storeString(RopeNode *node, std::string &st);
    void DestroyRecursive(RopeNode *node);
    char findChar(RopeNode *node, int index);
    RopeNode* cloneRopeNode(RopeNode* node);

public:
    ~Rope();
    Rope();
    void insert(const std::string &s, int index);
    void print();
    void getWeight();
    void Delete(int low, int high);
    void Searchbyindex(int index, int numletters);
    std::vector<int> Searchbyword(std::string word);
    char searchIn(int index); // search with index
    void insertFileIntoRope(const std::string &filename);
    void undo();
};

#endif // ROPE_HPP
