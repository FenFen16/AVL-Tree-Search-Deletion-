#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node* left;
	struct node* right;
	int ht;//height of node
};
struct node* root = NULL;

int height (struct node* root){
	int lh, rh;
	
	if (root == NULL){
		return 0;
	}
	if (root->left == NULL){
		lh = 0;
	}
	else{
		lh = 1 + root->left->ht;
	}
	if (root->right == NULL){
		rh = 0;
	}
	else {
		rh = 1 + root->right->ht;
	}
	if (lh > rh)
		return lh;
	return rh;
}

struct node* rotate_left(struct node* root)
{
    struct node* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;
 
    // update the heights of the nodes
    root->ht = height(root);
    right_child->ht = height(right_child);
 
    // return the new node after rotation
    return right_child;
}

struct node* rotate_right(struct node* root)
{
    struct node* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;
 
    // update the heights of the nodes
    root->ht = height(root);
    left_child->ht = height(left_child);
 
    // return the new node after rotation
    return left_child;
}

int balance_factor(struct node* root){
	int lh, rh;
	
	if (root == NULL){
		return 0;
	}
	if (root->left == NULL){
		lh = 0;
	}
	else{
		lh = 1 + root->left->ht;
	}
	if (root->right == NULL){
		rh = 0;
	}
	else {
		rh = 1 + root->right->ht;
	}
	return lh - rh;
}

// Buatlah node dengan fungsi yang sama dengan BST 
struct node* create_node(int data){
	struct node* new_node = (struct node*) malloc (sizeof(struct node));
	new_node->data = data;
	new_node->right = NULL;
	new_node->left = NULL;
	
	return new_node;
}

// Insert untuk menambah node baru dengan variasi balance factor
struct node* insert (struct node* root, int data){
	if(root == NULL){
		struct node* new_node = create_node(data);
		root = new_node;
	}
	else if ( data > root->data){
		root->right = insert(root->right, data);
		
		//if unbalanced, rotate!
		if (balance_factor(root) == -2){
			if (data > root->right->data){//case RR
				root = rotate_left(root);
			}
			else{ //case RL
				root->right = rotate_right(root->right);
				root = rotate_left(root);
			}			
		}		
	}
	else{
		root->left = insert(root->left, data);
		
		if (balance_factor(root) == 2){
			//CASE LL
			if (data < root->left->data){ 
				root = rotate_right(root);
			}
			//CASE LR
			else{
				root->left = rotate_left(root->left);
				root = rotate_right(root);

			}
		}
	}
	//get height of node
	root->ht = height(root);
	return root;
}


// Fungsi untuk menghapus node dengan nilai tertentu
struct node* delete_node(struct node* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->data) {
        root->left = delete_node(root->left, key);
    } else if (key > root->data) {
        root->right = delete_node(root->right, key);
    } else {
        // Node ditemukan, lakukan proses penghapusan
        if (root->left == NULL || root->right == NULL) {
            // Jika node memiliki satu atau tidak ada anak
            struct node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                // Jika tidak ada anak, maka root dihapus
                temp = root;
                root = NULL;
            } else {
                // Jika hanya memiliki satu anak, root digantikan dengan anak tersebut
                *root = *temp;
            }
            free(temp);
        } else {
            // Jika node memiliki dua anak
            // Cari successor inorder (node terkecil di subtree kanan)
            struct node* temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            // Salin data successor inorder ke root
            root->data = temp->data;
            // Hapus successor inorder dari subtree kanan
            root->right = delete_node(root->right, temp->data);
        }
    }

    // Jika tree hanya memiliki satu node atau tidak ada node
    if (root == NULL) {
        return root;
    }

    // Jangan lupa update ketinggian node
    root->ht = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));

    // Lakukan penyeimbangan AVL tree
    int balance = balance_factor(root);

    // Kasus LL
    if (balance > 1 && balance_factor(root->left) >= 0) {
        return rotate_right(root);
    }

    // Kasus LR
    if (balance > 1 && balance_factor(root->left) < 0) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    // Kasus RR
    if (balance < -1 && balance_factor(root->right) <= 0) {
        return rotate_left(root);
    }

    // Kasus RL
    if (balance < -1 && balance_factor(root->right) > 0) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

// Fungsi untuk mencari node dengan nilai tertentu
struct node* search(struct node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    if (root->data < key) {
        return search(root->right, key);
    }
    return search(root->left, key);
}

// inorder traversal of the tree
void inorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }
 
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
 
// preorder traversal of the tree
void preorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }
 
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}
 
 
 
 
// postorder traversal of the tree
void postorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }
 
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}




int main(){
	
	// Lakuukan insert sesuai dengan permintaan soal
	root = insert(root, 10);
	root = insert(root, 15); 
	root = insert(root, 20); 
	root = insert(root, 9);
	root = insert(root, 5);
	root = insert(root, 16);
	root = insert(root, 17);
	root = insert(root, 8);
	root = insert(root, 6);
	
	
	// Berikan mark sebelum dan sesudah data didelete
	printf("Before:\n");
	preorder(root);
	
	root = delete_node(root, 9);
	puts("");
	
	printf("After deletion (9) :\n");
	preorder(root);
	puts("");
	
	int key = 20;
	struct node* result = search(root, key);
	
	if (result != NULL) {
		printf("Node with data %d found.\n", key);
	} else {
		printf("Node with data %d not found.\n", key);
	}
	
	return 0;
}
