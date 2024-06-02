#ifndef RROPE_HPP
#define RROPE_HPP

#include <iostream>
#include <string>
#include <algorithm>

struct RopeNode
{
    std::string data;
    int weight;
    RopeNode *left;
    RopeNode *right;

    RopeNode(const std::string &data) : data(data), weight(data.length()), left(nullptr), right(nullptr) {}
};

class RROPE
{
private:
    RopeNode *root;

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
public:
    RROPE();
    void insert(const std::string &s, int index);
    void print();
    void getWeigth();
    void Delete(int low, int high);
};

#endif // ROPE_HPP
