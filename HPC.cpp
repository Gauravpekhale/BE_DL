  ////////////////////////////////////////////////////////////////////////////////////////////
// DFS
#include <iostream> #include <vector>
#include <stack> #include <omp.h>
using namespace std;
const int MAX = 100000;
vector<int> graph[MAX];s
bool visited[MAX];
void dfs(int node) {
	stack<int> s;
	s.push(node);
	while (!s.empty()) {
    	int curr_node = s.top();
    	s.pop();
    	if (!visited[curr_node]) {
        	visited[curr_node] = true;
        	if (visited[curr_node]) {
        	cout << curr_node << " ";  }
        	#pragma omp  parallel for
        	for (int i = 0; i < graph[curr_node].size(); i++) {
            	int adj_node = graph[curr_node][i];
            	if (!visited[adj_node]) {
                	s.push(adj_node);
            	}
        	}}}}
int main() {
	int n, m, start_node;
	cout << "Enter No of Node,Edges,and start node:" ;
	cin >> n >> m >> start_node;
         //n: node,m:edges
cout << "Enter Pair of edges:" ;
	for (int i = 0; i < m; i++) {
    	int u, v	
    	cin >> u >> v;
//u and v: Pair of edges
    	graph[u].push_back(v);
    	graph[v].push_back(u);
	} #pragma omp parallel for
	for (int i = 0; i < n; i++) {
    	visited[i] = false;
	}
	dfs(start_node);
  
  return 0 ; }
  ////////////////////////////////////////////////////////////////////////////////////////////
//BFS  - 1
#include<iostream>
#include<stdlib.h>
#include<queue>
using namespace std;
class node{
public:
    node *left, *right;
    int data; };
class Breadthfs {
public:
    node *insert(node *, int);
    void bfs(node *);  };
node *Breadthfs::insert(node *root, int data){
    if (!root){
        root = new node;
        root->left = NULL;
        root->right = NULL;
        root->data = data;
        return root; }
    queue<node *> q;
    q.push(root);
    while (!q.empty()){
        node *temp = q.front();
        q.pop();
        if (temp->left == NULL){
            temp->left = new node;
            temp->left->left = NULL;
            temp->left->right = NULL;
            temp->left->data = data;
            return root; } else {
            q.push(temp->left);  }
        if (temp->right == NULL){
            temp->right = new node;
            temp->right->left = NULL;
            temp->right->right = NULL;
            temp->right->data = data;
            return root; }
        else { q.push(temp->right);}
 }}
void Breadthfs::bfs(node *head){
    queue<node *> q;
//BFS - 2    
q.push(head);
    while (!q.empty()){
        int qSize = q.size();
        for (int i = 0; i < qSize; i++) {
            node *currNode = q.front();
            q.pop();
            cout << "\t" << currNode->data;
            if (currNode->left)
                q.push(currNode->left);
            if (currNode->right)
                q.push(currNode->right);
       }}}

int main(){
    node *root = NULL;
    int data;
    char ans; 
do{
        cout << "\nEnter data: ";
        cin >> data;
        Breadthfs obj;
        root = obj.insert(root, data);
        cout << "Do you want to insert one more node? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
    Breadthfs obj;
    obj.bfs(root);
    return 0; }
////////////////////////////////////////////////////////////////////////////////////////////
// merge sort – 1           
#include<iostream> #include<stdlib.h>
#include<omp.h>  using namespace std;
void mergesort(int a[],int i,int j);
void merge(int a[],int i1,int j1,int i2,int j2);
void mergesort(int a[],int i,int j){
	int mid;
	if(i<j){
    	mid=(i+j)/2;
    	#pragma omp parallel sections {
	#pragma omp section {
            	mergesort(a,i,mid);  }
        // Merge Sort -2        	
#pragma omp section  {
            	mergesort(a,mid+1,j);    
       }}
    	merge(a,i,mid,mid+1,j);   } }
 
void merge(int a[],int i1,int j1,int i2,int j2){
	int temp[1000];    
	int i,j,k;
	i=i1;    
	j=i2;    
	k=0;
	while(i<=j1 && j<=j2)    {
    	if(a[i]<a[j])   {
        	temp[k++]=a[i++];  }
    	else  {
        	temp[k++]=a[j++];  } }
    while(i<=j1)    {
    	temp[k++]=a[i++];   }
	while(j<=j2)    {
    	temp[k++]=a[j++];    }
	for(i=i1,j=0;i<=j2;i++,j++)  {
    	a[i]=temp[j];  }    }
int main(){
	int *a,n,i;
	cout<<"\n enter total no of elements=>";
	cin>>n;
	a= new int[n];
	cout<<"\n enter elements=>";
	for(i=0;i<n;i++) {
    	cin>>a[i];  }
   //	 start=.......
//#pragma omp…..
	mergesort(a, 0, n-1);
//          stop…….
	cout<<"\n sorted array is=>";
	for(i=0;i<n;i++)  {
    	cout<<"\n"<<a[i];  }
  	// Cout<<Stop-Start
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////

// MIN_MAX
#include <iostream> #include <omp.h>
#include <climits>
using namespace std;
void min_reduction(int arr[], int n) {
  int min_value = INT_MAX;
  #pragma omp parallel for reduction(min: min_value)
  for (int i = 0; i < n; i++) {
	if (arr[i] < min_value) {
  	min_value = arr[i];  } } 
cout << "Minimum value: " << min_value << endl; }
void max_reduction(int arr[], int n) {
  int max_value = INT_MIN;
  #pragma omp parallel for reduction(max: max_value)
  for (int i = 0; i < n; i++) {
	if (arr[i] > max_value) {
  	max_value = arr[i]; 	}   }
cout << "Maximum value: " << max_value << endl; }
void sum_reduction(int arr[], int n) {
  int sum = 0;
   #pragma omp parallel for reduction(+: sum)
   for (int i = 0; i < n; i++) {
	sum += arr[i] ;  }
  cout << "Sum: " << sum << endl; }
void average_reduction(int arr[], int n) {
  int sum = 0;
  #pragma omp parallel for reduction(+: sum)
  for (int i = 0; i < n; i++) {
	sum += arr[i];  } 
cout << "Average: " << (double)sum / (n-1) << endl;    }
int main() {
    int *arr,n;
    cout<<"\n enter total no of elements=>";
    cin>>n;   arr=new int[n];
    cout<<"\n enter elements=>";
    for(int i=0;i<n;i++) { cin>>arr[i];  }
  min_reduction(arr, n);
  max_reduction(arr, n);
  sum_reduction(arr, n);
  average_reduction(arr, n);   }
  
  ////////////////////////////////////////////////////////////////////////////////////////////
// Parallel Bubble Sort
#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;
void bubble(int *, int);
void swap(int &, int &);
void bubble(int *a, int n) {
    for(  int i = 0;  i < n;  i++ ) {  	 
   	 int first = i % 2; 	 
   	 #pragma omp parallel for shared(a,first)
   	 for(  int j = first;  j < n-1;  j += 2  ){  	  if(  a[ j ]  >  a[ j+1 ]  ) { 
          swap(  a[ j ],  a[ j+1 ]  );   }  	 
   		   }  	  }  }
void swap(int &a, int &b)
{
    int test;  test=a;
    a=b;
    b=test;
}
int main() {
    int *a,n;
    cout<<"\n enter total no of elements=>";
    cin>>n;
    a=new int[n];
    cout<<"\n enter elements=>";
    for(int i=0;i<n;i++)
    {
   	 cin>>a[i];
    }
    bubble(a,n);
    cout<<"\n sorted array is=>";
    for(int i=0;i<n;i++)
    {
   	 cout<<a[i]<<endl;
    }
return 0;
}
