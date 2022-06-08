/** Spajany zoznam struktur
 *  Martin Hric
 * PRPR 2020
 */
 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define max 52

/**
 * Defined struct with attributes
 */
struct list {                                 
    char meno[50],druh[30],osetrovatel[50];
    int vyska;
    double vaha;
    long narodenie, krmenie;
    struct list * next;                        
};
typedef struct list list_z;

/**
 * Function to load from .txt into struct
 */ 
list_z *funkcia_n(){

    FILE *f;                                         
    f = fopen("zvierata.txt", "r");
    if (f == NULL) {
        printf("Zaznamy neboli nacitane\n");
    }                                                
    char line[max];
    int pocet = 0;                                  
    while (fgets(line, max, f) != NULL)                
    {
        pocet++;
    }
    rewind(f);
    int pocet_zaznamov=pocet/8;                     

    int vy;
    double va;                                      
    long na, kr;

    list_z *head = NULL;
    list_z *tmp = NULL;
    list_z *p = NULL;

    for(int i=0;i<pocet_zaznamov;i++) {
        tmp = (list_z*) malloc(sizeof(list_z));
        for (int k = 0; k < 8; k++) {                            
            fgets(line, max, f);                                
            switch (k % 8) {
                                                                              
                case 1:
                    strcpy(tmp->meno, line);                               
                    break;                                                  
                case 2:                                                     
                    strcpy(tmp->druh, line);
                    break;
                case 3:
                    vy = atoi(line);
                    tmp->vyska = vy;
                    break;
                case 4:
                    va = atof(line);
                    tmp->vaha = va;
                    break;
                case 5:
                    na = atol(line);
                    tmp->narodenie = na;
                    break;
                case 6:
                    kr = atol(line);
                    tmp->krmenie = kr;
                    break;
                case 7:
                    strcpy(tmp->osetrovatel, line);
                    break;
            }
        }
        tmp->next = NULL;
        if (head == NULL)                       
        {
            head = tmp;
        }
        else                                    
        {
            p = head;
            while(p->next!=NULL) {               
                p = p->next;                     
            }
            p->next=tmp;                        
        }
    }
    printf("Nacitalo sa %d zaznamov\n",pocet_zaznamov);   
    fclose(f);
    return head;
                                                          
}

/**
 * Function to write whole LinkedList to stdout
 */
void funkcia_v(list_z *head){
                        
    list_z *p=head;

    while (p != NULL)
    {
        int d=1;
        printf("%d.\n",d);                         
        printf("Meno: %s", p->meno);
        printf("Druh: %s", p->druh);
        printf("Vyska: %d\n", p->vyska);
        printf("Vaha: %g\n", p->vaha);
        printf("Datum narodenia: %ld\n", p->narodenie);  /
        printf("Datum krmenia: %ld\n", p->krmenie);
        printf("Meno osetrovatela: %s", p->osetrovatel);
        p = p->next;
        d++;              
    }
}

/**
 * Add new node into linkedlist
 */ 
list_z *funkcia_p(list_z *head)
{
    list_z *tmp=(list_z*) malloc(sizeof(list_z));           

    char line[max];

    int c1,vy,pocet=0;
    double va;                             
    long na, kr;

    scanf("%d", &c1);                   
    getchar();
    for(int i=0;i<7;i++){                   
        if(i==0){
            fgets(line,max,stdin);
            strcpy(tmp->meno, line);
        }
        if(i==1){
            fgets(line,max,stdin);
            strcpy(tmp->druh, line);
        }
        if(i==2){
            gets(line);
            vy = atoi(line);
            tmp->vyska = vy;
        }
        if(i==3){
            gets(line);
            va = atof(line);
            tmp->vaha = va;
        }
        if(i==4){
            gets(line);
            na = atol(line);
            tmp->narodenie = na;
        }
        if(i==5){
            gets(line);
            kr = atol(line);
            tmp->krmenie = kr;
        }
        if(i==6){
            fgets(line,max,stdin);
            strcpy(tmp->osetrovatel, line);
        }
    }
    tmp->next=NULL;                           
    if(c1==1){
        tmp->next=head;                       
        head=tmp;                             
        return head;                           
    }
    list_z *p=head;                            
    while(p!=NULL){
        pocet++;
        p=p->next;                              
    }
    p=head;                                     
    if(c1>pocet){
        for(int a=0;a<pocet-1;a++){             
            p=p->next;
        }
        tmp->next=p->next;                      
        p->next=tmp;                            
        return head;
    }
    for(int i=0;i<c1-2;i++){                 
        p=p->next;
    }
    tmp->next=p->next;                    
    p->next=tmp;

    return head;                            
}

/**
 * Function to delete node from linkedlist
 */
list_z *funkcia_z(list_z *head){

    char line[max];
    char *meno_z;
    getchar();              
    fgets(line,max,stdin);

    for(int i=0;line[i];i++){
        line[i]=tolower(line[i]);               
    }
    int pocet=0;
    list_z *p=head;
    while(p!=NULL){
        pocet++;
        p=p->next;                             
    }
    p=head;
    for(int k=0;k<pocet;k++){
        meno_z=strdup(p-> meno);               
        for(int i=0;meno_z[i];i++){
            meno_z[i]=tolower(meno_z[i]);

        }
        if(strcmp(line,meno_z)==0 && p==head){       
            head=p->next;
            free(p);
            strtok(meno_z,"\n");                   
            printf("Zviera s menom %s bolo vymazane\n",meno_z);
            return head;
        }
        if(strcmp(line,meno_z)==0){
            list_z *tmp=p->next;
            list_z *p1=head;
            for(int o=0;o<k-1;o++){
                p1=p1->next;                       
            }
            p1->next=tmp;
            free(p);
            strtok(meno_z,"\n");
            printf("Zviera s menom %s bolo vymazane\n",meno_z);
            return head;
        }
        p=p->next;
    }
    return head;            
}

/**
 *function to show all animals that are not fed till some date
 */  
void funkcia_h(list_z *head){
    long d;                                         
    int a=1;
    scanf("%ld",&d);                                  
    list_z *tmp=head;                                 
    while(tmp!=NULL){                                 
        if(d>tmp->krmenie){
            printf("%d.\n",a);
            printf("Meno: %s", tmp->meno);                                
            printf("Druh: %s", tmp->druh);
            printf("Vyska: %d\n", tmp->vyska);
            printf("Vaha: %g\n", tmp->vaha);
            printf("Datum narodenia: %ld\n", tmp->narodenie);
            printf("Datum krmenia: %ld\n", tmp->krmenie);
            printf("Meno osetrovatela: %s", tmp->osetrovatel);
            a++;
        }
        tmp=tmp->next;
    }
    if(a==1){                                                           
        printf("Vsetky zvierata boli k datumu %ld nakrmene\n",d);
    }
}

/**
 * function to update date of feeding 
 */ 
void funkcia_a(list_z *head){
    char meno[max];
    long d;               
    getchar();
    fgets(meno,max,stdin);         
    scanf("%ld",&d);                   
    list_z *tmp=head;
    while(tmp!=NULL){                       
        if(strcmp(meno,tmp->meno)==0){       
            tmp->krmenie=d;                 
            strtok(meno,"\n");         // https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
            printf("Zviera s menom %s bolo naposledy krmene dna %ld\n",meno,d);
            return;                          
        }
        tmp=tmp->next;       
    }
}

/**
 * to end program, free the allocated memory
 */ 
void funkcia_k(list_z *head){
    list_z *tmp;                  
    while(head!=NULL){

        tmp=head;
        head=head->next;
        free(tmp);
    }
}

/**
 * function to revert the linked list
 */ 
list_z *otoc_zoznam(list_z *head){
    list_z *next = NULL;
    list_z *tmp = head;
    list_z *pre = NULL;
    if(tmp==NULL||tmp->next==NULL)
        return head;
    else {
        while (tmp != NULL) {
            next = tmp->next;
            tmp->next = pre;
            pre = tmp;
            tmp = next;
        }
        head = pre;
        return head;
    }
}

int main(){
    list_z *HEAD=NULL;
    char funkcia;
    while(1)
    {
        scanf("%c",&funkcia);
        {
            switch (funkcia) {
                case 'n':
                    HEAD=funkcia_n();
                    break;
                case 'v':
                    funkcia_v(HEAD);
                    break;
                case 'p':
                    HEAD=funkcia_p(HEAD);
                    break;
                case 'z':
                    HEAD=funkcia_z(HEAD);
                    break;
                case 'h':
                    funkcia_h(HEAD);
                    break;
                case 'a':
                    funkcia_a(HEAD);
                    break;
                case 'o':
                    HEAD=otoc_zoznam(HEAD);
                    break;
                case 'k':
                    funkcia_k(HEAD);
                    exit(0);
            }
        }
    }
}