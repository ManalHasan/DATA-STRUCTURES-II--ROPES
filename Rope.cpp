#include "Rope.hpp"

Rope::Rope() : root(nullptr),len(0) {}

//INSERT
void Rope::insert(const std::string &s, int index)
{   // Save current state before modification for undo support
    history.push_back(cloneRopeNode(root));
    len+=s.length();
    //actual insertion starts here
    if (root == nullptr)//first node to be inserted
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

void Rope::printRope(RopeNode *&node)//following in-order traversal
{
    if (!node)
        return;
    if (node->left)
        printRope(node->left);
    if (!node->data.empty())//if its a node which holds string
        std::cout << node->data ;
    if (node->right)
        printRope(node->right);
}

void Rope::print()
{
    printRope(root);
    std::cout << std::endl;
}
void Rope::getWeight()
{
    std::cout << root->weight;
}

//SPLIT- returns the nodes as a pair after being splitted
std::pair<RopeNode *, RopeNode *> Rope::split(RopeNode *&root, int index)
{
    if (!root)//nothing to split
        return {nullptr, nullptr};

    if (index <= root->weight)//go to left subtree
    {
        if (!root->left)//if leaf node
        {
            std::string leftPart = root->data.substr(0, index);
            std::string rightPart = root->data.substr(index);
            root->weight = leftPart.size();
            return {new RopeNode(leftPart), new RopeNode(rightPart)};
        }
        //else recursive calls to reach a leaf node
        auto splitPair = split(root->left, index);
        root->left = splitPair.second;
        updateWeight(root);
        return {splitPair.first, balance(root)};
    }
    else//go to right subtree
    {
        if (!root->right)//leaf node
        {
            std::string leftPart = root->data.substr(0, index - root->weight);
            std::string rightPart = root->data.substr(index - root->weight);
            return {new RopeNode(leftPart), new RopeNode(rightPart)};
        }
        //if not internal node
        auto splitPair = split(root->right, index - root->weight);
        root->right = splitPair.first;
        return {balance(root), splitPair.second};
    }
}

int Rope::getHeight(RopeNode *&node)//traverses down following the longest path
{
    if (!node)
        return 0;
    return 1 + std::max(getHeight(node->left), getHeight(node->right));
}

//ROTATIONS:
RopeNode *Rope::rotateLeft(RopeNode *&x)
{
    RopeNode *y = x->right;
    x->right = y->left;
    y->left = x;
    updateWeight(y);
    return y;
}

RopeNode *Rope::rotateRight(RopeNode *&x)
{
    RopeNode *y = x->left;
    x->left = y->right;
    updateWeight(x);
    y->right = x;
    return y;
}

//calculating balance factor
int Rope::getBalance(RopeNode *&node)
{
    if (!node)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

//BALANCE: Identifies unbalanced rope and then balances via rotations
RopeNode *Rope::balance(RopeNode *&n)
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

//APPEND: merges two nodes
RopeNode *Rope::append(RopeNode *&leftRoot, RopeNode *&rightRoot)
{
    if (!leftRoot)
        return rightRoot;
    if (!rightRoot)
        return leftRoot;

    // If both nodes are leaves and the total size is within a threshold, just concatenate them
    if (leftRoot->left == nullptr && leftRoot->right == nullptr &&
        rightRoot->left == nullptr && rightRoot->right == nullptr &&
        (leftRoot->weight + rightRoot->weight) <= 10)// Assuming leaf limit size
    { 
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

void Rope::updateWeight(RopeNode *&newNode)
{
    //if nor grandchildren then directly take the weight of the left child
    if (!newNode->left->left && !newNode->left->right)
        newNode->weight = newNode->left->weight;

    else
    {
        int count = newNode->left->weight;
        RopeNode *leftnode = newNode->left;
        while (leftnode->right != nullptr)//since we already have the weight of left child in a node therfore we go down in right child(s)
        {
            count += leftnode->right->weight;
            leftnode = leftnode->right;
        }
        newNode->weight = count;
    }
}
//CONCATENATION: two ropes concatenated
RopeNode *Rope::concatenate(RopeNode *root2, RopeNode *root, RopeNode *root1, int n1)
{
    root2 = new RopeNode("");
    root2->left = root;
    root2->right = root1;
    updateWeight(root2);
    return root2;
}

//
// int Rope::Length(RopeNode *node)
// {
//     int l = node->weight;
//     RopeNode *temp = node;
//     while (temp->right != nullptr)//complete BT so if right child doesn't exist then neither does left child
//     {
//         l += temp->right->weight;
//         temp = temp->right;
//     }
//     return l;
// }
//DELETION

RopeNode *Rope::Del(int low, int high)
{
    auto splitPair = split(root, low);
    auto splitPair1 = split(splitPair.second, high - low + 1);
    root = append(splitPair.first, splitPair1.second);
    return splitPair1.first;
    //
}

void Rope::Delete(int low, int high)
{
    // Save current state before modification
        history.push_back(cloneRopeNode(root));
    low = std::max(0, low);
    high = std::min(high, len - 1);

    if (low > high)
    {
        return; // Return an empty rope
    }

    RopeNode *mid = Del(low, high);
    std::cout << "Deleted substring: " << mid->data << std::endl;
    mid = nullptr;
    delete mid;
    len-=(high-low)+1;//maintaining length of the string stored throughout all nodes
}
void Rope::Searchbyindex(int index, int numletters)
{
    std::vector<int> indexes;
    for (int i = 0; i < numletters; i++)
    {
        indexes.push_back(index + i);
    }

    std::string returnstr;
    searchhelper(root, indexes, returnstr);

    std::cout <<"String found: "<<returnstr;
}
void Rope::searchhelper(RopeNode *&node, std::vector<int> indexes, std::string &s)
{
    if (node->left == nullptr && node->right == nullptr)
    {
        s.append(node->data.substr(indexes[0], indexes.size()));
    }
    else
    {
        std::vector<int> right;
        std::vector<int> left;
        for (const int &i : indexes)
        {
            if (i < node->weight)
            {
                left.push_back(i);
            }
            else
            {
                right.push_back(i - node->weight);
            }
        }
        if (!left.empty())
        {
            searchhelper(node->left, left, s);
        }
        if (!right.empty())
        {
            searchhelper(node->right, right, s);
        }
    }
}
void Rope::storeString(RopeNode *node, std::string &st)
{

    if (node == nullptr)
        return;
    if (node->left == nullptr && node->right == nullptr && !node->data.empty())
    {
        std::string temp = node->data;
        st.append(temp);
    }
    storeString(node->left, st);
    storeString(node->right, st);
}
std::vector<int> Rope::Searchbyword(std::string word)
{
    std::string s;
    storeString(root, s);
    std::vector<int> index;
    int start = 0;
    while (start < s.size())
    {
        int found = s.find(word, start);
        if (found != std::string::npos)
        {
            index.push_back(found);
            start = found + word.size();
        }
        else
        {
            break;
        }
    }
    return index;
}
//CLONE: copying entire rope for undo support
RopeNode* Rope::cloneRopeNode(RopeNode* node) {
        if (!node) return nullptr;
        RopeNode* newNode = new RopeNode(node->data);
        newNode->weight = node->weight;
        newNode->left = cloneRopeNode(node->left);
        newNode->right = cloneRopeNode(node->right);
        return newNode;
    }
//UNDO
void Rope::undo() {
        if (history.empty()) {
            std::cout << "No more actions to undo." << std::endl;
            return;
        }

        // Clean up current rope
        DestroyRecursive(root);
        // Restore previous state
        root = history.back();
        history.pop_back();
    }

void Rope::DestroyRecursive(RopeNode *node)
{
    if (node != nullptr)
    {
        DestroyRecursive(node->left);
        DestroyRecursive(node->right);
        delete node;
    }
}

Rope::~Rope()
{
    DestroyRecursive(root);
}
// char Rope::searchIn(int index)
// {
//     if (index < 0 || index >= Length(root))
//     {
//         // Index out of bounds
//         throw std::out_of_range("Index out of bounds");
//     }

//     return findChar(root, index);
// }

// char Rope::findChar(RopeNode *node, int index)
// {
//     if (node->left == nullptr && node->right == nullptr)
//     {
//         return node->data[index]; // Not found
//     }

//     if (index < node->weight)
//     {

//         return findChar(node->left, index);
//     }
//     else
//     {
//         return findChar(node->right, index - node->weight);
//     }
// }

//Reads .txt file
void Rope::insertFileIntoRope(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    int n = 0;
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string word;

        while (iss >> word)
        {
            std::string s = word + " ";
            insert(s, n);
            n += s.size()+1;
        }
    }

    file.close();
}