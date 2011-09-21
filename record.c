#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "record.h"
#include "proc.h"
#include "spinlock.h"

int startrecording(){
  if( proc->recording == 0 ){
    proc->recording = 1;
    return 0;
  }
  return -1;
}

int stoprecording(){
  if( proc->recording == 1 ){
    proc->recording = 0;
    return 0;
  }
  return -1;
}

int fetchrecords(struct record *records, int num_records){
  reclist runner;
  int cnt;  

  if( num_records == 0){
    for(cnt = 0, runner = proc->recl; runner != 0; runner = runner->next, cnt++);
  }else{
    cnt = 0;
    runner = proc->recl;
    
    while(cnt < num_records && runner != 0){
      records[cnt++] = runner->rec;
      runner = runner->next;
    }
  }
  
  return cnt;
}

int addrecordtolist(reclist *list, struct record rec){
  reclist aux;
  
  if(!proc->recording)
    return 0;

  if( *list == 0){
    if( (*list = (reclist) kalloc()) == 0)
       return 0;
    (*list)->rec = rec;
    (*list)->next = 0;
   }else{
    for( aux = *list; aux -> next != 0; aux =  aux -> next);

    if( (aux -> next = (reclist) kalloc()) == 0 )
      return 0;
    aux = aux -> next;
    aux -> rec = rec;
    aux -> next = 0;
  }
  
  return 1;
}

int releaserecordslist(reclist list){
  reclist runner, next;
  
  runner = list; 
  
  while(runner != 0){
    next = runner->next;
    kfree( (char *) runner );
    runner = next; 
  }
  
  return 1;
}
