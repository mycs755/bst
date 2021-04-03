#include <iostream>
#include <vector>
#include <queue>
using namespace std;
/*struct horizontal_line{
    int pres_end_x;
    int other_end_x;
    int pres_end_y;
    int other_end_y;
    int type_line;
    int type_end;
};*/
struct node{
    int key;
    int present_x_cord;
    int type_endpoint;
    int otherend_y_cord;
    int otherend_x_cord;
    int line_type;
    node *leftchild;
    node* rightchild;
    int height;
};
struct lines{
    int pres_end_x;
    int other_end_x;
    int pres_end_y;
    int other_end_y;
    int type_line;
    int type_end;
};
struct compare_x_coord{
     bool operator()(lines const& line1,lines const& line2) {
         return line1.pres_end_x >= line2.pres_end_x;
     }
};
class intersection{
    public:
    vector<struct lines>l;
  //  vector<struct horizontal_line>hl;

    intersection(vector<int> v1,vector<int>v2);

   vector<int>all_intersection_points;
    void execute();
   // void make_queue(vector<struct lines>l);
    void display();
    void inorder(node *R,vector<int> &v);
    node *create_node(int a,int b,int c,int d,int e,int f);
    node *leftrotate(node *R);
    node *rightrotate(node *R);
    node *insert(node*R,int a,int b,int c,int d,int e,int f);
    node *parent(node *R,int x);
    node *predecessor(node*R,int x);;
    node *position(node*R,int x);
    node *deletes(node *R,int x);
    void range_searching(node *R,int k1,int k2,int x);
   // void inorders(node *R,vector<int>&v1,vector<int>&v2);
    int heights(node *R);
    
};
node* intersection::create_node(int a,int b,int c,int d,int e,int f){
    cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1"<<endl;
    node *newnode = new node();
    newnode->key = a;
    newnode->present_x_cord=b;
    newnode->otherend_y_cord=c;
    newnode->otherend_x_cord=d;
    newnode->line_type=e;
    newnode->type_endpoint=f;
    newnode->leftchild=NULL;
    newnode->rightchild=NULL;
    newnode->height=1;
    return newnode;
}

int intersection::heights(node *R){
    cout<<"hhhhhhhhhhhhhhhhhhhhhh"<<endl;
    if(R==NULL){
        return 0;
    }
    node *leftside = R->leftchild;
    node *rightside = R->rightchild;
    
    return max(heights(leftside),heights(rightside))+1;
}

node* intersection::rightrotate(node *R){
    cout<<"rrrrrrrrrrrrrrrrrrrrrrrrrr"<<endl;
    node* newroot = R->leftchild;
    //R->leftchild = NULL
    R->leftchild = newroot->rightchild;

    newroot->rightchild=R;
    R->height = heights(R);
    newroot->height = heights(newroot);
    return newroot;
}

node* intersection::leftrotate(node *R){
    cout<<"llllllllllllllllllllllllll"<<endl;
    node* newroot = R->rightchild;
    R->rightchild = newroot->leftchild;
    newroot->leftchild=R;
    R->height = heights(R);
    newroot->height = heights(newroot);
    return newroot;
}

node * intersection::insert(node* R,int a,int b,int c,int d,int e,int f){
    if(R==NULL){
        cout<<"HHHHIIIIIIIIIII"<<endl;
        node *ne = create_node(a,b,c,d,e,f);
        return ne;
    }
    else if(a<= R->key){
        R->leftchild = insert(R->leftchild,a,b,c,d,e,f);
    }
    else{
        R->rightchild=insert(R->rightchild,a,b,c,d,e,f);
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

node *intersection::parent(node *R,int x){
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
node * intersection::position(node *R,int x){
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

node *intersection::predecessor(node *R,int x){
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


node * intersection::deletes(node *R,int x){
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

void intersection::inorder(node *R,vector<int>&v){
    if(R!=NULL){
        inorder(R->leftchild,v);
      // cout<<R->key<<endl;
        v.push_back(R->key);
       // v1.push_back(R->present_x_cord);
        inorder(R->rightchild,v);
    }
}

/*void intersection::inorders(node *R,vector<int>&v1,vector<int>&v2){
    if(R!=NULL){
        inorders(R->leftchild,v1,v2);
      // cout<<R->key<<endl;
        v1.push_back(R->key);
       v2.push_back(R->present_x_cord);
        inorders(R->rightchild,v1,v2);
    }
}*/

void intersection::range_searching(node *R,int k1,int k2,int x){
    vector<int>v1;
   // vector<int>v2;
    inorder(R,v1);
    cout<<"QWERTYUIOPASDFGHJKLZXCVBNM1234567890"<<endl;
    for(int i=0;i<v1.size();i++){
        if(v1[i]>=k1 && v1[i]<=k2){
            all_intersection_points.push_back(x);
            all_intersection_points.push_back(v1[i]);
           // cout<<v2[i]<<" "<<v1[i]<<endl;
        }
    }
}
void intersection::execute(){
    cout<<"**********************************"<<endl;
   // make_queue(vector<struct lines>l);
   priority_queue<lines,vector<lines>,compare_x_coord> min_q;
   for(int i=0;i<l.size();i++){
       min_q.push(l[i]);
   }
   cout<<min_q.size()<<endl;
   node* Root = NULL;
   while(!min_q.empty()){
       cout<<"$$$$$$$$$$$$$$$$$$$$"<<endl;
       lines ll = min_q.top();
       cout<<ll.pres_end_x<<" "<<ll.pres_end_y<<endl;
       int y_cord = ll.pres_end_y;
       int x_cord = ll.pres_end_x;
       int o_y_cord = ll.other_end_y;
       int o_x_cord = ll.other_end_x;
       int t_l = ll.type_line;
       int t_e = ll.type_end;
       if(t_l==1){
           if(t_e==1){
               //keep in avl
               Root = insert(Root,y_cord,x_cord,o_y_cord,o_x_cord,t_l,t_e);
           }
           else{
               //remove from avl
               Root = deletes(Root,y_cord);
           }
       }
       else{
           //check
            
            int k1=y_cord;
            int k2 = o_y_cord;
            int x_vertical = x_cord;
            range_searching(Root,k1,k2,x_vertical);
       }
        
       min_q.pop();    
   }
    cout<<"???????????????????????????"<<endl; 
   vector<int>v1;
       inorder(Root,v1);
       for(int i=0;i<v1.size();i++){
           cout<<v1[i]<<" ";
       }
       cout<<"???????????????????????????"<<endl; 
}
//void make_queue(vector<struct lines> l){
  //  priority_queue<lines,vector<lines>,compare_x_coord> min_q;
//}
intersection::intersection(vector<int>v1,vector<int>v2){
    for(int i=0;i<v1.size();){
        cout<<"LLLLLLLLLLLL"<<endl;
       // int j=0;
       // horizontal_line h;
       lines ls;
        //int count=0;
        for(int j=0;j<2;j++){
        if(j==0){
            cout<<"KKKKKKKKKKKK"<<endl;
            ls.pres_end_x=v1[i];
            ls.pres_end_y=v1[i+1];
            ls.other_end_x=v1[i+2];
            ls.other_end_y=v1[i+3];
            ls.type_end=1;
            ls.type_line=1;
            l.push_back(ls);
            
        }
        else{
            cout<<"JJJJJJJJJJJJJJJJ"<<endl;
            ls.pres_end_x=v1[i+2];
            ls.pres_end_y=v1[i+3];
            ls.other_end_x=v1[i];
            ls.other_end_y=v1[i+1];
            ls.type_end=0;
            ls.type_line=1;
            l.push_back(ls);
        }
        }   
        i=i+4; 
    }
    for(int i=0;i<v2.size();){
        cout<<"OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO"<<endl;
        //vertical_line v;
        lines ls;
            ls.pres_end_x=v2[i];
            ls.pres_end_y=v2[i+1];
            ls.other_end_x=v2[i+2];
            ls.other_end_y=v2[i+3];
            ls.type_end=0;
            ls.type_line=0;
            cout<<ls.pres_end_x;
            l.push_back(ls);
            i=i+4;
    }
}
void intersection::display(){
    for(int i=0;i<l.size();i++){
        cout<<l[i].pres_end_x<<endl;;
    }
    cout<<"::::::::::::::::::"<<endl;
     
   /* for(int i=0;i<vl.size();i++){
        cout<<vl[i].pres_end_x<<endl;;
    }*/
    for(int i=0;i<all_intersection_points.size();){
        cout<<all_intersection_points[i]<<" "<<all_intersection_points[i+1]<<endl;
        i=i+2;
    }
}
int main(){
    vector<int> v1;
    vector<int> v2;
    cout<<"enter horizontal"<<endl;
    cout<<"enter number of horizontal lines"<<endl;
    int n1;
    cin>>n1;
    int x;
    for(int i=0;i<4*n1;i++){
        cin>>x;
        v1.push_back(x);
    }
    cout<<endl;
    int n2;
    cin>>n2;
    for(int i=0;i<4*n2;i++){
        cin>>x;
        v2.push_back(x);
    }
    intersection inter(v1,v2);
    inter.execute();
    inter.display();
    return 0;
}