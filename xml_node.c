/*
 * xml.c
 *
 *  Created on: 2017��5��22��
 *      Author: xfwangqiang
 */

/*========================================================*
 * �����޸ļ�¼��
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���>
 *  V1.0.0  2017-06-05  xfwangqiang     ����
 *========================================================*/


#include <stdio.h>
#include <stdlib.h>
#include "xml_node.h"
#include "xml_string.h"
#include "xml.h"


//============================================================================
// �������ƣ�new_xml_node
// �������ܣ�����һ���µ�XML�ڵ����--���캯��
//
// ��������� 1 -- �ڵ�����
//			2 -- �ڵ�ֵ
//			3 -- �ڵ�����
// ���������
// ����ֵ���ڵ����ָ��
// ˵��������һ���µ�XML�ڵ����--���캯��
//============================================================================
struct xmlnode *new_xmlnode(char *name, char *value, enum xmlnode_type type )
{
	struct xmlnode *node = (struct xmlnode *)malloc( sizeof(struct xmlnode) );
	node->name = name;
	node->value = value;
	node->type = type;
	node->father = NULL;
	node->prev = NULL;
	node->next = NULL;
	node->child = NULL;
	node->getname = xmlnode_getname;
	node->getvalue = xmlnode_getvalue;
	return node;
}


//============================================================================
// �������ƣ�del_xml_node
// �������ܣ�ɾ��һ��XML�ڵ����--��������
//
// ��������� 1 -- �ڵ�����
//			2 -- �ڵ�ֵ
//			3 -- �ڵ�����
// ���������
// ����ֵ���ڵ����ָ��
// ˵����ɾ��һ��XML�ڵ����--��������
//============================================================================
void del_xmlnode( void *this )
{
	struct xmlnode *node = (struct xmlnode *)this;
	xml_free( node->name );
	xml_free( node->value );
	node->name = NULL;
	node->value = NULL;
	node->type = 0;
	node->father = NULL;
	node->prev = NULL;
	node->next = NULL;
	node->child = NULL;
	node->getname = NULL;
	node->getvalue = NULL;
	xml_free( node );
}


//============================================================================
// �������ƣ�xmlnode_init
// �������ܣ���ʼ��һ���µ�XML�ڵ����--���캯��
//
// ��������� 1 -- �ڵ����
// 			2 -- �ڵ�����
//			3 -- �ڵ�ֵ
//			4 -- �ڵ�����
// ���������
// ����ֵ��
// ˵������ʼ��һ���µ�XML�ڵ����--���캯��
//============================================================================
void xmlnode_init( void *this , char *name, char *value, enum xmlnode_type type )
{
	struct xmlnode *node = (struct xmlnode *)this;
	node->name = name;
	node->value = value;
	node->type = type;
	node->father = NULL;
	node->prev = NULL;
	node->next = NULL;
	node->child = NULL;
	node->getname = xmlnode_getname;
	node->getvalue = xmlnode_getvalue;
}


void xmlnode_create( char *name, char *value, enum xmlnode_type type )
{	
	struct xmlnode *node = (struct xmlnode *)malloc( sizeof(struct xmlnode) );
	node->name = xml_strnew( name );
	node->value = xml_strnew( value );
	node->type = type;
	node->father = NULL;
	node->prev = NULL;
	node->next = NULL;
	node->child = NULL;
	node->getname = xmlnode_getname;
	node->getvalue = xmlnode_getvalue;
}


//============================================================================
// �������ƣ�xml_get_node_name
// �������ܣ��õ�һ���ڵ���������
//
// ��������� 1 -- �ڵ��������
// ���������	2 -- �������
// ����ֵ�����ֵĳ���
// ˵�����õ�һ���ڵ���������
//============================================================================
int xmlnode_getname(  void *this, char *buffer  )
{
	struct xmlnode *node = (struct xmlnode *)this;
	return xml_strcpy( buffer, node->name );
}



//============================================================================
// �������ƣ�xml_get_node_name
// �������ܣ��õ�һ���ڵ�����ֵ
//
// ��������� 1 -- �ڵ��������
// ���������	2 -- ���ֵ
// ����ֵ�����ֵ�ֵ���ַ�������
// ˵�����õ�һ���ڵ�����ֵ
//============================================================================
int xmlnode_getvalue(  void *this, char *buffer  )
{
	struct xmlnode *node = (struct xmlnode *)this;
	return xml_strcpy( buffer, node->value);
}



//============================================================================
// �������ƣ�xmlnode_getfather
// �������ܣ��õ�һ���ڵ���󸸽ڵ�
//
// ��������� 1 -- �ڵ��������
// ���������
// ����ֵ���ڵ����ڸ��ڵ�
// ˵�����õ�һ���ڵ���󸸽ڵ�
//============================================================================
struct xmlnode * xmlnode_getfather(void *this)
{
	struct xmlnode *node = (struct xmlnode *)this;
	if (NULL == node)
	{
		return NULL;
	}
	return node->father;
}


//============================================================================
// �������ƣ�xmlnode_setfather
// �������ܣ�����һ���ڵ���󸸽ڵ�
//
// ��������� 1 -- �ڵ��������
//			  2 -- ���ڵ����
// ���������
// ����ֵ���ڵ����ڸ��ڵ�
// ˵��������һ���ڵ���󸸽ڵ�
//============================================================================
int xmlnode_setfather(void *this, struct xmlnode *father)
{
	struct xmlnode *node = (struct xmlnode *)this;
	if (NULL == node)
	{
		return 0;
	}

	node->father = father;
	return 1;
}


//============================================================================
// �������ƣ�xmlnode_getchild
// �������ܣ��õ�һ���ڵ�����һ���ӽڵ�
//
// ��������� 1 -- �ڵ��������
// ���������
// ����ֵ���ڵ�����һ���ӽڵ�
// ˵�����õ�һ���ڵ�����һ���ӽڵ�
//============================================================================
struct xmlnode * xmlnode_getchild(void *this)
{
	struct xmlnode *node = (struct xmlnode *)this;
	if (NULL == node)
	{
		return NULL;
	}
	return node->child;
}


//============================================================================
// �������ƣ�xmlnode_getprev
// �������ܣ��õ�һ���ڵ������һ���ֵܽڵ�
//
// ��������� 1 -- �ڵ��������
// ���������
// ����ֵ���ڵ������һ���ֵܽڵ�
// ˵�����õ�һ���ڵ������һ���ֵܽڵ�
//============================================================================
struct xmlnode * xmlnode_getprev(void *this)
{
	struct xmlnode *node = (struct xmlnode *)this;
	if (NULL == node)
	{
		return NULL;
	}
	return node->prev;
}


//============================================================================
// �������ƣ�xmlnode_getnext
// �������ܣ��õ�һ���ڵ������һ���ֵܽڵ�
//
// ��������� 1 -- �ڵ��������
// ���������
// ����ֵ���ڵ������һ���ֵܽڵ�
// ˵�����õ�һ���ڵ������һ���ֵܽڵ�
//============================================================================
struct xmlnode * xmlnode_getnext(void *this)
{
	struct xmlnode *node = (struct xmlnode *)this;
	if (NULL == node)
	{
		return NULL;
	}
	return node->next;
}




//============================================================================
// �������ƣ�xmlnode_add
// �������ܣ���һ������������һ���ڵ����
//
// ��������� 1 -- �������ĵ�ַ
// 			  2 -- �ڵ��������
// ���������
// ����ֵ��none
// ˵����������Ԫ�ظ���
//============================================================================
int xmlnode_add( struct xmlnode **list, struct xmlnode *node )
{
	struct xmlnode *temp = NULL;
	int size = 1;
	if ( NULL == *list )
	{
		*list = node;
		node->next = NULL;
		node->prev = NULL;
	}
	else
	{
		temp = *list;
		for ( ;; )
		{
			if ( NULL == temp->next )
			{
				temp->next = node;
				node->next = NULL;
				node->prev = temp;
				size++;
				break;
			}
			temp = temp->next;
			size++;
		}
	}
	return size;
}


//============================================================================
// �������ƣ�xmlnode_remove
// �������ܣ���һ��������ɾ��һ���ڵ����
//
// ��������� 1 -- �������ĵ�ַ
// 			2 -- �ڵ��������
// ���������
// ����ֵ��none
// ˵������һ��������ɾ��һ���ڵ����
//============================================================================
int xmlnode_remove( struct xmlnode **list, struct xmlnode *node )
{
	struct xmlnode *prev, *next;

	prev = node->prev;
	next = node->next;

	if ( NULL == prev )		// head
	{
		del_xmlnode( node );
		if ( NULL == next )
		{
			// the link list has only one
			*list = NULL;
		}
		else
		{
			next->prev = NULL;
			*list = next;
		}
	}
	else
	{
		del_xmlnode( node );
		if ( NULL == next )
		{
			// the last one of link list
			prev->next = NULL;
		}
		else
		{
			prev->next = next;
			next->prev = prev;
		}
	}

	return 1;
}

//============================================================================
// �������ƣ�xml_remove_linklist
// �������ܣ�ɾ��һ���������
//
// ��������� 1 -- �������ĵ�ַ
// ���������
// ����ֵ��none
// ˵����ɾ��һ���������
//============================================================================
void xmlnode_removelinklist( struct xmlnode **list )
{
	struct xmlnode *pnode = (*list)->next;
	xmlnode_remove( list, *list );
	if ( NULL == pnode )
	{
		return ;
	}
	xmlnode_removelinklist(  list  );
}



