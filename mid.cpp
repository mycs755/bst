#include <iostream>
#include <vector>
using namespace std;
struct horizontal_line{
    int pres_end_x;
    int other_end_x;
    int pres_end_y;
    int other_end_y;
    int type_line;
    int type_end;
};
struct vertical_line{
    int pres_end_x;
    int other_end_x;
    int pres_end_y;
    int other_end_y;
    int type_line;
    int type_end;
};
class intersection{
    public:
    vector<struct vertical_line>vl;
    vector<struct horizontal_line>hl;
    intersection(vector<int> v1,vector<int>v2);
    void display();
    
};
intersection::intersection(vector<int>v1,vector<int>v2){
    for(int i=0;i<v1.size();){
        cout<<"LLLLLLLLLLLL"<<endl;
       // int j=0;
        horizontal_line h;
        //int count=0;
        for(int j=0;j<2;j++){
        if(j==0){
            cout<<"KKKKKKKKKKKK"<<endl;
            h.pres_end_x=v1[i];
            h.pres_end_y=v1[i+1];
            h.other_end_x=v1[i+2];
            h.other_end_y=v1[i+3];
            h.type_end=1;
            h.type_line=1;
            hl.push_back(h);
            
        }
        else{
            cout<<"JJJJJJJJJJJJJJJJ"<<endl;
            h.pres_end_x=v1[i+2];
            h.pres_end_y=v1[i+3];
            h.other_end_x=v1[i];
            h.other_end_y=v1[i+1];
            h.type_end=1;
            h.type_line=1;
            hl.push_back(h);
        }
        }   
        i=i+4; 
    }
    for(int i=0;i<v2.size();){
        vertical_line v;
            v.pres_end_x=v1[i];
            v.pres_end_y=v1[i+1];
            v.other_end_x=v1[i+2];
            v.other_end_y=v1[i+3];
            v.type_end=0;
            v.type_line=0;
            vl.push_back(v);
            i=i+4;
    }
}
void intersection::display(){
    for(int i=0;i<hl.size();i++){
        cout<<hl[i].pres_end_x<<endl;;
    }
    cout<<"::::::::::::::::::"<<endl;
    for(int i=0;i<vl.size();i++){
        cout<<vl[i].pres_end_x<<endl;;
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
    inter.display();
    return 0;
}