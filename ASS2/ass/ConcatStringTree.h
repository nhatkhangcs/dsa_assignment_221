#ifndef __CONCAT_STRING_TREE_H__
#define __CONCAT_STRING_TREE_H__

#include "main.h"

class HashConfig
{
private:
    int p;
    double c1, c2;
    double lambda;
    double alpha;
    int initSize;

    friend class LitStringHash;
    friend class ReducedConcatStringTree;

public:
    HashConfig(int p = 0, double c1 = 0, double c2 = 0, double l= 0 , double a= 0 , int s= 0){
        this->p = p;
        this->c1 = c1;
        this->c2 = c2;
        this->lambda = l;
        this->alpha = a;
        this->initSize = s;
    }

    int getSize() const{
        return initSize;
    }
};

struct parentNode
{
    long long idParent;
    int height;
    parentNode *left;
    parentNode *right;

    parentNode(long long id)
    {
        this->idParent = id;
        height = 0;
        left = nullptr;
        right = nullptr;
    }
};

struct node
{
    string s;
    int length;
    int leftLength;
    int rightLength;
    string leftString = "";
    string rightString = "";
    int id;
    node *left;
    node *right;
    bool justDoIt = false;

    /*
        maybe need to store the parent of the node as well, but later (if needed)
    */
    node(string s)
    {
        this->s = s;
        this->length = s.length();
        leftLength = 0;
        rightLength = 0;
        id = 0;
        left = nullptr;
        right = nullptr;
        paTree = nullptr;
    }

    class ParentsTree
    {
        parentNode *root;
        int s;

    public:
        ParentsTree()
        {
            root = nullptr;
            s = 0;
        }

        parentNode *getRoot()
        {
            return root;
        }

        void increase()
        {
            s++;
        }

        void copySize(int s){
            this->s = s;
        }

        void decrease()
        {
            s--;
        }

        void changeRoot()
        {
            root = new parentNode(0);
        }

        void update(parentNode *t)
        {
            root = t;
        }

        parentNode* Insert(parentNode *root, int theKey)
        {
            if (root == nullptr)
            {
                root = new parentNode(theKey);
                root->height = 1;
                root->left = nullptr;
                root->right = nullptr;
                s++;

                return root;
            }

            else if (theKey < root->idParent)
            {
                parentNode* t = root;
                root->left = Insert(t->left, theKey);
                if (getHeight(root->left) - getHeight(root->right) == 2)
                    RotateWithLeftChild(root);

                ComputeHeight(root);
                return root;
            }

            else
            {
                parentNode* t = root;
                
                root->right = Insert(t->right, theKey);
                if (getHeight(root->right) - getHeight(root->left) == 2)
                    RotateWithRightChild(root);

                ComputeHeight(root);
                return root;
            }
        }

        void RotateWithLeftChild(parentNode *&p)
        {
            parentNode *q = p->left;
            if (getHeight(q->left) >= getHeight(q->right))
                SingleWithLeftChild(p);
            else
                DoubleWithleftChild(p);
        }

        void SingleWithLeftChild(parentNode *&p)
        {
            parentNode *q = p->left;
            p->left = q->right;
            q->right = p;
            ComputeHeight(p);
            ComputeHeight(q);
            p = q;
        }

        void DoubleWithleftChild(parentNode *&p)
        {
            parentNode *q = p->left;
            parentNode *r = q->right;
            q->right = r->left;
            p->left = r->right;
            r->left = q;
            r->right = p;
            ComputeHeight(q);
            ComputeHeight(p);
            ComputeHeight(r);
            p = r;
        }

        void SingleWithRightChild(parentNode *&p)
        {
            parentNode *q = p->right;
            p->right = q->left;
            q->left = p;
            ComputeHeight(p);
            ComputeHeight(q);
            p = q;
        }

        void DoubleWithRightChild(parentNode *&p)
        {
            parentNode *q = p->right;
            parentNode *r = q->left;
            q->left = r->right;
            p->right = r->left;
            r->left = p;
            r->right = q;
            ComputeHeight(q);
            ComputeHeight(p);
            ComputeHeight(r);
            p = r;
        }

        void RotateWithRightChild(parentNode *&p)
        {
            parentNode *q = p->right;
            if (getHeight(q->left) <= getHeight(q->right))
                SingleWithRightChild(p);
            else
                DoubleWithRightChild(p);
        }

        int getHeight(parentNode *p)
        {
            if (p == NULL)
                return 0;
            else
                return p->height;
        }

        void ComputeHeight(parentNode *p)
        {
            if (getHeight(p->left) >= getHeight(p->right))
                p->height = getHeight(p->left) + 1;
            else
                p->height = getHeight(p->right) + 1;
        }

        void RemoveRightMostNode(parentNode *&r, parentNode * &q)
        {
            if (r->right)
            {
                RemoveRightMostNode(r->right, q);
                ComputeHeight(r);
            }

            else
            {
                q->idParent = r->idParent;
                q = r;
                r = r->left;
            }
        }

        void Remove(parentNode *&p, int theKey)
        {
            if (p != nullptr)
            {
                if (theKey < p->idParent)
                {
                    Remove(p->left, theKey);
                    if (getHeight(p->right) - getHeight(p->left) == 2)
                        RotateWithRightChild(p);
                    ComputeHeight(p);
                }

                else if (theKey > p->idParent)
                {
                    Remove(p->right, theKey);
                    if (getHeight(p->left) - getHeight(p->right) == 2)
                        RotateWithLeftChild(p);
                    ComputeHeight(p);
                }

                else if (theKey == p->idParent)
                {
                    parentNode *q = p;
                    if (p->left == nullptr && p->right == nullptr)
                        p = nullptr;
                    else if (p->left != nullptr && p->right == nullptr)
                        p = p->left;
                    else if (p->left == nullptr && p->right != nullptr)
                        p = p->right;
                    else
                    {
                        RemoveRightMostNode(p->left, q);
                        if (getHeight(p->right) - getHeight(p->left) == 2)
                            RotateWithRightChild(p);
                        ComputeHeight(p);
                    }

                    delete q;
                }

                else
                {
                    Remove(p->right, theKey);
                    if (p->left->height - p->right->height == 2)
                        RotateWithLeftChild(p);
                    ComputeHeight(p);
                }
            }
        }

        int size() const;

        string toStringPreOrder() const;
    };
    ParentsTree *paTree;

    long long getID(){
        return id;
    }

    void deletePatree()
    {
        delete paTree;
        paTree = nullptr;
    }
};

struct LitString
{
    string s;
    int numOfRef;

    LitString(string s, int n)
    {
        this->s = s;
        this->numOfRef = n;
    }

    friend class LitStringHash;

    class ParentsTree
    {
        parentNode *root;
        parentNode *pNode;
        bool left = false;
        bool right = false;
        int s;

    public:
        ParentsTree()
        {
            root = new parentNode(0);
            pNode = nullptr;
            s = 0;
        }

        parentNode *getRoot()
        {
            return root;
        }

        long long getID()
        {
            return root->idParent;
        }

        void increase()
        {
            s++;
        }

        void decrease()
        {
            s--;
        }

        void changeRoot()
        {
            root = new parentNode(0);
        }

        void update(parentNode *t)
        {
            root = t;
        }

        void Insert(parentNode *root, int theKey)
        {
            if (root == nullptr)
            {
                root = new parentNode(theKey);
                if (left)
                    pNode->left = root;
                else if (right)
                    pNode->right = root;
                left = false;
                right = false;
                root->height = 1;
                root->left = nullptr;
                root->right = nullptr;
                s++;
            }

            else if (theKey < root->idParent)
            {
                pNode = root;
                parentNode *t = root;
                left = true;
                Insert(t->left, theKey);
                if (getHeight(t->left) - getHeight(t->right) == 2)
                    RotateWithLeftChild(root);

                ComputeHeight(root);
            }

            else
            {
                pNode = root;
                parentNode *t = root;
                right = true;
                Insert(t->right, theKey);
                if (getHeight(root->right) - getHeight(root->left) == 2)
                    RotateWithRightChild(root);

                ComputeHeight(root);
            }
        }

        void RotateWithLeftChild(parentNode *&p)
        {
            parentNode *q = p->left;
            if (getHeight(p->left) >= getHeight(p->right))
                SingleWithLeftChild(p);
            else
                DoubleWithleftChild(p);
        }

        void SingleWithLeftChild(parentNode *&p)
        {
            parentNode *q = p->left;
            p->left = q->right;
            q->right = p;
            ComputeHeight(p);
            ComputeHeight(q);
            p = q;
        }

        void DoubleWithleftChild(parentNode *&p)
        {
            parentNode *q = p->left;
            parentNode *r = q->right;
            q->right = r->left;
            q->left = r->right;
            r->left = q;
            r->right = p;
            ComputeHeight(q);
            ComputeHeight(p);
            ComputeHeight(r);
            p = r;
        }

        void SingleWithRightChild(parentNode *&p)
        {
            parentNode *q = p->right;
            p->right = q->left;
            q->left = p;
            ComputeHeight(p);
            ComputeHeight(q);
            p = q;
        }

        void DoubleWithRightChild(parentNode *&p)
        {
            parentNode *q = p->right;
            parentNode *r = q->left;
            q->left = r->right;
            q->right = r->left;
            r->left = p;
            r->right = q;
            ComputeHeight(q);
            ComputeHeight(p);
            ComputeHeight(r);
            p = r;
        }

        void RotateWithRightChild(parentNode *&p)
        {
            parentNode *q = p->right;
            if (getHeight(p->left) <= getHeight(p->right))
                SingleWithRightChild(p);
            else
                DoubleWithRightChild(p);
        }

        int getHeight(parentNode *p)
        {
            if (p == NULL)
                return 0;
            else
                return p->height;
        }

        void ComputeHeight(parentNode *p)
        {
            if (getHeight(p->left) >= getHeight(p->right))
                p->height = getHeight(p->left) + 1;
            else
                p->height = getHeight(p->right) + 1;
        }

        void RemoveRightMostNode(parentNode *&r, parentNode *q)
        {
            if (r->right)
            {
                RemoveRightMostNode(r->right, q);
                ComputeHeight(r);
            }

            else
            {
                q->idParent = r->idParent;
                q = r;
                r = r->left;
            }
        }

        void Remove(parentNode *&p, int theKey)
        {
            if (p != nullptr)
            {
                if (theKey < p->idParent)
                {
                    Remove(p->left, theKey);
                    if (getHeight(p->right) - getHeight(p->left) == 2)
                        RotateWithRightChild(p);
                    ComputeHeight(p);
                }

                else if (theKey > p->idParent)
                {
                    Remove(p->right, theKey);
                    if (getHeight(p->left) - getHeight(p->right) == 2)
                        RotateWithLeftChild(p);
                    ComputeHeight(p);
                }

                else if (theKey == p->idParent)
                {
                    parentNode *q = p;
                    if (p->left == nullptr && p->right == nullptr)
                        p = nullptr;
                    else if (p->left != nullptr && p->right == nullptr)
                        p = p->left;
                    else if (p->left == nullptr && p->right != nullptr)
                        p = p->right;
                    else
                    {
                        RemoveRightMostNode(p->left, q);
                        if (getHeight(p->right) - getHeight(p->left) == 2)
                            RotateWithRightChild(p);
                        ComputeHeight(p);
                    }

                    delete q;
                }

                else
                {
                    Remove(p->right, theKey);
                    if (p->left->height - p->right->height == 2)
                        RotateWithLeftChild(p);
                    ComputeHeight(p);
                }
            }
        }

        int size() const;

        string toStringPreOrder() const;
    };
    ParentsTree *paTree;

    void deletePatree()
    {
        delete paTree;
        paTree = nullptr;
    }
};

class ConcatStringTree
{

public:
    ConcatStringTree(const char *s);
    ConcatStringTree(const ConcatStringTree&& otherS);
    ConcatStringTree();
    virtual ~ConcatStringTree();
    int length() const;
    char get(int index);
    int indexOf(char c);
    string toStringPreOrder() const;
    string toString() const;
    ConcatStringTree concat(const ConcatStringTree &otherS) const;
    ConcatStringTree subString(int from, int to) const;
    ConcatStringTree reverse() const;

    int getParTreeSize(const string &query) const;
    string getParTreeStringPreOrder(const string &query) const;

protected:
    node *root;
    bool notToday = false;
    bool categorical = false;
};

class ReducedConcatStringTree; 
class LitStringHash; // forward declaration

class LitStringHash
{
private:
    int numOfEle;
    LitString **arr;
    HashConfig myConfig;
    int oriSizePrincess;
    int idx = -1;

public:
    ~LitStringHash();
    LitStringHash(const HashConfig &hashConfig);
    int getLastInsertedIndex() const;
    string toString() const;

    long long hashFunc(string, int);
    long long probingFunc(LitString **&,string, int ,bool);
    void rehash();
    bool insert(string);
    //int searchKey();
    bool remove(string);

    LitString** get(){
        return arr;
    }

    void initialize(){
        myConfig.initSize = oriSizePrincess;
        arr = new LitString*[myConfig.initSize];
        int s = myConfig.initSize;
        for(int i = 0; i < s; i++){
            arr[i] = nullptr;
        }
    }

    HashConfig getConfig(){
        return myConfig;
    }

    void reset(){
        oriSizePrincess = myConfig.initSize;
    }

    void probingAll(node* root);
    void probMinus(node* root);
};

class ReducedConcatStringTree: public ConcatStringTree
{
public:
    ReducedConcatStringTree(const char *s, LitStringHash *litStringHash);
    ReducedConcatStringTree(const char *s, LitStringHash *litStringHash, bool concat);
    ReducedConcatStringTree(ReducedConcatStringTree && other);
    ~ReducedConcatStringTree();

    ReducedConcatStringTree concat(const ReducedConcatStringTree &otherS) const;

private:
    LitStringHash * litStringHash;
    bool isConcat = false;
};

#endif // __CONCAT_STRING_TREE_H__