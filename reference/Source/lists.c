/********************************************************************
 *    Descrição: Funções referentes a manipulações de Lista
 *    			 encadeadas.
 *
 *    Autor: Marco Antonio Vargas
 *
 *    Data:18/02/2009
 *******************************************************************/

#include "lists.h"
#include "def_types.h"

#define THIS_FILE   "lists.c"


//Declaração de Váriaveis externas
//extern Status_VoIP  StatusVoIP;

//---------------------------------------------------------------
//#define ATTR_MAY_ALIAS      __attribute__((__may_alias__))
/**
 * This structure describes generic list node and list. The owner of this list
 * must initialize the 'value' member to an appropriate value (typically the
 * owner itself).
 */
typedef struct
{
    DECL_LIST_MEMBER(void);
} t_list;
//ATTR_MAY_ALIAS; /* may_alias avoids warning with gcc-4.4 -Wall -O2 */


//Prototipos de funções
void list_init(void * node)
{
    ((t_list*)node)->next = ((t_list*)node)->prev = node;
}

/**
 * Check that the list is empty.
 * @param node  The list head.
 * @return Non-zero if the list is empty, or zero if it is not empty.
 *
 * PJ_INLINE(int) pj_list_empty(const pj_list_type * node)
 *  {
 *   return ((pj_list*)node)->next == node;
 *  }
 *
 */
int list_empty(const void * node)
{
    return ((t_list*)node)->next == node;
}


/*
 *
 */
void list_insert_after(void *pos, void *node)
{
    ((t_list*)node)->prev = pos;
    ((t_list*)node)->next = ((t_list*)pos)->next;
    ((t_list*) ((t_list*)pos)->next) ->prev = node;
    ((t_list*)pos)->next = node;
}

/*
 *
 */
void list_insert_before(void *pos, void *node)
{
    list_insert_after(((t_list*)pos)->prev, node);
}


/**
 * Insert the node to the back of the list. This is just an alias for
 * #list_insert_before().
 *
 * @param list  The list.
 * @param node  The element to be inserted.
 */
void list_push_back(void *list, void *node)
{
    list_insert_before(list, node);
}


/*
 *
 */
void* list_find_node(void *list, void *node)
{
    t_list *p = (t_list *) ((t_list*)list)->next;
    while (p != list && p != node)
        p = (t_list *) p->next;

    return p==node ? p : NULL;
}

/*
 *
 */
void* list_search(void *list, void *value, int (*comp)(void *value, const void *node))
{
    t_list *p = (t_list *) ((t_list*)list)->next;
    while (p != list && (*comp)(value, p) != 0)
        p = (t_list *) p->next;

    return p==list ? NULL : p;
}

/*
 *
 */
int list_size(const void *list)
{
    const t_list *node = (const t_list*) ((const t_list*)list)->next;
    int count = 0;

    while (node != list) {
        ++count;
        node = (t_list*)node->next;
    }

    return count;
}

/*
 *
 */
void link_node(void *prev, void *next)
{
    ((t_list*)prev)->next = next;
    ((t_list*)next)->prev = prev;
}

/*
 *
 */
void list_erase(void *node)
{
    link_node( ((t_list*)node)->prev, ((t_list*)node)->next);
    list_init(node);
}

