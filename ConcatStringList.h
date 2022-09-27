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
    int length = 0;
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
        
        CharALNode* returnHead() {
            return head;
        };
    };
    class CharALNode {
    private:
        friend class ConcatStringList;
        friend class CharArrayList;
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
    
    CharArrayList* AList = new CharArrayList();
public:
    ConcatStringList(const char* s) {
        string a = s;
        this->length = a.length();
        AList->insertNode(a);
    };
    int length() const{
        return length;
    };
    char get(int index) const {
        //hello world hoang 10 5 0
        CharALNode* temp = AList->returnHead();
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
        CharALNode* temp = AList->returnHead();
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
        while (temp != NULL) {
            result += temp->s;
            temp = temp->next;
        }
        result = "ConcatStringList[\"" + result + "]\"";
        return result;
    };
    ConcatStringList concat(const ConcatStringList& otherS) const {
        ConcatStringList newString;
        newString.AList->head = this->AList->head;
        this->AList->tail->next = otherS.AList->head;
        newString.AList->tail = otherS.AList->tail;
        return newString;
    };
    ConcatStringList subString(int from, int to) const;
    ConcatStringList reverse() const;
    ~ConcatStringList();

public:
    class ReferencesList {
        // TODO: may provide some attributes

        public:
            int size() const;
            int refCountAt(int index) const;
            std::string refCountsString() const;
    };

    class DeleteStringList {
        // TODO: may provide some attributes

        public:
            int size() const;
            std::string totalRefCountsString() const;
    };
};

#endif // __CONCAT_STRING_LIST_H__