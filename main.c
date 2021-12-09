/** This program should print the following output for each text file: 
    1. The height of a tree 
    2. The number of distinct words 
    3. The number of words 
    4. The tree where each word indented as its depth
**/ 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define WORDLEN 128 

//-------------------------------------------------------
typedef struct node node; 
struct node
{
	char word[WORDLEN];
	int freq;     
	node *lchild, *rchild;  

};

//-------------------------------------------------------
char *getword(char *w, FILE *fp); 

// to insert a word to the tree rooted by rp 
void insert(node **rp, char *w); 

// to return a pointer of a node containing string s 
node *search(node *root, char *w); 

// to delete a subtree rooted by the root 
void delete_tree(node *root); 

// to return the height of a subtree rooted by the root 
int height(node *root); 

// to return the number of distinct words of a subtree 
int count(node *root); 

// to return the number of words of a subtree 
int total(node *root);

// to print a subtree whose root is indented by depth 
int print(node *root, int depth, FILE *fout);

//-------------------------------------------------------
char *getword(char *w, FILE *fp)
{
	int ch;
	char *s = w; 
	
	while(!isalpha(ch=fgetc(fp)) && ch != EOF)
		;
	if (ch == EOF)
	{
		return NULL;
	}
		
	*s++ = ch; 
	while(isalpha(ch=fgetc(fp)))
		*s++ = ch;
	*s = '\0';
	return w; 

}

// to insert a word to the tree rooted by rp 
void insert(node **rp, char *w)
{
	if ((*rp) == NULL)
	{

		(*rp) = (node*)malloc(sizeof(node));  
		strcpy((*rp)->word, w);
		(*rp)->freq =1; 
		(*rp)->lchild = NULL; 
		(*rp)->rchild = NULL;
	}
	else if (strcmp(w, (*rp)->word) < 0)
	{
		insert(&(*rp)->lchild, w);
	}
	else if (strcmp(w, (*rp)->word) > 0) 
	{
		insert(&(*rp)->rchild, w);
	}
	else  
	{
		(*rp)->freq +=1; // same word, then increment frequency
	}
	
} 

 //to return a pointer of a node containing string s 
node *search(node *root, char *w)
{
	node index; 

	if (strcmp(w, root->word)< 0)
	{ 
		return search(root->lchild, w);
	}
	else if (strcmp(w, *root->word) > 0)
	{
		return search(root->rchild, w);
	}
	else
	{
		return root;
	}


}

// to delete a subtree rooted by the root 
void delete_tree(node *root)
{
	if (root != NULL)
	{
		delete_tree(root->lchild);
		delete_tree(root->rchild);
		free(root);
	}
}

int maxNum(int a, int b)
{
	return(a > b ? a : b);
}

// to return the height of a subtree rooted by the root 
int height(node *root)
{
	if (root == NULL)
	{
		return -1;
	}
	return (maxNum(height(root->lchild) ,height(root->rchild)) + 1);
	
}

// to return the number of distinct words of a subtree 
int count(node *root)
{
	if(root == NULL)
		return 0;
	return count(root->lchild) + count(root->rchild) +1; 

}

// to return the number of words of a subtree 
int total(node *root)
{
	if (root == NULL)
		return 0;
	return total(root->lchild) + total(root->rchild) + root->freq;
}

// to print a subtree whose root is indented by depth 
int print(node *root, int depth, FILE *fout)
{
	if (root == NULL)
		return 0;
	int d = depth - height(root);
	
	for (int i = 0; i < d; i++)
	{
		fprintf(fout , " ");
	}
	fprintf(fout , "%s (%d)\n", root->word, root->freq , d );
	int a= print(root->lchild, depth, fout);
	int b = print(root->rchild, depth, fout);
	return 1;
	

}

int main (int argc, char* argv[])
{
	// store each work read from the fule 
	char current_word[WORDLEN]; 
	int depth =0; 
	int counter =0; 
	if (argc < 2)
	{
		printf("NO INPUT FILE IN ARGUMENT!!");
		return 0;
	}
	char* fileName = argv[1];
	FILE *fp; 
	fp = fopen(fileName, "r");

	// root of the tree 
	node *rp = NULL;

	// read each word from the file and build the tree 
	while(getword(current_word, fp) != NULL)
	{ 
		insert(&rp, current_word); 
	}
	FILE* fout;
	fout = fopen("output.txt", "w");
	print(rp, height(rp), fout);
	printf("OUTPUT FILE CREATED");
	fprintf(fout, "--summary of %s\n", fileName);
	fprintf(fout , "Height = %d\n", height(rp));
	fprintf(fout , "number of nodes = %d\n", count(rp));
	fprintf(fout , "number of words = %d\n", total(rp));
	fclose(fp); 

	free(rp); 

}