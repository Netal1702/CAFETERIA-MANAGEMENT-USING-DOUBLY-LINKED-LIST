#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

struct Item
{
     char name[50];
     float rating;
     float price;
     int food_Id_No;
     struct Item *next;
     struct Item *prev;
};

int cust_id=1;
struct Item* head;
struct Item* last;
int Today_custmer=0;
float total_income=0;

struct order_List
{
    int Customer_ID;
    int items[10][2];
    float amount;
    char date[11];
    struct order_List *next;
    struct order_List *prev;
};

struct order_List* head1;
struct order_List* last1;

// BST Start
struct node {
    float key;
    struct node *left, *right;
};
// A utility function to create a new BST node
struct node* newNode(float item)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

void view(float rate){
    struct Item* temp = head;
    while(temp!=NULL)
    {
        if(temp->rating==rate){
        printf("\t%d\t%s\t%0.2f\t%0.2f\n",temp->food_Id_No,temp->name,temp->price,temp->rating);
        }
        temp=temp->next;
    }
}
// A utility function to do in order traversal of BST
void inorder(struct node* root)
{
    float key;
    if (root != NULL) {
        inorder(root->right);
        key=root->key;
        view(key);
        inorder(root->left);
    }
}
// A utility function to insert a new node with given key in BST 
struct node* insert_b(struct node* node, float key)
{
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert_b(node->left, key);
    else if (key > node->key)
        node->right = insert_b(node->right, key);

    return node;
}
// BST END

void Display_L()
{
    printf("                                                    -------------                                            \n");
    printf("---------------------------------------------------- LEADERBOARD -------------------------------------------------\n");
    printf("                                                    -------------                                            \n");
    printf("       INDEX     ITEM NAME     PRICE       RATING\n");

    struct node* root = NULL;
    inorder(root);

    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("");
}

struct Item* getnewNode(char a[],float p,float r,int f_id)
{
    struct Item* temp=(struct Item*)malloc(sizeof(struct Item));

    temp->food_Id_No=f_id;
    strcpy(temp->name,a);
    temp->rating=r;
    temp->price=p;
    temp->next=NULL;
    temp->prev=NULL;
    return temp;
}

void insert(char n[],float p,float r,int f_id)
{
     struct Item* temp1=getnewNode(n,p,r,f_id);
     if(head==NULL)
     {
        head=temp1;
        last=temp1;
     }

    else
    {
        temp1->prev=last;
        last->next=temp1;
        last=temp1;
    }

}
struct order_List* getnewNode_List()
{
    struct order_List* temp=(struct order_List*)malloc(sizeof(struct order_List));
    temp->next=temp->prev=NULL;
    return (temp);
}

void Display()
{
    printf("                                                 -------------                                            \n");
    printf("----------------------------------------------------- MENU -------------------------------------------------\n");
    printf("                                                 -------------                                            \n");
    printf("    INDEX     ITEM NAME     PRICE       RATING\n");

    struct Item* temp=head;
    if(head==NULL)
    {
        printf("Empty");
    }

    while(temp!=NULL)
    {
        printf("\t%d\t%s\t%0.2f\t%0.2f\n",temp->food_Id_No,temp->name,temp->price,temp->rating);
        temp=temp->next;
    }
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("");
}

int login()
{
      char username[20];
      char userpwd[11]; // for storing password
      int i;

      printf("Enter your User Name : ");
      scanf("%s",username);

      printf("Enter your password : ");
      scanf("%s",userpwd);

     if(strcmp(username,"Admin ") && strcmp(userpwd,"123456"))
     {
          printf("\n\nLogged In Successful\n");
          return 1;
     }

     else
    {
        printf("\n\nIncorrect username or password\n");
        return 0;
    }
}

void order()
{
    int a[10][2];
    int n,j=0,i=0;

    do{
            printf("PLEASE ENTER THE FOOD ID NUMBER AND ITS QUANTITY: ");
            for(i=0;i<2;i++)
            {
                scanf("%d",&a[j][i]);
            }
            j++;
            printf("\nDO YOU WANT ORDER MORE FOOD: \n1. YES\n2. NO\n\n...ANSWER : ");
            scanf("%d",&n);
    }while(n==1);

    float total_amount=0.0;
    char name[25];
    char Date[10];
    printf("\nENTER YOUR NAME : ");
    scanf("%s",name);
    printf("ENTER TODAY'S DATE : ");
    scanf("%s",Date);
    printf("\n-------------------------------------------------------------------------------------------------------\n");
    printf("                                          BILL                             \n");
    printf("NAME :-%s\n",name);
    printf("DATE :-%s\n",Date);

    for(int k=0;k<j;k++)
    {
        struct Item* temp=head;
        while(temp->food_Id_No!=a[k][0])
        {
            temp=temp->next;
        }

        printf("-------------------------------------------------------------------------------------------------------\n");
        printf("%d\t%s\t%d\t\t%f\n",temp->food_Id_No,temp->name,a[k][1],(a[k][1]*(temp->price)));
        total_amount+=(a[k][1]*(temp->price));
    }

    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("\nTotal Payble amount is:-\t\t%f\n",total_amount);
    printf("-------------------------------------------------------------------------------------------------------\n\n");

    struct order_List* temp2=getnewNode_List();
    temp2->amount=total_amount;
    temp2->Customer_ID=cust_id++;

    int p,s;

    for(p=0;p<j;p++)
    {
        for(s=0;s<2;s++)
        {
            temp2->items[p][s]=a[p][s];
        }
    }

    if(head1==NULL)
    {
        head1=last1=temp2;
    }

    else
    {
        last1->next=temp2;
        temp2->prev=last1;
        last1=temp2;
    }

    strcpy(temp2->date,Date);

    Today_custmer++;
    total_income+=total_amount;
}

void display_rd_List()
{
    printf("                                                       -------------                                                 \n");
    printf("\n-----------------------------------------------------ORDER HISTORY-------------------------------------------------\n");
    printf("                                                       -------------                                                 \n");
    printf("SR_NO     DATE      TOTAL AMOUNT\n");

    struct order_List* temp=head1;
    if(head1==NULL)
    {
        printf("Empty");
    }

    while(temp!=NULL)
    {
        printf("%d\t%s\t%f\t\n",temp->Customer_ID,temp->date,temp->amount);
        temp=temp->next;
    }
}

int main()
{
    head=NULL;
    last=NULL;

    insert("BURGER   ",70,9.6,1);
    insert("PIZZA    ",250,9.8,2);
    insert("HOT CAKE ",450,5.6,3);
    insert("COFFEE   ",100,7.6,4);
    insert("ICE-CREAM",50,8.4,5);
    insert("SANDWICH ",60,4.6,6);
    insert("VEG WRAP   ",80,6.6,7);
    insert("BUTTER-BREAD",35,3.4,8);
    insert("COLD DRINKS",30,8.7,9);

    int choice;
    do{
    printf("                                                      -------------                                            \n");
    printf("----------------------------------------------------- CONTROL PANEL -------------------------------------------------\n");
    printf("                                                      -------------                                            \n");
        printf("\n1....FOOD PART");
        printf("\n2....GIVE RATINGS");
        printf("\n3....ADMIN PANEL");
        printf("\n4....EXIT");

        printf("\nEnter your choice : ");
        scanf("%d",&choice);
        printf("\n");

        switch(choice)
        {
            case 1:
                printf("");
                int ex;

                do{
                    printf("1....FOOD LIST\n2....ORDER\n3....LEADERBOARD\n\n.....ANSWER : ");
                    int n;
                    scanf("%d",&n);
                    printf("");

                    switch(n)
                    {
                        case 1: Display();
                                break;
                        case 2: order();
                                break;
                        case 3: Display_L();
                                break;
                    }

                    printf("1....FOOD PART\n2....MAIN MENU\n\n.....ANSWER : ");
                    scanf("%d",&ex);
                    printf("");
                }while(ex==1);
            break;

            case 2:
                Display_L();
                float rate;
                int id;
                printf("TYPE THE FOOD ID NO. FOR WHICH YOU WANT TO GIVE RATING : ");
                scanf("%d",&id);

                struct Item* dish = find_dish(id);
                printf("GIVE RATING TO %s : ",dish->name);
                scanf("%f",&rate);
                dish->rating = rate;
                Display_L();
                break;

            case 3:
                printf("\n");
                int k=login();
                int e;
                if(k==1){
                do{
                    printf("-------------------------------------------------------------------------------------------------------\n");
                    printf("1.     ADD NEW DISH\n");
                    printf("2.     TODAY'S  TOTAL INCOME\n");
                    printf("3.     TODAY TOTAL NO OF CUSTOMER\n");
                    printf("4.     ORDER HISTORY\n");
                    printf("5      LIST OF ITEM\n");
                    printf("\n------------------------------------------------------------------------------------------------------\n");

                    int ch;
                    scanf("%d",&ch);
                    switch(ch)
                    {
                        case 1:
                            printf(" ");
                            float p;
                            float r;
                            int f_id;
                            char  n[50];

                            printf("Enter the name of Item : ");
                            scanf("%s",n);

                            printf("Enter the Price of Item : ");
                            scanf("%f",&p);

                            printf("Enter the Rating of Item : ");
                            scanf("%f",&r);

                            printf("Enter the food_id_no of Item : ");
                            scanf("%d",&f_id);

                            insert(n,p,r,f_id);
                            printf("-------------------------------------------------------------------------------------------------------\n");
                            printf("                 NEW DISH IS ADDED SUCESSFULLY.......\n");
                            printf("-------------------------------------------------------------------------------------------------------\n");
                            printf("\n");
                        break;

                        case 2:
                            printf("-------------------------------------------------------------------------------------------------------\n");
                            printf("        TODAY'S  TOTAL INCOME IS:- %f\n",total_income);
                            printf("-------------------------------------------------------------------------------------------------------\n");
                        break;

                        case 3:
                            printf("-------------------------------------------------------------------------------------------------------\n");
                            printf("        TODAY TOTAL NO OF CUSTOMER VISITED ID:-%d\n",Today_custmer);
                            printf("-------------------------------------------------------------------------------------------------------\n");
                        break;

                        case 4:
                            printf("-------------------------------------------------------------------------------------------------------\n");
                            printf("                    ORDER SUMMARY");
                            printf("-------------------------------------------------------------------------------------------------------\n");
                            display_rd_List();
                            printf("\n");
                        break;

                        case 5:
                            printf("\n");
                            Display();
                        break;
                    }
                    printf("1.ADMIN PANEL\n2.MAIN MENU\n");
                    scanf("%d",&e);

                }while(e==1);
            }
                break;
        }
    }while(choice!=4);

    printf("Thank You, Visit Again!");
    return 0;
}

