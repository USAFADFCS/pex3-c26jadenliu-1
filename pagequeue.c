/** pagequeue.c
 * ===========================================================
 * Name: Jaden Liu, 11 Apr 2026
 * Section: CS483 / M3
 * Project: PEX3 - Page Replacement Simulator
 * Purpose: Implementation of the PageQueue ADT — a doubly-linked
 *          list for LRU page replacement.
 *          Head = LRU (eviction end), Tail = MRU end.
 * =========================================================== */
#include <stdio.h>
#include <stdlib.h>

#include "pagequeue.h"

/**
 * @brief Create and initialize a page queue with a given capacity
 */
PageQueue *pqInit(unsigned int maxSize) {
    // TODO: malloc a PageQueue, set head and tail to NULL,
    //       size to 0, maxSize to maxSize, and return the pointer
    PageQueue *pq=(PageQueue*)malloc(sizeof(PageQueue));
    if(pq==NULL){
        fprintf(stderr,"malloc error pqInit");
        exit(-1);
    }    
    pq->head=NULL;
    pq->tail=NULL;
    pq->size=0;
    pq->maxSize=maxSize;

    return pq;
}

/**
 * @brief Access a page in the queue (simulates a memory reference)
 */
long pqAccess(PageQueue *pq, unsigned long pageNum) {
    if(pq==NULL){
        return -1;
    }

    //set up current with tail 
    PqNode *current = pq->tail;
    long depth=0;

    // TODO: Search the queue for pageNum (suggest searching tail->head
    //       so you naturally count depth from the MRU end).
    //
    while(current != NULL){
        //check hit
        if(current->pageNum==pageNum){
            if(current==pq->tail){
                return depth;
            }

            if(current->prev !=NULL){
                current->prev->next = current->next;
            }
            else{
                pq->head = current->next;
            }
            if(current->next !=NULL){
                current->next->prev=current->prev;
            }
            current->prev=pq->tail;
            current->next=NULL;

            if(pq->tail!=NULL){
                pq->tail->next=current;
            }
            pq->tail=current;

            if(pq->head==NULL){
                pq->head = current;
            }
            return depth;
        }
        current = current->prev;
        depth = depth+1;
    }
    
    // HIT path (page found at depth d):
    //   - Remove the node from its current position and re-insert
    //     it at the tail (most recently used).
    //   - Return d.
    //
    // MISS path (page not found):
    //   - Allocate a new node for pageNum and insert it at the tail.
    //   - If size now exceeds maxSize, evict the head node (free it).
    //   - Return -1.

    PqNode *newNode = (PqNode *)malloc(sizeof(PqNode));
    
    newNode->pageNum=pageNum;
    newNode->prev=pq->tail;
    newNode->next=NULL;

    if(pq->tail != NULL){
        pq->tail->next=newNode;
    }
    else{
        pq->head=newNode;
    }

    //check max
    if(pq->size > pq->maxSize){
        PqNode *oldHead=pq->head;
        pq->head=oldHead->next;

        if(pq->head!=NULL){
            pq->head->prev=NULL;
            
        }
        else{
            pq->tail=NULL;
        }
        free(oldHead);
        pq->size--;
    }


    return -1;
}

/**
 * @brief Free all nodes in the queue and reset it to empty
 */
void pqFree(PageQueue *pq) {
    // TODO: Walk from head to tail, free each node, then free
    //       the PageQueue struct itself.
    

}

/**
 * @brief Print queue contents to stderr for debugging
 */
void pqPrint(PageQueue *pq) {
    // TODO (optional): Print each page number from head to tail,
    //                  marking which is head and which is tail.
    //                  Useful for desk-checking small traces.
    if(pq==NULL){
        exit(-1);
    }


}
