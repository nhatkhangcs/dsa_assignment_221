#include "ConcatStringTree.h"
#define ll long long

long long idCST = 0;
long long idRCST = 0;
bool trivia = false;

string subStringHelper(string s, int from, int to){
    string res = "";
    for (int i = from; i < to; i++) res += s[i];
    return res;
}

ll LitStringHash::hashFunc(string s, int m)
{
    ll result = 0;
    ll currP = 1;
    int l = s.length();
    for (int i = 0; i < l; i++)
    {
        result = ((result % m + (((int)s[i]) % m) * (currP % m)) % m) % m;
        currP = ((currP % m) * (myConfig.p % m)) % m;
    }
    return result;
}

ll LitStringHash::probingFunc(LitString **&currLitHash, string s, int m, bool acceptNull)
{
    ll index = hashFunc(s, m);
    ll hashedValue = index;
    for (int i = 0; i < m; i++)
    {
        ll c1 = myConfig.c1;
        ll c2 = myConfig.c2;
        index = (long long)((hashedValue + (myConfig.c1 - c1) * i + (myConfig.c2 - c2) * (i * i)) + ((i * c1) % m + (i * i * c2) % m) % m) % m;

        if (currLitHash[index] == nullptr && acceptNull) return index;
        if (currLitHash[index] == nullptr) continue;
        if (currLitHash[index]->s == s) return index;
    }
    return -1;
}

void LitStringHash::rehash()
{
    ll newSize = myConfig.alpha * (double)myConfig.initSize;
    LitString ** newHashArray = new LitString *[newSize];
    bool met = true;
    for (int i = 0; i < newSize; i++) newHashArray[i] = nullptr;
    for (int i = 0; i < myConfig.initSize; i++)
    {
        if (arr[i] == nullptr) continue;
        LitString *nLitString = new LitString(arr[i]->s, arr[i]->numOfRef);
        ll newIndex = probingFunc(newHashArray, arr[i]->s, newSize, true);

        newHashArray[newIndex] = nLitString;
        if (i == idx && met){
            idx = newIndex;
            met = false;
        }
        delete arr[i];
    }

    delete[] arr;
    arr = newHashArray;
    myConfig.initSize = newSize;
}

bool LitStringHash::insert(string s)
{
    // cout << numOfEle << " " <<  myConfig.initSize << '\n';
    if (numOfEle == myConfig.initSize) return false;
    ll litIndex = probingFunc(arr, s, myConfig.initSize, true);
    if (litIndex == -1) return false;
    if (arr[litIndex] == nullptr)
    {
        arr[litIndex] = new LitString(s, 1);
        numOfEle++;
        idx = litIndex;
        if ((double)numOfEle / (double)myConfig.initSize > myConfig.lambda) rehash();
        return true;
    }
    else
    {
        arr[litIndex]->numOfRef++;
        return true;
    }
}

bool LitStringHash::remove(string s)
{
    ll index = probingFunc(arr, s, myConfig.initSize, false);
    if (index < 0)
        return false;
    arr[index]->numOfRef--;
    if (arr[index]->numOfRef == 0)
    {
        delete arr[index];
        arr[index] = nullptr;
        numOfEle--;
        if (numOfEle == 0){
            delete[] arr;
            arr = nullptr;
        }
        return true;
    }
    return false;
}

// clone tree with parameter root
node *cloneTree(node *root)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    node *root_copy = new node(root->s);
    root_copy->leftLength = root->leftLength;
    root_copy->rightLength = root->rightLength;
    root_copy->id = root->id;
    root_copy->justDoIt = true;
    root_copy->left = cloneTree(root->left);
    root_copy->right = cloneTree(root->right);

    return root_copy;
}

ConcatStringTree::ConcatStringTree(const char *s)
{
    root = new node(string(s));
    root->length = string(s).length();
    idCST++;
    if (idCST > 1e7)
        throw overflow_error("Id is overflow!");
    root->id = idCST;
    root->paTree = new node::ParentsTree();
    root->paTree->update(root->paTree->Insert(this->root->paTree->getRoot(), idCST));
    categorical = false;
    notToday = false;
}

ConcatStringTree::ConcatStringTree()
{
    root = nullptr;
    categorical = false;
    notToday = false;
}

// destroy parentsTree
void treeDestroyParents(parentNode *root)
{
    if (root == NULL)
        return;

    /* first delete both subtrees */
    treeDestroyParents(root->left);
    treeDestroyParents(root->right);
    delete root;
    root = nullptr;
}

// first version, when we basically don't care the degree
void treeDestroy(node *&root)
{
    if (root == NULL)
        return;

    /* first delete both subtrees */
    treeDestroy(root->left);
    treeDestroy(root->right);
    delete root;
}

bool findNode(parentNode* root, long long key){
    if(!root) return false;
    if(root->idParent == key) return true;
    if(root->idParent < key){
        return findNode(root->right, key);
    }
    return findNode(root->left, key);
}

// second version, when we care if we should delete or not
void deleteWithConds(node *&root)
{
    if (root == NULL)
        return;
    if (!root->justDoIt)
    {
        int reID = root->getID();
        bool found = findNode(root->paTree->getRoot(), reID);
        if(found){
            root->paTree->decrease();
            parentNode *t = root->paTree->getRoot();
            root->paTree->Remove(t, reID);
            root->paTree->update(t);
        }
        
        if (root->paTree->size() == 0)
        {
            if (root->left)
            {
                parentNode *t = root->left->paTree->getRoot();
                //reID = root->getID();
                found = findNode(root->left->paTree->getRoot(), reID);
                if(found){
                    root->left->paTree->Remove(t, reID);
                    root->left->paTree->decrease();
                    root->left->paTree->update(t);
                }
                if(root->left->paTree->size() == 0) deleteWithConds(root->left);
            }

            /*
                    7
                  5   6
                1   2   4
            */

            if (root->right)
            {
                parentNode *t = root->right->paTree->getRoot();
                //reID = root->getID();
                found = findNode(root->right->paTree->getRoot(), reID);
                if(found){
                    root->right->paTree->Remove(t, reID);
                    root->right->paTree->decrease();
                    root->right->paTree->update(t);
                }
                if(root->right->paTree->size() == 0) deleteWithConds(root->right);
            }

            root->deletePatree();
            delete root;
            root = nullptr;
        }
    }

    else
    {
        deleteWithConds(root->left);
        deleteWithConds(root->right);
        delete root;
        root = nullptr;
    }
}

ConcatStringTree::~ConcatStringTree()
{
    if (notToday)
        return;
    if (!root->justDoIt)
    {
        deleteWithConds(root);
    }

    else
    {
        deleteWithConds(root->left);
        deleteWithConds(root->right);
        delete root;
        root = nullptr;
    }
}

void destroyer(node *root)
{
    if (!root)
        return;
    destroyer(root->left);
    destroyer(root->right);
    // treeDestroyParents(root->paTree->getRoot());
    delete root;
    root = nullptr;
}

ConcatStringTree::ConcatStringTree(const ConcatStringTree &&otherS)
{
    this->root = nullptr;
    this->categorical = false;
    this->notToday = false;
    if (otherS.categorical)
    { // is return from concat so we shallow copy
        (this->root) = (otherS.root);
        return;
    }

    // is return from the reverse or substring so we deep copy
    root = cloneTree(otherS.root);

    destroyer(otherS.root);
}

int ConcatStringTree::length() const
{
    return root->length;
}

char ConcatStringTree::get(int idx)
{
    node *temp = root;
    if (idx < 0 || idx >= root->length)
        throw ::out_of_range("Index of string is invalid!");
    else
    {
        while (temp->left || temp->right)
        {
            if (idx < temp->leftLength)
            {
                temp = temp->left;
                // temp->paTree = new node::ParentsTree();
                // temp->paTree->Insert(temp->paTree->getRoot(), keep->paTree->getID());
            }
            else
            {
                idx -= temp->leftLength;
                temp = temp->right;
                // temp->paTree = new node::ParentsTree();
                // temp->paTree->Insert(temp->paTree->getRoot(), keep->paTree->getID());
            }
        }
        return temp->s[idx];
    }
}

int ConcatStringTree::indexOf(char c)
{
    string t = string(root->s);
    std::size_t found = t.find(c);
    if (found != std::string::npos)
        return found;
    else
        return -1;
}

// extra function to build preOrder
string helpPre(node *root)
{
    if (!root)
        return "";
    if (root->leftLength != 0 || root->rightLength != 0)
        return "(LL=" + to_string(root->leftLength) + "," + "L=" + to_string(root->length) + "," + "<" + "NULL" + ">);" + helpPre(root->left) + helpPre(root->right);
    else
        return "(LL=" + to_string(root->leftLength) + "," + "L=" + to_string(root->length) + "," + "\"" + root->s + "\");" + helpPre(root->left) + helpPre(root->right);
}

void reBuild(node *&root)
{
    if (!root)
        return;

    reBuild(root->left);
    reBuild(root->right);

    if (root->left && root->right)
    {
        root->s = root->left->s + root->right->s;
        root->leftLength = root->left->s.length(); // key attribute
        root->rightLength = root->right->s.length();
        root->length = root->s.length();
    }

    else if (root->right)
    {
        root->s = root->right->s;
        root->leftLength = 0;
        root->length = root->s.length();
        root->rightLength = root->right->s.length();
    }

    else if (root->left)
    {
        root->s = root->left->s;
        root->leftLength = root->left->s.length();
        root->length = root->s.length();
        root->rightLength = 0;
    }

    else
    {
        root->leftLength = 0;
        root->rightLength = 0;
        root->length = root->s.length();
    }
}

string preOrder(node *root)
{
    string res = helpPre(root);
    res.pop_back();
    return "ConcatStringTree[" + res + "]";
}

string ConcatStringTree::toStringPreOrder() const
{
    node *t = root;
    string temp = preOrder(t);
    temp.pop_back();
    return temp + "]";
}

string ConcatStringTree::toString() const
{
    return "ConcatStringTree[" + string("\"") + root->s + "\"" + "]";
}

ConcatStringTree ConcatStringTree::concat(const ConcatStringTree &otherS) const
{
    string s = root->s + otherS.root->s;
    ConcatStringTree myTree(s.c_str());
    if (idCST > 1e7)
        throw overflow_error("Id is overflow!");
    myTree.root->s = s;
    myTree.root->left = root;
    myTree.root->right = otherS.root;

    myTree.root->leftLength = root->length; // key attribute
    myTree.root->rightLength = otherS.root->length;
    myTree.root->length = myTree.root->leftLength + myTree.root->rightLength;

    // myTree.root->degree = 1;
    // updateDegree(root);
    // updateDegree(otherS.root);

    root->paTree->update(root->paTree->Insert(root->paTree->getRoot(), myTree.root->getID()));
    otherS.root->paTree->update(otherS.root->paTree->Insert(otherS.root->paTree->getRoot(), myTree.root->getID()));

    // myTree.root->paTree->Insert(myTree.root->paTree->getRoot(), id);
    myTree.notToday = true;
    myTree.categorical = true;
    return (ConcatStringTree &&) myTree;
}

ConcatStringTree ConcatStringTree::subString(int from, int to) const
{
    if (from < 0 || from > this->length() - 1 || to <= 0 || to > this->length())
        throw ::out_of_range("Index of string is invalid!");
    else if (from >= to)
        throw ::logic_error("Invalid range!");

    ConcatStringTree myTree = ConcatStringTree();
    myTree.root = cloneTree(root);

    // myTree.root->paTree = new node::ParentsTree();
    // myTree.root->paTree->increase();

    node *low = nullptr, *high = nullptr;
    node *temp = myTree.root;
    int x = from, y = to, str_len = y - x;
    while (temp->left || temp->right)
    {
        if (from < temp->leftLength)
        {
            low = temp;
            temp = temp->left;
            // temp->paTree = new node::ParentsTree();
            // temp->paTree->Insert(temp->paTree->getRoot(), keep->paTree->getID());
        }
        else
        {
            from -= temp->leftLength;
            low = temp;

            temp = temp->right;
            treeDestroy(low->left);
            low->left = nullptr;
            // temp->paTree = new node::ParentsTree();
            // temp->paTree->Insert(temp->paTree->getRoot(), keep->paTree->getID());
        }
    }
    low = temp;

    temp = myTree.root;
    while (temp->left || temp->right)
    {
        // cout << root->leftLength << " " << root->rightLength << '\n';
        // cout << temp->s.length() << " " << temp->leftLength << " " << temp->rightLength << '\n';
        if (to <= temp->leftLength)
        {
            high = temp;
            temp->rightLength = 0;
            temp = temp->left;
            treeDestroy(high->right);
            high->right = nullptr;
            // temp->paTree = new node::ParentsTree();
            // temp->paTree->Insert(temp->paTree->getRoot(), keep->paTree->getID());
        }
        else
        {
            to -= temp->leftLength;
            high = temp;
            temp = temp->right;
            // temp->paTree = new node::ParentsTree();
            // temp->paTree->Insert(temp->paTree->getRoot(), keep->paTree->getID());
        }
    }
    high = temp;
    temp->length = temp->s.length();

    if (high == low)
    {
        // cout << from << " " << to << '\n';
        low->s = subStringHelper(low->s, from, to);
    }

    else
    {
        // cout << "here\n";
        // cout << low->s << " " << from << " " << high->s << " " << to << '\n';
        low->length = low->s.length();
        low->s = subStringHelper(low->s, from, low->s.length());
        high->length = high->s.length();
        high->s = subStringHelper(high->s, 0, to);
    }

    reBuild(myTree.root);
    myTree.notToday = true;
    myTree.categorical = false;
    return (ConcatStringTree &&) myTree;
}

void reverseStr(string &str)
{
    int len = str.length();
    int n = len - 1;
    int i = 0;
    while (i <= n)
    {
        // Using the swap method to switch values at each index
        swap(str[i], str[n]);
        n = n - 1;
        i = i + 1;
    }
}

void invertTree(node *&root)
{
    if (!root) return;
    
    invertTree(root->left);
    invertTree(root->right);

    reverseStr(root->s);
    node *temp = root->left;
    root->left = root->right;
    root->right = temp;
}

ConcatStringTree ConcatStringTree::reverse() const
{
    ConcatStringTree myTree = ConcatStringTree();
    myTree.root = cloneTree(root);

    invertTree(myTree.root);
    reBuild(myTree.root);
    myTree.root->justDoIt = false;
    myTree.notToday = true;
    myTree.categorical = false;
    return (ConcatStringTree &&) myTree;
}

int ConcatStringTree::getParTreeSize(const string &query) const
{
    node *temp = root;
    int i = 0;
    int s = query.length();
    while (i < s)
    {
        if (temp)
        {
            if (query[i] == 'l')
                temp = temp->left;
            else if (query[i] == 'r')
                temp = temp->right;
            else
                throw runtime_error("Invalid character of query");
            i++;
        }

        else
            throw runtime_error("Invalid query: reaching NULL");
    }

    if (temp){
        return temp->paTree->size();
    }
    else
        throw runtime_error("Invalid query: reaching NULL");
}

string NLRParent(parentNode *root)
{
    if (!root)
        return "";
    return "(id=" + to_string(root->idParent) + ");" + NLRParent(root->left) + NLRParent(root->right);
}

string ConcatStringTree::getParTreeStringPreOrder(const string &query) const
{
    node *temp = root;
    int i = 0;
    int s = query.length();
    while (i < s)
    {
        if (temp)
        {
            if (query[i] == 'l')
                temp = temp->left;
            else if (query[i] == 'r')
                temp = temp->right;
            else
            {
                throw runtime_error("Invalid character of query");
            }
            i++;
        }

        else
        {
            throw runtime_error("Invalid query: reaching NULL");
            return "";
        }
    }

    if (temp && temp->paTree)
        return temp->paTree->toStringPreOrder();

    else
    {
        throw runtime_error("Invalid query: reaching NULL");
        return "";
    }
}

int node::ParentsTree::size() const
{
    return s;
}

string node::ParentsTree::toStringPreOrder() const
{
    parentNode *temp = root;
    string s = NLRParent(temp);
    if (s != "")
        s.pop_back();
    return "ParentsTree[" + s + "]";
}

LitStringHash::LitStringHash(const HashConfig &hashConfig)
{
    myConfig = hashConfig;
    numOfEle = 0;
    arr = new LitString *[hashConfig.getSize()];

    for (int i = 0; i < hashConfig.getSize(); i++)
        arr[i] = nullptr;
}

ReducedConcatStringTree::ReducedConcatStringTree(const char *s, LitStringHash *litStringHash)
{
    idRCST++;
    root = new node(s);
    root->paTree = new node::ParentsTree();
    root->id = idRCST;
    root->paTree->update(root->paTree->Insert(root->paTree->getRoot(), idRCST));
    if (trivia == false)
    {
        trivia = true;
        litStringHash->reset();
    }
    if (!litStringHash->get())
        litStringHash->initialize();
    if (!litStringHash->insert(string(s)))
    {
        idRCST--;
        notToday = false;
        categorical = false;
        throw runtime_error("No possible slot");
    }
    this->litStringHash = litStringHash;

    if (idRCST > 1e7)
    {
        categorical = false;
        notToday = false;
        throw overflow_error("Id is overflow!");
    }
}

void LitStringHash::probMinus(node *root)
{
    if (!root)
        return;
    if (!root->left && !root->right)
    {
        int size = myConfig.initSize;
        ll idx = probingFunc(arr, root->s, size, false);
        if (idx != -1)
            remove(root->s);
    }

    probMinus(root->left);
    probMinus(root->right);
}

ReducedConcatStringTree::~ReducedConcatStringTree()
{
    if (notToday)
        return;
    string x = root->s;
    if (isConcat) litStringHash->probMinus(root);
    else litStringHash->remove(x);

    if (!root->justDoIt) deleteWithConds(root);
    
    else{
        deleteWithConds(root->left);
        deleteWithConds(root->right);
        delete root;
        root = nullptr;
    }

    

    notToday = true;
}

ReducedConcatStringTree::ReducedConcatStringTree(ReducedConcatStringTree &&otherS)
{
    this->root = nullptr;
    this->litStringHash = otherS.litStringHash;
    this->categorical = false;
    this->notToday = false;
    this->isConcat = otherS.isConcat;
    if (otherS.categorical)
    {
        this->root = otherS.root;
        return;
    }
}

ReducedConcatStringTree::ReducedConcatStringTree(const char *s, LitStringHash *litStringHash, bool concat)
{
    idRCST++;
    root = new node(s);
    root->paTree = new node::ParentsTree();
    root->id = idRCST;
    root->paTree->update(root->paTree->Insert(root->paTree->getRoot(), idRCST));
    this->litStringHash = litStringHash;

    if (idRCST > 1e7)
    {
        throw overflow_error("Id is overflow!");
    }

    categorical = false;
    notToday = false;
}

void LitStringHash::probingAll(node *root)
{
    if (!root)
        return;
    if (!root->left && !root->right)
    {
        int size = myConfig.initSize;
        ll idx = probingFunc(arr, root->s, size, false);
        if (idx != -1)
            arr[idx]->numOfRef++;
    }

    probingAll(root->left);
    probingAll(root->right);
}

ReducedConcatStringTree ReducedConcatStringTree::concat(const ReducedConcatStringTree &otherS) const
{
    string s = root->s + otherS.root->s;
    ReducedConcatStringTree myTree(s.c_str(), litStringHash, true);
    myTree.root->s = s;
    myTree.root->left = root;
    myTree.root->right = otherS.root;

    myTree.root->leftLength = root->length; // key attribute
    myTree.root->rightLength = otherS.root->length;
    myTree.root->length = myTree.root->leftLength + myTree.root->rightLength;

    if (idRCST > 1e7)
        throw overflow_error("Id is overflow!");
    root->paTree->update(root->paTree->Insert(this->root->paTree->getRoot(), myTree.root->getID()));
    if (idRCST > 1e7)
        throw overflow_error("Id is overflow!");
    otherS.root->paTree->update(otherS.root->paTree->Insert(otherS.root->paTree->getRoot(), myTree.root->getID()));
    litStringHash->probingAll(myTree.root);
    myTree.root->leftString = root->s;
    myTree.root->rightString = otherS.root->s;
    myTree.notToday = true;
    myTree.categorical = true;
    myTree.isConcat = true;
    return (ReducedConcatStringTree &&) myTree;
}

string LitStringHash::toString() const
{
    string result = "LitStringHash[";
    for (int i = 0; i < myConfig.initSize; i++)
    {
        if (!arr)
            break;
        if (result.back() == ')')
            result += ";";
        result += "(";
        if (arr[i] != nullptr && arr[i]->numOfRef != 0)
        {
            result += "litS=\"" + arr[i]->s + "\"";
        }
        result += ")";
    }

    result += "]";
    return result;
}

int LitStringHash::getLastInsertedIndex() const
{
    return idx;
}

LitStringHash::~LitStringHash()
{
    if (numOfEle == 0)
    {
        delete[] arr;
        arr = nullptr;
        idx = -1;
        trivia = false;
    }

    else
        return;
}
