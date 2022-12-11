#ifndef __CONCAT_STRING_LIST_H__
#define __CONCAT_STRING_LIST_H__

#include "main.h"
using namespace std;

struct CharALNode
{
    string s;
    int numOfRef;
    int idx;
    CharALNode *next;
    CharALNode* prev;

    CharALNode(string s, int idx, int n)
    {
        this->s = s;
        this->idx = idx;
        numOfRef = n;
        next = nullptr;
        prev = nullptr;
    }
};

struct DelNode
{
    string headString;
    string tailString;
    int Headidx;
    int Tailidx;
    int totalRef;
    DelNode *next;

    DelNode(string h, string t, int idxh, int idxt)
    {
        headString = h;
        tailString = t;
        Headidx = idxh;
        Tailidx = idxt;
        totalRef = 0;
        next = nullptr;
    }
};

typedef CharALNode *pALN;
typedef DelNode *pDN;

class ConcatStringList
{
public:
    class ReferencesList;   // forward declaration
    class DeleteStringList; // forward declaration

public:
    static ReferencesList refList;
    static DeleteStringList delStrList;

    // TODO: may provide some attributes

public:
    ConcatStringList(const char *);
    ConcatStringList();
    ~ConcatStringList();
    int length() const;
    char get(int index) const;
    int indexOf(char c) const;
    std::string toString() const;
    ConcatStringList concat(const ConcatStringList &otherS) const;
    ConcatStringList subString(int from, int to) const;
    ConcatStringList reverse() const;

public:
    class ReferencesList
    {
        int numOfNode;
        static pALN Refhead;
        static pALN Reftail;
        friend class ConcatStringList;

    public:
        // TODO: may provide some attributes

        ReferencesList();

        ~ReferencesList();

        void addPointer(string inp)
        {
            if (Refhead == nullptr)
            {
                Refhead = Reftail = new CharALNode(inp, 0, 2);
                numOfNode = 1;
            }
        }

        int getNumOfNode()
        {
            return numOfNode;
        }

        void increaseNumOfNode()
        {
            numOfNode++;
        }

        void decreaseNumOfNode()
        {
            numOfNode--;
        }

        void reset()
        {
            numOfNode = 0;
        }

        pALN getRefHead()
        {
            return Refhead;
        }

        pALN getRefTail()
        {
            return Reftail;
        }

        void moveRefTail()
        {
            Reftail = Reftail->next;
        }

        void moveRefHead()
        {
            Refhead = Refhead->next;
        }

        void changeHead(pALN otherHead)
        {
            Refhead = otherHead;
        }

        void changeTail(pALN otherTail)
        {
            Reftail = otherTail;
        }

        // DEBUG

        int size() const;
        int refCountAt(int index) const;
        std::string refCountsString() const;
    };

    class DeleteStringList
    {
        int numOfNode;
        static pDN Delhead;
        static pDN Deltail;

        friend class ConcatStringList;

    public:
        // TODO: may provide some attributes
        DeleteStringList();
        ~DeleteStringList();

        int size() const;

        std::string totalRefCountsString() const;

        pDN getDelhead()
        {
            return Delhead;
        }

        pDN getDeltail()
        {
            return Deltail;
        }

        void changeTail(pDN otherTail)
        {
            Deltail = otherTail;
        }

        void changeHead(pDN otherHead)
        {
            Delhead = otherHead;
        }

        void increaseSize()
        {
            numOfNode++;
        }

        void decreaseSize()
        {
            numOfNode--;
        }

        void reset()
        {
            numOfNode = 0;
        }

        void addPointer(string h, string t, int hidx, int tidx)
        {
            Delhead = new DelNode(h, t, hidx, tidx);
            Deltail = Delhead;
            numOfNode = 1;
        }
    };

private:
    pALN head;
    pALN tail;
    int stringLength;
};

#endif // __CONCAT_STRING_LIST_H__