#include <iostream>
#include <vector>
using namespace std;
struct node{
    int key;
    node *leftchild;
    node* rightchild;
    int height;
};
void inorder(node *R,vector<int> &v){
    if(R!=NULL){
        inorder(R->leftchild,v);
      // cout<<R->key<<endl;
        v.push_back(R->key);
        inorder(R->rightchild,v);
    }
}
node *create_node(int x){
    node* newnode = new node();
    newnode->key = x;
    newnode->leftchild = NULL;
    newnode->rightchild = NULL;
    newnode->height = 1;
    return newnode;
}
int heights(node *R){
    if(R==NULL){
        return 0;
    }
    node *leftside = R->leftchild;
    node *rightside = R->rightchild;
    
    return max(heights(leftside),heights(rightside))+1;
}
node* rightrotate(node *R){
    node* newroot = R->leftchild;
    //R->leftchild = NULL
    R->leftchild = newroot->rightchild;

    newroot->rightchild=R;
    R->height = heights(R);
    newroot->height = heights(newroot);
    return newroot;
}

node* leftrotate(node *R){
    node* newroot = R->rightchild;
    R->rightchild = newroot->leftchild;
    newroot->leftchild=R;
    R->height = heights(R);
    newroot->height = heights(newroot);
    return newroot;
}

node *parent(node *R,int x){
    //cout<<"PPPPPPPPPPPPPPPPPP"<<endl;
    
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

node *predecessor(node *R,int x){
    vector<int> v1;
    inorder(R,v1);
    int t=0;
    for(int k=0;k<v1.size();k++){
        if(v1[k]==x){
            t=k;
        }
    }
    node *y=NULL;
  //  cout<<t<<"PPPPPPPPPPPP"<<endl;
    if(t>0){
        //return position(R,v1[t-1]);
         y=position(R,v1[t-1]);
    }
    else{
       // cout<<"predecessor doesnt exist";
        y=NULL;
    }
    return y;
}


node * deletes(node *R,int x){
   // cout<<"LLLLLLLLLLLLLLLLL"<<endl;
    node *pos = position(R,x);
   // cout<<pos->key<<endl;
   // cout<<"KKKKKKKKKKKKKKKKK"<<endl;
    node *pred = predecessor(R,x);
    //cout<<pred->key<<endl;
    //cout<<"WWWWWWWWWWWWWWWWWW"<<endl;
    node *par = parent(R,x);
   // cout<<par->key<<endl;
   // cout<<"VVVVVVVVVVVVVVVVVV"<<endl;
    node *curr=R;
    if(pos==NULL){
        return NULL;
    }
    else if(pos->leftchild==nullptr && pos->rightchild==nullptr){
        if(pos==R)
        return NULL;
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
   // vector<int>q1;
   // inorder(R,q1);
   // for(int j=0;j<q1.size();j++){
    //    cout<<q1[j]<<" ";
    //}
    int balance_factor =heights(R->leftchild)-heights(R->rightchild);
    if(balance_factor>1){ // if left subtree height more tha right subtree
        cout<<"[[[[[[[[[[[[[[["<<endl;
        if(heights(R->leftchild->leftchild)>=heights(R->leftchild->rightchild)){ //to check ll or lr
            
            node * rr = rightrotate(R);
            return rr;
        }
        else{  //lr
        cout<<",,,,,,,,,,,"<<endl;
            R->leftchild = leftrotate(R->leftchild);
            node * rr = rightrotate(R);
            return rr;
        }
    }
    if(balance_factor<-1){  // if right subtree height is more
    cout<<"{{{{{{{{{{"<<endl;
        if(heights(R->rightchild->rightchild)>=heights(R->rightchild->leftchild)){ //to check rr or rl
            node * ll = leftrotate(R);
            return ll;
        }
        else{  //rl
        cout<<"mmmmmmmmmmm"<<endl;
            R->leftchild = rightrotate(R->leftchild);
            node * ll = leftrotate(R);
            return ll;
        }
    }
    //return R;
    R->height = heights(R);
    return R;
    
}



node * insert(node* R,int x){
    if(R==NULL){
        cout<<"HHHHIIIIIIIIIII"<<endl;
        node *ne = create_node(x);
        return ne;
    }
    else if(x<= R->key){
        R->leftchild = insert(R->leftchild,x);
    }
    else{
        R->rightchild=insert(R->rightchild,x);
    }
    int balance_factor =heights(R->leftchild)-heights(R->rightchild);
    if(balance_factor>1){ // if left subtree height more tha right subtree
        cout<<"[[[[[[[[[[[[[[["<<endl;
        if(heights(R->leftchild->leftchild)>=heights(R->leftchild->rightchild)){ //to check ll or lr
            
            node * rr = rightrotate(R);
            return rr;
        }
        else{  //lr
        cout<<",,,,,,,,,,,"<<endl;
            R->leftchild = leftrotate(R->leftchild);
            node * rr = rightrotate(R);
            return rr;
        }
    }
    if(balance_factor<-1){  // if right subtree height is more
    cout<<"{{{{{{{{{{"<<endl;
        if(heights(R->rightchild->rightchild)>=heights(R->rightchild->leftchild)){ //to check rr or rl
            node * ll = leftrotate(R);
            return ll;
        }
        else{  //rl
        cout<<"mmmmmmmmmmm"<<endl;
            R->leftchild = rightrotate(R->leftchild);
            node * ll = leftrotate(R);
            return ll;
        }
    }
    //return R;
    R->height = heights(R);
    return R;

}
int main(){
    node * Root = NULL;
    for(int i=2;i<6;i++){
        Root = insert(Root,i);
    }
    //inorder(Root);
    vector<int>v1;
    inorder(Root,v1);
    for(int i=0;i<v1.size();i++){
        cout<<v1[i]<<endl;
    }
    deletes(Root,4);
    vector<int>v2;
    inorder(Root,v2);
    for(int i=0;i<v2.size();i++){
        cout<<v2[i]<<endl;
    }
    return 0;
}