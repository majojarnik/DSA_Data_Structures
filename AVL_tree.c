#include <stdio.h>
#include <stdlib.h>

struct node{
  	char inc;
	short height;
  	int value;
  	struct node *right, *left;
};

struct node *novy(int value){
	struct node *novy = malloc(sizeof(struct node));
	novy->value = value;
	novy->right = NULL;
	novy->left  = NULL;
	novy->height = 1;
	novy->inc = 0;
	return novy; 	
}

int k = 0;

void preorder(struct node *root){
	if(root != NULL){
        printf("%d....%d    height = %d\n",++k, root->value, root->height); 
        preorder(root->left); 
        preorder(root->right); 
    } 
}

struct node *search(struct node *root ,int value){
	struct node *act = root;
	while (1)
		if (value > act->value)
			if (act->right != NULL)	
				act = act->right;
			else
				return NULL;		 		
		else if (value < act->value)
			if (act->left != NULL)	
				act = act->left;
			else
				return NULL;
		else
			return act;
}

int max(int a, int b){
	if (a > b) 
		return a;
	return b;
}

int height(struct node *node){
	if (node == NULL)
		return 0;
	return node->height;	
}

struct node *rotationLeft(struct node *node, struct node *nodeRight){
	struct node *pom;
	
	pom = nodeRight->left;
	nodeRight->left = node;
	node->right = pom;
		
	node->height = max(height(node->left), height(node->right)) + 1;
	
	nodeRight->height = max(height(nodeRight->left), height(nodeRight->right)) + 1;
	
	return nodeRight;
}

struct node *rotationRight(struct node *node, struct node *nodeLeft){
	struct node *pom;
	
	pom = nodeLeft->right;
	nodeLeft->right = node;
	node->left = pom;
	
	node->height = max(height(node->left), height(node->right)) + 1;	
	nodeLeft->height = max(height(nodeLeft->left), height(nodeLeft->right)) + 1;
		
	return nodeLeft;
}

struct node *insert(struct node *root ,int value){
	if (root == NULL){
		root = novy(value);
		return root;
	}
	int i=1;
	struct node *act = root;
	while (1){
		i++;
		if (value > act->value)
			if (act->right != NULL)	
				act = act->right;
			else{
				act->right = novy(value);
				break;
			}		 		
		else if (value < act->value)
			if (act->left != NULL)	
				act = act->left;
			else{
				act->left = novy(value);
				break;
			}
		else
			return root;
	}
	int old;
	act = root;
	while (1){
		old = act->height;
		act->height = max(i,act->height);
		if (act->height == old)
			act->inc = 0;
		else
			act->inc = 1;	
		i--;
		if (value > act->value)
			if (act->right != NULL)	
				act = act->right;
			else
				break;		
		else if (value < act->value)
			if (act->left != NULL)	
				act = act->left;
			else
				break;
		else
			break;
	}
	
	act = root;
	struct node *prev = root;
	struct node *pom = root; 
	while (1){	
		if (height(act->left) - height(act->right) > 1 || height(act->left) - height(act->right) < -1){
			pom = act;
			while (1){
				if (value > act->value)
					if (act->right != NULL){
						if (height(act->right->left) - height(act->right->right) > 1 || height(act->right->left) - height(act->right->right) < -1){
							prev = act;
							pom = act->right;
							
						}
						act = act->right;
					}	
					else
						break;
				else if (value < act->value)
					if (act->left != NULL){
						if (height(act->left->left) - height(act->left->right) > 1 || height(act->left->left) - height(act->left->right) < -1){
							prev = act;
							pom = act->left;	
						}
						act = act->left;
					}		
					else
						break;
				else
					break;
			}	
			
			act = pom;
			
			if (height(act->left) - height(act->right) > 1 && value < act->left->value){
			//	printf("problem vlavo vlavo pri %d\n",act->value);
				if (act == root)
					act = root = rotationRight(act, act->left);
				else if (prev->left == act)
					act = prev->left = rotationRight(act, act->left);
				else
					act = prev->right = rotationRight(act, act->left);
			}
			
			if (height(act->left) - height(act->right) > 1 && value > act->left->value){
			//	printf("problem vlavo vpravo pri %d\n",act->value);
				act->left = rotationLeft(act->left, act->left->right);
				if (act == root)
					act = root = rotationRight(act, act->left);
				else if (prev->left == act)
					act = prev->left = rotationRight(act, act->left);
				else
					act = prev->right = rotationRight(act, act->left);
			}
				
			if (height(act->left) - height(act->right) < -1 && value > act->right->value){
			//	printf("problem vpravo vpravo pri %d\n",act->value);
				if (act == root)
					act = root = rotationLeft(act, act->right);
				else if (prev->left == act)
					act = prev->left = rotationLeft(act, act->right);
				else
					act = prev->right = rotationLeft(act, act->right);
			}
			
			if (height(act->left) - height(act->right) < -1 && value < act->right->value){
				//printf("problem vpravo vlavo pri %d\n",act->value);
				act->right = rotationRight(act->right, act->right->left);
				if (act == root)
					act = root = rotationLeft(act, act->right);
				else if (prev->left == act)
					act = prev->left = rotationLeft(act, act->right);
				else
					act = prev->right = rotationLeft(act, act->right);
			}
			pom = root;
			while(act != pom){
				if (value > pom->value){
					if (height(pom) - 1 > height(pom->left) && pom->inc == 1)
						pom->height--;	
					pom = pom->right;	 				
				}
				else{
					if (height(pom) - 1 > height(pom->right) && pom->inc == 1)
						pom->height--;		 
					pom = pom->left;
				}
			}
	
			return root;
		}	
		
		if (value > act->value)
			if (act->right != NULL){
				prev = act;
				act = act->right;
			}
			else
				break;
		else if (value < act->value)
			if (act->left != NULL){
				prev = act;
				act = act->left;
			}
			else
				break;
		else
			break;	

	}
	return root;	
}

int main(){ 
	int value, i;
	struct node *root = NULL;
	
	for (i=0; i<1000000; i++){
		root = insert(root, rand()*rand());
	}
	//preorder(root);

	
	
/*	for (i=0; i<10; i++){
		scanf("%d",&value);
		if (search(root, value) == NULL)
			printf("nenasiel som\n");
		else
			printf("nasiel som\n");	
	}	*/
	return 0;
} 
