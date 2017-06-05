/*
 * xml_element.c
 *
 *  Created on: 2017��5��23��
 *      Author: xfwangqiang
 */


/*========================================================*
 * �����޸ļ�¼��
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���>
 *  V1.0.0  2017-06-05  xfwangqiang     ����
 *========================================================*/



#include <stdio.h>
#include <stdlib.h>
#include "xml_string.h"
#include "xml_element.h"
#include "xml_node.h"


// �������غ���
static int getattrvalue(char *string, char *buffer);
static struct xmlnode *setattribute(char *name, char *value);
static int getattrname(char *string, char *buffer);
static int getattrnum(char *string);


//============================================================================
// �������ƣ�xmlelement_create
// �������ܣ�����һ��Ԫ�ؽڵ�
//
// ��������� 1 -- Ԫ�ض�������
//			2 -- Ԫ�ض����ı�
// ���������
// ����ֵ��Ԫ�ؽڵ����
// ˵��������һ��Ԫ�ؽڵ�
//============================================================================
struct xmlelement *xmlelement_create( char *string, char *text, enum xmlnode_type type )
{
	struct xmlelement *element = NULL;
	char name[128] = { 0 };
	int listlen = xml_strsplit( string, ' ' );
	if ( listlen > 1 )
	{
		xml_strsplitlist( string, ' ', 0, name );
		element = (struct xmlelement *)malloc( sizeof(struct xmlelement) );
		xmlnode_init( element, xml_strnew(name), NULL, type );
		element->attribute = NULL;
		xmlelement_parserattr( element, string );
	}
	else
	{
		element = (struct xmlelement *)malloc( sizeof(struct xmlelement) );
		xmlnode_init( element, xml_strnew(string), NULL, type );
		element->attribute = NULL;
	}
	element->text = xml_strnew( text );
	element->gettag = xmlelement_gettag;
	element->getattribute = xmlelement_getattribute;
	element->gettext = xmlelement_gettext;
	return element;
}



//============================================================================
// �������ƣ�getattrnum
// �������ܣ��õ�Ԫ�����Ը���
//
// ��������� 1 -- �ַ���
// ���������
// ����ֵ��Ԫ�ص����Ը���
// ˵�����õ�Ԫ�����Ը���
//============================================================================
static int getattrnum(char *string)
{
	int size = xml_strsplit(string, '=');
	if (size > 1)
	{
		size--;
	}
	return size;
}



//============================================================================
// �������ƣ�xmlelement_getattrnum
// �������ܣ��õ�Ԫ�����Ը���
//
// ��������� 1 -- Ԫ�ض���
// ���������
// ����ֵ��Ԫ�ص����Ը���
// ˵�����õ�Ԫ�����Ը���
//============================================================================
int xmlelement_getattrnum( struct xmlelement *element )
{
	struct xmlnode *attribute;
	int size = 0;
	if (NULL == element)
	{
		return 0;
	}
	attribute = element->attribute;
	for (; NULL != attribute; size++ )
	{
		attribute = attribute->next;
	}

	return size;
}


//============================================================================
// �������ƣ�xmlelement_parserattr
// �������ܣ���������
//
// ��������� 1 -- Ԫ�ض���
//			2 -- �ַ���
// ���������
// ����ֵ��
// ˵������������
//============================================================================
void  xmlelement_parserattr( struct xmlelement *element, char *string )
{
	int index;
	char temp[128];
	char name[128];
	char value[128];
	int size = getattrnum( string );
	if ( size > 0 )
	{
		for ( index = 0; index < size; index++ )
		{
			xml_strsplitlist( string, '=', index, temp );
			getattrname( temp, name );
			xml_strsplitlist( string, '=', index + 1, temp );
			getattrvalue( temp, value );
			xmlnode_add( &(element->attribute), setattribute( name, value ) );
		}
	}
	else
	{
		element->attribute = NULL;
	}
}


//============================================================================
// �������ƣ�getattrname
// �������ܣ���ȡԪ�ص�������
//
// ��������� 1 -- Ԫ�ض�����������
//			2 -- Ԫ�ض�������ֵ
// ���������
// ����ֵ��
// ˵������ȡԪ�ص�������
//============================================================================
static int getattrname( char *string, char *buffer )
{
	int index, len;
	char temp[128] = { 0 };
	int size = xml_strsplit( string, ' ' );
	len = 0;
	if ( size <= 1 )
	{
		return 0;
	}
	for ( index = size - 1; index >= 0; index-- )
	{
		len = xml_strsplitlist( string, ' ', index, temp );
		if ( len > 0 )
		{
			xml_strcpy( buffer, temp );
			break;
		}
	}
	return len;
}


//============================================================================
// �������ƣ�getattrvalue
// �������ܣ���ȡԪ�ص�����ֵ
//
// ��������� 1 -- Ԫ�ض�����������
//			2 -- Ԫ�ض�������ֵ
// ���������
// ����ֵ��Ԫ�ص����Խڵ����
// ˵������ȡԪ�ص�����ֵ
//============================================================================
static int getattrvalue( char *string, char *buffer )
{
	int len;
	char temp[128] = { 0 };
	int size = xml_strsplit( string, '\"' );
	len = 0;
	if ( size < 3 )
	{
		return 0;
	}
	len = xml_strsplitlist( string, '\"', 1, temp );
	if ( len > 0 )
	{
		xml_strcpy( buffer, temp );
	}
	return len;
}


//============================================================================
// �������ƣ�setattribute
// �������ܣ�����Ԫ�ؽڵ������
//
// ��������� 1 -- Ԫ�ض�����������
//			2 -- Ԫ�ض�������ֵ
// ���������
// ����ֵ��Ԫ�ص����Խڵ����
// ˵��������Ԫ�ؽڵ������
//============================================================================
static struct xmlnode *setattribute( char *name, char *value  )
{
	char *newname = xml_strnew( name );
	char *newvalue = xml_strnew( value );
	return new_xmlnode( newname, newvalue, ATTRIBUTE_NODE );
}

//============================================================================
// �������ƣ�xmlelement_gettag
// �������ܣ��õ�Ԫ�ؽڵ�ı�ǩ
//
// ��������� 1 -- Ԫ�ض�������
// ��������� 2 -- Ԫ�ض�����ı��ڵ�ı�ǩ
// ����ֵ����ǩ�ĳ���
// ˵�����õ�Ԫ�ؽڵ�ı�ǩ
//============================================================================
int xmlelement_gettag( void *this, char *buffer )
{
	struct xmlelement *element = (struct xmlelement *)this;
	return xml_strcpy( buffer, element->base.name);
	// return 1;
}



//============================================================================
// �������ƣ�xmlelement_checkattribute
// �������ܣ����Ԫ�ؽڵ�������������Ƿ����
//
// ��������� 1 -- Ԫ�ض�������
//			  2 -- Ԫ�ض������Խڵ������
//			  3 -- ������ַ���
// ���������
// ����ֵ��0 -- ʧ�� 1 -- �ɹ�
// ˵�������Ԫ�ؽڵ�������������Ƿ����
//============================================================================
int xmlelement_checkattribute(void *this, char *name, char *buffer)
{
	char attr[100] = { 0 };
	int size = xmlelement_getattribute(this, name, attr);
	if (size > 0)
	{
		if (0 == xml_strcmp(attr, buffer))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return -1;
}

//============================================================================
// �������ƣ�xmlelement_getattribute
// �������ܣ��õ�Ԫ�ؽڵ������
//
// ��������� 1 -- Ԫ�ض�������
//			2 -- Ԫ�ض������Խڵ������
// ���������
// ����ֵ��none
// ˵�����õ�Ԫ�ؽڵ������
//============================================================================
int xmlelement_getattribute( void *this, char *name, char *buffer )
{
	int size = 0;
	struct xmlelement *element = (struct xmlelement *)this;
	struct xmlnode *list = NULL;
	if ( NULL == element )
	{
		return 0;
	}
	list = element->attribute;
	for ( ;; )
	{
		if ( NULL == list )
		{
			return 0;
		}
		if ( 0 == xml_strcmp(list->name, name) )
		{
			size = xml_strcpy( buffer, list->value );
			break;
		}
		list = list->next;
	}
	return size;
}



//============================================================================
// �������ƣ�xmlelement_getattrbyint
// �������ܣ��õ�Ԫ�ؽڵ�����Ե�����ֵ
//
// ��������� 1 -- Ԫ�ض�������
//			  2 -- Ԫ�ض������Խڵ������
// ��������� 3 -- Ԫ�ض������������ֵ
// ����ֵ��0 -- ʧ�� 1 -- �ɹ�
// ˵�����õ�Ԫ�ؽڵ�����Ե�����ֵ
//============================================================================
int xmlelement_getattrbyint(void *this, char *name, int *value)
{
	char buffer[100] = { 0 };
	int size = xmlelement_getattribute(this, name, buffer);
	if (size > 0)
	{
		if (xml_isint(buffer))
		{
			*value = xml_strtoint(buffer);
			return 1;
		}
	}
	return 0;
}

//============================================================================
// �������ƣ�xmlelement_getattrbyfloat
// �������ܣ��õ�Ԫ�ؽڵ�����Եĸ�������ֵ
//
// ��������� 1 -- Ԫ�ض�������
//			  2 -- Ԫ�ض������Խڵ������
// ��������� 3 -- Ԫ�ض�������Ը�������ֵ
// ����ֵ��0 -- ʧ�� 1 -- �ɹ�
// ˵�����õ�Ԫ�ؽڵ�����Եĸ�������ֵ
//============================================================================
int xmlelement_getattrbyfloat(void *this, char *name, float *value)
{
	char buffer[100] = { 0 };
	int size = xmlelement_getattribute(this, name, buffer);
	if (size > 0)
	{
		if (xml_isfloat(buffer))
		{
			*value = xml_strtofloat(buffer);
			return 1;
		}
	}
	return 0;
}





//============================================================================
// �������ƣ�xmlelement_setattribute
// �������ܣ�����Ԫ�ؽڵ������
//
// ��������� 1 -- Ԫ�ض�������
//			  2 -- Ԫ�ض������Խڵ������
//			  3 -- Ԫ�ض�������ֵ
// ���������
// ����ֵ��none
// ˵��������Ԫ�ؽڵ������
//============================================================================
int xmlelement_setattribute(void *this, char *name, char *buffer)
{
	int size = 0;
	struct xmlelement *element = (struct xmlelement *)this;
	struct xmlnode *list = NULL;
	if (NULL == element)
	{
		return 0;
	}
	list = element->attribute;
	for (;; )
	{
		if (NULL == list)
		{
			break;
		}
		if (0 == xml_strcmp(list->name, name))
		{
			if (NULL != list->value)
			{
				xml_free(list->value);
			}
			list->value = xml_strnew(buffer);
			if (NULL == list->value)
			{
				size = 0;
			}
			else
			{
				size = xml_strlen(list->value);
			}
			return size;
		}
		list = list->next;
	}
	xmlnode_add(&(element->attribute), setattribute(name, buffer));
	size = xml_strlen(buffer);
	return size;
}


//============================================================================
// �������ƣ�xmlelement_setattrbyint
// �������ܣ�����Ԫ�ؽڵ�����Ե�����ֵ
//
// ��������� 1 -- Ԫ�ض�������
//			  2 -- Ԫ�ض������Խڵ������
//			  3 -- Ԫ�ض������������ֵ
// ��������� 
// ����ֵ��0 -- ʧ�� 1 -- �ɹ�
// ˵��������Ԫ�ؽڵ�����Ե�����ֵ
//============================================================================
int xmlelement_setattrbyint(void *this, char *name, int value)
{
	char buffer[100] = { 0 };
	int size;
	sprintf(buffer, "%d", value);
	size = xmlelement_setattribute(this, name, buffer);
	if (size > 0)
	{
		size = 1;
	}
	return size;
}


//============================================================================
// �������ƣ�xmlelement_indexofattr
// �������ܣ��õ�Ԫ�ؽڵ������
//
// ��������� 1 -- Ԫ�ض�������
//			2 -- Ԫ�ض�������������
// �������������ֵ
// ����ֵ������ֵ�ַ�������
// ˵�����õ�Ԫ�ؽڵ������
//============================================================================
int xmlelement_indexofattr(void *this, int index, char *buffer)
{
	int size = 0;
	struct xmlelement *element = (struct xmlelement *)this;
	struct xmlnode *list = NULL;
	if (NULL == element)
	{
		return 0;
	}
	list = element->attribute;

	for (; index > 0; index-- )
	{
		if (NULL == list)
		{
			break;
		}
		list = list->next;
	}
	if (0 == index)
	{
		if (NULL == list)
		{
			return 0;
		}
		size = xml_strcpy(buffer, list->value);
	}

	return size;
}


//============================================================================
// �������ƣ�xmlelement_gettext
// �������ܣ��õ�Ԫ�ؽڵ���ı�
//
// ��������� 1 -- Ԫ�ض�������
// ��������� 2 -- Ԫ�ض�����ı��ڵ���ı�
// ����ֵ���ı��ĳ���
// ˵�����õ�Ԫ�ؽڵ���ı�
//============================================================================
int xmlelement_gettext( void *this, char *buffer )
{
	struct xmlelement *element = (struct xmlelement *)this;
	return xml_strcpy( buffer, element->text );
}
