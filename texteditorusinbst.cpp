#include <bits/stdc++.h>
using namespace std;

typedef struct text{
	int key;
	struct text* left;
	struct text* right;
	int height;
}text_t;

text_t* stk[100];
int top=-1;

void createstk(){
	top=-1;}

void push(text_t * tree_node){
	if(top==100){
		printf("Stack limit reached");
		exit(1);}
	stk[++top]=tree_node;}

text_t * pop(){
	if(top==-1){
		printf("Stack is empty, underflow");
		exit(1);}
	return stk[top--];}
void remove_stk(){
	top=-1;}

void insert_line(text_t *txt, int index, char * new_line);
text_t * create_text(){
    text_t * root= (text_t *) malloc(sizeof(text_t));
    root->key=0;
    root->left=NULL;
    root->right=NULL;
    root->height=0;
    insert_line(root,1,NULL);
return root;}

int length_text(text_t * txt){
	if(txt==NULL||txt->left==NULL){
		return 0;}
	if(((char*)txt->left->left==NULL)&&txt->right==NULL){
		return 0;
	}else{
		int count=0;
		if(txt->right==NULL){
			return 0;}
		if(txt->right->left==NULL){
			return 1;
		}else{
			while(txt->right!=NULL){
				count=count+txt->key;
				txt=txt->right;}
			if(txt->key==0){
				count=count+1;}}
		return count-1;}}

char * get_line(text_t *txt, int index){
	if(txt==NULL){
		return NULL;
	}else{
		if(index==0){
			return NULL;}
		if(index==length_text(txt)+1){
			return NULL;}
		if(index>length_text(txt)+1){
			return NULL;}
		while(txt->right!=NULL){
			if(index<=txt->key){
				txt=txt->left;
			}else if(index>txt->key){
				index=index-txt->key;
				txt=txt->right;}}
		return (char*)txt->left;}}

int stk_empty(){
	if(top==-1){
		return 1;
	}else{
		return 0;}}

int height(text_t * txt){
	if(txt==NULL){
		return 0;}
	int left = txt->left->height;
	int right = txt->right->height;
	int height= 0;
	if(left<=right){
		height=right+1;
	}else{
		height=left+1;
	} return height;}

void left_rotation(text_t * node){
	text_t *tmp_node;
	int tmp_key;
	tmp_node = node->left;
	tmp_key = node->key;
	node->left = node->right;
	//node->key=node->key+1;
	node->key = node->key+node->right->key;
	node->right = node->left->right;
	node->left->right = node->left->left;
	node->left->left = tmp_node;
	node->left->key = tmp_key;}

void right_rotation(text_t * node){
	text_t *tmp_node;
	int tmp_key;
	tmp_node = node->right;
	tmp_key = node->key;
	node->right = node->left;
	node->key = node->left->key;
	node->left = node->right->left;
	node->right->left = node->right->right;
	node->right->right = tmp_node;
	node->right->key = tmp_key-node->key;}

void insert_line(text_t *txt, int index, char * new_line) {
	if(txt==NULL){
		return;
	}else if( txt->left == NULL ){ 
		if(index>length_text(txt)+1){
			index=length_text(txt)+1;}
		txt->left = (struct text*) new_line;
		txt->key = 0;
		txt->height = 0;
		txt->right = NULL;
	}else{
		if(index>length_text(txt)+1){
			index=length_text(txt)+1;}
		createstk();
		while(txt->right!=NULL){
			push(txt);
			if(index<=txt->key){
				txt->key=txt->key+1;
				txt=txt->left;
			}else if(index>txt->key){
				index=index-txt->key;
				txt=txt->right;}}
		
		text_t * old_node=(text_t *) malloc(sizeof(text_t));
		old_node->key=0;
		old_node->left=txt->left;
		old_node->right=txt->right;
		old_node->height=0;

		text_t * new_node=(text_t *) malloc(sizeof(text_t));
		new_node->key=0;
		new_node->left=(struct text*)new_line;
		new_node->right=NULL;
		new_node->height=0;

		if(index-txt->key==0){
		txt->left=new_node;
		txt->right=old_node;
		txt->height=height(txt);
		}else if(index-txt->key==1){
		txt->left=new_node;
		txt->right=old_node;
		txt->height=height(txt);
	
		}else{
		txt->left=old_node;
		txt->right=new_node;
		txt->height=height(txt);}

		txt->key=1;

		//balance the tree
		text_t * tmp_node=NULL;
		int finished =0;
		while( !stk_empty() && !finished ){
			int tmp_height, old_height;
			tmp_node = pop();
			old_height= tmp_node->height;
			if( tmp_node->left->height - tmp_node->right->height == 2 ){ 	
				if( tmp_node->left->left->height - tmp_node->right->height == 1 )
				{ 	right_rotation( tmp_node );
					tmp_node->right->height =  tmp_node->right->left->height + 1;
					tmp_node->height = tmp_node->right->height + 1;}
				else{ 
					left_rotation( tmp_node->left );
					right_rotation( tmp_node );
					tmp_height =
					tmp_node->left->left->height;
					tmp_node->left->height = tmp_height + 1;
					tmp_node->right->height = tmp_height + 1;
					tmp_node->height = tmp_height + 2;}
			}else if( tmp_node->left->height - tmp_node->right->height == -2 ){ 
				if( tmp_node->right->right->height -tmp_node->left->height == 1 ){ 	
						left_rotation( tmp_node );
						tmp_node->left->height =tmp_node->left->right->height + 1;
						tmp_node->height = tmp_node->left->height + 1;}
					else{
						right_rotation( tmp_node->right );
						left_rotation( tmp_node );
						tmp_height = tmp_node->right->right->height;
						tmp_node->left->height = tmp_height + 1;
						tmp_node->right->height = tmp_height + 1;
						tmp_node->height = tmp_height + 2;}}
			else /* update height even if there
			was no rotation */{ 
				if( tmp_node->left->height > 	tmp_node->right->height )
					tmp_node->height = tmp_node->left->height + 1;
				else
					tmp_node->height =	tmp_node->right->height + 1;}
			if( tmp_node->height == old_height )
				finished = 1;}
			remove_stk();}}

void append_line(text_t *txt, char * new_line){
	if(txt==NULL){
		return;
	}else{
		int total_line=length_text(txt);
		insert_line(txt,total_line+1,new_line);}}

char * set_line(text_t *txt, int index, char * new_line) {
	if(txt==NULL){
		return NULL;	
	}else{
		while(txt->right!=NULL){
			if(index<=txt->key){
				txt=txt->left;
			}else if(index>txt->key){
				index=index-txt->key;
				txt=txt->right;}}
		if(index==1){
			char * temp = (char*)txt->left;
			txt->left=(struct text*)new_line;
			return temp;
		}else{
			return NULL;}}}

char * delete_line(text_t *txt, int index){
text_t * init_text=txt;
    if(txt==NULL){
    	return NULL;
    }else{
    	int length=length_text(txt);
    	//Check index with maxlength
    	if(index>length){
	    	return NULL;
	    }else{
		//Initialize stk
		    createstk();
		text_t * uppernode;
		text_t * sel_node;
		text_t * other_node;
		while(txt->right!=NULL){
			push(txt);
			uppernode=txt;
			if(index<=txt->key){
				sel_node=txt->left;
				other_node=txt->right;
				txt->key=txt->key-1;
				txt=txt->left;
			}else{
				index=index-txt->key;
				sel_node=txt->right;
				other_node=txt->left;
				txt=txt->right;}}
		//Pop the last node
		pop();
		uppernode->left=other_node->left;
		uppernode->right=other_node->right;
		uppernode->key=other_node->key;
		uppernode->height=other_node->height;

		text_t * tmp_node=NULL;
		int finished=0;
		
		while( !stk_empty() && !finished ){
			int tmp_height, old_height;
			tmp_node = pop();
			old_height= tmp_node->height;
		
			if( tmp_node->left->height - tmp_node->right->height == 2 ){ 	
				if( tmp_node->left->left->height - tmp_node->right->height == 1 )
				{ 	right_rotation( tmp_node );
					tmp_node->right->height =  tmp_node->right->left->height + 1;
					tmp_node->height = tmp_node->right->height + 1;}
				else{ 
					left_rotation( tmp_node->left );
					right_rotation( tmp_node );
					tmp_height =
					tmp_node->left->left->height;
					tmp_node->left->height = tmp_height + 1;
					tmp_node->right->height = tmp_height + 1;
					tmp_node->height = tmp_height + 2;}
			}else if( tmp_node->left->height - tmp_node->right->height == -2 ){ 
				if( tmp_node->right->right->height -	tmp_node->left->height == 1 ){ 	
						left_rotation( tmp_node );
						tmp_node->left->height =tmp_node->left->right->height + 1;
						tmp_node->height = tmp_node->left->height + 1;}
					else{
						right_rotation( tmp_node->right );
						left_rotation( tmp_node );
						tmp_height = tmp_node->right->right->height;
						tmp_node->left->height = tmp_height + 1;
						tmp_node->right->height = tmp_height + 1;
						tmp_node->height = tmp_height + 2;}}
			else /* update height even if there
			was no rotation */
		      { if( tmp_node->left->height > 	tmp_node->right->height )
					tmp_node->height = tmp_node->left->height + 1;
				else
					tmp_node->height =	tmp_node->right->height + 1;}
			if( tmp_node->height == old_height )
				finished = 1;}
			remove_stk();
			return (char *)sel_node->left;}}}

void print(text_t* root){
	cout<<endl;
	cout<<endl;
    text_t* temp=root;
    for(int i=1;i<=length_text(temp);i++){
        cout<<i<<"."<<get_line(root,i)<<endl;}}

int main(){ 
	system("cls");     
    cout<<"\t\t\tTEXT EDITOR USING ROPE\n";
	int i, tmp; text_t *root,*temp; char c[100];
    int ind ,choice,choice1;
	  root = create_text();
      append_line(root,"" );
      insert_line(root,1,"ADVANCED DATA STRUCTURES");
	  insert_line(root,2,"PROJECT DEMO");
	  insert_line(root,3,"TEXT EDITOR");
	  insert_line(root,4,"USING ROPE");
      print(root);
    do{
        cout<<"\n\t\t\t\tMENU";
        cout<<"\n\t\t\t1.INSERT \n\t\t\t2.DELETE \n\t\t\t3.FIND\n\t\t\t4.FIND AND REPLACE \n\nEnter your choice: ";
        cin>>choice;
        switch( choice ){
        case 1:
				   cout<<"ENTER THE INDEX";
				   cin>>ind;
                   cout<<"\n ENTER THE TEXT\n";
                   cin>>c;
                   insert_line(root,ind,c);
                   cout<<endl;break;

        case 2:
                    cout<<"\n ENTER THE INDEX:";
                    cin>>ind;
                    if(delete_line( root,ind)== NULL){
                        cout<<"THE INDEX: "<<ind<<" NOT IN THE FILE";}
                    cout<<endl;
                    break;
                    
        case 3:  
		            cout<<"\n ENTER THE INDEX TO FIND THE STRING:";
                    cin>>ind;
                    cout<<get_line(root,ind);
                    break;

        case 4:     
                    temp=root;
                    cout<<"\nREPLACE WITH : ";
                    cin>>c;
                    cout<<"\n ENTER THE INDEX:";
                    cin>>ind;
                    if( get_line(temp,ind)!=NULL )
                        cout<<set_line(temp,ind,c);
                    else
                        cout<<"\nNot in Text\n";
                    break;

        default:
                    cout<<"\nINVALID OPTION";}
					print(root);
        cout<<"\n \n 1 - CONTINUE \n 0 - EXIT";
        cin>>choice1;
    }while( choice1 );}