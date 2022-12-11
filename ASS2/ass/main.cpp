#include "ConcatStringTree.h"

void tc1(){
    ConcatStringTree* s1 = new ConcatStringTree("Hello");
    ConcatStringTree* s2 = new ConcatStringTree("_,t");
    ConcatStringTree* s3 = new ConcatStringTree("his_is");
    ConcatStringTree* s4 = new ConcatStringTree("_an");
    ConcatStringTree* s5 = new ConcatStringTree(s1->concat(*s2));
    ConcatStringTree* s6 = new ConcatStringTree(s1->concat(*s3));
    ConcatStringTree* s7 = new ConcatStringTree(s1->concat(*s4));
    ConcatStringTree* s9 = new ConcatStringTree(s5->concat(*s3));
    ConcatStringTree* s10 = new ConcatStringTree(s6->reverse());
    cout << s5->length() << endl;
    cout << s6->length() << endl;
    cout << s5->toString() << '\n'  ;
    cout << s6->toString() << '\n';
    cout << s5->getParTreeSize("l") << '\n';
    try {
        cout << "char at index 14: " << s5->get(14) << endl;
    }
    catch (out_of_range & ofr) {
        cout << "Exception out_of_range: " << ofr.what() << endl;
    }
    try {
        cout << "char at index 1: " << s6->get(1) << endl;
    }
    catch (out_of_range & ofr) {
        cout << "Exception out_of_range: " << ofr.what() << endl;
    }
    cout << s5->indexOf('i')<<endl;
    cout << s6->indexOf('i')<<endl;
    cout << s5->toStringPreOrder() <<  endl;
    cout << s5->toString()<<endl;
    cout << s6->toString()<<endl;

    delete s10;
    delete s9;
    delete s7;
    delete s6;
    delete s5;
    delete s4;
    delete s3;
    delete s2;
    delete s1;
}

void tc2(){
    ConcatStringTree t1("Hello");
    ConcatStringTree t2("hrhsdtn");
    ConcatStringTree t3("nrnzdn");
    ConcatStringTree t4 = t1.concat(t2);
        ConcatStringTree t5 = t3.concat(t4);
    cout << t4.toStringPreOrder() << endl;
    cout << t4.toString();
    ConcatStringTree t6 = t5.reverse();
    ConcatStringTree t7 = t6.subString(4, 9);
}

void tc6(){
    ConcatStringTree *t1 = new ConcatStringTree("Doraemon,");
    ConcatStringTree *t2 = new ConcatStringTree("Luke,");

    ConcatStringTree *s1 =  new ConcatStringTree(t1->concat(*t2));
    delete t1;
    delete t2;
    cout << s1->toString();
    delete s1;
}

void tc7(){
    ConcatStringTree *t1 = new ConcatStringTree("Doraemon,");
    ConcatStringTree *t2 = new ConcatStringTree("Luke,");
    ConcatStringTree *t3 = new ConcatStringTree("Jerry,");
    ConcatStringTree *t4 = new ConcatStringTree("Than Don Dat Viet");

    ConcatStringTree s1 = t1->concat(*t4).concat(*t3).concat(*t2);
    delete t1;
    delete t3;

    cout << s1.getParTreeSize("llr") << endl;
    cout << s1.getParTreeSize("lr") << endl;
    cout << s1.getParTreeSize("lll") << endl;
    delete t2;
    delete t4;
}

void tc8(){
    ConcatStringTree *t1 = new ConcatStringTree("Hello");
    ConcatStringTree *t2 = new ConcatStringTree(",_t");
    ConcatStringTree *t3 = new ConcatStringTree("his_is");
    ConcatStringTree *t4 = new ConcatStringTree("_an");

    ConcatStringTree s1 = t1->concat(*t2).concat(*t3);

    delete t1;
    
    delete t2;
    delete t3;
    delete t4;

    
    ConcatStringTree *t5 = new ConcatStringTree("_assign");
    ConcatStringTree *t6 = new ConcatStringTree("ment.");
    ConcatStringTree s2 = t5->concat(*t6);

    delete t5; 
    delete t6;

    
    ConcatStringTree s3 = s1.concat(s2).reverse().subString(2, 5);
    cout << s3.reverse().toStringPreOrder() << endl;
    cout << s3.reverse().toString() << endl;
    
    cout << s3.subString(1,5).toStringPreOrder() << endl;
    cout << s3.subString(3,10).toStringPreOrder() << endl;
    cout << s3.subString(5,15).toStringPreOrder() << endl;

    cout << s3.subString(1,5).reverse().toStringPreOrder() << endl;
    cout << s3.subString(3,10).reverse().toStringPreOrder() << endl;
    cout << s3.subString(5,15).reverse().toStringPreOrder() << endl;

    cout << s3.getParTreeStringPreOrder("llr") << endl;
    cout << s3.getParTreeSize("llr") << endl;

    cout << s3.getParTreeStringPreOrder("rl") << endl;
    cout << s3.getParTreeSize("rl") << endl; 
}

void tc9(){
    ConcatStringTree *t1 = new ConcatStringTree("Doraemon,");
    ConcatStringTree *t2 = new ConcatStringTree("Luke,");
    ConcatStringTree *t3 = new ConcatStringTree("Jerry,");
    ConcatStringTree *t4 = new ConcatStringTree("Than Don Dat Viet");
    ConcatStringTree* s0 = new ConcatStringTree(t1->concat(*t4));
    ConcatStringTree s1 = s0->concat(*t3);
    ConcatStringTree s2 = s1.concat(*t2);

    delete t1;
    delete t3;
    delete s0;
    cout << s1.getParTreeStringPreOrder("ll") << endl;
    delete t2;
    delete t4;
}

void tc10(){
    HashConfig hashConfig(
        2,
        0.5,
        0.5,
        0.75,
        2,
        4);
    LitStringHash *litStringHash = new LitStringHash(hashConfig);
    ReducedConcatStringTree *t1 = new ReducedConcatStringTree("Hello", litStringHash);
    ReducedConcatStringTree *t2 = new ReducedConcatStringTree(",_t", litStringHash);

    delete t1;
    delete t2;
    ReducedConcatStringTree *t3 = new ReducedConcatStringTree("Hello", litStringHash);
    cout << litStringHash->toString() << endl;
    
    delete t3;
    delete litStringHash;
}

void tc11(){
    HashConfig hashConfig(11,0.901578,0.606372,0.713767,1.62496,4);
        LitStringHash litStringHash(hashConfig);

        ReducedConcatStringTree s1("6BZRfvt3GfPwQi9MC", &litStringHash);
        ReducedConcatStringTree s2("11", &litStringHash);
        ReducedConcatStringTree s3("vKmGhiG", &litStringHash);

        cout << litStringHash.toString() << endl;
        cout << litStringHash.getLastInsertedIndex() << endl;
}

void tc16(){
    ConcatStringTree *t1 = new ConcatStringTree("Hello");
    ConcatStringTree *t2 = new ConcatStringTree(",_t");
    ConcatStringTree *t3 = new ConcatStringTree("his_is");
    ConcatStringTree *t4 = new ConcatStringTree("_an");

    //ConcatStringTree s1 = t1->concat(*t2).concat(*t3).concat(*t4);
    ConcatStringTree * v1 = new ConcatStringTree( t1->concat(*t2));
    ConcatStringTree s1 = v1->concat(*t3);
    delete v1;

    delete t1;
    delete t2;
    delete t3;
    delete t4;

    ConcatStringTree *t5 = new ConcatStringTree("_assign");
    ConcatStringTree *t6 = new ConcatStringTree("ment.");
    ConcatStringTree s2 = t5->concat(*t6);

    delete t5; delete t6;
    ConcatStringTree s3 = s1.concat(s2);

    cout << s3.reverse().toStringPreOrder() << endl;
    cout << s3.reverse().toString() << endl;

    cout << s3.subString(1,5).toStringPreOrder() << endl;
    cout << s3.subString(3,10).toStringPreOrder() << endl;
    cout << s3.subString(5,15).toStringPreOrder() << endl;

    cout << s3.subString(1,5).reverse().toStringPreOrder() << endl;
    cout << s3.subString(3,10).reverse().toStringPreOrder() << endl;
    cout << s3.subString(5,15).reverse().toStringPreOrder() << endl;

    cout << s3.getParTreeStringPreOrder("llr") << endl;
    cout << s3.getParTreeSize("llr") << endl;

    cout << s3.getParTreeStringPreOrder("rl") << endl;
    cout << s3.getParTreeSize("rl") << endl; 
}

void tc351() {
 
    HashConfig hashConfig(
        2,
        0.5,
        0.5,
        0.75,
        2.0,
        4
    );
    LitStringHash* litStringHash = new LitStringHash(hashConfig);
    ReducedConcatStringTree* s1 = new ReducedConcatStringTree("a", litStringHash);
    ReducedConcatStringTree* s2 = new ReducedConcatStringTree("b", litStringHash);
    ReducedConcatStringTree* s3 = new ReducedConcatStringTree("b", litStringHash);
    ReducedConcatStringTree* s4 = new ReducedConcatStringTree("c", litStringHash);
 
    ReducedConcatStringTree* s5 = new ReducedConcatStringTree(s1->concat(*s2));
    cout << litStringHash->getLastInsertedIndex() << endl;
    cout << litStringHash->toString() << endl;
 
    ReducedConcatStringTree* s6 = new ReducedConcatStringTree(s3->concat(*s4));
    cout << litStringHash->getLastInsertedIndex() << endl;
    cout << litStringHash->toString() << endl;
 
    ReducedConcatStringTree* s7 = new ReducedConcatStringTree(s5->concat(*s6));
    cout << litStringHash->getLastInsertedIndex() << endl;
    cout << litStringHash->toString() << endl;
 
 
    cout << "s7 = " << s7->getParTreeSize("") << endl;
    cout << "s5 = " << s7->getParTreeSize("l") << endl;
    cout << "s1 = " << s7->getParTreeSize("ll") << endl;
    cout << "s2 = " << s7->getParTreeSize("lr") << endl;
    cout << "s6 = " << s7->getParTreeSize("r") << endl;
    cout << "s3 = " << s7->getParTreeSize("rl") << endl;
    cout << "s4 = " << s7->getParTreeSize("rr") << endl;
 
 
    cout << "s7 = " << s7->getParTreeStringPreOrder("") << endl;
    cout << "s5 = " << s7->getParTreeStringPreOrder("l") << endl;
    cout << "s1 = " << s7->getParTreeStringPreOrder("ll") << endl;
    cout << "s2 = " << s7->getParTreeStringPreOrder("lr") << endl;
    cout << "s6 = " << s7->getParTreeStringPreOrder("r") << endl;
    cout << "s3 = " << s7->getParTreeStringPreOrder("rl") << endl;
    cout << "s4 = " << s7->getParTreeStringPreOrder("rr") << endl;
 
 
    delete s4;
    cout << "DELETEING s4\n";
    cout << litStringHash->toString() << endl;
 
    cout << "s7 = " << s7->getParTreeStringPreOrder("") << endl;
    cout << "s5 = " << s7->getParTreeStringPreOrder("l") << endl;
    cout << "s1 = " << s7->getParTreeStringPreOrder("ll") << endl;
    cout << "s2 = " << s7->getParTreeStringPreOrder("lr") << endl;
    cout << "s6 = " << s7->getParTreeStringPreOrder("r") << endl;
    cout << "s3 = " << s7->getParTreeStringPreOrder("rl") << endl;
    cout << "s4 = " << s7->getParTreeStringPreOrder("rr") << endl;
 
    delete s1;
 
    cout << "DELETEING s1\n";
    cout << litStringHash->toString() << endl;
 
    cout << "s7 = " << s7->getParTreeStringPreOrder("") << endl;
    cout << "s5 = " << s7->getParTreeStringPreOrder("l") << endl;
    cout << "s1 = " << s7->getParTreeStringPreOrder("ll") << endl;
    cout << "s2 = " << s7->getParTreeStringPreOrder("lr") << endl;
    cout << "s6 = " << s7->getParTreeStringPreOrder("r") << endl;
    cout << "s3 = " << s7->getParTreeStringPreOrder("rl") << endl;
    cout << "s4 = " << s7->getParTreeStringPreOrder("rr") << endl;
 
    delete s2;
 
    cout << "DELETEING s2\n";
    cout << litStringHash->toString() << endl;
 
    cout << "s7 = " << s7->getParTreeStringPreOrder("") << endl;
    cout << "s5 = " << s7->getParTreeStringPreOrder("l") << endl;
    cout << "s1 = " << s7->getParTreeStringPreOrder("ll") << endl;
    cout << "s2 = " << s7->getParTreeStringPreOrder("lr") << endl;
    cout << "s6 = " << s7->getParTreeStringPreOrder("r") << endl;
    cout << "s3 = " << s7->getParTreeStringPreOrder("rl") << endl;
    cout << "s4 = " << s7->getParTreeStringPreOrder("rr") << endl;
 
    delete s3;
 
    cout << "DELETEING s3\n";
    cout << litStringHash->toString() << endl;
 
    cout << "s7 = " << s7->getParTreeStringPreOrder("") << endl;
    cout << "s5 = " << s7->getParTreeStringPreOrder("l") << endl;
    cout << "s1 = " << s7->getParTreeStringPreOrder("ll") << endl;
    cout << "s2 = " << s7->getParTreeStringPreOrder("lr") << endl;
    cout << "s6 = " << s7->getParTreeStringPreOrder("r") << endl;
    cout << "s3 = " << s7->getParTreeStringPreOrder("rl") << endl;
    cout << "s4 = " << s7->getParTreeStringPreOrder("rr") << endl;
 
    delete s5;
 
    cout << "DELETEING s5\n";
    cout << litStringHash->toString() << endl;
 
    cout << "s7 = " << s7->getParTreeStringPreOrder("") << endl;
    cout << "s5 = " << s7->getParTreeStringPreOrder("l") << endl;
    cout << "s1 = " << s7->getParTreeStringPreOrder("ll") << endl;
    cout << "s2 = " << s7->getParTreeStringPreOrder("lr") << endl;
    cout << "s6 = " << s7->getParTreeStringPreOrder("r") << endl;
    cout << "s3 = " << s7->getParTreeStringPreOrder("rl") << endl;
    cout << "s4 = " << s7->getParTreeStringPreOrder("rr") << endl;
 
    delete s6;
 
    cout << "DELETEING s6\n";
    cout << litStringHash->toString() << endl;
 
    cout << "s7 = " << s7->getParTreeStringPreOrder("") << endl;
    cout << "s5 = " << s7->getParTreeStringPreOrder("l") << endl;
    cout << "s1 = " << s7->getParTreeStringPreOrder("ll") << endl;
    cout << "s2 = " << s7->getParTreeStringPreOrder("lr") << endl;
    cout << "s6 = " << s7->getParTreeStringPreOrder("r") << endl;
    cout << "s3 = " << s7->getParTreeStringPreOrder("rl") << endl;
    cout << "s4 = " << s7->getParTreeStringPreOrder("rr") << endl;
 
    delete s7;
    cout << litStringHash->toString() << endl;
 
    delete litStringHash;
}

void tc200(){

    HashConfig h = HashConfig(9, 0.738121, 0.74752, 0.745705, 1.56618, 7);
	LitStringHash* lsh = new LitStringHash(h);

	ReducedConcatStringTree* r0 = new ReducedConcatStringTree("8tXNY6", lsh);
	ReducedConcatStringTree* r1 = new ReducedConcatStringTree("zmJTUgylXufHci5qO", lsh);
	ReducedConcatStringTree* r2 = new ReducedConcatStringTree("vOiC3PK", lsh);
	ReducedConcatStringTree* r3 = new ReducedConcatStringTree("Znvo", lsh);
	ReducedConcatStringTree* r4 = new ReducedConcatStringTree("2p41S", lsh);
	ReducedConcatStringTree* r5 = new ReducedConcatStringTree("1zDn1LyRJvlAH6PyYn", lsh);
	ReducedConcatStringTree* r6 = new ReducedConcatStringTree("WvOK", lsh);
	ReducedConcatStringTree* r7 = new ReducedConcatStringTree("Bp1mVx5eMYzTU6", lsh);
	ReducedConcatStringTree* r8 = new ReducedConcatStringTree("K", lsh);
	ReducedConcatStringTree* r9 = new ReducedConcatStringTree("IeyRAEVM7Wv3k3LI", lsh);

	ReducedConcatStringTree* r10 = new ReducedConcatStringTree("xWTALZbWJup6glGxKHAu", lsh);
	cout << lsh->toString() << endl;
	cout << lsh->getLastInsertedIndex() << endl;

	ReducedConcatStringTree* r11 = new ReducedConcatStringTree("q0Swy1SoGaS24Tr", lsh);
	cout << lsh->toString() << endl;
	cout << lsh->getLastInsertedIndex() << endl;

	delete r0;
	delete r1;
	delete r2;
	delete r3;
	delete r4;
	delete r5;
	delete r6;
	delete r7;
	delete r8;
	delete r9;
	delete r10;
    delete r11;
	delete lsh;
}

void tc201(){
    ConcatStringTree *t1 = new ConcatStringTree("Doraemon,");
    ConcatStringTree *t2 = new ConcatStringTree("Luke,");
    ConcatStringTree *t3 = new ConcatStringTree("Doraemon,");
    ConcatStringTree *t4 = new ConcatStringTree("Luke,");
    ConcatStringTree *t5 = new ConcatStringTree("Doraemon,");
    ConcatStringTree *t6 = new ConcatStringTree("Luke,");
    ConcatStringTree *t7 = new ConcatStringTree(t2->concat(*t1));
    ConcatStringTree *t8 = new ConcatStringTree(t3->concat(*t1));
    ConcatStringTree *t9 = new ConcatStringTree(t4->concat(*t1));
    ConcatStringTree *t10 = new ConcatStringTree(t5->concat(*t1));
    ConcatStringTree *t11 = new ConcatStringTree(t6->concat(*t1));
    delete t1;
    delete t2;
    delete t3;
    delete t4;
    delete t5;
    delete t6;
    delete t7;
    delete t8;
    delete t9;
    delete t10;
    delete t11;
}

void tc353() {
 
    ConcatStringTree* s1 = new ConcatStringTree("a");
    ConcatStringTree* s2 = new ConcatStringTree("b");
    ConcatStringTree* s4 = new ConcatStringTree("c");
 
 
    ConcatStringTree* s5 = new ConcatStringTree(s1->concat(*s2));
 
    ConcatStringTree* s6 = new ConcatStringTree(s2->concat(*s4));
 
    ConcatStringTree* s7 = new ConcatStringTree(s5->concat(*s6));
 
 
    cout << "s7 = " << s7->getParTreeSize("") << endl;
    cout << "s5 = " << s7->getParTreeSize("l") << endl;
    cout << "s1 = " << s7->getParTreeSize("ll") << endl;
    cout << "s2 = " << s7->getParTreeSize("lr") << endl;
    cout << "s6 = " << s7->getParTreeSize("r") << endl;
    cout << "s2 = " << s7->getParTreeSize("rl") << endl;
    cout << "s4 = " << s7->getParTreeSize("rr") << endl;
 
 
    cout << "s7 = " << s7->getParTreeStringPreOrder("") << endl;
    cout << "s5 = " << s7->getParTreeStringPreOrder("l") << endl;
    cout << "s1 = " << s7->getParTreeStringPreOrder("ll") << endl;
    cout << "s2 = " << s7->getParTreeStringPreOrder("lr") << endl;
    cout << "s6 = " << s7->getParTreeStringPreOrder("r") << endl;
    cout << "s2 = " << s7->getParTreeStringPreOrder("rl") << endl;
    cout << "s4 = " << s7->getParTreeStringPreOrder("rr") << endl;
 
 
    delete s4;
    cout << "DELETEING s4\n";
 
    cout << "s7 = " << s7->getParTreeStringPreOrder("") << endl;
    cout << "s5 = " << s7->getParTreeStringPreOrder("l") << endl;
    cout << "s1 = " << s7->getParTreeStringPreOrder("ll") << endl;
    cout << "s2 = " << s7->getParTreeStringPreOrder("lr") << endl;
    cout << "s6 = " << s7->getParTreeStringPreOrder("r") << endl;
    cout << "s2 = " << s7->getParTreeStringPreOrder("rl") << endl;
    cout << "s4 = " << s7->getParTreeStringPreOrder("rr") << endl;
 
 
    delete s2;
 
    cout << "DELETEING s2\n";
 
    cout << "s7 = " << s7->getParTreeStringPreOrder("") << endl;
    cout << "s5 = " << s7->getParTreeStringPreOrder("l") << endl;
    cout << "s1 = " << s7->getParTreeStringPreOrder("ll") << endl;
    cout << "s2 = " << s7->getParTreeStringPreOrder("lr") << endl;
    cout << "s6 = " << s7->getParTreeStringPreOrder("r") << endl;
    cout << "s2 = " << s7->getParTreeStringPreOrder("rl") << endl;
    cout << "s4 = " << s7->getParTreeStringPreOrder("rr") << endl;
 
 
    delete s6;
 
    cout << "DELETEING s6\n";
 
    cout << "s7 = " << s7->getParTreeStringPreOrder("") << endl;
    cout << "s5 = " << s7->getParTreeStringPreOrder("l") << endl;
    cout << "s1 = " << s7->getParTreeStringPreOrder("ll") << endl;
    cout << "s2 = " << s7->getParTreeStringPreOrder("lr") << endl;
    cout << "s6 = " << s7->getParTreeStringPreOrder("r") << endl;
    cout << "s2 = " << s7->getParTreeStringPreOrder("rl") << endl;
    cout << "s4 = " << s7->getParTreeStringPreOrder("rr") << endl;
 
    delete s5;
 
    cout << "DELETEING s5\n";
 
    cout << "s7 = " << s7->getParTreeStringPreOrder("") << endl;
    cout << "s5 = " << s7->getParTreeStringPreOrder("l") << endl;
    cout << "s1 = " << s7->getParTreeStringPreOrder("ll") << endl;
    cout << "s2 = " << s7->getParTreeStringPreOrder("lr") << endl;
    cout << "s6 = " << s7->getParTreeStringPreOrder("r") << endl;
    cout << "s2 = " << s7->getParTreeStringPreOrder("rl") << endl;
    cout << "s4 = " << s7->getParTreeStringPreOrder("rr") << endl;
 
 
    delete s1;
 
    cout << "DELETEING s1\n";
 
    cout << "s7 = " << s7->getParTreeStringPreOrder("") << endl;
    cout << "s5 = " << s7->getParTreeStringPreOrder("l") << endl;
    cout << "s1 = " << s7->getParTreeStringPreOrder("ll") << endl;
    cout << "s2 = " << s7->getParTreeStringPreOrder("lr") << endl;
    cout << "s6 = " << s7->getParTreeStringPreOrder("r") << endl;
    cout << "s2 = " << s7->getParTreeStringPreOrder("rl") << endl;
    cout << "s4 = " << s7->getParTreeStringPreOrder("rr") << endl;
 
    delete s7;
    cout << "DELETEING s7\n";
}

void test(){
    ConcatStringTree *t1 = new ConcatStringTree("Doraemon,");
    ConcatStringTree *t2 = new ConcatStringTree("Luke,");
    ConcatStringTree *t3 = new ConcatStringTree("Jerry,");
    ConcatStringTree *t4 = new ConcatStringTree("Than Don Dat Viet");
    cout << t1->get(5) << '\n';
    cout << t2->get(3) << '\n';
    cout << t3->get(3) << '\n';
    cout << t4->get(2) << '\n';  

    ConcatStringTree *t5 = new ConcatStringTree(t1->concat(*t2));
    ConcatStringTree *t6 = new ConcatStringTree(t2->concat(*t4));
    ConcatStringTree *t7 = new ConcatStringTree(t6->concat(*t5));
    ConcatStringTree *t8 = new ConcatStringTree(t7->concat(*t3));

    cout << t5->get(5) << '\n';
    cout << t6->get(3) << '\n';
    cout << t7->get(3) << '\n';
    cout << t8->get(2) << '\n';  
    
    delete t1;
    delete t2;
    delete t3;
    delete t4;
    delete t5;
    delete t6;
    delete t8;
    delete t7;
}

void t3()
{
    // this testcase mainly test the concat function without delete
    ConcatStringTree s1("My");
    ConcatStringTree s2("Name");
    ConcatStringTree s3("Is");
    ConcatStringTree s4("Loc");

    ConcatStringTree s5(s1.concat(s2));
    ConcatStringTree s6(s3.concat(s4));
    ConcatStringTree s7(s5.concat(s6));

    cout << s7.indexOf('L') << endl;

    ConcatStringTree s8(s1.concat(s2).concat(s3).concat(s4));

    ConcatStringTree s9(s1.concat(s2));
    ConcatStringTree s10(s2.concat(s3));
    ConcatStringTree s11(s9.concat(s10));

    ConcatStringTree s12(s1.concat(s2).concat(s3));
    ConcatStringTree s13(s2.concat(s3).concat(s4));
    ConcatStringTree s14(s12.concat(s13));

    cout << "-----------s5-------------" << endl;
    cout << s5.length() << endl;
    cout << s5.get(0) << endl;
    cout << s5.indexOf('M') << endl;
    cout << s5.toStringPreOrder() << endl;
    cout << s5.toString() << endl;
    cout << "-----------s7-------------" << endl;
    cout << s7.length() << endl;
    cout << s7.get(0) << endl;
    cout << s7.indexOf('M') << endl;
    cout << s7.toStringPreOrder() << endl;
    cout << s7.toString() << endl;
    cout << "-----------s8-------------" << endl;
    cout << s8.length() << endl;
    cout << s8.get(0) << endl;
    cout << s8.indexOf('M') << endl;
    cout << s8.toStringPreOrder() << endl;
    cout << s8.toString() << endl;
    cout << "-----------s11-------------" << endl;
    cout << s11.length() << endl;
    cout << s11.get(0) << endl;
    cout << s11.indexOf('M') << endl;
    cout << s11.toStringPreOrder() << endl;
    cout << s11.toString() << endl;
    cout << "-----------s14-------------" << endl;
    cout << s14.length() << endl;
    cout << s14.get(0) << endl;
    cout << s14.indexOf('M') << endl;
    cout << s14.toStringPreOrder() << endl;
    cout << s14.toString() << endl;
    // -----------s5-------------
    // 6
    // M
    // -1
    // ConcatStringTree[(LL=2,L=6,<NULL>);(LL=0,L=2,"My");(LL=0,L=4,"Name")]
    // ConcatStringTree["MyName"]
    // -----------s7-------------
    // 11
    // M
    // -1
    // ConcatStringTree[(LL=6,L=11,<NULL>);(LL=2,L=6,<NULL>);(LL=0,L=2,"My");(LL=0,L=4,"Name");(LL=2,L=5,<NULL>);(LL=0,L=2,"Is");(LL=0,L=3,"Loc")]
    // ConcatStringTree["MyNameIsLoc"]
    // -----------s8-------------
    // 11
    // M
    // -1
    // ConcatStringTree[(LL=8,L=11,<NULL>);(LL=6,L=8,<NULL>);(LL=2,L=6,<NULL>);(LL=0,L=2,"My");(LL=0,L=4,"Name");(LL=0,L=2,"Is");(LL=0,L=3,"Loc")]
    // ConcatStringTree["MyNameIsLoc"]
    // -----------s11-------------
    // 12
    // M
    // -1
    // ConcatStringTree[(LL=6,L=12,<NULL>);(LL=2,L=6,<NULL>);(LL=0,L=2,"My");(LL=0,L=4,"Name");(LL=4,L=6,<NULL>);(LL=0,L=4,"Name");(LL=0,L=2,"Is")]
    // ConcatStringTree["MyNameNameIs"]
    // -----------s14-------------
    // 17
    // M
    // -1
    // ConcatStringTree[(LL=8,L=17,<NULL>);(LL=6,L=8,<NULL>);(LL=2,L=6,<NULL>);(LL=0,L=2,"My");(LL=0,L=4,"Name");(LL=0,L=2,"Is");(LL=6,L=9,<NULL>);(LL=4,L=6,<NULL>);(LL=0,L=4,"Name");(LL=0,L=2,"Is");(LL=0,L=3,"Loc")]
    // ConcatStringTree["MyNameIsNameIsLoc"]
}

void test1()
{
    ConcatStringTree* s0 = new ConcatStringTree("0123456789");
    ConcatStringTree* s1 = new ConcatStringTree("0123456789");
    ConcatStringTree* s2 = new ConcatStringTree("0123456789");
    ConcatStringTree* s3 = new ConcatStringTree("0123456789");
    ConcatStringTree* s4 = new ConcatStringTree("0123456789");
    ConcatStringTree* s5 = new ConcatStringTree("0123456789");
    ConcatStringTree* s6 = new ConcatStringTree("0123456789");
    ConcatStringTree* s7 = new ConcatStringTree("0123456789");

    ConcatStringTree* s8 = new ConcatStringTree(s0->concat(*s1));
    ConcatStringTree* s9 = new ConcatStringTree(s1->concat(*s2));
    ConcatStringTree* s10 = new ConcatStringTree(s2->concat(*s3));
    ConcatStringTree* s11 = new ConcatStringTree(s3->concat(*s4));
    ConcatStringTree* s12 = new ConcatStringTree(s4->concat(*s5));
    ConcatStringTree* s13 = new ConcatStringTree(s5->concat(*s6));
    ConcatStringTree* s14 = new ConcatStringTree(s6->concat(*s7));

    ConcatStringTree* s15 = new ConcatStringTree(s8->concat(*s9));
    ConcatStringTree* s16 = new ConcatStringTree(s9->concat(*s10));
    ConcatStringTree* s17 = new ConcatStringTree(s10->concat(*s11));
    ConcatStringTree* s18 = new ConcatStringTree(s11->concat(*s12));
    ConcatStringTree* s19 = new ConcatStringTree(s12->concat(*s13));
    ConcatStringTree* s20 = new ConcatStringTree(s13->concat(*s14));

    ConcatStringTree* s21 = new ConcatStringTree(s15->concat(*s16));
    ConcatStringTree* s22 = new ConcatStringTree(s16->concat(*s17));
    ConcatStringTree* s23 = new ConcatStringTree(s17->concat(*s18));
    ConcatStringTree* s24 = new ConcatStringTree(s18->concat(*s19));
    ConcatStringTree* s25 = new ConcatStringTree(s19->concat(*s20));

    ConcatStringTree* s26 = new ConcatStringTree(s21->concat(*s22));
    ConcatStringTree* s27 = new ConcatStringTree(s22->concat(*s23));
    ConcatStringTree* s28 = new ConcatStringTree(s23->concat(*s24));
    ConcatStringTree* s29 = new ConcatStringTree(s24->concat(*s25));

    ConcatStringTree* s30 = new ConcatStringTree(s26->concat(*s27));
    ConcatStringTree* s31 = new ConcatStringTree(s27->concat(*s28));
    ConcatStringTree* s32 = new ConcatStringTree(s28->concat(*s29));

    ConcatStringTree* s33 = new ConcatStringTree(s30->concat(*s31));
    ConcatStringTree* s34 = new ConcatStringTree(s31->concat(*s32));

    ConcatStringTree* s35 = new ConcatStringTree(s33->concat(*s34));

    cout << "==================== BEFORE DELETE ====================" << '\n';
    cout << "PreOrder of Parent s0: " << s0->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s1: " << s1->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s2: " << s2->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s3: " << s3->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s4: " << s4->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s5: " << s5->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s6: " << s6->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s7: " << s7->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s8: " << s8->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s9: " << s9->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s10: " << s10->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s11: " << s11->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s12: " << s12->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s13: " << s13->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s14: " << s14->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s15: " << s15->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s16: " << s16->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s17: " << s17->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s18: " << s18->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s19: " << s19->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s20: " << s20->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s21: " << s21->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s22: " << s22->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s23: " << s23->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s24: " << s24->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s25: " << s25->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s26: " << s26->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s27: " << s27->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s28: " << s28->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s29: " << s29->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s30: " << s30->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s31: " << s31->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s32: " << s32->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s33: " << s33->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s34: " << s34->getParTreeStringPreOrder("") << '\n';
    cout << "PreOrder of Parent s35: " << s35->getParTreeStringPreOrder("") << '\n';
    cout << "==================== END ====================" << '\n';

    delete s4;
    delete s5;
    delete s7;
    delete s9;
    delete s13;
    delete s17;
    delete s18;
    delete s21;
    delete s24;
    delete s33;
    delete s34;

    cout << "==================== CALLING s29 ====================" << '\n';
    cout << "Length of s29: " << s29->length() << '\n';
    cout << "String of s29: " << s29->toString() << '\n';
    cout << "PreOrder of s29: " << s29->toStringPreOrder() << '\n';
    cout << "Size of Parent s29: " << s29->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s29: " << s29->getParTreeStringPreOrder("") << '\n';
    delete s29;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s32 ====================" << '\n';
    cout << "Length of s32: " << s32->length() << '\n';
    cout << "String of s32: " << s32->toString() << '\n';
    cout << "PreOrder of s32: " << s32->toStringPreOrder() << '\n';
    cout << "Size of Parent s32: " << s32->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s32: " << s32->getParTreeStringPreOrder("") << '\n';
    delete s32;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s3 ====================" << '\n';
    cout << "Length of s3: " << s3->length() << '\n';
    cout << "String of s3: " << s3->toString() << '\n';
    cout << "PreOrder of s3: " << s3->toStringPreOrder() << '\n';
    cout << "Size of Parent s3: " << s3->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s3: " << s3->getParTreeStringPreOrder("") << '\n';
    delete s3;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s8 ====================" << '\n';
    cout << "Length of s8: " << s8->length() << '\n';
    cout << "String of s8: " << s8->toString() << '\n';
    cout << "PreOrder of s8: " << s8->toStringPreOrder() << '\n';
    cout << "Size of Parent s8: " << s8->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s8: " << s8->getParTreeStringPreOrder("") << '\n';
    delete s8;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s2 ====================" << '\n';
    cout << "Length of s2: " << s2->length() << '\n';
    cout << "String of s2: " << s2->toString() << '\n';
    cout << "PreOrder of s2: " << s2->toStringPreOrder() << '\n';
    cout << "Size of Parent s2: " << s2->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s2: " << s2->getParTreeStringPreOrder("") << '\n';
    delete s2;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s11 ====================" << '\n';
    cout << "Length of s11: " << s11->length() << '\n';
    cout << "String of s11: " << s11->toString() << '\n';
    cout << "PreOrder of s11: " << s11->toStringPreOrder() << '\n';
    cout << "Size of Parent s11: " << s11->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s11: " << s11->getParTreeStringPreOrder("") << '\n';
    delete s11;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s12 ====================" << '\n';
    cout << "Length of s12: " << s12->length() << '\n';
    cout << "String of s12: " << s12->toString() << '\n';
    cout << "PreOrder of s12: " << s12->toStringPreOrder() << '\n';
    cout << "Size of Parent s12: " << s12->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s12: " << s12->getParTreeStringPreOrder("") << '\n';
    delete s12;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s35 ====================" << '\n';
    cout << "Length of s35: " << s35->length() << '\n';
    cout << "String of s35: " << s35->toString() << '\n';
    cout << "PreOrder of s35: " << s35->toStringPreOrder() << '\n';
    cout << "Size of Parent s35: " << s35->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s35: " << s35->getParTreeStringPreOrder("") << '\n';
    delete s35;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s20 ====================" << '\n';
    cout << "Length of s20: " << s20->length() << '\n';
    cout << "String of s20: " << s20->toString() << '\n';
    cout << "PreOrder of s20: " << s20->toStringPreOrder() << '\n';
    cout << "Size of Parent s20: " << s20->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s20: " << s20->getParTreeStringPreOrder("") << '\n';
    delete s20;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s0 ====================" << '\n';
    cout << "Length of s0: " << s0->length() << '\n';
    cout << "String of s0: " << s0->toString() << '\n';
    cout << "PreOrder of s0: " << s0->toStringPreOrder() << '\n';
    cout << "Size of Parent s0: " << s0->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s0: " << s0->getParTreeStringPreOrder("") << '\n';
    delete s0;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s14 ====================" << '\n';
    cout << "Length of s14: " << s14->length() << '\n';
    cout << "String of s14: " << s14->toString() << '\n';
    cout << "PreOrder of s14: " << s14->toStringPreOrder() << '\n';
    cout << "Size of Parent s14: " << s14->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s14: " << s14->getParTreeStringPreOrder("") << '\n';
    delete s14;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s15 ====================" << '\n';
    cout << "Length of s15: " << s15->length() << '\n';
    cout << "String of s15: " << s15->toString() << '\n';
    cout << "PreOrder of s15: " << s15->toStringPreOrder() << '\n';
    cout << "Size of Parent s15: " << s15->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s15: " << s15->getParTreeStringPreOrder("") << '\n';
    delete s15;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s16 ====================" << '\n';
    cout << "Length of s16: " << s16->length() << '\n';
    cout << "String of s16: " << s16->toString() << '\n';
    cout << "PreOrder of s16: " << s16->toStringPreOrder() << '\n';
    cout << "Size of Parent s16: " << s16->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s16: " << s16->getParTreeStringPreOrder("") << '\n';
    delete s16;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s31 ====================" << '\n';
    cout << "Length of s31: " << s31->length() << '\n';
    cout << "String of s31: " << s31->toString() << '\n';
    cout << "PreOrder of s31: " << s31->toStringPreOrder() << '\n';
    cout << "Size of Parent s31: " << s31->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s31: " << s31->getParTreeStringPreOrder("") << '\n';
    delete s31;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s19 ====================" << '\n';
    cout << "Length of s19: " << s19->length() << '\n';
    cout << "String of s19: " << s19->toString() << '\n';
    cout << "PreOrder of s19: " << s19->toStringPreOrder() << '\n';
    cout << "Size of Parent s19: " << s19->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s19: " << s19->getParTreeStringPreOrder("") << '\n';
    delete s19;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s6 ====================" << '\n';
    cout << "Length of s6: " << s6->length() << '\n';
    cout << "String of s6: " << s6->toString() << '\n';
    cout << "PreOrder of s6: " << s6->toStringPreOrder() << '\n';
    cout << "Size of Parent s6: " << s6->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s6: " << s6->getParTreeStringPreOrder("") << '\n';
    delete s6;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s22 ====================" << '\n';
    cout << "Length of s22: " << s22->length() << '\n';
    cout << "String of s22: " << s22->toString() << '\n';
    cout << "PreOrder of s22: " << s22->toStringPreOrder() << '\n';
    cout << "Size of Parent s22: " << s22->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s22: " << s22->getParTreeStringPreOrder("") << '\n';
    delete s22;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s1 ====================" << '\n';
    cout << "Length of s1: " << s1->length() << '\n';
    cout << "String of s1: " << s1->toString() << '\n';
    cout << "PreOrder of s1: " << s1->toStringPreOrder() << '\n';
    cout << "Size of Parent s1: " << s1->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s1: " << s1->getParTreeStringPreOrder("") << '\n';
    delete s1;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s25 ====================" << '\n';
    cout << "Length of s25: " << s25->length() << '\n';
    cout << "String of s25: " << s25->toString() << '\n';
    cout << "PreOrder of s25: " << s25->toStringPreOrder() << '\n';
    cout << "Size of Parent s25: " << s25->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s25: " << s25->getParTreeStringPreOrder("") << '\n';
    delete s25;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s26 ====================" << '\n';
    cout << "Length of s26: " << s26->length() << '\n';
    cout << "String of s26: " << s26->toString() << '\n';
    cout << "PreOrder of s26: " << s26->toStringPreOrder() << '\n';
    cout << "Size of Parent s26: " << s26->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s26: " << s26->getParTreeStringPreOrder("") << '\n';
    delete s26;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s27 ====================" << '\n';
    cout << "Length of s27: " << s27->length() << '\n';
    cout << "String of s27: " << s27->toString() << '\n';
    cout << "PreOrder of s27: " << s27->toStringPreOrder() << '\n';
    cout << "Size of Parent s27: " << s27->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s27: " << s27->getParTreeStringPreOrder("") << '\n';
    delete s27;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s10 ====================" << '\n';
    cout << "Length of s10: " << s10->length() << '\n';
    cout << "String of s10: " << s10->toString() << '\n';
    cout << "PreOrder of s10: " << s10->toStringPreOrder() << '\n';
    cout << "Size of Parent s10: " << s10->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s10: " << s10->getParTreeStringPreOrder("") << '\n';
    delete s10;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s28 ====================" << '\n';
    cout << "Length of s28: " << s28->length() << '\n';
    cout << "String of s28: " << s28->toString() << '\n';
    cout << "PreOrder of s28: " << s28->toStringPreOrder() << '\n';
    cout << "Size of Parent s28: " << s28->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s28: " << s28->getParTreeStringPreOrder("") << '\n';
    delete s28;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s30 ====================" << '\n';
    cout << "Length of s30: " << s30->length() << '\n';
    cout << "String of s30: " << s30->toString() << '\n';
    cout << "PreOrder of s30: " << s30->toStringPreOrder() << '\n';
    cout << "Size of Parent s30: " << s30->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s30: " << s30->getParTreeStringPreOrder("") << '\n';
    delete s30;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';
    cout << "==================== CALLING s23 ====================" << '\n';
    cout << "Length of s23: " << s23->length() << '\n';
    cout << "String of s23: " << s23->toString() << '\n';
    cout << "PreOrder of s23: " << s23->toStringPreOrder() << '\n';
    cout << "Size of Parent s23: " << s23->getParTreeSize("") << '\n';
    cout << "PreOrder of Parent s23: " << s23->getParTreeStringPreOrder("") << '\n';
    delete s23;
    cout << "==================== END CALLING ====================" << '\n';
    cout << '\n';

    /*
==================== BEFORE DELETE ====================
PreOrder of Parent s0: ParentsTree[(id=1);(id=9)]
PreOrder of Parent s1: ParentsTree[(id=9);(id=2);(id=10)]
PreOrder of Parent s2: ParentsTree[(id=10);(id=3);(id=11)]
PreOrder of Parent s3: ParentsTree[(id=11);(id=4);(id=12)]
PreOrder of Parent s4: ParentsTree[(id=12);(id=5);(id=13)]
PreOrder of Parent s5: ParentsTree[(id=13);(id=6);(id=14)]
PreOrder of Parent s6: ParentsTree[(id=14);(id=7);(id=15)]
PreOrder of Parent s7: ParentsTree[(id=8);(id=15)]
PreOrder of Parent s8: ParentsTree[(id=9);(id=16)]
PreOrder of Parent s9: ParentsTree[(id=16);(id=10);(id=17)]
PreOrder of Parent s10: ParentsTree[(id=17);(id=11);(id=18)]
PreOrder of Parent s11: ParentsTree[(id=18);(id=12);(id=19)]
PreOrder of Parent s12: ParentsTree[(id=19);(id=13);(id=20)]
PreOrder of Parent s13: ParentsTree[(id=20);(id=14);(id=21)]
PreOrder of Parent s14: ParentsTree[(id=15);(id=21)]
PreOrder of Parent s15: ParentsTree[(id=16);(id=22)]
PreOrder of Parent s16: ParentsTree[(id=22);(id=17);(id=23)]
PreOrder of Parent s17: ParentsTree[(id=23);(id=18);(id=24)]
PreOrder of Parent s18: ParentsTree[(id=24);(id=19);(id=25)]
PreOrder of Parent s19: ParentsTree[(id=25);(id=20);(id=26)]
PreOrder of Parent s20: ParentsTree[(id=21);(id=26)]
PreOrder of Parent s21: ParentsTree[(id=22);(id=27)]
PreOrder of Parent s22: ParentsTree[(id=27);(id=23);(id=28)]
PreOrder of Parent s23: ParentsTree[(id=28);(id=24);(id=29)]
PreOrder of Parent s24: ParentsTree[(id=29);(id=25);(id=30)]
PreOrder of Parent s25: ParentsTree[(id=26);(id=30)]
PreOrder of Parent s26: ParentsTree[(id=27);(id=31)]
PreOrder of Parent s27: ParentsTree[(id=31);(id=28);(id=32)]
PreOrder of Parent s28: ParentsTree[(id=32);(id=29);(id=33)]
PreOrder of Parent s29: ParentsTree[(id=30);(id=33)]
PreOrder of Parent s30: ParentsTree[(id=31);(id=34)]
PreOrder of Parent s31: ParentsTree[(id=34);(id=32);(id=35)]
PreOrder of Parent s32: ParentsTree[(id=33);(id=35)]
PreOrder of Parent s33: ParentsTree[(id=34);(id=36)]
PreOrder of Parent s34: ParentsTree[(id=35);(id=36)]
PreOrder of Parent s35: ParentsTree[(id=36)]
==================== END ====================
==================== CALLING s29 ====================
Length of s29: 160
String of s29: ConcatStringTree["0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"]
PreOrder of s29: ConcatStringTree[(LL=80,L=160,<NULL>);(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789")]
Size of Parent s29: 2
PreOrder of Parent s29: ParentsTree[(id=30);(id=33)]
==================== END CALLING ====================

==================== CALLING s32 ====================
Length of s32: 320
String of s32: ConcatStringTree["01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"]
PreOrder of s32: ConcatStringTree[(LL=160,L=320,<NULL>);(LL=80,L=160,<NULL>);(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=80,L=160,<NULL>);(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789")]
Size of Parent s32: 2
PreOrder of Parent s32: ParentsTree[(id=33);(id=35)]
==================== END CALLING ====================

==================== CALLING s3 ====================
Length of s3: 10
String of s3: ConcatStringTree["0123456789"]
PreOrder of s3: ConcatStringTree[(LL=0,L=10,"0123456789")]
Size of Parent s3: 3
PreOrder of Parent s3: ParentsTree[(id=11);(id=4);(id=12)]
==================== END CALLING ====================

==================== CALLING s8 ====================
Length of s8: 20
String of s8: ConcatStringTree["01234567890123456789"]
PreOrder of s8: ConcatStringTree[(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789")]
Size of Parent s8: 2
PreOrder of Parent s8: ParentsTree[(id=9);(id=16)]
==================== END CALLING ====================

==================== CALLING s2 ====================
Length of s2: 10
String of s2: ConcatStringTree["0123456789"]
PreOrder of s2: ConcatStringTree[(LL=0,L=10,"0123456789")]
Size of Parent s2: 3
PreOrder of Parent s2: ParentsTree[(id=10);(id=3);(id=11)]
==================== END CALLING ====================

==================== CALLING s11 ====================
Length of s11: 20
String of s11: ConcatStringTree["01234567890123456789"]
PreOrder of s11: ConcatStringTree[(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789")]
Size of Parent s11: 3
PreOrder of Parent s11: ParentsTree[(id=18);(id=12);(id=19)]
==================== END CALLING ====================

==================== CALLING s12 ====================
Length of s12: 20
String of s12: ConcatStringTree["01234567890123456789"]
PreOrder of s12: ConcatStringTree[(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789")]
Size of Parent s12: 3
PreOrder of Parent s12: ParentsTree[(id=19);(id=13);(id=20)]
==================== END CALLING ====================

==================== CALLING s35 ====================
Length of s35: 1280
String of s35: ConcatStringTree["01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"]
PreOrder of s35: ConcatStringTree[(LL=640,L=1280,<NULL>);(LL=320,L=640,<NULL>);(LL=160,L=320,<NULL>);(LL=80,L=160,<NULL>);(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=80,L=160,<NULL>);(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=160,L=320,<NULL>);(LL=80,L=160,<NULL>);(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=80,L=160,<NULL>);(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=320,L=640,<NULL>);(LL=160,L=320,<NULL>);(LL=80,L=160,<NULL>);(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=80,L=160,<NULL>);(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=160,L=320,<NULL>);(LL=80,L=160,<NULL>);(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=80,L=160,<NULL>);(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789")]
Size of Parent s35: 1
PreOrder of Parent s35: ParentsTree[(id=36)]
==================== END CALLING ====================

==================== CALLING s20 ====================
Length of s20: 40
String of s20: ConcatStringTree["0123456789012345678901234567890123456789"]
PreOrder of s20: ConcatStringTree[(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789")]
Size of Parent s20: 2
PreOrder of Parent s20: ParentsTree[(id=21);(id=26)]
==================== END CALLING ====================

==================== CALLING s0 ====================
Length of s0: 10
String of s0: ConcatStringTree["0123456789"]
PreOrder of s0: ConcatStringTree[(LL=0,L=10,"0123456789")]
Size of Parent s0: 2
PreOrder of Parent s0: ParentsTree[(id=1);(id=9)]
==================== END CALLING ====================

==================== CALLING s14 ====================
Length of s14: 20
String of s14: ConcatStringTree["01234567890123456789"]
PreOrder of s14: ConcatStringTree[(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789")]
Size of Parent s14: 2
PreOrder of Parent s14: ParentsTree[(id=15);(id=21)]
==================== END CALLING ====================

==================== CALLING s15 ====================
Length of s15: 40
String of s15: ConcatStringTree["0123456789012345678901234567890123456789"]
PreOrder of s15: ConcatStringTree[(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789")]
Size of Parent s15: 2
PreOrder of Parent s15: ParentsTree[(id=16);(id=22)]
==================== END CALLING ====================

==================== CALLING s16 ====================
Length of s16: 40
String of s16: ConcatStringTree["0123456789012345678901234567890123456789"]
PreOrder of s16: ConcatStringTree[(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789")]
Size of Parent s16: 3
PreOrder of Parent s16: ParentsTree[(id=22);(id=17);(id=23)]
==================== END CALLING ====================

==================== CALLING s31 ====================
Length of s31: 320
String of s31: ConcatStringTree["01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"]
PreOrder of s31: ConcatStringTree[(LL=160,L=320,<NULL>);(LL=80,L=160,<NULL>);(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=80,L=160,<NULL>);(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789")]
Size of Parent s31: 1
PreOrder of Parent s31: ParentsTree[(id=32)]
==================== END CALLING ====================

==================== CALLING s19 ====================
Length of s19: 40
String of s19: ConcatStringTree["0123456789012345678901234567890123456789"]
PreOrder of s19: ConcatStringTree[(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789")]
Size of Parent s19: 3
PreOrder of Parent s19: ParentsTree[(id=25);(id=20);(id=26)]
==================== END CALLING ====================

==================== CALLING s6 ====================
Length of s6: 10
String of s6: ConcatStringTree["0123456789"]
PreOrder of s6: ConcatStringTree[(LL=0,L=10,"0123456789")]
Size of Parent s6: 3
PreOrder of Parent s6: ParentsTree[(id=14);(id=7);(id=15)]
==================== END CALLING ====================

==================== CALLING s22 ====================
Length of s22: 80
String of s22: ConcatStringTree["01234567890123456789012345678901234567890123456789012345678901234567890123456789"]
PreOrder of s22: ConcatStringTree[(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789")]
Size of Parent s22: 3
PreOrder of Parent s22: ParentsTree[(id=27);(id=23);(id=28)]
==================== END CALLING ====================

==================== CALLING s1 ====================
Length of s1: 10
String of s1: ConcatStringTree["0123456789"]
PreOrder of s1: ConcatStringTree[(LL=0,L=10,"0123456789")]
Size of Parent s1: 3
PreOrder of Parent s1: ParentsTree[(id=9);(id=2);(id=10)]
==================== END CALLING ====================

==================== CALLING s25 ====================
Length of s25: 80
String of s25: ConcatStringTree["01234567890123456789012345678901234567890123456789012345678901234567890123456789"]
PreOrder of s25: ConcatStringTree[(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789")]
Size of Parent s25: 1
PreOrder of Parent s25: ParentsTree[(id=26)]
==================== END CALLING ====================

==================== CALLING s26 ====================
Length of s26: 160
String of s26: ConcatStringTree["0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"]
PreOrder of s26: ConcatStringTree[(LL=80,L=160,<NULL>);(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789")]
Size of Parent s26: 2
PreOrder of Parent s26: ParentsTree[(id=27);(id=31)]
==================== END CALLING ====================

==================== CALLING s27 ====================
Length of s27: 160
String of s27: ConcatStringTree["0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"]
PreOrder of s27: ConcatStringTree[(LL=80,L=160,<NULL>);(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789")]
Size of Parent s27: 2
PreOrder of Parent s27: ParentsTree[(id=31);(id=28)]
==================== END CALLING ====================

==================== CALLING s10 ====================
Length of s10: 20
String of s10: ConcatStringTree["01234567890123456789"]
PreOrder of s10: ConcatStringTree[(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789")]
Size of Parent s10: 3
PreOrder of Parent s10: ParentsTree[(id=17);(id=11);(id=18)]
==================== END CALLING ====================

==================== CALLING s28 ====================
Length of s28: 160
String of s28: ConcatStringTree["0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"]
PreOrder of s28: ConcatStringTree[(LL=80,L=160,<NULL>);(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789")]
Size of Parent s28: 1
PreOrder of Parent s28: ParentsTree[(id=29)]
==================== END CALLING ====================

==================== CALLING s30 ====================
Length of s30: 320
String of s30: ConcatStringTree["01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"]
PreOrder of s30: ConcatStringTree[(LL=160,L=320,<NULL>);(LL=80,L=160,<NULL>);(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=80,L=160,<NULL>);(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789")]
Size of Parent s30: 1
PreOrder of Parent s30: ParentsTree[(id=31)]
==================== END CALLING ====================

==================== CALLING s23 ====================
Length of s23: 80
String of s23: ConcatStringTree["01234567890123456789012345678901234567890123456789012345678901234567890123456789"]
PreOrder of s23: ConcatStringTree[(LL=40,L=80,<NULL>);(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=20,L=40,<NULL>);(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789");(LL=10,L=20,<NULL>);(LL=0,L=10,"0123456789");(LL=0,L=10,"0123456789")]
Size of Parent s23: 1
PreOrder of Parent s23: ParentsTree[(id=24)]
==================== END CALLING ====================
    */
}

void khoa(){
    HashConfig hashConfig(
        2,
        0.5,
        0.5,
        0.75,
        2,
        4);
    LitStringHash *litStringHash = new LitStringHash(hashConfig);

    ReducedConcatStringTree *s1 = new ReducedConcatStringTree("d", litStringHash);
    cout << litStringHash->toString() << endl;
    ReducedConcatStringTree *s2 = new ReducedConcatStringTree("h", litStringHash);
    cout << litStringHash->toString() << endl;
    ReducedConcatStringTree *s3 = new ReducedConcatStringTree("l", litStringHash);
    cout << litStringHash->toString() << endl;
    delete s2;
    cout << litStringHash->toString() << endl;
    ReducedConcatStringTree *s4 = new ReducedConcatStringTree("h", litStringHash);
    cout << litStringHash->toString() << endl;

    cout << litStringHash->toString() << endl;
    delete s1;
    // delete s2;
    delete s3;
    delete s4;
    delete litStringHash;
}


int main() {
    khoa();
    return 0;
}   