#include<iostream>
#include<vector>
using namespace std;

struct node{
    int key;
    node *leftchild;
    node *rightchild;
    node(int x){
        key=x;
        leftchild=rightchild=NULL;
    }
};

void inorder(node *R,vector <int> &v){
    if(R!=NULL){
        inorder(R->leftchild,v);
        cout<<R->key<<endl;
        v.push_back(R->key);
        inorder(R->rightchild,v);
    }
}

void preorder(node *R){
    if(R!=NULL){
        cout<<R->key<<endl;
        preorder(R->leftchild);
        preorder(R->rightchild);
    }
}

void postorder(node *R){
    if(R!=NULL){
        postorder(R->leftchild);
        postorder(R->rightchild);
        cout<<R->key<<endl;
    }
}

bool search(node *R,int x){
    if(R==NULL){
        return false;
    }
    if(R->key==x){
        return true;
    }
    if(x>R->key){
        return search(R->rightchild,x);
    }
    else if(x<R->key){
        return search(R->leftchild,x);
    }
    return false;
}

bool check_bst(vector<int> &v){
     int len=v.size();
     for(int j=0;j<len-1;j++){
         if(v[j]>v[j+1]){
             return false;
         }
     }
     return true;
}

node * position(node *R,int x){
    node *t=NULL;
    if(R==NULL){
        t = NULL;
    }
    if(R->key==x){
        t = R;
    }
    if(x>R->key){
        return position(R->rightchild,x);
    }
    else if(x<R->key){
        return position(R->leftchild,x);
    }
    return t;
}

node *parent(node *R,int x){
    cout<<"PPPPPPPPPPPPPPPPPP"<<endl;
    
    if(R==NULL || R->key==x){
        return NULL;
    }
    
    if((R->leftchild!=NULL && R->leftchild->key==x) || (R->rightchild!=NULL && R->rightchild->key==x)){
        return R;
    }
    node *t=parent(R->leftchild,x);
    if(t!=NULL)
    return t;

    t=parent(R->rightchild,x);
    return t;
    
}
node *predecessor(node *R,int x){
    vector<int> v1;
    inorder(R,v1);
    int t=0;
    for(int k=0;k<v1.size();k++){
        if(v1[k]==x){
            t=k;
        }
    }
    cout<<t<<"PPPPPPPPPPPP"<<endl;
    if(t>0){
        return position(R,v1[t-1]);
    }
    else{
        cout<<"predecessor doesnt exist";
        return NULL;
    }
}
void deletes(node *R,int x){
    cout<<"LLLLLLLLLLLLLLLLL"<<endl;
    node *pos = position(R,x);
    cout<<pos->key<<endl;
    cout<<"KKKKKKKKKKKKKKKKK"<<endl;
    node *pred = predecessor(R,x);
    cout<<pred->key<<endl;
    cout<<"WWWWWWWWWWWWWWWWWW"<<endl;
    node *par = parent(R,x);
    cout<<par->key<<endl;
    cout<<"VVVVVVVVVVVVVVVVVV"<<endl;
    node *curr=R;
    if(pos==NULL){
        return;
    }
    else if(pos->leftchild==nullptr && pos->rightchild==nullptr){
        if(pos==R)
        return;
        else{
            if(par->leftchild==pos){
                par->leftchild=nullptr;
            }
            else
            par->rightchild=nullptr;
        }
        free(pos);
    }
    else if((pos->leftchild==nullptr && pos->rightchild) || (pos->rightchild==nullptr && pos->leftchild)){
        if(pos==R){
            if(pos->rightchild && (pos->leftchild==nullptr)){
                R=pos->rightchild;
            }
            else
            R=pos->leftchild;
        }
        else{
           if(par->leftchild==pos){
                if(pos->rightchild && (pos->leftchild==nullptr)){
                par->leftchild=pos->rightchild;
                }
                else
                par->rightchild=pos->leftchild;
           }
           else{
                if(pos->rightchild && (pos->leftchild==nullptr)){
                par->rightchild=pos->rightchild;
                }
                else
                par->leftchild=pos->leftchild;
           }
        }
        free(pos);
    }
     else if(pos->leftchild && pos->rightchild){
        pos->key=pred->key;
        deletes(pred,pred->key);
    }
    //pos->key=pred->key;
    //par->rightchild=pred->leftchild;
}

int kth_smallest(node *R,int k){
    vector<int>v1;
    inorder(R,v1);
    if(k<v1.size()){
        return v1[k-1];
    }
    else
    return -1;
}

vector <int> integers_in_range(node *R,int k1,int k2){
    vector<int>v1;
    inorder(R,v1);
    int x=-1,y=-1;
    for(int i=0;i<v1.size();i++){
        if(v1[i]==k1)
          x=i;
        else if(v1[i]==k2)
          y=i;
    }
    auto first = v1.cbegin()+x;
    auto last = v1.cbegin()+y+1;
    v1.erase(first,last);
    return v1;
}
void insert(node *R,int x){
    node *tmp = new node(x);
    if(R==NULL){
        R=tmp;
    }
    if(x>R->key){
        if(R->rightchild!=NULL){
            insert(R->rightchild,x);
        }
        else{
            R->rightchild=tmp;
        }
    }
    else if(x<R->key){
        if(R->leftchild!=NULL){
            insert(R->leftchild,x);
        }
        else{
            R->leftchild=tmp;
        }
    }
}

int main(){
    int n;
    cin>>n;
    int x;
    cin>>x;
    vector<int> v;
    node *Root = new node(x);
    for(int i=1;i<n;i++){
        cin>>x;
        insert(Root,x);
    }  
    int y;
    cin>>y;
    inorder(Root,v);
    cout<<"::::::::::::::::::"<<endl;
    preorder(Root);
    cout<<"::::::::::::::::::"<<endl;
    postorder(Root);
    cout<<"::::::::::::::::::"<<endl;
    cout<<check_bst(v);
    cout<<"::::::::::::::::::"<<endl;
    //int y;
    
    cout<<search(Root,y);
    int z;
    cin>>z;
    deletes(Root,z);
    vector<int>temperary;
    inorder(Root,temperary);
    return 0;
}