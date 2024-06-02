#include "RROPE.hpp"

RROPE::RROPE() : root(nullptr) {}

void RROPE::insert(const std::string &s, int index)
{
    if (root == nullptr)
    {
        root = new RopeNode(s);
    }
    else
    {
        auto splitRopes = split(root, index);
        RopeNode *newNode = new RopeNode(s);
        RopeNode *firstAppend = append(splitRopes.first, newNode);
        root = append(firstAppend, splitRopes.second);
    }
}

void RROPE::printRope(RopeNode *&node)
{
    if (!node)
        return;
    if (node->left)
        printRope(node->left);
    if (!node->data.empty())
        std::cout << node->data;
    if (node->right)
        printRope(node->right);
}

void RROPE::print()
{
    printRope(root);
    std::cout << std::endl;
}
void RROPE::getWeigth()
{
    std::cout << root->weight;
}

std::pair<RopeNode *, RopeNode *> RROPE::split(RopeNode *&root, int index)
{
    if (!root)
        return {nullptr, nullptr};

    if (index <= root->weight)
    {
        if (!root->left)
        {
            std::string leftPart = root->data.substr(0, index);
            std::string rightPart = root->data.substr(index);
            root->weight = leftPart.size();
            return {new RopeNode(leftPart), new RopeNode(rightPart)};
        }
        auto splitPair = split(root->left, index);
        root->left = splitPair.second;
        updateWeight(root);
        return {splitPair.first, balance(root)};
    }
    else
    {
        if (!root->right)
        {
            std::string leftPart = root->data.substr(0, index - root->weight);
            std::string rightPart = root->data.substr(index - root->weight);
            return {new RopeNode(leftPart), new RopeNode(rightPart)};
        }
        auto splitPair = split(root->right, index - root->weight);
        root->right = splitPair.first;
        return {balance(root), splitPair.second};
    }
}

int RROPE::getHeight(RopeNode *&node)
{
    if (!node)
        return 0;
    return 1 + std::max(getHeight(node->left), getHeight(node->right));
}

RopeNode *RROPE::rotateLeft(RopeNode *&x)
{
    RopeNode *y = x->right;
    x->right = y->left;
    y->left = x;
    updateWeight(y);
    return y;
}

RopeNode *RROPE::rotateRight(RopeNode *&x)
{
    RopeNode *y = x->left;
    x->left = y->right;
    updateWeight(x);
    y->right = x;
    return y;
}

int RROPE::getBalance(RopeNode *&node)
{
    if (!node)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

RopeNode *RROPE::balance(RopeNode *&n)
{
    int balance = getBalance(n);
    if (balance > 1)
    {
        if (getBalance(n->left) < 0)
        {
            n->left = rotateLeft(n->left);
        }
        return rotateRight(n);
    }
    if (balance < -1)
    {
        if (getBalance(n->right) > 0)
        {
            n->right = rotateRight(n->right);
        }
        return rotateLeft(n);
    }
    return n;
}
RopeNode *RROPE::append(RopeNode *&leftRoot, RopeNode *&rightRoot)
{
    if (!leftRoot)
        return rightRoot;
    if (!rightRoot)
        return leftRoot;

    // If both nodes are leaves and the total size is within a threshold, just concatenate them
    if (leftRoot->left == nullptr && leftRoot->right == nullptr &&
        rightRoot->left == nullptr && rightRoot->right == nullptr &&
        (leftRoot->weight + rightRoot->weight) <= 10)
    { // Assuming leaf limit size
        leftRoot->data += rightRoot->data;
        leftRoot->weight = leftRoot->data.size();
        delete rightRoot; // Clean up rightRoot as it's no longer needed
        return leftRoot;
    }

    // Otherwise, create a new node
    RopeNode *newNode = new RopeNode("");
    newNode->left = leftRoot;
    newNode->right = rightRoot;
    updateWeight(newNode);
    return balance(newNode);
}

void RROPE::updateWeight(RopeNode *&newNode)
{
    if (!newNode->left->left && !newNode->left->right)
        newNode->weight = newNode->left->weight;

    else
    {
        int count = newNode->left->weight;
        RopeNode *leftnode = newNode->left;
        while (leftnode->right != nullptr)
        {
            count += leftnode->right->weight;
            leftnode = leftnode->right;
        }
        newNode->weight = count;
    }
}

//////////////////deletion
int RROPE::Length(RopeNode *node){
    int l= node->weight;
    RopeNode *temp=node;
    while (temp->right!=nullptr){
        l+=temp->right->weight;
        temp=temp->right;
    }
    return l;
}

RopeNode * RROPE::Del(int low, int high){
    auto splitPair = split(root, low);
    auto splitPair1 = split(splitPair.second, high-low+1);
    root=append(splitPair.first,splitPair1.second);
    return splitPair1.first;
    //


}

void RROPE::Delete(int low, int high){
    
        low = std::max(0, low);
        high = std::min(high, Length(root) - 1);

        if (low > high) {
            return; // Return an empty rope
        }

        RopeNode* mid = Del(low, high);
        std::cout<<"Deleted substring: "<<mid->data<<std::endl;
        mid=nullptr;
        delete mid;
}