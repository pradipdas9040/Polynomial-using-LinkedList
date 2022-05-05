#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int deg;
    double cof;
    struct Node *next;
};

void push(struct Node** head_ref,int h)
{
	struct Node* new,*tail;
	double c;
	do
	{
	    new=(struct Node*) malloc(sizeof(struct Node));
	    printf("Enter the coefficient of x^%d: ",h);
    	scanf("%lf",&c);
    	new->cof=c;
    	new->deg=h;
    	new->next=NULL;
    	if(*head_ref==NULL)
    	{
    	    *head_ref=new;
    	    tail=new;
    	}
    	else
    	{
    	    tail->next = new;
            tail = new;
    	}
    	h--;
	}while(h>=0);
}

struct Node* insert(struct Node* head,double c, int d)
{
    struct Node *temp,*new=(struct Node*) malloc(sizeof(struct Node));
    new->cof=c;
    new->deg=d;
    new->next=NULL;
    if(head==NULL|| d>head->deg)
    {
        new->next=head;
        head=new;
    }
    else
    {
        temp=head;
        while(temp->next!=NULL && temp->next->deg>=d)
        {
            temp=temp->next;
        }
        new->next=temp->next;
        temp->next=new;
    }
    return head;
}

void print(struct Node* head_ref)
{
    char *q=" ";
    struct Node *temp;
    temp=head_ref;
    while (temp != NULL)
    {
        printf("%s (%.2lf x^%d)",q,temp->cof,temp->deg);
        q="+";
        temp = temp->next;
    }
}

void polmadd(struct Node *head)
{
    struct Node *ptr1=head,*ptr2=head,*head2=NULL,*temp;
    while(ptr2->deg!=0)
    {
        if(ptr1->next==ptr2->next)
            ptr2=ptr2->next;
        while(ptr1->deg==ptr2->deg)
        {
            ptr1->cof=ptr1->cof+ptr2->cof;
            ptr2=ptr2->next;
        }
        head2=insert(head2,ptr1->cof,ptr1->deg);
        while(ptr1->next!=ptr2->next)
        {
            ptr1=ptr1->next;
        }
    }
    head2=insert(head2,ptr2->cof,ptr2->deg);
    print(head2);
}

void addpoly(struct Node *head1,struct Node *head2)
{
	struct Node *ptr1=head1,*ptr2=head2,*head3=NULL;
	while(ptr1!=NULL && ptr2!=NULL)
	{
		if(ptr1->deg==ptr2->deg)
		{
			head3=insert(head3,ptr1->cof+ptr2->cof,ptr1->deg);
			ptr1=ptr1->next;
			ptr2=ptr2->next;
		}
		else if(ptr1->deg>ptr2->deg)
		{
			head3=insert(head3,ptr1->cof,ptr1->deg);
			ptr1=ptr1->next;
		}
		else if(ptr1->deg<ptr2->deg)
		{
			head3=insert(head3,ptr2->cof,ptr2->deg);
			ptr2=ptr2->next;
		}
	}
	print(head3);
}

void polymu( struct Node *head1,struct Node *head2)
{
    struct Node *ptr1=head1,*ptr2=head2,*head3=NULL;
    while(ptr1!=NULL)
    {
        while(ptr2!=NULL)
        {
            head3=insert(head3,ptr1->cof*ptr2->cof,ptr1->deg+ptr2->deg);
            ptr2=ptr2->next;
        }
        ptr1=ptr1->next;
        ptr2=head2;
    }
    polmadd(head3);
}

void diff(struct Node *head)
{
    struct Node *head4=NULL,*tail,*temp=head;
    do
    {
        struct Node *new=(struct Node *)malloc(sizeof(struct Node));
        new->cof=(temp->cof)*(temp->deg);
        new->deg=(temp->deg-1);
        if(head4==NULL)
        {
        	head4=new;
            tail=new;
		}
        else
        {
            tail->next=new;
            tail = new;
        }
        temp=temp->next;
    }while(temp->deg>0);
    print(head4);   
}

int main()
{
    int hd1,hd2;
    struct Node *head1=NULL,*head2=NULL;
    printf("\nEnter the highest degree of 1st polynomial: ");
    scanf("%d",&hd1);
    push(&head1,hd1);
    printf("\nEnter the highest degree of 2nd polynomial: ");
    scanf("%d",&hd2);
    push(&head2,hd2);
    printf("\nAdded polynomial is: ");
    addpoly(head1,head2);
    printf("\nThe multiplication of polynomial is: ");
    polymu(head1,head2);
    printf("\nDifferentiation of the 1st polynomial is: ");
    diff(head1);
    printf("\nDifferentiation of the 2nd polynomial is: ");
    diff(head2);
    return 0;
}

