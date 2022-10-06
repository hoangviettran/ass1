#include "ConcatStringList.h"
/*
void tc1() {
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
    // test concat
    ConcatStringList s2("hoang");
    ConcatStringList s3 = s1.concat(s2);
    ConcatStringList s4 = s3.reverse();
    ConcatStringList s5 = s3.subString(2, 14);
    //ConcatStringList s3 = s1.concat(s4);
    cout << "s2 toString: " << s2.toString() << endl;
    cout << "s3 toString: " << s3.toString() << endl;
    cout << "s4 toString: " << s4.toString() << endl;
    cout << "s5 toString: " << s5.toString() << endl;
}*/
/*
void tc2() {
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
}*/

void tc3() {
    ConcatStringList * s1 = new ConcatStringList("Hello");
    ConcatStringList * s2 = new ConcatStringList("_world");
    ConcatStringList * s3 = new ConcatStringList(s1->concat(*s2));
    //ConcatStringList* s4 = new ConcatStringList("hoang");
    //test
    /*cout << ConcatStringList::refList.size() << endl;
    cout << ConcatStringList::refList.refCountAt(0) << endl;
    cout << ConcatStringList::refList.refCountAt(2) << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;*/
    
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    
    /*cout << s1->AList->returnHead() << " " << s1->AList->returnTail() << endl;
    cout << s3->AList->returnHead() << " " << s3->AList->returnTail() << endl;
    cout << s2->AList->returnHead() << " " << s2->AList->returnTail() << endl;*/
    s1->printAddress();
    s2->printAddress();
    s3->printAddress();
    cout << "---After deleting s1---" << endl;
    delete s1;
    cout << ConcatStringList::refList.refCountsString() << endl;
    delete s3;
    cout << ConcatStringList::refList.refCountsString() << endl;
    delete s2;
    
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    /*
    cout << "---After deleting s3---" << endl;
    delete s3;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s2---" << endl;
    delete s2;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    */
}

int main() {
    
    tc3();
    return 0;
}