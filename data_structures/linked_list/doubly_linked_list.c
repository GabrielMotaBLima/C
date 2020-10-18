#include <stdio.h>
#include <stdlib.h>

// Standard type variable for list values
typedef double type;

// Doubly linked list struct
typedef struct list {
    type value;
    struct list * next, * prev;
} List;

// Create list function
List * create (type value)
{
    List * new_list = (List *) malloc (sizeof (List));
    
    new_list -> value = value;
    new_list -> next = NULL;
    new_list -> prev = NULL;
    
    return new_list;
}

// Search list function
// 1 means "exist" and 0 means "not exist"
int search (List * list, type value) {
    if (list == NULL) return 0;
    if (list -> value == value) return 1;
    search (list -> next, value);
}

// Insertion by position into the list
List * insert (List * list, type value, int pos)
{
    // List NULL case
    if (list == NULL)
    {
          list = create(value);
          return list;
    }
    
    // Position existing case
    if (pos > 0)
    {
        List * cpy = list, * tmp = cpy;
        int flag = 1, index = 1, size = 0;
                
        while (tmp != NULL)
        {
            size++;
            tmp = tmp -> next;
        }
        
        // First position case
        if (pos == 1)
        {
            List * new_node = create(value);
            new_node -> next = cpy;
            cpy -> prev = new_node;
            list = new_node;
            
            return new_node;
        }
        
        // Position existing in list range case
        if (size + 2 > pos)
        {
            while (cpy -> next != NULL && index < pos)
            {
                flag++;
                index++;
                cpy = cpy -> next;
            }
            
            List * new_node = (List *) malloc (sizeof (List));
            new_node -> value = value;
            
            // Position into list with no poiting for NULL
            if (flag == pos)
            {
                cpy -> prev -> next = new_node;
                new_node -> next = cpy;
                new_node -> prev = cpy -> prev;
                cpy -> prev = new_node;
            }
            
            // Last position case
            if (flag < pos)
            {
                new_node -> next = cpy->next;
                new_node -> prev = cpy;
                cpy -> next = new_node;
            }
        }
        return list;
    }
}

// Deletion by position into the list
List * delete (List * list, int pos)
{
    // List NULL case
    if (list == NULL)
          return list;
    
    // Position existing case
    if (pos > 0)
    {
        List * cpy = list, * tmp = cpy;
        int flag = 1, index = 1, size = 0;
                
        while (tmp != NULL)
        {
            size++;
            tmp = tmp -> next;
        }
        
        // First position case
        if (pos == 1)
        {
            if (size == 1) return NULL;
            
            cpy = cpy -> next;
            cpy -> prev = NULL;
            
            return cpy;
        }
        
        // Position existing in list range case
        if (size + 2 > pos)
        {
            while (cpy -> next != NULL && index < pos)
            {
                flag++;
                index++;
                cpy = cpy -> next;
            }
            
            if (flag == pos)
            {   
                // Position into list with no poiting for NULL
                if (cpy -> next != NULL)
                {
                    cpy -> prev -> next = cpy -> next;
                    cpy -> next -> prev = cpy -> prev;
                }
                
                // Last position case
                else cpy -> prev -> next = NULL;
            }
        }
        
        return list;
    }
}

// Print list function
void print (List * list)
{
    if (list != NULL)
    {
        printf("%f\t", list->value);
        print(list->next);
    }
}

int main () {
   
    List * my_list = NULL;
    type node_value = 0;
    int searching;
  
    my_list = create (node_value);
    my_list = insert (my_list, 3, 1);
    my_list = insert (my_list, 5, 3);
    my_list = insert (my_list, 10, 3);
    my_list = insert (my_list, 20, 3);
    
    print(my_list);
    searching = search(my_list, 20);
    printf("\n%d\n", searching);
    
    my_list = delete (my_list, 1);
    my_list = delete (my_list, 1);
    my_list = delete (my_list, 1);
    my_list = delete (my_list, 1);
    
    print(my_list);
    searching = search(my_list, 20);
    printf("\n%d\n", searching);
    
    return 0;
}
