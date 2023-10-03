#include <stdio.h>
#include <stdlib.h>

struct node{
  int value;
  struct node *right, *left;
};

struct node *novy(int value){
	struct node *novy = malloc(sizeof(struct node));
	novy->value = value;
	novy->right = NULL;
	novy->left  = NULL;
	return novy; 	
}

struct node *search(struct node *root ,int key){
	struct node *act = root;
	while (1)
		if (key > act->value)
			if (act->right != NULL)	
				act = act->right;
			else
				return NULL;		 		
		else if (key < act->value)
			if (act->left != NULL)	
				act = act->left;
			else
				return NULL;
		else
			return act;
}

void insert(struct node *root ,int key){
	struct node *act = root;
	while (1)
		if (key > act->value)
			if (act->right != NULL)	
				act = act->right;
			else{
				act->right = novy(key);
				break;
			}		 		
		else if (key < act->value)
			if (act->left != NULL)	
				act = act->left;
			else{
				act->left = novy(key);
				break;
			}
		else
			break;
}

void preorder(struct node *root){
	if(root != NULL){
        printf("....%d  \n", root->value); 
        preorder(root->left); 
        preorder(root->right); 
    } 
}

void preeorder(struct node *root){
	printf("%d\n",root->value);
	if (root->left != NULL)
		preeorder(root->left);
	struct node *pom = root->left;
	root->left = (struct node*) malloc(sizeof(struct node));
	root->left->value = root->value;
	root->left->right = NULL;
	root->left->left = pom;
	if (root->right != NULL){
		printf("sss\n");
		printf("%d\n\n\n\n",root->value);
		preeorder(root->right);
	}
	
}

int main() { 
	
	int value, i;
	
	struct node *root = novy(3);
	
	
	for (i=0; i<1000000; i++){
		//value = rand()*rand();
		//insert(root, 2);
		insert(root, 2);
		insert(root, 1);
		insert(root, 4);
		insert(root, 5);
	}
	
	preorder(root);
	
	preeorder(root);
	
	printf("\n\n\n");
	preorder(root);
	
	/*for (i=0; i<10; i++){
		scanf("%d",&value);
		insert(root, value);	
	}
	for (i=0; i<10; i++){
		scanf("%d",&value);
		if (search(root, value) == NULL)
			printf("nenasiel som\n");
		else
			printf("nasiel som\n");	
	}	*/
	return 0;
} 
