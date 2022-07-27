#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <tuple>
#include <map>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Node
{
    Node* left;
    Node* right;
    int val;
};

class btree{
    public:
        btree();
        Node* create_tree(vector<int> arr);
        Node* create_node(int val1);
        void preorder(Node* rr, int target);
        void preorder(int target);
        void find_pairs(int target);
        bool isleaf(Node* p);
        vector<pair<int, int>> result = {};
        Node* first_blank();
        Node* root;
        vector<Node*> parents_of_leaves;
        int i=0;
        unordered_map<int, vector<int>> hash;
       
    
};

btree:: btree(){
    root = NULL;
};


Node* btree::create_node(int val1) {
    Node* ptr = new Node;
    ptr->val = val1;
    //ptr->name = name1;
    ptr->left=NULL;
    ptr->right=NULL;
    if (root == NULL) root = ptr;
    return ptr;
}

Node* btree::create_tree(vector <int> arr)
    {
        
            //cout<<"enetered create_tree";
            int n = arr.size();
            Node* node1=NULL;
            Node* node = NULL;
            //char s, s1, s2;
            int v, v1, v2;
            
            // cin>>n;
            // cin>>v;
            // cin>>s;
            //cout<<"loop1";
            if(arr.size()>0 && arr[0]!=1000000000){
            //if((n>0)&&(v!=1000000000)){
               //cout<<"inside loop1";
               node1 = create_node(arr[0]);
            }
            queue <Node*> nodes;
            nodes.push(node1);
            for (int i=1;i<n-1;i=i+2)
            {
               
                //cin>>v1;
                //cin>>v2;
                v1 = arr.at(i);
                v2 = arr.at(i+1);
                node = nodes.front();
                nodes.pop();
                if(v1!=1000000000){
                node->left = create_node(v1);
                nodes.push(node->left);  
                }
                if(v2!=1000000000){
                node->right = create_node(v2);
                nodes.push(node->right);
                }
            }
    if((n>0)&&(n%2==0)){
        
        Node* temp;
        //cin>>v;
        //cin>>s;
        v = arr.at(n-1);
        node = nodes.front();
        nodes.pop();
        if(v!=1000000000){
        node->left = create_node(v);
        }
    }
    //cout<<"\ncreate tree done\n";
     return node1;
};


void btree::preorder(Node* rr, int target) {
    
    if(rr==NULL)return;
    {
        
        if(hash.count(target-rr->val)>0)
             {
                 //cout<<"\ncurrent val: "<< rr->val<<endl;
                 //cout<< "\nfound target - val: "<< target-rr->val<<endl;
                 for (auto& v2 : hash[target-rr->val])
                    {
                         
                         if(i<v2)
                         {
                             result.push_back(make_pair(i,v2));
                         }
                         else if(i>v2)
                         {
                             result.push_back(make_pair(v2, i));
                         }
                         
                    }
                    
                    
             }
        
        
        
        if(hash.count(rr->val)==0)
        {
             hash[rr->val]={i};
        
        }
        else
        {
            hash[rr->val].push_back(i);
        }
        
        
        
       
        //cout<<"found vale: "<<rr->val<<" at position "<<i<<";";
       
        i = i+1;
    }
    preorder(rr->left, target);
    preorder(rr->right, target);
};

void btree::preorder(int target) {
  //cout<<"the value at the root is "<<root->val;
  preorder(root, target);
};

bool btree::isleaf(Node* p){
    if(p==NULL) return false;
    if((p->left==NULL)&&(p->right==NULL)){
        return true;
    }
    return false;
}



void btree::find_pairs(int target)
{
    // int flag=0; //, v1, v2;
    // for (const auto &[k, v] : hash)
    //     //std::cout << "m[" << k << "] = (" << v <<") " << std::endl;
    //     if(k< target/2)
    //     {   
    //         if(hash.count(target-k) == 1)
    //         {
    //             for (auto& v1 : hash[k])
    //             {
    //                 for (auto& v2 : hash[target-k])
    //                 {
    //                      //cout<<v1<<" "<<v2;
    //                      if(v1<v2)
    //                      {
    //                          result.push_back(make_pair(v1,v2));
    //                      }
    //                      else if(v1>v2)
    //                      {
    //                          result.push_back(make_pair(v2, v1));
    //                      }
                         
    //                 }
                    
    //             }
               
    //             flag=1;
    //         }

    //     }
        
    //     if(target%2==0&& hash.count(target/2)==1)
    //     {
            
    //         auto vec = hash[target/2];
    //         int m = vec.size();
    //         if(m>1)
    //         {
    //             flag=1;
    //             for (int p=0; p<m; p++) 
    //             {
    //               for (int l=p+1; l<m; l++) 
    //                 {
    //                     if(vec[p]<vec[l])
    //                     {
    //                         result.push_back(make_pair(vec[p], vec[l]));
    //                     }
    //                     else
    //                     {
    //                         result.push_back(make_pair(vec[l], vec[p]));
    //                     }
                        
    //                 } 
        
    //             }
                
    //         }
    //     }
        
    //     if(!flag)
    //     {
    //         //cout<<-1<<" "<<-1;
    //         result.push_back(make_pair(-1,-1));
            
    //     }
    //unique(result.begin(), result.end());
    //result.resize(distance(result.begin(), jj));
    
    sort(result.begin(), result.end()); 
    if(result.size()>0)
    {
        for(int i = 0; i < result.size(); i++)
        {
             cout << result[i].first << " " << result[i].second << endl;
        }
    }
    else
    {
        cout<<-1<<" "<<-1;
    }
    
    
}




int main()
{
    btree t;
    int target = 0;
    cin>> target;
    //cout<<"target is "<<target;
    vector< int >arr={};
    string input;
    
    cin.ignore();
    getline (cin >> ws, input);
    //cout<<"\n getline done\n";
    istringstream is1(input);
    int num;
    while(is1>>num) arr.push_back(num);
    //cout<< "\ncreated array\n";
    //cout<<arr.size() << arr.at(0);
    //cout<<"printing array\n";
    //cout<<arr.back();
    // for (auto& it : arr) {
    //     //cout<<"\n entered\n";
    //     cout << it << ' ';
    // }
    
    t.create_tree(arr);
    t.preorder(target);
    
    // for (const auto &[k, v] : t.hash)
    // {
    //     std::cout << "m[" << k << "] = (" << v <<") " << std::endl;
    // }
    
    // cout<<"PRINTING T.HASH\n";
    //  for(map<int, vector<int> >::iterator ii=t.hash.begin(); ii!=t.hash.end(); ++ii){
    //   cout << (*ii).first << ": ";
    //   vector <int> inVect = (*ii).second;
    //   for (int j=0; j<inVect.size(); j++){
    //       cout << inVect[j] << " ";
    //   }
    //   cout << endl;
    //  }
        
    t.find_pairs(target);
    
   

    return 0;
};

