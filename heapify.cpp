#include <iostream>
#include <queue>
using namespace std;
//template <typename T>
class heap{
public:    
    int size;
    int capacity;
    int *arr;
    int findposition;
public:
    heap(int c);
    int leftside(int i){
        return 2*i+1;
    }
    int rightside(int i){
        return 2*i+2;
    }
    int parent(int i){
        return (i-1)/2;
    }
    void addelement(int x); // to add element 
    void display(); // to print the elemnets
    void heapify(int arr[],int a,int b); //to correct the given heap to be a max heap from node a and to a maximum of b-1
    void buildmaxheap(); //to build heap if we have array pf random elements
    void heapsort(int arr[]); // to sort the heap
    int minpriority(int y);
    void deletearray();
};
heap::heap(int c){
    capacity=c;
    size=0;
    arr=new int[c];
    //findposition=-1;
}
void heap::addelement(int x){
    if(size==capacity)
    return;
    size++; // first incrementing the size of heap
    arr[size-1]=x; // adding the element to it at last
}
void heap::display(){
    for(int i=0;i<size;i++){
        cout<<arr[i]<<" ";
    }
}
void heap::heapify(int *arr,int x,int n){
    int leftvalue=leftside(x);
    int rightvalue=rightside(x);
    int largeindex=x; //assuming that the largest value index is current node
    if(leftvalue<n && arr[leftvalue]>arr[x]) //checking it with leftnode value
    largeindex = leftvalue;
     if(rightvalue<n && arr[rightvalue]>arr[largeindex]) //checking t with right nodevalue
    largeindex = rightvalue;
    if(largeindex!=x){ //if the greater value is not the current node swap it with the high value
        int tmp = arr[x];
        arr[x]=arr[largeindex];
        arr[largeindex]=tmp;
        heapify(arr,largeindex,n); //since the largeindex value is changed we have to heapify it recursively
    }

}
void heap::buildmaxheap(){
    for(int i=(size-1)/2;i>=0;i--){ //starting from the last node to top
        heapify(arr,i,size); //heapify every node so that it becomes max heap
    }
}
void heap::heapsort(int *arr){
    for(int i=size-1;i>=0;i--){ //here we first swap the last leaf with top node
        int tmp=arr[i];    //and we heapify the remaining heap except the last leaf as it contains maximum value
        arr[i]=arr[0];    //do it upto top
        arr[0]=tmp;
        heapify(arr,0,i);
    }
}
int heap::minpriority(int y){
    priority_queue<int,vector<int>,greater<int>>pq;
    int size=sizeof(arr)/sizeof(arr[0]);
    for(int i=0;i<size;i++){
        pq.push(arr[i]);
    }
    int count=1;
    while(pq.empty()==false){
        if(pq.top()==y)
        break;
        else{
            count++;
            pq.pop();
        }
    }
    return count;
}
/*void heap::deletearray(){
    delete[] arr;
}*/
int main(){
    int k;
    cin>>k;
    int n;
    cin>>n;
    int x;
    if(n==1){
        cin>>x;
        cout<<x;
    }
    else{
    int arr[n]={0};
    heap h(20);
    for(int i=0;i<n;i++){
        cin>>arr[i];
        h.addelement(arr[i]);
    }
    h.buildmaxheap();
   // h.heapify(0);
   h.heapsort(h.arr);
    h.display();
    cout<<endl;
   // cout<<h.minpriority(3);
   // h.deletearray;
   // h.display();
   //delete[] arr;
    }
   heap h1(20);
   int m;
   cin >> m;
   int a;
   cin>>a;
   int arr1[m]={0};
   for(int i=0;i<m;i++){
        cin>>arr1[i];
        h.addelement(arr1[i]);
    }
    h.heapsort(h.arr);
    //h.display();
    cout<<h.minpriority(a);
    return 0;
}