#include "ConcatStringList.h"
#include <iostream>

void tc4() {
    cout << endl;
    ConcatStringList* s0 = new ConcatStringList("XYZ");
    cout << "s0: " << s0->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size()<<endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    for(int i = 0; i < ConcatStringList::refList.size(); i++){
        cout << ConcatStringList::refList.refCountAt(i) << " ";
    }
 
    cout << endl;
    ConcatStringList* s1 = new ConcatStringList("ABC");
    cout << "s1: " << s1->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    for(int i = 0; i < ConcatStringList::refList.size(); i++){
        cout << ConcatStringList::refList.refCountAt(i) << " ";
    }
 
    cout << endl;
    ConcatStringList* s2 = new ConcatStringList("DEF");
    cout << "s2: " << s2->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    for(int i = 0; i < ConcatStringList::refList.size(); i++){
        cout << ConcatStringList::refList.refCountAt(i) << " ";
    } 

    cout << endl;
    ConcatStringList* s3 = new ConcatStringList("GHI");
    cout << "s3: " << s3->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    for(int i = 0; i < ConcatStringList::refList.size(); i++){
        cout << ConcatStringList::refList.refCountAt(i) << " ";
    }
 
    cout << endl;
    ConcatStringList* s4 = new ConcatStringList(s1->concat(*s2));
    cout << "s4: " << s4->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    for(int i = 0; i < ConcatStringList::refList.size(); i++){
        cout << ConcatStringList::refList.refCountAt(i) << " ";
    }
 
    cout << endl;
    ConcatStringList* s5 = new ConcatStringList(s4->reverse().concat(*s3));
    cout << "s5: " << s5->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    for(int i = 0; i < ConcatStringList::refList.size(); i++){
        cout << ConcatStringList::refList.refCountAt(i) << " ";
    }
 
    cout << endl;
    ConcatStringList* s6 = new ConcatStringList(s5->reverse().reverse());
    cout << "s6: " << s6->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    for(int i = 0; i < ConcatStringList::refList.size(); i++){
        cout << ConcatStringList::refList.refCountAt(i) << " ";
    }
 
    cout << endl;
    ConcatStringList* s7 = new ConcatStringList(s5->subString(1,8));
    cout << "s7: " << s7->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    for(int i = 0; i < ConcatStringList::refList.size(); i++){
        cout << ConcatStringList::refList.refCountAt(i) << " ";
    }
 
    cout << endl;
    ConcatStringList* s8 = new ConcatStringList(s5->subString(1, 8).subString(1,5).subString(2,3));
    cout << "s8: " << s8->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    for(int i = 0; i < ConcatStringList::refList.size(); i++){
        cout << ConcatStringList::refList.refCountAt(i) << " ";
    }

    cout << endl;
    ConcatStringList* s9 = new ConcatStringList(s6->concat(s5->reverse().subString(4,5)).reverse());
    cout << "s9: " << s9->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    for(int i = 0; i < ConcatStringList::refList.size(); i++){
        cout << ConcatStringList::refList.refCountAt(i) << " ";
    }

    cout << endl;
    ConcatStringList* s10 = new ConcatStringList(s0->reverse().concat((s0->reverse().concat(s0->reverse()).reverse())));
    cout << "s10: " << s10->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    for(int i = 0; i < ConcatStringList::refList.size(); i++){
        cout << ConcatStringList::refList.refCountAt(i) << " ";
    }
 
 
    cout << "---After deleting s0---" << endl;
    delete s0;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    for(int i = 0; i < ConcatStringList::refList.size(); i++){
        cout << ConcatStringList::refList.refCountAt(i) << " ";
    }
 
    cout << endl;
    cout << "---After deleting s1---" << endl;
    delete s1;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    for(int i = 0; i < ConcatStringList::refList.size(); i++){
        cout << ConcatStringList::refList.refCountAt(i) << " ";
    }
 
    cout << endl;
    cout << "---After deleting s3---" << endl;
    delete s3;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    cout << "---After deleting s2---" << endl;
    delete s2;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    cout << "---After deleting s4---" << endl;
    delete s4;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    cout << "---After deleting s5---" << endl;
    delete s5;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    cout << "---After deleting s6---" << endl;
    delete s6;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    cout << "---After deleting s7---" << endl;
    delete s7;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    cout << "---After deleting s8---" << endl;
    delete s8;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    cout << "---After deleting s9-- -" << endl;
    delete s9;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    cout << "---After deleting s10---" << endl;
    delete s10;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    
}

void tc1() {
    ConcatStringList * s1 = new ConcatStringList("Hello");
    ConcatStringList * s2 = new ConcatStringList("_world");
    ConcatStringList * s3 = new ConcatStringList(s1->concat(*s2));

    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s1---" << endl;
    delete s1;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s3---" << endl;
    delete s3;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s2---" << endl;
    delete s2;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
}

void tc2() {
    ConcatStringList s1("Hello,_world");
    // test length
    cout << "s1's length: " << s1.length() << endl;
    // test get
    cout << "char at index 2: " << s1.get(2) << endl;
    try {
        cout << "char at index 22: " << s1.get(22) << endl;
    }
    catch (out_of_range & ofr) {
        cout << "Exception out_of_range: " << ofr.what() << endl;
    }
    // test indexOf
    cout << "in s1, index of 'o': " << s1.indexOf('o') << endl;
    cout << "in s1, index of 'a': " << s1.indexOf('a') << endl;
    // test toString
    cout << "s1 toString: " << s1.toString() << endl;
}

void tc3() {
    ConcatStringList s1("Hello,");
    ConcatStringList s2("_this_is");
    ConcatStringList s3("_an_assignment");

    // test concat
    ConcatStringList s4 = s1.concat(s2);
    cout << "s4: " << s4.toString() << endl;

    ConcatStringList s5 = s1.concat(s2).concat(s3);
    cout << "s5: " << s5.toString() << endl;

    // test subString
    ConcatStringList s6 = s5.subString(5, 15);
    cout << "s6: " << s6.toString() << endl;
    
    // test reverse
    ConcatStringList s7 = s5.reverse();
    cout << "s7: " << s7.toString() << endl;
}

void tc47() {
    cout << endl;
    ConcatStringList* s0 = new ConcatStringList("0123456789");
    cout << "s0: " << s0->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    int sum = 0;
    for (int i = 9; i >= 0; i--) {
        sum += s0->indexOf((char)'0' + i);
    }
    cout << "SUM = " << sum << endl;
 
 
    for (int i = 9; i >= 0; i--) {
        cout << s0->get(i);
    }
    cout << endl;
    cout << endl;
 
 
 
    ConcatStringList* s2 = new ConcatStringList
    (s0->subString(0, 1).concat(
        (s0->subString(1, 2).concat(
            (s0->subString(2, 3).concat(
                (s0->subString(3, 4).concat(
                    (s0->subString(4, 5).concat(
                        (s0->subString(5, 6).concat(
                            (s0->subString(6, 7).concat(
                                (s0->subString(7, 8).concat(
                                    (s0->subString(8, 9).concat(
                                        (s0->subString(9, 10)))
                                        .subString(0, 2)))
                                    .subString(0, 3)))
                                .subString(0, 4)))
                            .subString(0, 5)))
                        .subString(0, 6)))
                    .subString(0, 7)))
                .subString(0, 8)))
            .subString(0, 9)))
        .subString(0, 10));
 
    //Literally s0 == s2 = "0123456789" but take extra effort for no reason
    cout << "s2: " << s2->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    sum = 0;
    for (int i = 9; i >= 0; i--) {
        sum += s2->indexOf((char)'0' + i);
    }
    cout << "SUM = " << sum << endl;
 
 
    for (int i = 9; i >= 0; i--) {
        cout << s2->get(i);
    }
 
    cout << endl;
    cout << "AT 10th index" << s2->indexOf(10) << endl;
 
 
    cout << endl;
    ConcatStringList* s3 = new ConcatStringList(s2->reverse());
    cout << "s3: " << s3->toString() << endl;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    sum = 0;
    for (int i = 9; i >= 0; i--) {
        sum += s3->indexOf((char)'0' + i);
    }
    cout << "SUM = " << sum << endl;
 
 
    for (int i = 9; i >= 0; i--) {
        cout << s3->get(i);
    }
 
    cout << endl;
    cout << endl;
 
    cout << "---After deleting 3---" << endl;
    delete s3;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    cout << endl;
    cout << "---After deleting 0---" << endl;
    delete s0;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    //_CrtDumpMemoryLeaks();
 
    cout << endl;
    cout << "---After deleting s2---" << endl;
    delete s2;
    cout << "refList size: " << ConcatStringList::refList.size() << ", delStrList size: " << ConcatStringList::delStrList.size() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
 
    //_CrtDumpMemoryLeaks();
}

int main()
{
    tc4();
    return 0;
}