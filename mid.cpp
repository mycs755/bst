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

   
    void execute();
   // void make_queue(vector<struct lines>l);
    void display();
    
};
void intersection::execute(){
    cout<<"**********************************"<<endl;
   // make_queue(vector<struct lines>l);
   priority_queue<lines,vector<lines>,compare_x_coord> min_q;
   for(int i=0;i<l.size();i++){
       min_q.push(l[i]);
   }
   cout<<min_q.size()<<endl;
   while(!min_q.empty()){
       cout<<"$$$$$$$$$$$$$$$$$$$$"<<endl;
       lines ll = min_q.top();
       min_q.pop();
       cout<<ll.pres_end_x<<" "<<ll.pres_end_y<<endl;
   }
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