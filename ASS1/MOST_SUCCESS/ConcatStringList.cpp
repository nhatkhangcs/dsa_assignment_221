#include "ConcatStringList.h"

bool isReferenceCreated = false;
bool callFromConcat = false;
bool callFromSub = false;
bool callFromRev = false;
bool isDelCreated = false;

int nodeDependencyForRef = 0; // to index the item, preserve for deleting purpose

ConcatStringList::ReferencesList ConcatStringList::refList = ConcatStringList::ReferencesList();
ConcatStringList::DeleteStringList ConcatStringList::delStrList = ConcatStringList::DeleteStringList();

string firstStore;
string optional1;
string optional2;

pALN ConcatStringList::ReferencesList::Refhead;
pALN ConcatStringList::ReferencesList::Reftail;
pDN ConcatStringList::DeleteStringList::Delhead;
pDN ConcatStringList::DeleteStringList::Deltail;

// Sort linked list non-decreasing order
pALN sort_list(pALN head)
{
    CharALNode dumy_node("", nodeDependencyForRef, 0);
    pALN cur_node = head;

    while (cur_node)
    {
        pALN insert_cur_pos = dumy_node.next;
        pALN insert_pre_pos = NULL;

        while (insert_cur_pos)
        {
            if (insert_cur_pos->numOfRef > cur_node->numOfRef)
                break;

            insert_pre_pos = insert_cur_pos;
            insert_cur_pos = insert_cur_pos->next;
        }

        if (!insert_pre_pos)
            insert_pre_pos = &dumy_node;

        pALN temp_node = cur_node->next;

        cur_node->next = insert_pre_pos->next;
        insert_pre_pos->next = cur_node;

        cur_node = temp_node;
    }

    return dumy_node.next;
}

ConcatStringList::ConcatStringList()
{
    head = nullptr;
    tail = nullptr;
    stringLength = 0;
}

ConcatStringList::ConcatStringList(const char *s)
{
    string inp = string(s);
    head = new CharALNode(inp, nodeDependencyForRef, 0);
    tail = head;
    // In case there is only 1 node, then the following line is neccesary
    stringLength = inp.length();

    // Check if refList is created
    if (isReferenceCreated == false)
    {
        refList.addPointer(inp);
        isReferenceCreated = true;
        nodeDependencyForRef++;
    }

    // check if the Node already exist in the refList
    else if (!callFromConcat && !callFromRev && !callFromSub)
    {
        pALN temp = refList.getRefHead();
        optional2 = tail->s;

        bool tailCreated = false;

        while (temp != nullptr)
        {
            if (temp->s == head->s)
            {
                temp->numOfRef++;
                tailCreated = true;
                break;
            }

            temp = temp->next;
        }

        if (tailCreated == false)
        {
            pALN newNode = new CharALNode(optional2, nodeDependencyForRef, 2);
            nodeDependencyForRef++;
            temp = refList.getRefHead();
            refList.changeHead(newNode);
            refList.getRefHead()->next = temp;
        }

        refList.increaseNumOfNode();

        pALN newRefHead = sort_list(refList.getRefHead());
        refList.changeHead(newRefHead);

        pALN connect = refList.getRefHead();
        while (connect->next != nullptr)
            connect = connect->next;
        refList.changeTail(connect);
    }
}

ConcatStringList::~ConcatStringList()
{
    // clear the ConcatList but quite hard;
    // need to append to delList
    pALN check1 = nullptr;
    pALN check2 = nullptr;
    bool checkOK1 = false;
    bool checkOK2 = false;
    if (!isDelCreated)
    {
        delStrList.addPointer(head->s, tail->s, head->idx, tail->idx);
        isDelCreated = true;
        pALN temp = refList.getRefHead();
        bool checkOK1 = false;
        bool checkOK2 = false;
        int t = 0;
        if (head == tail)
        {
            while (temp != nullptr)
            {
                if (temp->idx == head->idx && temp->s == head->s)
                {
                    temp->numOfRef = temp->numOfRef - 2;
                    check1 = temp;
                    delStrList.getDelhead()->totalRef = temp->numOfRef;
                    break;
                }

                temp = temp->next;
            }
        }

        else
        {
            while (temp != nullptr)
            {
                if (temp->idx == head->idx && temp->s == head->s)
                {
                    temp->numOfRef--;
                    t += temp->numOfRef;
                    check1 = temp;
                    checkOK1 = true;
                }
                if (temp->idx == tail->idx && temp->s == tail->s)
                {
                    temp->numOfRef--;
                    t += temp->numOfRef;
                    check2 = temp;
                    checkOK2 = true;
                }
                if (checkOK1 && checkOK2)
                {
                    delStrList.getDelhead()->totalRef = t;
                }

                temp = temp->next;
            }
        }  
    }

    else
    {
        pDN traDel = delStrList.getDelhead();
        while (traDel->next != nullptr)
            traDel = traDel->next;
        traDel->next = new DelNode(head->s, tail->s, head->idx, tail->idx);
        delStrList.changeTail(traDel->next);
        delStrList.increaseSize();
        pALN temp = refList.getRefHead();
        if (head == tail)
        {
            while (temp != nullptr)
            {

                if (temp->idx == head->idx && temp->s == head->s)
                {
                    temp->numOfRef = temp->numOfRef - 2;
                    check1 = temp;
                }
                temp = temp->next;
            }
        }

        else
        {
            while (temp != nullptr)
            {
                if (temp->idx == head->idx && temp->s == head->s)
                {
                    temp->numOfRef--;
                    check1 = temp;
                }
                if (temp->idx == tail->idx && temp->s == tail->s)
                {
                    temp->numOfRef--;
                    check2 = temp;
                }

                temp = temp->next;
            }
        }
    }

    pDN traDel = delStrList.getDelhead();
    while (traDel != nullptr)
    {
        checkOK1 = false;
        checkOK2 = false;
        pALN temp = refList.getRefHead();
        int t = 0;
        while (temp != nullptr)
        {
            if (traDel->Headidx == traDel->Tailidx && traDel->headString == temp->s && traDel->Headidx == temp->idx)
            {
                traDel->totalRef = temp->numOfRef;
                break;
            }

            else
            {
                if (temp->idx == traDel->Headidx && temp->s == traDel->headString)
                {
                    t += temp->numOfRef;
                    checkOK1 = true;
                }
                if (temp->idx == traDel->Tailidx && temp->s == traDel->tailString)
                {
                    t += temp->numOfRef;
                    checkOK2 = true;
                }
                if (checkOK1 && checkOK2)
                {
                    traDel->totalRef = t;

                    break;
                }
            }
            temp = temp->next;
        }
        traDel = traDel->next;
    }

    pDN r = delStrList.getDelhead();
    while (r != nullptr)
    {
        if (r->totalRef == 0)
        {
            if(r == delStrList.getDelhead()){
                pDN temp = r;
                if(r->next != nullptr){
                    delStrList.changeHead(r->next);
                    r = r->next;
                    delStrList.decreaseSize();
                    delete temp;
                }

                else{
                    delete temp;
                    delStrList.changeHead(nullptr);
                    delStrList.changeTail(nullptr);
                    isDelCreated = false;
                    delStrList.decreaseSize();
                    break;
                }
            }

            else if(r == delStrList.getDeltail()){
                pDN traversal = delStrList.getDelhead();
                while(traversal->next != r) traversal = traversal->next;
                traversal->next = nullptr;
                delStrList.changeTail(traversal);
                delStrList.decreaseSize();
                delete r;
                break;
            }

            else{
                pDN traversal = delStrList.getDelhead();
                while(traversal->next != r) traversal = traversal->next;
                traversal->next = r->next;
                pDN temp = r;
                r = r->next;
                temp->next = nullptr;
                    delStrList.decreaseSize();
                delete temp;
            }
        }
        else
            r = r->next;
    }

    if(delStrList.size() == 0){
        isDelCreated = false;
        delStrList.changeHead(nullptr);
        delStrList.changeTail(nullptr);
    }

    if(check1 != nullptr){
        if (head == tail && check1->numOfRef == 0)
        {
            delete tail;
        }
    }

    else if (check1 != nullptr && check2 != nullptr)
    {
        if (check1->numOfRef == 0)
            delete head;
        if (check2->numOfRef == 0)
            delete tail;
    }

    pALN newRefHead = sort_list(refList.getRefHead());
    refList.changeHead(newRefHead);

    bool doNotSort = true;
    pALN connect = refList.getRefHead();
    connect = refList.getRefHead();
    while (connect->next != nullptr)
    {
        connect = connect->next;
    }
    refList.changeTail(connect);
    while (connect != nullptr)
    {
        if (connect->numOfRef != 0)
        {
            doNotSort = false;
            break;
        }
        connect = connect->next;
    }

    if (doNotSort == false)
    {
        if (refList.getRefHead()->numOfRef == 0)
        {
            while (refList.getRefHead()->numOfRef == 0)
            {
                refList.getRefTail()->next = refList.getRefHead();
                refList.moveRefHead();
                refList.moveRefTail();
                refList.getRefTail()->next = nullptr;
            }
        }
    }

    else
    {
        pALN deleteTime = refList.getRefHead();
        while (deleteTime != nullptr)
        {
            pALN temp = deleteTime;
            deleteTime = deleteTime->next;
            delete temp;
        }
        refList.changeHead(nullptr);
        refList.changeTail(nullptr);
        refList.reset();

        pDN del = delStrList.getDelhead();
        while (del != nullptr)
        {
            pDN tem = del;
            del = del->next;
            delete tem;
        }

        delStrList.changeHead(nullptr);
        delStrList.changeTail(nullptr);
        delStrList.reset();
        refList.changeHead(nullptr);
        refList.changeTail(nullptr);
        refList.reset();
        isReferenceCreated = false;
        isDelCreated = false;
        nodeDependencyForRef = 0;
        callFromConcat = false;
        callFromRev = false;
        callFromSub = false;
    }
}

// get String length in Concat
int ConcatStringList::length() const
{
    return stringLength;
}

char ConcatStringList::get(int index) const
{
    if (index < 0 || index >= toString().length())
        throw out_of_range("Index of string is invalid!");
    pALN temp = head;

    int keepTrack = 0;
    int idx = 0;

    // get the node which contains "from" index
    while (keepTrack < index)
    {
        if (temp->s[idx] == '\0')
        {
            idx = 0;
            temp = temp->next;
        }

        else
        {
            idx++;
            keepTrack++;
        }
    }

    return temp->s[keepTrack];
}

int ConcatStringList::indexOf(char c) const
{
    int idx = 0;
    for (pALN current{this->head}; current != nullptr; current = current->next)
    {
        const auto ind = current->s.find(c);
        if (ind == std::string::npos)
            idx += current->s.length();
        else
        {
            idx += ind;
            return idx;
        }
    }

    return -1;
}

std::string ConcatStringList::toString() const
{
    pALN temp = head;
    string res = "";
    while (temp != tail->next)
    {
        res += temp->s;
        temp = temp->next;
    }
    return res;
}

ConcatStringList ConcatStringList::concat(const ConcatStringList &otherS) const
{
    callFromConcat = true;
    union S
    {
        ConcatStringList newList = ConcatStringList();
        S(){};
        ~S(){};
    } s;

    // connect 2 object
    tail->next = otherS.head;

    // assign head and tail of new object
    s.newList.head = head;
    s.newList.tail = otherS.tail;

    pALN myPtr = refList.getRefHead();

    // traverse through refList to see if there is any increasing in reference
    while (myPtr != nullptr)
    {
        if (myPtr->s == s.newList.head->s && myPtr->idx == s.newList.head->idx)
        {
            myPtr->numOfRef++;
            myPtr = myPtr->next;
        }

        else if (myPtr->s == s.newList.tail->s && myPtr->idx == s.newList.tail->idx)
        {
            myPtr->numOfRef++;
            myPtr = myPtr->next;
        }

        else
            myPtr = myPtr->next;
    }

    // sort refList again
    pALN newRefHead = sort_list(refList.getRefHead());
    refList.changeHead(newRefHead);

    pALN connect = refList.getRefHead();
    while (connect->next != nullptr)
        connect = connect->next;
    refList.changeTail(connect);
    if (refList.getRefHead()->numOfRef == 0)
        {
            while (refList.getRefHead()->numOfRef == 0)
            {
                refList.getRefTail()->next = refList.getRefHead();
                refList.moveRefHead();
                refList.moveRefTail();
                refList.getRefTail()->next = nullptr;
            }
        }
    callFromConcat = false;

    // calculate string length
    int idx = 0;
    pALN temp = head;
    s.newList.stringLength = 0;
    while (temp != nullptr && idx < toString().length())
    {
        if (temp->s[idx] == '\0')
        {
            temp = temp->next;
            idx = 0;
        }
        else
        {
            idx++;
            s.newList.stringLength++;
        }
    }

    return s.newList;
}

ConcatStringList ConcatStringList::subString(int from, int to) const
{
    if (from < 0 || to < 0 || from >= toString().length() || to > toString().length())
        throw out_of_range("Index of string is invalid");
    else if (from >= to)
        throw logic_error("Invalid range");
    union S
    {
        ConcatStringList newList = ConcatStringList();
        S(){};
        ~S(){};
    } s;

    callFromSub = true;

    pALN temp = head;

    int keepTrack = 0;
    int idx = 0;

    // get the node which contains "from" index
    int keep = 0;
    while (keepTrack < from)
    {
        if (temp->s[idx] == '\0')
        {
            idx = 0;
            temp = temp->next;
        }

        else
        {
            idx++;
            keepTrack++;
            keep++;
        }
    }
    nodeDependencyForRef++;
    pALN subList = new CharALNode("", nodeDependencyForRef, 0);

    string t = "";

    // initialize a new "head" for the subString
    while (true)
    {
        if (temp->s[idx] == '\0' || keep == to)
        {
            subList->s = t;
            idx = 0;
            if (keepTrack != keep)
                temp = temp->next;
            break;
        }

        else
        {
            t += temp->s[idx];
            idx++;
            keep++;
        }
    }

    s.newList.head = subList;
    s.newList.tail = s.newList.head;
    t = "";

    // append the rest
    if (keep < to)
    {
        keepTrack = keep;
        while (keepTrack < to)
        {
            if (temp->s[idx] == '\0')
            {
                nodeDependencyForRef++;
                s.newList.tail->next = new CharALNode(t, nodeDependencyForRef, 0);
                s.newList.tail = s.newList.tail->next;
                idx = 0;
                temp = temp->next;

                t = "";
            }

            else
            {
                t += temp->s[idx];
                keepTrack++;
                idx++;

                if (keepTrack == to)
                {
                    nodeDependencyForRef++;
                    s.newList.tail->next = new CharALNode(t, nodeDependencyForRef, 0);
                    s.newList.tail = s.newList.tail->next;
                    break;
                }
            }
        }
    }

    pALN myPtr = refList.getRefHead();
    optional1 = s.newList.head->s;
    optional2 = s.newList.tail->s;

    bool headCreated = false;
    bool tailCreated = false;

    // refList update
    while (myPtr != nullptr)
    {
        if (myPtr->s == s.newList.head->s && myPtr->idx == s.newList.head->idx)
        {
            myPtr->numOfRef++;
            headCreated = true;
        }

        if (myPtr->s == s.newList.tail->s && myPtr->idx == s.newList.tail->idx)
        {
            myPtr->numOfRef++;
            tailCreated = true;
        }

        myPtr = myPtr->next;
    }

    if (headCreated == false)
    {
        int decision;
        if (s.newList.head != s.newList.tail)
            decision = 1;
        else
            decision = 2;
        refList.getRefTail()->next = new CharALNode(optional1, s.newList.head->idx, decision);

        refList.moveRefTail();
    }

    if (tailCreated == false && s.newList.head != s.newList.tail)
    {
        refList.getRefTail()->next = new CharALNode(optional2, s.newList.tail->idx, 1);
        refList.moveRefTail();
    }

    if (s.newList.head == s.newList.tail)
    {
        refList.increaseNumOfNode();
    }

    else
    {
        refList.increaseNumOfNode();
        refList.increaseNumOfNode();
    }

    pALN newRefHead = sort_list(refList.getRefHead());
    refList.changeHead(newRefHead);
    pALN connect = refList.getRefHead();
    while (connect->next != nullptr)
        connect = connect->next;
    refList.changeTail(connect);
    if (refList.getRefHead()->numOfRef == 0)
        {
            while (refList.getRefHead()->numOfRef == 0)
            {
                refList.getRefTail()->next = refList.getRefHead();
                refList.moveRefHead();
                refList.moveRefTail();
                refList.getRefTail()->next = nullptr;
            }
        }


    callFromSub = false;

    // calculate string length
    idx = 0;
    temp = head;
    s.newList.stringLength = 0;
    while (temp != nullptr && idx < toString().length())
    {
        if (temp->s[idx] == '\0')
        {
            temp = temp->next;
            idx = 0;
        }
        else
        {
            idx++;
            s.newList.stringLength++;
        }
    }
    return s.newList;
}

ConcatStringList ConcatStringList::reverse() const
{
    callFromRev = true;
    union S
    {
        ConcatStringList newList = ConcatStringList();
        S(){};
        ~S(){};
    } s;
    int numOfIter = 0;

    string res = "";
    for (int i = int(tail->s.length()) - 1; i >= 0; i--)
        res += tail->s[i];
    nodeDependencyForRef++;
    pALN revList = new CharALNode(res, nodeDependencyForRef, 0);

    s.newList.head = revList;
    s.newList.tail = s.newList.head;
    int num = 1;

    pALN current = head;
    while (current->next != nullptr)
    {
        num++;
        current = current->next;
    }

    // create object that stores reversed string
    pALN prevTail = tail;
    while (numOfIter < num)
    {
        current = head;
        if (prevTail == head)
            break;
        else
        {
            while (current->next != prevTail)
                current = current->next;
            res = "";
            for (int i = int(current->s.length()) - 1; i >= 0; i--)
                res += current->s[i];
            prevTail = current;
            nodeDependencyForRef++;
            s.newList.tail->next = new CharALNode(res, nodeDependencyForRef, 0);
            s.newList.tail = s.newList.tail->next;
            numOfIter++;
        }
    }

    pALN myPtr = refList.getRefHead();

    // cout << s.newList.head->s << " " << s.newList.tail->s << '\n';
    bool headCreated = false;
    bool tailCreated = false;

    // update refList
    while (myPtr != nullptr)
    {
        if (myPtr->s == s.newList.head->s && myPtr->idx == s.newList.head->idx)
        {
            myPtr->numOfRef++;
            headCreated = true;
        }

        if (myPtr->s == s.newList.tail->s && myPtr->idx == s.newList.tail->idx)
        {
            myPtr->numOfRef++;
            tailCreated = true;
        }

        myPtr = myPtr->next;
    }

    optional1 = s.newList.head->s;
    optional2 = s.newList.tail->s;

    if (headCreated == false)
    {
        int decision;
        if (s.newList.head != s.newList.tail)
            decision = 1;
        else
            decision = 2;
        refList.getRefTail()->next = new CharALNode(optional1, s.newList.head->idx, decision);
        refList.moveRefTail();
    }

    if (tailCreated == false && s.newList.head != s.newList.tail)
    {
        refList.getRefTail()->next = new CharALNode(optional2, s.newList.tail->idx, 1);
        refList.moveRefTail();
    }

    if (s.newList.head == s.newList.tail)
        refList.increaseNumOfNode();
    else
    {
        refList.increaseNumOfNode();
        refList.increaseNumOfNode();
    }

    pALN newRefHead = sort_list(refList.getRefHead());
    refList.changeHead(newRefHead);

    pALN connect = refList.getRefHead();
    while (connect->next != nullptr)
        connect = connect->next;
    refList.changeTail(connect);
    if (refList.getRefHead()->numOfRef == 0)
        {
            while (refList.getRefHead()->numOfRef == 0)
            {
                refList.getRefTail()->next = refList.getRefHead();
                refList.moveRefHead();
                refList.moveRefTail();
                refList.getRefTail()->next = nullptr;
            }
        }
    callFromRev = false;

    // calculate string length
    int idx = 0;
    pALN temp = head;
    s.newList.stringLength = 0;
    while (temp != nullptr && idx < toString().length())
    {
        if (temp->s[idx] == '\0')
        {
            temp = temp->next;
            idx = 0;
        }

        else
        {
            idx++;
            s.newList.stringLength++;
        }
    }


    return s.newList;
}

ConcatStringList::ReferencesList::ReferencesList()
{
    // initialize refList
    Refhead = nullptr;
    Reftail = nullptr;
    numOfNode = 0;
};

ConcatStringList::ReferencesList::~ReferencesList()
{
    pALN temp = refList.getRefHead();
    while (temp != nullptr)
    {
        pALN del = temp;
        temp = temp->next;
        delete del;
    }
    refList.changeHead(nullptr);
    refList.changeTail(nullptr);
}

int ConcatStringList::ReferencesList::size() const
{
    return numOfNode;
};

int ConcatStringList::ReferencesList::refCountAt(int index) const
{
    if (index < 0 || index >= size())
        throw out_of_range("Index of references list is invalid!");
    pALN temp = refList.getRefHead();
    int idx = 0;
    while (idx < index)
    {
        temp = temp->next;
        idx++;
    }

    return temp->numOfRef;
};

std::string ConcatStringList::ReferencesList::refCountsString() const
{
    string res = "RefCounts[";

    pALN temp = refList.getRefHead();
    if (temp == nullptr || temp->numOfRef == 0)
        return "RefCounts[]";
    while (temp != nullptr)
    {
        if (res[res.length() - 1] == '[')
            res += to_string(temp->numOfRef);
        else
            res += ',' + to_string(temp->numOfRef);
        temp = temp->next;
    }

    return res + ']';
};

ConcatStringList::DeleteStringList::DeleteStringList()
{
    Delhead = nullptr;
    Deltail = Delhead;
};

ConcatStringList::DeleteStringList::~DeleteStringList()
{
    pDN temp = Delhead;
    while (temp != nullptr)
    {
        pDN del = temp;
        temp = temp->next;
        delete del;
    }
    Delhead = nullptr;
    Deltail = nullptr;
};

int ConcatStringList::DeleteStringList::size() const
{
    return numOfNode;
}

string ConcatStringList::DeleteStringList::totalRefCountsString() const
{
    string res = "TotalRefCounts[";
    pDN check = delStrList.getDelhead();
    if (check == nullptr)
        return "TotalRefCounts[]";
    while (check != nullptr)
    {
        if (check->totalRef != 0)
        {
            if (res[res.length() - 1] == '[')
                res += to_string(check->totalRef);
            else
                res += ',' + to_string(check->totalRef);
        }
        check = check->next;
    }

    return res + ']';
}