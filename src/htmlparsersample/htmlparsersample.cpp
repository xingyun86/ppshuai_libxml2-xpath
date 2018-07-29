// htmlparsersample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/xmlmemory.h>
#include <libxml/xpointer.h>
#include <libxml/HTMLtree.h>
#include <libxml/HTMLparser.h>

xmlXPathObjectPtr getNodeset(xmlDocPtr pdoc, const xmlChar *xpath)
{
	xmlXPathContextPtr context = NULL;//XPath上下文指针
	xmlXPathObjectPtr result = NULL; //XPath结果指针
	context = xmlXPathNewContext(pdoc);

	if (pdoc == NULL) {
		printf("pdoc is NULL\n");
		return NULL;
	}

	if (xpath) {
		if (context == NULL) {
			printf("context is NULL\n");
			return NULL;
		}

		result = xmlXPathEvalExpression(xpath, context);
		xmlXPathFreeContext(context); //释放上下文指针
		if (result == NULL) {
			printf("xmlXPathEvalExpression return NULL\n");
			return NULL;
		}

		if (xmlXPathNodeSetIsEmpty(result->nodesetval)) {
			xmlXPathFreeObject(result);
			printf("nodeset is empty\n");
			return NULL;
		}
	}

	return result;
}
int xml_xpath()
{
	xmlDocPtr pdoc = NULL;
	xmlNodePtr proot = NULL;

	/*****************打开xml文档********************/
	xmlKeepBlanksDefault(0);//必须加上，防止程序把元素前后的空白文本符号当作一个node
	pdoc = xmlReadFile("D:\\test.xml", "UTF-8", XML_PARSE_RECOVER);//libxml只能解析UTF-8格式数据

	if (pdoc == NULL)
	{
		printf("error:can't open file!\n");
		exit(1);
	}

	/*****************获取xml文档对象的根节对象********************/
	proot = xmlDocGetRootElement(pdoc);

	if (proot == NULL)
	{
		printf("error: file is empty!\n");
		exit(1);
	}

	/*****************查找书店中所有书籍的名称********************/
	xmlChar *xpath = BAD_CAST("//book"); //xpath语句
	xmlXPathObjectPtr result = getNodeset(pdoc, xpath); //查询XPath表达式，得到一个查询结果
	if (result == NULL)
	{
		printf("result is NULL\n");
		exit(1);
	}

	if (result)
	{
		xmlNodeSetPtr nodeset = result->nodesetval; //获取查询到的节点指针集合
		xmlNodePtr cur;

		//nodeset->nodeNr是集合元素总数
		for (int i = 0; i < nodeset->nodeNr; i++)
		{
			cur = nodeset->nodeTab[i];
			cur = cur->xmlChildrenNode;

			while (cur != NULL)
			{
				//如同标准C中的char类型一样，xmlChar也有动态内存分配，字符串操作等 相关函数。例如xmlMalloc是动态分配内存的函数；xmlFree是配套的释放内存函数；xmlStrcmp是字符串比较函数等。
				//对于char* ch="book", xmlChar* xch=BAD_CAST(ch)或者xmlChar* xch=(const xmlChar *)(ch)
				//对于xmlChar* xch=BAD_CAST("book")，char* ch=(char *)(xch)
				if (!xmlStrcmp(cur->name, BAD_CAST("title"))) {
					printf("title: %s\n", ((char*)XML_GET_CONTENT(cur->xmlChildrenNode)));
					break;
				}

				cur = cur->next;
			}
		}

		xmlXPathFreeObject(result);//释放结果指针
	}

	/*****************释放资源********************/
	xmlFreeDoc(pdoc);
	xmlCleanupParser();
	xmlMemoryDump();

	return 0;
}
int html_xpath()
{
	xmlDocPtr pdoc = NULL;
	xmlNodePtr proot = NULL;

	/*****************打开xml文档********************/
	xmlKeepBlanksDefault(0);//必须加上，防止程序把元素前后的空白文本符号当作一个node

	pdoc = htmlParseFile("D:\\test.htm", "UTF-8");

	if (pdoc == NULL)
	{
		printf("error:can't open file!\n");
		exit(1);
	}

	/*****************获取xml文档对象的根节对象********************/
	proot = xmlDocGetRootElement(pdoc);

	if (proot == NULL)
	{
		printf("error: file is empty!\n");
		exit(1);
	}

	/*****************查找书店中所有书籍的名称********************/
	xmlChar *xpath = BAD_CAST("//book"); //xpath语句
	xmlXPathObjectPtr result = getNodeset(pdoc, xpath); //查询XPath表达式，得到一个查询结果
	if (result == NULL)
	{
		printf("result is NULL\n");
		exit(1);
	}

	if (result)
	{
		xmlNodeSetPtr nodeset = result->nodesetval; //获取查询到的节点指针集合
		xmlNodePtr cur;

		//nodeset->nodeNr是集合元素总数
		for (int i = 0; i < nodeset->nodeNr; i++)
		{
			cur = nodeset->nodeTab[i];
			cur = cur->xmlChildrenNode;

			while (cur != NULL)
			{
				//如同标准C中的char类型一样，xmlChar也有动态内存分配，字符串操作等 相关函数。例如xmlMalloc是动态分配内存的函数；xmlFree是配套的释放内存函数；xmlStrcmp是字符串比较函数等。
				//对于char* ch="book", xmlChar* xch=BAD_CAST(ch)或者xmlChar* xch=(const xmlChar *)(ch)
				//对于xmlChar* xch=BAD_CAST("book")，char* ch=(char *)(xch)
				if (!xmlStrcmp(cur->name, BAD_CAST("title"))) {
					printf("title: %s\n", ((char*)XML_GET_CONTENT(cur->xmlChildrenNode)));
					break;
				}

				cur = cur->next;
			}
		}

		xmlXPathFreeObject(result);//释放结果指针
	}

	/*****************释放资源********************/
	xmlFreeDoc(pdoc);
	xmlCleanupParser();
	xmlMemoryDump();

	return 0;
}
int html_xpath2()
{
	xmlDocPtr pdoc = NULL;
	xmlNodePtr proot = NULL;

	/*****************打开xml文档********************/
	xmlKeepBlanksDefault(0);//必须加上，防止程序把元素前后的空白文本符号当作一个node

	pdoc = htmlParseFile("D:\\test1.html", "UTF-8");

	if (pdoc == NULL)
	{
		printf("error:can't open file!\n");
		exit(1);
	}

	/*****************获取xml文档对象的根节对象********************/
	proot = xmlDocGetRootElement(pdoc);

	if (proot == NULL)
	{
		printf("error: file is empty!\n");
		exit(1);
	}

	/*****************查找书店中所有书籍的名称********************/
	xmlChar *xpath = BAD_CAST("//link"); //xpath语句
	xmlXPathObjectPtr result = getNodeset(pdoc, xpath); //查询XPath表达式，得到一个查询结果
	if (result == NULL)
	{
		printf("result is NULL\n");
		exit(1);
	}

	if (result)
	{
		xmlNodeSetPtr nodeset = result->nodesetval; //获取查询到的节点指针集合
		xmlNodePtr cur;

		//nodeset->nodeNr是集合元素总数
		for (int i = 0; i < nodeset->nodeNr; i++)
		{
			cur = nodeset->nodeTab[i];
			xmlAttr * pxAttr = cur->properties;
			while (pxAttr != NULL)
			{
				//如同标准C中的char类型一样，xmlChar也有动态内存分配，字符串操作等 相关函数。例如xmlMalloc是动态分配内存的函数；xmlFree是配套的释放内存函数；xmlStrcmp是字符串比较函数等。
				//对于char* ch="book", xmlChar* xch=BAD_CAST(ch)或者xmlChar* xch=(const xmlChar *)(ch)
				//对于xmlChar* xch=BAD_CAST("book")，char* ch=(char *)(xch)
				if (!xmlStrcmp(cur->name, BAD_CAST("link"))) {
					printf("rel: %s\n", ((char*)XML_GET_CONTENT(pxAttr->children)));
					break;
				}

				pxAttr = pxAttr->next;
			}

			cur = cur->xmlChildrenNode;

			while (cur != NULL)
			{
				//如同标准C中的char类型一样，xmlChar也有动态内存分配，字符串操作等 相关函数。例如xmlMalloc是动态分配内存的函数；xmlFree是配套的释放内存函数；xmlStrcmp是字符串比较函数等。
				//对于char* ch="book", xmlChar* xch=BAD_CAST(ch)或者xmlChar* xch=(const xmlChar *)(ch)
				//对于xmlChar* xch=BAD_CAST("book")，char* ch=(char *)(xch)
				if (!xmlStrcmp(cur->name, BAD_CAST("href"))) {
					printf("title: %s\n", ((char*)XML_GET_CONTENT(cur->xmlChildrenNode)));
					break;
				}

				cur = cur->next;
			}
		}

		xmlXPathFreeObject(result);//释放结果指针
	}

	/*****************释放资源********************/
	xmlFreeDoc(pdoc);
	xmlCleanupParser();
	xmlMemoryDump();

	return 0;
}
int main(int argc, char **argv) 
{
	int nResult = 0;

	nResult = html_xpath2();
	
	return nResult;
}