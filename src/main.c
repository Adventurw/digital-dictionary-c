 #include<stdio.h>

#include<stdlib.h>

struct dictionary {

	struct dictionary *left,*right;

	char word[50],meaning[200],synonym[200];

}*Root = NULL;



typedef struct dictionary d;

int check(char a[100],char b[100]);

void Search();

void Insert_word(d *);

void View(d *);





int check(char a[100],char b[100]) {

	int i,j,c; // c is counter

	for(i=0,j=0; a[i]!='\0' && b[j]!='\0'; i++,j++) {

		if(a[i]>b[j]) {

			c=1;

			break;

		} else if(b[i]>a[j]) {

			c=-1;

			break;

		} else {

			c=0;

		}

	}

	if(c==1)

		return 1;

	else if(c==-1)

		return -1;

	else

		return 0;

}

void Search() {
    if(Root == NULL)
    {
        printf("Dictionary is empty.\n");
        return;
    }

	char w[200]; // w for words

	d *ptr;

	int flag=0; //counter

	ptr=Root;

	printf("\n search word:");

	scanf("%s",w);

    	if(check(w,ptr->word)>0){

			ptr=ptr->right;}

		else if(check(w,ptr->word)<0){

			ptr=ptr->left;}

		else if(check(w,ptr->word)==0) {

			flag=1;

			printf("\nMeaning|Synonym\n\n");

			printf(" %s|%s",ptr->meaning,ptr->synonym);

		}

	if(flag == 0){

		printf("\n Searched word not found!");

		printf("\a");}

}

void Insert_word(d* temp) {

	d *ptr,*par;

	int flag=0; //

	ptr=Root;



	if(Root==NULL)

		Root=temp;

	else {

		while(ptr != NULL) {

			if(check(temp->word,ptr->word)>0) {

				par=ptr;

				ptr=ptr->right;

			}



			else if(check(temp->word,ptr->word)<0) {

				par=ptr;

				ptr=ptr->left;

			}



			else if(flag==0 && ptr==NULL) {

				flag=1;

				printf("\n Word exists\n");

				printf("\a");

				break;

			}



		}

		if(flag==0 && ptr==NULL) {

			if(check(par->word,temp->word)==1)

				par->left=temp;

			else if(check(par->word,temp->word)==-1)

				par->right	= temp;

		}

	}

}

void View(d *ptr) {

		FILE *fp;char ch[80];

	fp= fopen("dictionary words.txt","r");

	if(fp == NULL)

	{

		printf("\n Unable to Open!");

	}

	else{

		while(!feof(fp) )

		{   fgets(ch,80,fp);

			puts(ch);

			

		}

	}

	if(Root ==NULL) {

		printf("\nempty dictionary");

	} else if(ptr!=NULL) {

		View(ptr->left);

        printf("\n\nword\t|meaning\t|synonym\n\n");

		printf("\n%s\t|%s\t|%s",ptr->word,ptr->meaning,ptr->synonym);

		View(ptr->right);

		}

}

int main(int argc,char const *argv[]) {

	int ch;

	d *temp;

	while(ch != 4) {

		printf("\n\n1.Search\n\n2.Insert\n\n3.View\n\n4.Quit\n\n CHOOSE:");

		scanf("%d",&ch);

		switch(ch) {

			case 1:

				printf("\n\t\t============================================\n");

				printf("\t\t-----------------WORD SEARCH------------------\n");

				printf("\t\t==============================================\n");

				Search();

				break;

			case 2:

				temp=(d *)malloc(sizeof(d));

				temp->left=NULL;

				temp->right=NULL;

				printf("\n\t\t================================================\n");

				printf("\t\t-------------------------------------------------\n");

				printf("\t\t----------------INSERTION OF WORDS---------------\n");

				printf("\t\t-------------------------------------------------\n");

				printf("\t\t=================================================\n");

				printf("\n insert word:");

				scanf("%s",temp->word);

				printf("\n insert meaning:");

				scanf("%s",temp->meaning);

				printf("\n insert synonyms:");

				scanf("%s",temp->synonym);

				Insert_word(temp);

				break;

			case 3:

				printf("\n\t\t===========================================\n");

	            printf("\t\t--------------                  -------------\n");

	            printf("\t\t==============Viewing Dictionary=============\n");

	            printf("\t\t--------------                  -------------\n");

	            printf("\t\t=============================================\n"); 

			    View(Root);

		    	break;

			case 4:

				printf("\t\t========THANKS FOR USING OUR DICITONARY=======\n\a");

				exit(0);

				

		}

	}

	return 0;

}

