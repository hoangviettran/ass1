#ifndef __CONCAT_STRING_LIST_H__
#define __CONCAT_STRING_LIST_H__

#include "main.h"

class ConcatStringList {
public:
    class ReferencesList; // forward declaration
    class DeleteStringList; // forward declaration

public:
    static ReferencesList refList;
    static DeleteStringList delStrList;

    // TODO: may provide some attributes
    class CharALNode; // forward declaration
    class CharArrayList; // forward declaration
    class ReferenceNode; // forward declaration
    class DeleteNode; // forward declaration
    int concatlength;
    class CharArrayList {
    private:
        friend class ConcatStringList;
        CharALNode* head;
        CharALNode* tail;
    public:
        CharArrayList() {
            head = tail = NULL;
        };
        void insertNode(string s) {
            CharALNode* newNode = new CharALNode(s);

            if (head == NULL) {
                head = tail = newNode;
                return;
            }
            tail->next = newNode;
            tail = newNode;
        };
        void insertHead(string s) {
            CharALNode* newNode = new CharALNode(s);

            if (head == NULL) {
                head = tail = newNode;
                return;
            }
            newNode->next = head;
            head = newNode;
        }
        CharALNode* returnHead() {
            return head;
        };
        CharALNode* returnTail() {
            return tail;
        };
    };
    class CharALNode {
    private:
        friend class ConcatStringList;
        friend class CharArrayList;
        friend class ReferencesList;
        friend class ReferenceNode;
        friend class DeleteStringList;
        friend class DeleteNode;
        int stringLength = 0;
        string s;
        CharALNode* next;
    public:
        CharALNode(string s) {
            this->stringLength = s.length();
            this->s = s;
            this->next = NULL;
        };
    };
    
    CharArrayList* AList;
public:
    ConcatStringList() {
        this->AList = new CharArrayList();
        this->concatlength = 0;
    };
    ConcatStringList(const char* s) {
        this->AList = new CharArrayList();
        string a = s;
        this->concatlength = a.length();
        this->AList->insertNode(a);
        refList.addTail(this->AList->head);
        refList.addTail(this->AList->tail);
    };
    int length() const {
        return this->concatlength;
    };
    char get(int index) const {
        
        CharALNode* temp = this->AList->returnHead();
        if (temp == NULL) throw out_of_range("Index of string is invalid!");
        while(index > temp->stringLength-1){
            if(temp->next == NULL) throw out_of_range("Index of string is invalid!");
            else {
                temp = temp->next;
                index -= temp->stringLength;
            }
        }
        string a = temp->s;
        return a[index];
    };
    int indexOf(char c) const {
        CharALNode* temp = this->AList->returnHead();
        int index = 0;
        while (temp != NULL) {
            string a = temp->s;
            for (int i = 0; i < temp->stringLength; i++) {
                if (c == a[i]) {
                    return index;
                }
                index++;
            }
            temp = temp->next;
        }
        return -1;
    };
    std::string toString() const {
        string result = "";
        CharALNode* temp = AList->returnHead();
        //test
        cout << "head: " << temp<< " ";
        while (temp != NULL) {
            result += temp->s;
            // test
            if (temp->next == NULL) cout << "tail: " << temp << "  ";
            temp = temp->next;
        }
        //result = "ConcatStringList[\"" + result + "]\"";
        return result;
    };
    ConcatStringList concat(const ConcatStringList& otherS) const {
        ConcatStringList newString;
        newString.AList->head = this->AList->head;
        refList.addTail(newString.AList->head);
        this->AList->tail->next = otherS.AList->head;
        newString.AList->tail = otherS.AList->tail;
        refList.addTail(newString.AList->tail);
        newString.concatlength = this->concatlength + otherS.concatlength;
        return newString;
    };
    ConcatStringList subString(int from, int to) const {
        if (from > to) throw logic_error("Invalid range");
        ConcatStringList newList;
        int count = to - from;
        CharALNode* temp = this->AList->returnHead();
        if (temp == NULL) throw out_of_range("Index of string is invalid!");
        while (from > temp->stringLength - 1) {
            if (temp->next == NULL) throw out_of_range("Index of string is invalid!");
            else {
                temp = temp->next;
                from -= temp->stringLength;
            }
        }
        int i = 0;
        int j = 0;
        string add = "";
        while (1) {
            string a = temp->s;
            if (from + i < a.length()) {
                add += a[from + i];
                i++;
                j++;
            }
            else {
                newList.AList->insertNode(add);
                temp = temp->next;
                if(temp == NULL) throw out_of_range("Index of string is invalid!");
                add = "";
                i = 0;
                from = 0;
            }
            if (j == count) {
                if (add != "") newList.AList->insertNode(add);
                break;
            }
        }
        return newList;
    };
    ConcatStringList reverse() const {
        CharALNode* temp = this->AList->head;
        ConcatStringList result;
        result.concatlength = this->concatlength;
        while (temp != NULL) {
            string tmp = temp->s;
            string tmp_1 =  "";
            for (int i = tmp.length()-1; i >= 0; i--) {
                tmp_1 += tmp[i];
            }
            result.AList->insertHead(tmp_1);
            temp = temp->next;
        }
        refList.addTail(result.AList->head);
        refList.addTail(result.AList->tail);
        return result;
    };
    ~ConcatStringList() {
        delStrList.DeleteHeadTail(this->AList->head, this->AList->tail);
        this->AList->head = this->AList->tail = NULL;
    };
    void printAddress() {
        CharALNode* temp = this->AList->head;
        cout << "print: ";
        if (temp == this->AList->tail) cout << temp << " ";
        else while (temp != NULL) {
            cout << temp << " ";
            if (temp == this->AList->tail) break;
            temp = temp->next;
        }
        cout << endl;
    }
public:
    class ReferenceNode {
    private:
        friend class ReferencesList;
        friend class DeleteStringList;
        friend class DeleteNode;
        CharALNode* address;
        ReferenceNode* next;
        int numOfRef;
    public:
        ReferenceNode(CharALNode* a) {
            this->address = a;
            this->next = NULL;
            this->numOfRef = 0;
        }
    };
    class ReferencesList {
        // TODO: may provide some attributes
        public:
        friend class ConcatStringList;
        friend class DeleteStringList;
        int sizeOfList;
        ReferenceNode* head;
        public:
            ReferencesList() {
                head = NULL;
                sizeOfList = 0;
            }
            ReferenceNode* swapNode(ReferenceNode*& ptr1, ReferenceNode*& ptr2) {
                ReferenceNode* tmp = ptr2->next;
                ptr2->next = ptr1;
                ptr1->next = tmp;
                return ptr2;
            }
            void sort() {
                int i, j, swapped;
                for (i = 0; i <= sizeOfList; i++) {
                    ReferenceNode** h = &head;
                    swapped = 0;

                    for (j = 0; j < sizeOfList - i - 1; j++) {
                        
                        ReferenceNode* p1 = *h;
                        ReferenceNode* p2 = p1->next;

                        if ((p1->numOfRef > p2->numOfRef) && p2->numOfRef != 0 || (p2->numOfRef > p1->numOfRef) && p1->numOfRef == 0) {
                            *h = swapNode(p1, p2);
                            swapped = 1;
                        }
                        h = &(*h)->next;
                    }
                    if (swapped == 0)
                        break;
                }
                //check if all the 
                ReferenceNode* curr = head;
                bool flat = 0;
                while (curr != NULL) {
                    if (curr->numOfRef != 0) {
                        flat = 1;
                    }
                    curr = curr->next;
                }
                if (flat == 0) {
                   delRefList();
                }
            };
            void delRefList() {
                ReferenceNode* temp = head;
                while (temp != NULL) {
                    ReferenceNode* tmp = temp;
                    temp = temp->next;
                    delete tmp->address;
                    delete tmp;
                }
                head = NULL;
                sizeOfList = 0;
            }
            void addTail(CharALNode* &a) {
                if (head == NULL) {
                    ReferenceNode* temp = new ReferenceNode(a);
                    temp->numOfRef = 1;
                    head = temp;
                    sizeOfList++;
                    return;
                }
                ReferenceNode* temp = head;
                while(1) {
                    if (temp->address == a) {
                        temp->numOfRef++;
                        return;
                    }
                    if (temp->next == NULL) break;
                    temp = temp->next;
                }
                ReferenceNode* newNode = new ReferenceNode(a);
                newNode->numOfRef = 1;
                temp->next = newNode;
                this->sizeOfList++;
                sort();
                
            };
            ReferenceNode* checkout(CharALNode* &Node) {
                ReferenceNode* temp = head;
                while (1) {
                    if (temp->address == Node) {
                        temp->numOfRef--;
                        sort();
                        return temp;
                    }
                    temp = temp->next;
                }
            }
            int size() const {
                return sizeOfList;
            };
            int refCountAt(int index) const {
                ReferenceNode* temp = head;
                int i = 0;
                while (i < index) {
                    i++;
                    if (temp == NULL) throw out_of_range("Index of references list is invalid!");
                    temp = temp->next;
                }
                return temp->numOfRef;
            };
            std::string refCountsString() const {
                ReferenceNode* temp = head;
                string result = "";
                while (temp != NULL) {
                    int a = temp->numOfRef;
                    if (temp->next != NULL) {
                        result += to_string(a);
                        result += ",";
                    }
                    else { result += to_string(a); }
                    temp = temp->next;
                }
                result = "RefCounts[" + result + "]";
                return result;
            };
    };
    class DeleteNode {
    private:
        friend class DeleteStringList;
        ReferenceNode* head;
        ReferenceNode* tail;
        DeleteNode* next;
    public:
        DeleteNode(ReferenceNode* &head, ReferenceNode* &tail) {
            this->head = head;
            this->tail = tail;
            this->next = NULL;
        }
       
    };
    class DeleteStringList {
        // TODO: may provide some attributes
        int sizeOfDelList;
        DeleteNode* Dhead;
        public:
            DeleteStringList() {
                Dhead = NULL;
                sizeOfDelList = 0;
            }
            void DeleteHeadTail(CharALNode* &head, CharALNode* &tail) {
                ReferenceNode* Nhead = refList.checkout(head);
                ReferenceNode* Ntail = refList.checkout(tail);
                
                DeleteNode* newNode = new DeleteNode(Nhead, Ntail);
                insertDelNode(newNode);
                sizeOfDelList++;
                search();
            };
            void insertDelNode(DeleteNode*& node) {
                if (Dhead == NULL) {
                    Dhead = node;
                    return;
                }
                DeleteNode* temp = Dhead;
                while (temp->next != NULL)
                    temp = temp->next;
                temp->next = node;
            }
            void search() {
                // Store head node
                DeleteNode* temp = Dhead;
                DeleteNode* prev = NULL;
                // If head node itself holds
                // the key to be deleted
                if (temp != NULL && temp->head->numOfRef == 0 && temp->tail->numOfRef == 0) {
                    // Changed head
                    Dhead = temp->next;

                    // free old head
                    //delString(temp->head->address, temp->tail->address);
                    delString(temp->head->address, temp->tail->address);
                    delete temp;
                    sizeOfDelList--;
                    search();
                    return;
                }

                // Else Search for the key to be
                // deleted, keep track of the
                // previous node as we need to
                // change 'prev->next'
                else {
                    while (temp != NULL) {
                        prev = temp;
                        temp = temp->next;
                        if(temp != NULL)
                            if (temp->head->numOfRef == 0 && temp->tail->numOfRef == 0)
                                cout << temp->head->address << " " << temp->tail->address << endl;
                       
                    }

                    // If key was not present in linked list
                    if (temp == NULL)
                        return;
                    
                    // Unlink the node from linked list
                    if (temp->next != NULL) {
                        prev->next = temp->next;
                    }
                    else prev->next = NULL;

                    // Free memory
                    delString(temp->head->address, temp->tail->address);
                    delete temp;
                    sizeOfDelList--;
                    // search the list again
                    search();
                }
            }
                
            void delString(CharALNode*& head, CharALNode*& tail) {
                //cout << "delNode: " << head << " " << tail << endl;
                if (head == tail) {
                    return;
                }
                CharALNode* temp = head;
                //cout << "temp->next: " << temp->next << endl;
                //while (temp->next != NULL) {
                    /*CharALNode* tmp = temp->next;
                    temp->next = tmp->next;
                    delete tmp;*/
                //}
            }
            int size() const {
                return sizeOfDelList;
            };
            std::string totalRefCountsString() const {
                if (sizeOfDelList != 0) 
                    return ("TotalRefCounts[" + to_string(size()) + "]");
                return ("TotalRefCounts[]");
            };
    };
};

#endif // __CONCAT_STRING_LIST_H__