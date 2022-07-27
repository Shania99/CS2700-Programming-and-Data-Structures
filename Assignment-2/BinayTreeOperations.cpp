#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

struct Node
{
    Node* left;
    Node* right;
    char name;
    int val;
};

class btree{
    public:
        btree();
        Node* create_tree();
        void insert();
        Node* add_child(Node* parent, int v, char s);
        Node* create_node(int val1, char name1);
        void preorder(Node* rr, int target);
        void preorder(int target);
        void delete_node(char target);
        int search(Node* rr, char target) ;
        int search(char target);
        bool isleaf(Node* p);
        tuple<int, int> find_leaf_nonleaf(int val_target);
        void get_parents_of_leaves();
        Node* get_parent_of_first_leaf(char target);
        Node* find_parent_of_leaf(Node* p);
        
        Node* first_blank();
        Node* root;
        vector<Node*> parents_of_leaves;
       
    
};

btree:: btree(){
    root = NULL;
};


Node* btree::create_node(int val1, char name1) {
    Node* ptr = new Node;
    ptr->val = val1;
    ptr->name = name1;
    ptr->left=NULL;
    ptr->right=NULL;
    if (root == NULL) root = ptr;
    return ptr;
}

Node* btree::create_tree()
    {
            int n;
            Node* node1=NULL;
            Node* node = NULL;
            char s, s1, s2;
            int v, v1, v2;
            cin>>n;
            cin>>v;
            cin>>s;
            if((n>0)&&(v!=-1)){
               
                node1 = create_node(v,s);
            }
            queue <Node*> nodes;
            nodes.push(node1);
            for (int i=1;i<n-1;i=i+2)
            {
               
                cin>>v1;
                cin>>s1;
                cin>>v2;
                cin>>s2;
                
                node = nodes.front();
                nodes.pop();
                if(v1!=-1){
                node->left = create_node(v1,s1);
                nodes.push(node->left);  
                }
                if(v2!=-1){
                node->right = create_node(v2,s2);
                nodes.push(node->right);
                }
            }
    if((n>0)&&(n%2==0)){
        
        Node* temp;
        cin>>v;
        cin>>s;
        node = nodes.front();
        nodes.pop();
        if(v!=-1){
        node->left = create_node(v, s);
        }
    }
     return node1;
};

Node* btree::get_parent_of_first_leaf(char target){
    queue<Node*> treenode;
    Node* temp = NULL;
    if(!root)return root;
    treenode.push(root);
    while(!treenode.empty()){
        temp = treenode.front();
        treenode.pop();
        if(temp->left)
        {
            if(isleaf(temp->left)&&(temp->left->name!=target))return temp;
            treenode.push(temp->left);
            
        }
        if(temp->right)
        {
            if(isleaf(temp->right)&&(temp->right->name!=target))return temp;
            treenode.push(temp->right);
            
        }
        
        
    }
    return NULL;
}

Node* btree::find_parent_of_leaf(Node* p)
{
    if(p==NULL)return NULL;
    if(root==NULL)return NULL;
    queue<Node*> q;
    q.push(root);
    while(!q.empty())
    {
        auto node=q.front();
        q.pop();
        if((node->left==p)||(node->right==p))return node;
        if(node->left)
        {
            q.push(node->left);
        }
        if(node->right)
        {
            q.push(node->right);
        }
        
    }
    return NULL;
    
}

// void btree::delete_node(char s_target){
//     if(root==NULL)return;
//     Node* temp=root;
//     queue<Node*> treenode;
//     treenode.push(root);
//     get_parents_of_leaves();
//     //cout<<"Size of parents_of_leaves "<<parents_of_leaves.size()<<"\n";
//     //does not check root
//     if(root->name==s_target){
//         root==NULL;
//     }
//     while(!treenode.empty()){
//         temp = treenode.front();
//         treenode.pop();
//         if(temp->left!=NULL){
//             if(temp->left->name==s_target){
//                 //cout<<"found d in the left\n";
//                 if(isleaf(temp->left)){
//                     delete temp->left;
//                     temp->left = create_node(-1,'N');
//                 }
//                 else{
//                 for (int i=0; i<parents_of_leaves.size();i++) {
//                     auto parent_of_leaf=parents_of_leaves[i];
//                     if(isleaf(parent_of_leaf->left)&&(parent_of_leaf->left->val!=s_target)){
//                         //cout<<"Case: temp left parent left\n";
//                         parent_of_leaf->left->left = temp->left->left;
//                         parent_of_leaf->left->right = temp->left->right;
//                         temp->left->left = NULL;
//                         temp->left->right = NULL;
//                         delete temp->left;
//                         temp->left = parent_of_leaf->left;
                        
//                         parents_of_leaves.erase(parents_of_leaves.begin() + i);
                        
//                         parent_of_leaf->left=create_node(-1,'N');
//                         break;
//                     }
//                     else if(isleaf(parent_of_leaf->right)&&(parent_of_leaf->right->val!=s_target)){
//                         //cout<<"Case: temp left parent right\n";
//                         parent_of_leaf->right->left = temp->left->left;
//                         parent_of_leaf->right->right = temp->left->right;
//                         temp->left->left = NULL;
//                         temp->left->right = NULL;
//                         delete temp->left;
//                         temp->left = parent_of_leaf->right;
//                         parent_of_leaf->right=create_node(-1,'N');
//                         parents_of_leaves.erase(parents_of_leaves.begin() + i);
//                         break;
//                     }
//                 }
//             }
//             }
//             treenode.push(temp->left);
//         }
//         if(temp->right!=NULL){
//            if(temp->right->name==s_target){
//                if(isleaf(temp->right)){
//                     delete temp->right;
//                     temp->right = create_node(-1,'N');
//                 }
//                //cout<<"found d in the right\n";
//                 else{
//                     for (int i=0; i<parents_of_leaves.size();i++) {
//                     auto parent_of_leaf=parents_of_leaves[i];
//                     if(isleaf(parent_of_leaf->left)&&(parent_of_leaf->left->val!=s_target)){
//                         //cout<<"Case: temp right parent left\n";
//                         parent_of_leaf->left->left = temp->right->left;
//                         parent_of_leaf->left->right = temp->right->right;
//                         temp->right->left = NULL;
//                         temp->right->right = NULL;
//                         delete temp->right;
//                         temp->right = parent_of_leaf->left;
//                         parents_of_leaves.erase(parents_of_leaves.begin() + i);
                        
                        
//                         parent_of_leaf->left=create_node(-1,'N');
//                         break;
//                     }
//                     else if(isleaf(parent_of_leaf->right)&&(parent_of_leaf->right->val!=s_target)){
//                         //cout<<"Case: temp right parent right\n";
//                         parent_of_leaf->right->left = temp->right->left;
//                         parent_of_leaf->right->right = temp->right->right;
//                         temp->right->left = NULL;
//                         temp->right->right = NULL;
//                         delete temp->right;
//                         temp->right = parent_of_leaf->right;
//                         parent_of_leaf->right=create_node(-1,'N');
//                         parents_of_leaves.erase(parents_of_leaves.begin() + i);
//                         break;
//                     }
//                 }
//             }
//            }
//             treenode.push(temp->right);
//         }
//     }
//     return;
// }       
    

// void btree::delete_node(char s_target)
// {
//     queue<Node*> treenode;
//     queue<Node*> q;
//     Node* temp = NULL;
//     Node* parent_of_leaf = NULL;
//     Node* leaf = NULL;
//     if(!root)return;
//     if(root->name==s_target)
//     {
//         parent_of_leaf = get_parent_of_first_leaf(s_target);
//         if(isleaf(parent_of_leaf->left)&&parent_of_leaf->left->name!=s_target)
//           {
              
//               //cout<<"got leaf\n";
//               leaf = parent_of_leaf->left;
//               //cout<<"the leaf is"<<leaf->val<<leaf->name<<"\n";
//           }
//         else
//           {
//               //cout<<"got leaf\n";
//               leaf = parent_of_leaf->right;
//               //cout<<"the right leaf is"<<leaf->val<<leaf->name<<"\n";
//           }
          
//         leaf->left = root->left;
//           leaf->right = root->right;
//           //delink match from children
//           root->left = NULL;
//           root->right = NULL;
//           //cout<<"deleting\n";
//           root = leaf;
//           //delete temp->left;
//           if(parent_of_leaf->left==leaf)
//           {
//               parent_of_leaf->left=NULL;
//           }
//           else
//           {
//               parent_of_leaf->right = NULL;
//           }
          

//     }
    
//     treenode.push(root);
//     while(!treenode.empty())
//     {
//         temp = treenode.front();
//         treenode.pop();
//         if(temp->left!=NULL)
//         {
//             treenode.push(temp->left);
//             //if match
//             if(temp->left->name==s_target)
//             {
//                 //cout<<"left match\n";
//                 //leaf case
//                 // if(isleaf(temp->left))
//                 // {
//                 //     //cout<<"leaf case left\n";
//                 //     leaf = temp->left;
//                 //     //delete leaf;
//                 //     temp->left = NULL;
//                 //     //cout<<"leaf case left done\n";
                    
                    
//                 // }
//                 //non-leaf case
//                 if(!isleaf(temp->left))
//                 {
//                   //cout<<"obtaining parent\n";
//                   parent_of_leaf = get_parent_of_first_leaf(s_target);
//                   if((temp->left==parent_of_leaf))
//                   {
//                       if(isleaf(parent_of_leaf->left)&&parent_of_leaf->left->name!=s_target)
//                       {
//                           temp->left->val = parent_of_leaf->left->val;
//                           temp->left->name = parent_of_leaf->left->name;
//                           parent_of_leaf->left = NULL;
//                       }
                      
//                       if(isleaf(parent_of_leaf->right)&&parent_of_leaf->right->name!=s_target)
//                       {
//                           temp->left->val = parent_of_leaf->right->val;
//                           temp->left->name = parent_of_leaf->right->name;
//                           parent_of_leaf->right = NULL;
//                       }
                      
                      
                      
//                   }
                  
//                   else
//                   {
//                           //cout<<"obtained parent\n";
//                           //adding children of match to leaf
//                           if(isleaf(parent_of_leaf->left)&&parent_of_leaf->left->name!=s_target)
//                           {
//                               //cout<<"got leaf\n";
//                               leaf = parent_of_leaf->left;
//                           }
//                           else
//                           {
//                               //cout<<"got leaf\n";
//                               leaf = parent_of_leaf->right;
//                           }
//                           //cout<<"setting children\n";
//                           leaf->left = temp->left->left;
//                           leaf->right = temp->left->right;
//                           //delink match from children
//                           //cout<<"delinking\n";
//                           temp->left->left = NULL;
//                           temp->left->right = NULL;
//                           //cout<<"deleting\n";
//                           //delete temp->left;
//                           temp->left = leaf;
//                           if(parent_of_leaf->left==leaf)
//                           {
//                               parent_of_leaf->left=NULL;
//                           }
//                           else
//                           {
//                               parent_of_leaf->right = NULL;
//                           }
                          
//                           }
                          
//                         }
            
//             }
//         }
        
//         if(temp->right!=NULL)
//         {
//             treenode.push(temp->right);
//             //if match
            
//             if(temp->right->name==s_target)
//             {
//                 //cout<<"right match\n";
//                 //leaf case
//                 // if(isleaf(temp->right))
//                 // {
//                 //   //cout<<"leaf case right\n";
//                 //     leaf = temp->right;
//                 //     // delete leaf;
//                 //     temp->right = NULL;
//                 //     //cout<<"leaf case done\n";
//                 // }
//                 //non-leaf case
//                 if(!isleaf(temp->right))
//                 {
//                   //cout<<"obtaining parent\n";
//                   parent_of_leaf = get_parent_of_first_leaf(s_target);
                  
//                   if((temp->right==parent_of_leaf))
//                   {
//                       if(isleaf(parent_of_leaf->left)&&parent_of_leaf->left->name!=s_target)
//                       {
//                           temp->right->val = parent_of_leaf->left->val;
//                           temp->right->name = parent_of_leaf->left->name;
//                           parent_of_leaf->left = NULL;
//                       }
                      
//                       if(isleaf(parent_of_leaf->right)&&parent_of_leaf->right->name!=s_target)
//                       {
//                           temp->right->val = parent_of_leaf->right->val;
//                           temp->right->name = parent_of_leaf->right->name;
//                           parent_of_leaf->right = NULL;
//                       }
                      
                      
                      
//                   }
                  
                  
//                   else
//                   {
                     
//                          //adding children of match to leaf
//                       //cout<<"obtained parent\n";
//                       if(isleaf(parent_of_leaf->left)&&parent_of_leaf->left->name!=s_target)
//                       {
//                           leaf = parent_of_leaf->left;
//                       }
//                       else
//                       {
//                           leaf = parent_of_leaf->right;
//                       }
//                       //cout<<"right linked children to leaf\n";
//                       leaf->left = temp->right->left;
//                       leaf->right = temp->right->right;
//                       //delink match from children
//                       //cout<<"right: delinked children\n";
//                       temp->right->left = NULL;
//                       temp->right->right = NULL;
//                       //cout<<"right deleting node\n";
//                       //delete temp->right;
//                       //cout<<"right: chaining match\n";
//                       temp->right = leaf;
//                       if(parent_of_leaf->left==leaf)
//                       {
//                           parent_of_leaf->left=NULL;
//                       }
//                       else
//                       {
//                           parent_of_leaf->right = NULL;
//                       } 
//                   }
                  
                  
                  
                  
//                 }
            
//             }
//         }
        
        
//     }
    
    
//     q.push(root);
//     while(!q.empty())
//     {
//         auto node=q.front();
//         q.pop();
//         if(node->left)
//         {
//             q.push(node->left);
//         }
//         if(node->right)
//         {
//             q.push(node->right);
//         }
//         if(isleaf(node)&&node->name==s_target)
//         {
//             auto parent=find_parent(node);
//             if(parent->left==node)
//             {
//                 parent->left == NULL;
//             }
            
//             else if(parent->right==node)
//             {
//                 parent->right == NULL;
//             }
            
            
//         }
        
//     }
    
// }




void btree::delete_node(char target)
{
    queue<Node*>q;
    Node* temp = NULL;
    Node* parent_of_leaf;
    Node* parent=NULL;
    if(root==NULL)return;
    q.push(root);
    
    while(!q.empty())
    {
        temp = q.front();
        q.pop();
        if(temp->left)
        {
            q.push(temp->left);
        }
        if(temp->right)
        {
            q.push(temp->right);
        }
        
        if((temp->name==target)&&(!isleaf(temp)))
        {
            parent_of_leaf=get_parent_of_first_leaf(target);
            if(parent_of_leaf==NULL)return;
            if((isleaf(parent_of_leaf->left))&&(parent_of_leaf->left->name!=target))
            {
                auto leaf = parent_of_leaf->left;
                temp->val = leaf->val;
                temp->name = leaf->name;
                parent_of_leaf->left = NULL;
            }
            else if((isleaf(parent_of_leaf->right))&&(parent_of_leaf->right->name!=target))
            {
                auto leaf = parent_of_leaf->right;
                temp->val = leaf->val;
                temp->name = leaf->name;
                parent_of_leaf->right = NULL;
            }
            
        }
        if((temp->name==target)&&(isleaf(temp)))
        {
            parent = find_parent_of_leaf(temp);
            if(parent==NULL){
                root=NULL;
                return;
            } 
            if(parent->left==temp)
            {
                parent->left = NULL;
            }
            else
            {
                parent->right = NULL;
            }
        }        
    }
}


Node* btree::first_blank(){
    if(root==NULL)return root;
    Node* temp = root;
    queue<Node*> treenode;
    treenode.push(root);
    while(!treenode.empty()){
        temp = treenode.front();
        treenode.pop();
    
        if(temp->left==NULL)return temp;
        treenode.push(temp->left);
        if(temp->right==NULL)return temp;
        treenode.push(temp->right);
    }
    return NULL;
}



void btree::insert(){
     if (root != NULL) 
            {
             Node* node;
             node = first_blank();
             if (node->left==NULL){
                 node->left=create_tree();
             }
             else if(node->right==NULL){
                 node->right=create_tree();
             }
            }
        else
            {
            root = create_tree();
            }
};

void btree::preorder(Node* rr, int target) {
    
    if(rr==NULL)return;
    if(rr->val>target){
        
        cout<<rr->name<<" ";
    }
    preorder(rr->left, target);
    preorder(rr->right, target);
};

void btree::preorder(int target) {
 preorder(root, target);
};

bool btree::isleaf(Node* p){
    if(p==NULL) return false;
    if((p->left==NULL)&&(p->right==NULL)){
        return true;
    }
    return false;
}

void btree::get_parents_of_leaves(){
    if(root==NULL)return;
    Node* temp=root;
    queue<Node*> treenode;
    treenode.push(root);
    while(!treenode.empty()){
        temp = treenode.front();
        treenode.pop();
        if(temp->left!=NULL){
            if(isleaf(temp->left)){
                parents_of_leaves.push_back(temp);
            }
            treenode.push(temp->left);
        }
        if(temp->right!=NULL){
            if(isleaf(temp->right)){
                parents_of_leaves.push_back(temp);
            }
            treenode.push(temp->right);
        }
    }
    return;
}

int btree::search(Node* rr, char target) {
    if(!rr) return 0;
    if(rr->name==target){
        return 1+search(rr->left, target)+search(rr->right,target);
        }
    else{
        return search(rr->left, target)+search(rr->right,target);
    }
   
};

int btree::search(char target){
    int val = search(root,target);
    return val;
};


tuple<int, int> btree::find_leaf_nonleaf(int val_target) {
    int leaf = 0;
    int non_leaf = 0;
    if(root==NULL)return {0,0};;
    Node* temp;
    queue<Node*> treenode;
    treenode.push(root);
    while(!treenode.empty()){
        temp = treenode.front();
        treenode.pop();
        if(temp->val==val_target){
            if(isleaf(temp)){
                leaf+=1;
            }
            else if(!isleaf(temp)){
                non_leaf+=1;
            }
        };
        if(temp->left!=NULL){
            treenode.push(temp->left);
        }
        if(temp->right!=NULL){
            treenode.push(temp->right);
        }
    }
    return  {leaf, non_leaf};
}

int main()
{
    btree t;
   
    int T;
    cin>>T;
    while(T--)
    {
        int operation;
        cin>>operation;
        if (operation==1)
        {
            t.insert();
        }
        if (operation==2)
        {
            char s;
            cin>>s;
            int count = t.search(s);
            for(int i=0; i<count; i++)
            {
                t.delete_node(s);
            }
            
        }
        if (operation==3)
        {
            char s;
            cin>>s;
            int count;
            count = t.search(s);
            cout<<count<<endl;    
        }
        if (operation==4)
        {
            int target;
            cin>>target;
            int leaf=0,non_leaf=0;
            auto p = t.find_leaf_nonleaf(target);
            leaf = get<0>(p);
            non_leaf = get<1>(p);
            cout<<leaf<<" "<<non_leaf<<endl;    
        }
        if (operation==5)
        {
            int target;
            cin>>target;
            t.preorder(target);
            cout<<endl;
        }
    }
   

    return 0;
};


