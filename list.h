

struct process {
    int id;
    int arrival;
    int runtime;
    int priority;
    int memsize;
    int last_process;  // (1) means last process in all processes
    int last_in_second;  // (1) means last process in this second
    int remaining_time;
    int pid;
    //int TA;
    //int waiting;
};

struct node {
    struct process* data;
    struct node* next;
};

struct list {
    int count;
    struct node* head;
};

void initList(struct list* ls){
    ls->head = NULL;
    ls->count=0;
}

void add(struct list* ls , struct process* item){
    if(ls->head == NULL){
        ls->head = (struct node*) malloc(sizeof(struct node));
        ls->head->data = item;
        ls->head->next = NULL;
    }
    else{
        struct node* ptr = ls->head;
        while(ptr->next){
            ptr = ptr->next;
        }
        struct node* new_data = (struct node*) malloc(sizeof(struct node));
        new_data->data = item;
        new_data->next = NULL;
        ptr->next = new_data;
    }
}

struct process* search(struct list* ls , int arrival){
     struct node* ptr = ls->head;
     while(ptr){
        if(ptr->data->arrival == arrival)
            return ptr->data;
        ptr = ptr->next;
     }
     return NULL;
}

void clear(struct list* ls , struct process* item){
    if(item == ls->head->data){
        struct node* ptr = ls->head;
        ls->head = ptr->next;
        free(ptr);
    }
    else{
        struct node* ptr = ls->head;
        while(ptr->next->data != item)
            ptr = ptr->next;
        
        struct node* rm = ptr->next;
        ptr->next = rm->next;
        free(rm);
    }
    ls->count--;
}

void display(struct list* ls){
    struct node* ptr = ls->head;
    while(ptr){
        printf("%d\t" , ptr->data->id);
        ptr = ptr->next;
    }
    printf("\n");
}

struct process* get_first(struct list* ls){
    if(ls->head != NULL)
    {
        struct process* ptr = ls->head->data;
        clear(ls , ptr);
        return ptr;
    }
    else
        return NULL;
}

int isEmpty(struct list* ls){
    if(ls->head == NULL)
        return 1;
    else
        return 0;
}

void add_sjf(struct list* ls , struct process* item){
    if(ls->head == NULL){
        ls->head =(struct node*) malloc(sizeof(struct node));
        ls->head->data = item;
        ls->head->next = NULL;
        ls->count++;
        return;
    }
    else{
        struct node* ptr = ls->head;
        struct node* back = ls->head;
        while(ptr){
            if(ptr->data->runtime <= item->runtime){
                back = ptr;
                ptr=ptr->next;
            }
            else{
                struct node* new_node = (struct node*) malloc(sizeof(struct node));
                if(ptr==ls->head){
                    struct node* temp = (struct node*) malloc(sizeof(struct node));
                    temp = ls->head;
                    new_node->data = item;
                    new_node->next = back;
                    ls->head = new_node;
                    ls->count++;
                    return;
                }
                new_node->data = item;
                new_node->next = ptr;
                back->next = new_node;
                return;
            }
        }
        struct node* new_node = (struct node*) malloc(sizeof(struct node));
        new_node->data = item;
        new_node->next = back->next;
        back->next = new_node;
        ls->count++;
    }
}


void add_PIR(struct list* ls , struct process* item){
    if(ls->head == NULL){
        ls->head =(struct node*) malloc(sizeof(struct node));
        ls->head->data = item;
        ls->head->next = NULL;
        ls->count++;
        return;
    }
    else{
        struct node* ptr = ls->head;
        struct node* back = ls->head;
        while(ptr){
            if(ptr->data->priority <= item->priority){
                back = ptr;
                ptr=ptr->next;
            }
            else{
                struct node* new_node = (struct node*) malloc(sizeof(struct node));
                if(ptr==ls->head){
                    struct node* temp = (struct node*) malloc(sizeof(struct node));
                    temp = ls->head;
                    new_node->data = item;
                    new_node->next = back;
                    ls->head = new_node;
                    ls->count++;
                    return;
                }
                new_node->data = item;
                new_node->next = ptr;
                back->next = new_node;
                return;
            }
        }
        struct node* new_node = (struct node*) malloc(sizeof(struct node));
        new_node->data = item;
        new_node->next = back->next;
        back->next = new_node;
        ls->count++;
    }
}

#define VECTOR_INIT_CAPACITY 6
#define UNDEFINE  -1
#define SUCCESS 0
#define VECTOR_INIT(vec) vector vec;\
vector_init(&vec)



//========= begin basic DS ===========
typedef struct Pair
{
    int lower_bound;
    int upper_bound;
} Pair;

Pair Pair__create(int lower_bound,int upper_bound)
{
    Pair p;
    p.lower_bound = lower_bound;
    p.upper_bound = upper_bound;
    return p;
}

void Pair__print(Pair p) {
    printf("(%d, %d)\n", p.lower_bound, p.upper_bound);
}


//========= end basic DS ===========

//Store and track the stored data
typedef struct sVectorList
{
    Pair*items;
    int capacity;
    int total;
} sVectorList;
//structure contain the function pointer
typedef struct sVector vector;
struct sVector
{
    sVectorList vectorList;
//function pointers
    int (*pfVectorTotal)(vector *);
    int (*pfVectorResize)(vector *, int);
    int (*pfVectorAdd)(vector *, Pair);
    int (*pfVectorSet)(vector *, int, void *);
    int (*pfVectorGetFirst)(vector *, int);
    int (*pfVectorGetSecond)(vector *, int);
    int (*pfVectorDelete)(vector *, int);
    int (*pfVectorFree)(vector *);
};
int vectorTotal(vector *v)
{
    int totalCount = UNDEFINE;
    if(v)
    {
        totalCount = v->vectorList.total;
    }
    return totalCount;
}
int vectorResize(vector *v, int capacity)
{
    int  status = UNDEFINE;
    if(v)
    {
        void **items = realloc(v->vectorList.items, sizeof(void *) * capacity);
        if (items)
        {
            v->vectorList.items = items;
            v->vectorList.capacity = capacity;
            status = SUCCESS;
        }
    }
    return status;
}
int vectorPushBack(vector *v, Pair item)
{
    int  status = UNDEFINE;
    if(v)
    {
        if (v->vectorList.capacity == v->vectorList.total)
        {
            status = vectorResize(v, v->vectorList.capacity * 2);
            if(status != UNDEFINE)
            {
                v->vectorList.items[v->vectorList.total++] = item;
            }
        }
        else
        {
            v->vectorList.items[v->vectorList.total++] = item;
            status = SUCCESS;
        }
    }
    return status;
}
int vectorSet(vector *v, int index, Pair item)
{
    int  status = UNDEFINE;
    if(v)
    {
        if ((index >= 0) && (index < v->vectorList.total))
        {
            v->vectorList.items[index] = item;
            status = SUCCESS;
        }
    }
    return status;
}
int vectorGetFirst(vector *v, int index,Pair p)
{
    int readData = 0;
    if(v)
    {
        if ((index >= 0) && (index < v->vectorList.total))
        {
             readData = v->vectorList.items[index].lower_bound;
        }
    }
    return readData;
}




int vectorGetSecond(vector *v, int index,Pair p)
{
    int readData = 0;
    if(v)
    {
        if ((index >= 0) && (index < v->vectorList.total))
        {
             readData = v->vectorList.items[index].upper_bound;
        }
    }
    return readData;
}

int vectorFree(vector *v)
{
    int  status = UNDEFINE;
    if(v)
    {
        free(v->vectorList.items);
        v->vectorList.items = NULL;
        status = SUCCESS;
    }
    return status;
}
void vector_init(vector *v)
{
    //init function pointers
    v->pfVectorTotal = vectorTotal;
    v->pfVectorResize = vectorResize;
    v->pfVectorAdd = vectorPushBack;
    v->pfVectorSet = vectorSet;
    v->pfVectorGetFirst = vectorGetFirst;
    v->pfVectorGetSecond = vectorGetSecond;
    v->pfVectorFree = vectorFree;
    //v->pfVectorDelete = vectorDelete;
    //initialize the capacity and allocate the memory
    v->vectorList.capacity = VECTOR_INIT_CAPACITY;
    v->vectorList.total = 0;
    v->vectorList.items = malloc(sizeof(void *) * v->vectorList.capacity);
}