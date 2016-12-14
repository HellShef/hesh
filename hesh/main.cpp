#include <iostream>
#include <string>
using namespace std;
const int M=16;
class elem{
public:
    int x;
    int h;
    elem *next;
    elem(int a=0,int n=0){
        x=a;
        h=n;
        next=0;
    }
   
    elem operator=(elem * q)
    {
        elem res;
        res.next=q;
        return res;
    }
};
class hesh_list{
public:
    elem * root;
    hesh_list(int x,int n){
        root=new elem(x,n);
        *root=(elem *)(0);
    }
    ~hesh_list(){
        while(root->next){
            elem * t=root;
            while (t->next->next) {
                t=t->next;
            }
            delete t->next;
            t->next=0;
        }
        delete root;
    }
    
    elem * operator[](int n)
    {
        elem * res;
        res=root;
        for(int i=0;i<n;i++){
            if (res->next) {
                res=res->next;
            }
        }
        return res;
    
    }
    void add(int a,int n){
            elem *y=root->next;
            root=new elem(a,n);
            *root=y;
    }
    void kill(elem *q){//нужно чтобы это был указатель как минимум на предпоследний
        elem *t=q->next->next;
        delete q->next;
        q->next=t;
    }
    elem * finde(int u){
        elem* res,* t;
        res=0;
        t=root;
        while(t->next) {
            if(t->h==u) {
                return t;
            }
        }
        return 0;
    }
    
};
class hesh_table{
    hesh_list * a[M]={0,};
public:
    int hesh(const string &s){
        int h=0;
        for(int i=0;i<s.length();i++) {
            h=h*31+s[i];
        }
        return h;
    }
    void add(int x, string s) {
        int N=hesh(s)%M;;
        if(a[N]){
            a[N]->add(x,hesh(s));
        }
        else{
            a[N]=new hesh_list(x,hesh(s));
        }
    }
    ~hesh_table(){
        for(int i=0;i<M;i++){
            delete a[i];
        }
    }
    int finde(string s) {
        return a[hesh(s)%M]->finde(hesh(s))->x;
    }
    
};