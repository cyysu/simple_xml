/*
 * xml_string.c
 *
 *  Created on: 2017��5��23��
 *      Author: xfwangqiang
 */

/*========================================================*
 * �����޸ļ�¼��
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���>
 *  V1.0.0  2017-06-05  xfwangqiang     ����
 *========================================================*/


#include "xml_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// return the size of string, don't include '\0'
int xml_strlen( char *src )
{
	int size = 0;
	for ( ; '\0' != *src; src++, size++ )
	{
		;
	}
	return size;
}


// copy string from src to des, return index of copy char
int xml_strcpy( char *des, char *src )
{
	int index = 0;
	for ( ; '\0' != *src; src++, des++, index++ )
	{
		*des = *src;
	}
	*des = '\0';
	return index;
}

// copy string from src to des, return index of copy char
int xml_strncpy( char *des, char *src, int size )
{
	int index = 0;
	for ( ; ('\0' != *src) && (size > 0); src++, des++, index++, size-- )
	{
		*des = *src;
	}
	*des = '\0';
	return index;
}

// copy string from src to des, return index of copy char
int xml_strcat( char *des, char *src )
{
	int index = 0;

	for ( ; '\0' != *des; des++ )
	{
		;
	}

	for ( ; '\0' != *src; src++, des++, index++ )
	{
		*des = *src;
	}
	*des = '\0';
	return index;
}

// copy string from src to des, return index of copy char
int xml_strncat( char *des, char *src, int size )
{
	int index = 0;

	for ( ; '\0' != *des; des++ )
	{
		;
	}

	for ( ; ('\0' != *src) && (size > 0); src++, des++, index++, size-- )
	{
		*des = *src;
	}
	*des = '\0';
	return index;
}

// search the identifier in string
int xml_searchname( char *string, char *name, int size )
{
	int len = 0;
	for ( ; (0 == xml_checkidentify( *string )) && ('\0' != *string); string++ )
	{
		;
	}
	for ( ;(1 == xml_checkidentify( *string )) && ('\0' != *string) && (size > 0) ;  string++, name++, size--  )
	{
		*name = *string;
		len++;
	}
	*name = '\0';
	return len;
}


// check the identifier char
int xml_checkidentify( char c )
{
	if ( (c >= 'a') && (c <= 'z'))
	{
		return 1;
	}
	else if ( (c >= 'A') && (c <= 'Z'))
	{
		return 1;
	}
	else if ( ('_' == c) || (':' == c) )
	{
		return 1;
	}

	return 0;
}


//============================================================================
// �������ƣ�xml_strindexof
// �������ܣ��õ��ַ�������
//
// ��������� 1 -- �ַ���
//			2 -- ƫ��
//			3 -- �ַ�
// ���������
// ����ֵ��Ŀ���ַ�������ֵ
// ˵�����õ��ַ�������
//============================================================================
int xml_strindexof( char *string, int offset, char c )
{
	string += offset;
	for ( ;'\0' != *string; string++, offset++ )
	{
		if ( *string == c )
		{
			break;
		}
	}
	if ( '\0' == *string )
	{
		offset = -1;
	}
	return offset;
}


//============================================================================
// �������ƣ�xml_strsplitlist
// �������ܣ�ʹ���ض��ַ��ָ��ַ��õ��ַ����б���ָ�����ַ�
//
// ��������� 1 -- �ַ���
// 			2 -- Ŀ���ַ�
//			3 -- �ַ����б�������
// ��������� 4 -- �õ����ַ���
// ����ֵ���õ��ַ����ĳ���
// ˵����ʹ���ض��ַ��ָ��ַ��õ��ַ����б���ָ�����ַ�
//============================================================================
int xml_strsplitlist( char *string, char c, int index, char *buffer )
{
	int start = 0;
	int end = -1;
	for ( ; index >= 0; index-- )
	{
		start = end + 1;
		end = xml_strindexof( string, start, c );
		if ( -1 == end )
		{
			end = xml_strlen( string );
		}
	}
	return xml_strncpy( buffer, string + start, end - start);
}


//============================================================================
// �������ƣ�xml_strsplit
// �������ܣ�ʹ���ض��ַ��ָ��ַ��õ��ַ����б���Ԫ�ظ���
//
// ��������� 1 -- �ַ���
// 			2 -- Ŀ���ַ�
// ���������
// ����ֵ���õ��ַ����б���Ԫ�ظ���
// ˵����ʹ���ض��ַ��ָ��ַ��õ��ַ����б���Ԫ�ظ���
//============================================================================
int xml_strsplit( char *string, char c )
{
	int index = 0;
	int num = 0;
	for ( ; ; )
	{
		index = xml_strindexof( string, index, c );
		if ( -1 == index )
		{
			if ( 0 == num )
			{
				return 0;
			}
			else
			{
				num++;
				break;
			}
		}
		else
		{
			index++;
			num++;
		}
	}
	return num;
}


//============================================================================
// �������ƣ�xml_strtrim
// �������ܣ�ȥ����β�Ŀո�
//
// ��������� 1 -- ȥ��ո�ǰ���ַ���
// ��������� 2 -- ȥ���ո����ַ���
// ����ֵ��ȥ�����ַ����ĳ���
// ˵����ȥ����β�Ŀո�
//============================================================================
int  xml_strtrim( char *string, char *buffer )
{
	int size = 0;
	for ( ; (' ' == *string) && ('\0' != *string); string++ )
	{
		;
	}
	for ( ; (' ' != *string) && ('\0' != *string) ; string++, buffer++ )
	{
		*buffer = *string;
		size++;
	}
	*buffer = '\0';
	return size;
}



//============================================================================
// �������ƣ�xml_strnew
// �������ܣ��½�һ���ַ���
//
// ��������� 1 -- Դ�ַ���
// ����ֵ���½��ַ����ĵ�ַ
// ˵�����ڶ��п���һ��ͬ����С���ڴ�飬��Դ�ַ��������ݿ������µ��ַ���������µ��ַ�����ַ��
// ʹ����Ϻ�һ��Ҫ�ǵ��ͷţ�����ᷢ���ڴ�й©.
//============================================================================
char *xml_strnew( char *string )
{
	int size;
	char *newstr;
	if ( (NULL == string) || ('\0' == string[0]) )
	{
		return NULL;
	}
	size = xml_strlen( string );
	newstr = (char *)malloc( size + 1 );
	xml_strcpy( newstr, string );
	return newstr;
}



//============================================================================
// �������ƣ�xml_strcmp
// �������ܣ��ַ����Ƚ�
//
// ��������� 1 -- Դ�ַ���1
//			  2 -- Դ�ַ���2
// ����ֵ��0 -- ���
// ˵����
//============================================================================
int xml_strcmp( char *str1, char *str2 )
{
	int tmp;

    if (str1 == str2) return(0);
    if (str1 == NULL) return(-1);
    if (str2 == NULL) return(1);
    do {
        tmp = *str1++ - *str2;
        if (tmp != 0) return(tmp);
    } while (*str2++ != 0);
	return 0;
}




//============================================================================
// �������ƣ�xml_isint
// �������ܣ��ж��ַ����Ƿ�Ϊ����
//
// ��������� 1 -- �ַ���
// ����ֵ��0 -- ���� 1 -- ��
// ˵�����ж��ַ����Ƿ�Ϊ����
//============================================================================
int xml_isint(char *strvalue)
{
	if ((NULL == strvalue) || ('\0' == strvalue[0]) )
	{
		return 0;
	}
	if (('+' == *strvalue) || ('-' == *strvalue))
	{
		strvalue++;
	}
	forstrloop(strvalue)
	{
		if ((*strvalue < '0') || (*strvalue > '9'))
		{
			return 0;
		}
	}
	return 1;
}


//============================================================================
// �������ƣ�xml_isfloat
// �������ܣ��ж��ַ����Ƿ�Ϊ������
//
// ��������� 1 -- �ַ���
// ����ֵ��0 -- ���� 1 -- ��
// ˵�����ж��ַ����Ƿ�Ϊ������
//============================================================================
int xml_isfloat(char *strvalue)
{
	int point = 0;
	if ((NULL == strvalue) || ('\0' == *strvalue))
	{
		return 0;
	}

	if (('+' == *strvalue) || ('-' == *strvalue))
	{
		strvalue++;
	}
	forstrloop(strvalue)
	{
		if (((*strvalue < '0') || (*strvalue > '9')) && ('.' != *strvalue))
		{
			return 0;
		}
		else if ('.' == *strvalue)
		{
			if (point >= 1)
			{
				return 0;
			}
			point++;
		}
	}
	return 1;
}

//============================================================================
// �������ƣ�xml_strtoint
// �������ܣ����ַ���ת��Ϊ����
//
// ��������� 1 -- �ַ���
// ����ֵ������ֵ
// ˵�������ַ���ת��Ϊ����
//============================================================================
int xml_strtoint(char *strvalue)
{
	int value = 0;
	int sign = 1;
	if ('-' == *strvalue)
	{
		sign = -1;
		strvalue++;
	}
	else if ( '+' == *strvalue)
	{
		strvalue++;
	}

	forstrloop( strvalue )
	{
		value *= 10;
		value += *strvalue - '0';
	}
	return value * sign;
}


//============================================================================
// �������ƣ�xml_strtofloat
// �������ܣ����ַ���ת��Ϊ������
//
// ��������� 1 -- �ַ���
// ����ֵ������ֵ
// ˵�������ַ���ת��Ϊ������
//============================================================================
float xml_strtofloat(char *strvalue)
{
	float value = 0.0f;
	float unit = 0.1f;
	int sign = 1;
	if ('-' == *strvalue)
	{
		sign = -1;
		strvalue++;
	}
	else if ('+' == *strvalue)
	{
		strvalue++;
	}
	forstrloop(strvalue)
	{
		if ('.' == *strvalue)
		{
			break;
		}
		value *= 10;
		value += *strvalue - '0';
	}
	strvalue++;
	forstrloop(strvalue)
	{
		value += (*strvalue - '0') * unit;
		unit *= 0.1f;
	}
	return value * sign;
}

