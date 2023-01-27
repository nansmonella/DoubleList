#pragma once

#include "DoubleList.tpp"

template<typename T>
DoubleList<T>::DoubleList(T *a, unsigned n) {
    if (n==0) {
        this->mHead[Red] = nullptr;
        this->mHead[Blue] = nullptr;
    }
    else if (n==1) {
        Node* newNode = new Node();
        newNode->mValue = a[0]; 
        newNode->mNext[Red] = nullptr;
        newNode->mNext[Blue] = nullptr;
        this->mHead[Red] = newNode;
        this->mHead[Blue] = newNode;
    }
    else {
        Node* headNode = new Node();
        headNode->mValue = a[0];
        mHead[Red] = headNode;
        mHead[Blue] = headNode;
        Node* oldNode = headNode;
        for(unsigned i=1; i<n; i++) {
            Node* newNode = new Node();
            newNode->mValue = a[i];
            oldNode->mNext[Red] = newNode;
            oldNode->mNext[Blue] = newNode;
            oldNode = newNode;
        }
        oldNode->mNext[Red] = NULL;
        oldNode->mNext[Blue] = NULL;
    }
}

template <typename T>
DoubleList<T>::DoubleList(const DoubleList<T> &dl) {

    if(dl.mHead[Red] == NULL) return;

    Node *startOfClone = new Node();
    Node *next = startOfClone;
    startOfClone->mValue = dl.mHead[Blue]->mValue;
    this->mHead[Blue] = startOfClone;
    Node* hold = dl.mHead[Blue]->mNext[Blue];

    while(hold) {
        next ->mNext[Blue] = new Node;
        next = next -> mNext[Blue];
        next->mValue = hold->mValue;
        hold = hold -> mNext[Blue];
    }

    next->mNext[Blue] = nullptr;
    next = this->mHead[Blue];
    Node* temp = dl.mHead[Blue];
    hold = dl.mHead[Red];

    while(temp != hold){
        temp = temp->mNext[Blue];
        next = next->mNext[Blue];
    }
    hold = NULL;
    Node* newOne = dl.mHead[Red]-> mNext[Red];
    Node* newNext = next;
    mHead[Red] = newNext;

    while(newOne) {
        next = mHead[Blue];
        temp = dl.mHead[Blue];
        while(newOne!=temp){
            next = next->mNext[Blue];
            temp = temp->mNext[Blue];
        }
        newOne = newOne->mNext[Red];
        newNext->mNext[Red] = next;
        newNext = next;
    }
    newNext -> mNext[Red ] = nullptr;
}

template <typename T>
typename DoubleList<T>::Node *DoubleList<T>::get(unsigned index,
                                                 Color color) const {
  Node *temp = mHead[color];
  for(unsigned int i=0; i<index; i++){
    if(temp -> mNext[color]){
    temp = temp -> mNext[color];
    }
    else throw(InvalidIndexException());
  }
  return temp;
}

template <typename T>
typename DoubleList<T>::Node *DoubleList<T>::insert(T value, unsigned redIndex,
                                                    unsigned blueIndex) {
    unsigned x=0;
    unsigned y=0;
    unsigned c = 1;
    Node* IndexForRed = mHead[Red];
    Node* IndexForBlue = mHead[Blue];
    while(IndexForRed!=nullptr){
        IndexForRed = IndexForRed->mNext[Red];   
        x++;
    }
    while(IndexForBlue!=nullptr){
        IndexForBlue = IndexForBlue->mNext[Blue];   
        y++;
    }
    Node* new_node = new Node();
    new_node->mValue = value;
    if(blueIndex>y || redIndex>x){
        delete new_node;
        throw InvalidIndexException();
    }
    else{
        Node* temp = mHead[Blue];
        if(blueIndex==0){
            mHead[Blue] = new_node;
            new_node->mNext[Blue] = temp;
        }
        else if(blueIndex==y){
            while(temp->mNext[Blue]!=nullptr){
                temp = temp->mNext[Blue];                
            }
            temp->mNext[Blue] = new_node;
            new_node->mNext[Blue] = nullptr;
        }
        else{
            while(c<blueIndex){
                temp=temp->mNext[Blue];
                c++;
            }
            Node* temp2 = temp;
            new_node->mNext[Blue] = temp2->mNext[Blue];
            temp->mNext[Blue] = new_node;
        }
    }
        Node* temp = mHead[Red];
        if(redIndex==0){
            mHead[Red] = new_node;
            new_node->mNext[Red] = temp;
        }
        else if(redIndex==x){
            while(temp->mNext[Red]!=nullptr){
                temp = temp->mNext[Red];              
            }
            temp->mNext[Red] = new_node;
            new_node->mNext[Red] = nullptr;
        }
        else{
            unsigned c=1;
            while(c<redIndex){
                temp=temp->mNext[Red];
                c++;
            }
            Node* temp2 = temp;
            new_node->mNext[Red] = temp2->mNext[Red];
            temp->mNext[Red] = new_node;
        }
        return new_node;
}

template <typename T>
void DoubleList<T>::remove(unsigned index, Color color) {

    Node* IndexForRed = mHead[Red];
    Node* IndexForBlue = mHead[Blue];
    unsigned sizeOfRed=0;
    unsigned sizeOfBlue=0;

    while(IndexForRed!=nullptr){
        IndexForRed = IndexForRed->mNext[Red];   
        sizeOfRed++;
    }
    while(IndexForBlue!=nullptr){
        IndexForBlue = IndexForBlue->mNext[Blue];   
        sizeOfBlue++;
    }
    IndexForRed = mHead[Red];
    IndexForBlue = mHead[Blue];
    if(color == Red) {
        if(index>=sizeOfRed) throw(InvalidIndexException()); //if index is invalid

        else if(index == 0) { //if RedIndex is zero
            if(mHead[Red] == mHead[Blue]) { //if BlueIndex is zero
                Node* temp = mHead[Red];
                mHead[Red] = mHead[Red]->mNext[Red];
                mHead[Blue] = mHead[Blue]->mNext[Blue];
                delete temp;
                temp = NULL;
            }

            else{ //if BlueIndex is not zero
                IndexForBlue = mHead[Blue];
                Node* prevBlue = IndexForBlue;
                while(IndexForBlue!=NULL) {
                    if(IndexForBlue == mHead[Red]) {
                        break;
                    }                
                    else {
                        prevBlue = IndexForBlue;
                        IndexForBlue = IndexForBlue->mNext[Blue];
                    }
                }
                mHead[Red] = mHead[Red]->mNext[Red];
                prevBlue->mNext[Blue] = IndexForBlue->mNext[Blue];
                delete IndexForBlue;
                IndexForBlue = NULL;
            }
        }

        else { //if RedIndex is not zero and is valid
            IndexForRed = mHead[Red];
            Node* prevRed = IndexForRed;
            for(unsigned i=0; i<index; i++) { //SEE
                prevRed = IndexForRed;
                IndexForRed = IndexForRed->mNext[Red];
            }
        
            if(IndexForRed == mHead[Blue]) { //if BlueIndex is zero
                prevRed->mNext[Red] = IndexForRed->mNext[Red];
                mHead[Blue] = mHead[Blue]->mNext[Blue];
                delete IndexForRed;
                IndexForRed = nullptr;
            }

            else { //if BlueIndex is not zero;
                IndexForBlue = mHead[Blue];
                Node* prevBlue = IndexForBlue;
                while(IndexForBlue!=NULL) {
                    if(IndexForBlue == IndexForRed) {
                        break;
                    }                
                    else {
                        prevBlue = IndexForBlue;
                        IndexForBlue = IndexForBlue->mNext[Blue];
                    }
                }
                prevRed->mNext[Red] = IndexForRed->mNext[Red];
                prevBlue->mNext[Blue] = IndexForBlue->mNext[Blue];
                delete IndexForRed;
                IndexForRed = IndexForBlue = NULL;
            }
        }
    } else if(color == Blue) {
        if(index>=sizeOfBlue) throw(InvalidIndexException()); //if index is invalid

        else if(index == 0) { //if BlueIndex is zero
            if(mHead[Blue] == mHead[Red]) { //if RedIndex is zero
                Node* temp = mHead[Blue];
                mHead[Blue] = mHead[Blue]->mNext[Blue];
                mHead[Red] = mHead[Red]->mNext[Red];
                delete temp;
                temp = NULL;
            }

            else{ //if RedIndex is not zero
                IndexForRed = mHead[Red];
                Node* prevRed = IndexForRed;
                while(IndexForRed!=NULL) {
                    if(IndexForRed == mHead[Blue]) {
                        break;
                    }                
                    else {
                        prevRed = IndexForRed;
                        IndexForRed = IndexForRed->mNext[Red];
                    }
                }
                mHead[Blue] = mHead[Blue]->mNext[Blue];
                prevRed->mNext[Red] = IndexForRed->mNext[Red];
                delete IndexForRed;
                IndexForRed = NULL;
            }
        }

        else { //if BlueIndex is not zero and is valid
            IndexForBlue = mHead[Blue];
            Node* prevBlue = IndexForBlue;
            for(unsigned i=0; i<index; i++) { //SEE
                prevBlue = IndexForBlue;
                IndexForBlue = IndexForBlue->mNext[Blue];
            }
        
            if(IndexForBlue == mHead[Red]) { //if RedIndex is zero
                prevBlue->mNext[Blue] = IndexForBlue->mNext[Blue];
                mHead[Red] = mHead[Red]->mNext[Red];
                delete IndexForBlue;
                IndexForBlue = NULL;
            }

            else { //if RedIndex is not zero;
                IndexForRed = mHead[Red];
                Node* prevRed = IndexForRed;
                while(IndexForRed!=NULL) {
                    if(IndexForRed == IndexForBlue) {
                        break;
                    }                
                    else {
                        prevRed = IndexForRed;
                        IndexForRed = IndexForRed->mNext[Red];
                    }
                }
                if(IndexForRed==NULL) throw(InvalidIndexException());
                prevBlue->mNext[Blue] = IndexForBlue->mNext[Blue];
                prevRed->mNext[Red] = IndexForRed->mNext[Red];
                delete IndexForBlue;
                IndexForBlue = IndexForRed = NULL;
            }
        }
    }
    return;
}

template <typename T>
void DoubleList<T>::append(DoubleList<T> &dl) {
    Node* IndexForRed = this->mHead[Red];
    Node* IndexForBlue = this->mHead[Blue];
    
    if(IndexForRed!=NULL) {
        while(IndexForRed->mNext[Red]!=nullptr){
            IndexForRed = IndexForRed->mNext[Red];   
        }
    }
    if(IndexForBlue!=NULL) {
    while(IndexForBlue->mNext[Blue]!=nullptr){
        IndexForBlue = IndexForBlue->mNext[Blue];   
    }
    }

    if(IndexForRed!=NULL && IndexForRed!=NULL) {
        IndexForRed->mNext[Red] = dl.mHead[Red];
        IndexForBlue->mNext[Blue] = dl.mHead[Blue];
        dl.mHead[Red] = nullptr;
        dl.mHead[Blue] = nullptr;
    }
    else {
        mHead[Red] = dl.mHead[Red];
        mHead[Blue] = dl.mHead[Blue];
        dl.mHead[Red] = nullptr;
        dl.mHead[Blue] = nullptr;
    }
}

template <typename T>
DoubleList<T>::~DoubleList() {
    Node* headNode = this->mHead[Red];
    while(headNode) {
        Node* temp = headNode->mNext[Red];
        delete headNode;
        headNode = temp;
    }
}
