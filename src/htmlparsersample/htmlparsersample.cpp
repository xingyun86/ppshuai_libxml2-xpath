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
	xmlXPathContextPtr context = NULL;//XPath������ָ��
	xmlXPathObjectPtr result = NULL; //XPath���ָ��
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
		xmlXPathFreeContext(context); //�ͷ�������ָ��
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

	/*****************��xml�ĵ�********************/
	xmlKeepBlanksDefault(0);//������ϣ���ֹ�����Ԫ��ǰ��Ŀհ��ı����ŵ���һ��node
	pdoc = xmlReadFile("D:\\test.xml", "UTF-8", XML_PARSE_RECOVER);//libxmlֻ�ܽ���UTF-8��ʽ����

	if (pdoc == NULL)
	{
		printf("error:can't open file!\n");
		exit(1);
	}

	/*****************��ȡxml�ĵ�����ĸ��ڶ���********************/
	proot = xmlDocGetRootElement(pdoc);

	if (proot == NULL)
	{
		printf("error: file is empty!\n");
		exit(1);
	}

	/*****************��������������鼮������********************/
	xmlChar *xpath = BAD_CAST("//book"); //xpath���
	xmlXPathObjectPtr result = getNodeset(pdoc, xpath); //��ѯXPath���ʽ���õ�һ����ѯ���
	if (result == NULL)
	{
		printf("result is NULL\n");
		exit(1);
	}

	if (result)
	{
		xmlNodeSetPtr nodeset = result->nodesetval; //��ȡ��ѯ���Ľڵ�ָ�뼯��
		xmlNodePtr cur;

		//nodeset->nodeNr�Ǽ���Ԫ������
		for (int i = 0; i < nodeset->nodeNr; i++)
		{
			cur = nodeset->nodeTab[i];
			cur = cur->xmlChildrenNode;

			while (cur != NULL)
			{
				//��ͬ��׼C�е�char����һ����xmlCharҲ�ж�̬�ڴ���䣬�ַ��������� ��غ���������xmlMalloc�Ƕ�̬�����ڴ�ĺ�����xmlFree�����׵��ͷ��ڴ溯����xmlStrcmp���ַ����ȽϺ����ȡ�
				//����char* ch="book", xmlChar* xch=BAD_CAST(ch)����xmlChar* xch=(const xmlChar *)(ch)
				//����xmlChar* xch=BAD_CAST("book")��char* ch=(char *)(xch)
				if (!xmlStrcmp(cur->name, BAD_CAST("title"))) {
					printf("title: %s\n", ((char*)XML_GET_CONTENT(cur->xmlChildrenNode)));
					break;
				}

				cur = cur->next;
			}
		}

		xmlXPathFreeObject(result);//�ͷŽ��ָ��
	}

	/*****************�ͷ���Դ********************/
	xmlFreeDoc(pdoc);
	xmlCleanupParser();
	xmlMemoryDump();

	return 0;
}
int html_xpath()
{
	xmlDocPtr pdoc = NULL;
	xmlNodePtr proot = NULL;

	/*****************��xml�ĵ�********************/
	xmlKeepBlanksDefault(0);//������ϣ���ֹ�����Ԫ��ǰ��Ŀհ��ı����ŵ���һ��node

	pdoc = htmlParseFile("D:\\test.htm", "UTF-8");

	if (pdoc == NULL)
	{
		printf("error:can't open file!\n");
		exit(1);
	}

	/*****************��ȡxml�ĵ�����ĸ��ڶ���********************/
	proot = xmlDocGetRootElement(pdoc);

	if (proot == NULL)
	{
		printf("error: file is empty!\n");
		exit(1);
	}

	/*****************��������������鼮������********************/
	xmlChar *xpath = BAD_CAST("//book"); //xpath���
	xmlXPathObjectPtr result = getNodeset(pdoc, xpath); //��ѯXPath���ʽ���õ�һ����ѯ���
	if (result == NULL)
	{
		printf("result is NULL\n");
		exit(1);
	}

	if (result)
	{
		xmlNodeSetPtr nodeset = result->nodesetval; //��ȡ��ѯ���Ľڵ�ָ�뼯��
		xmlNodePtr cur;

		//nodeset->nodeNr�Ǽ���Ԫ������
		for (int i = 0; i < nodeset->nodeNr; i++)
		{
			cur = nodeset->nodeTab[i];
			cur = cur->xmlChildrenNode;

			while (cur != NULL)
			{
				//��ͬ��׼C�е�char����һ����xmlCharҲ�ж�̬�ڴ���䣬�ַ��������� ��غ���������xmlMalloc�Ƕ�̬�����ڴ�ĺ�����xmlFree�����׵��ͷ��ڴ溯����xmlStrcmp���ַ����ȽϺ����ȡ�
				//����char* ch="book", xmlChar* xch=BAD_CAST(ch)����xmlChar* xch=(const xmlChar *)(ch)
				//����xmlChar* xch=BAD_CAST("book")��char* ch=(char *)(xch)
				if (!xmlStrcmp(cur->name, BAD_CAST("title"))) {
					printf("title: %s\n", ((char*)XML_GET_CONTENT(cur->xmlChildrenNode)));
					break;
				}

				cur = cur->next;
			}
		}

		xmlXPathFreeObject(result);//�ͷŽ��ָ��
	}

	/*****************�ͷ���Դ********************/
	xmlFreeDoc(pdoc);
	xmlCleanupParser();
	xmlMemoryDump();

	return 0;
}
int html_xpath2()
{
	xmlDocPtr pdoc = NULL;
	xmlNodePtr proot = NULL;

	/*****************��xml�ĵ�********************/
	xmlKeepBlanksDefault(0);//������ϣ���ֹ�����Ԫ��ǰ��Ŀհ��ı����ŵ���һ��node

	pdoc = htmlParseFile("D:\\test1.html", "UTF-8");

	if (pdoc == NULL)
	{
		printf("error:can't open file!\n");
		exit(1);
	}

	/*****************��ȡxml�ĵ�����ĸ��ڶ���********************/
	proot = xmlDocGetRootElement(pdoc);

	if (proot == NULL)
	{
		printf("error: file is empty!\n");
		exit(1);
	}

	/*****************��������������鼮������********************/
	xmlChar *xpath = BAD_CAST("//link"); //xpath���
	xmlXPathObjectPtr result = getNodeset(pdoc, xpath); //��ѯXPath���ʽ���õ�һ����ѯ���
	if (result == NULL)
	{
		printf("result is NULL\n");
		exit(1);
	}

	if (result)
	{
		xmlNodeSetPtr nodeset = result->nodesetval; //��ȡ��ѯ���Ľڵ�ָ�뼯��
		xmlNodePtr cur;

		//nodeset->nodeNr�Ǽ���Ԫ������
		for (int i = 0; i < nodeset->nodeNr; i++)
		{
			cur = nodeset->nodeTab[i];
			xmlAttr * pxAttr = cur->properties;
			while (pxAttr != NULL)
			{
				//��ͬ��׼C�е�char����һ����xmlCharҲ�ж�̬�ڴ���䣬�ַ��������� ��غ���������xmlMalloc�Ƕ�̬�����ڴ�ĺ�����xmlFree�����׵��ͷ��ڴ溯����xmlStrcmp���ַ����ȽϺ����ȡ�
				//����char* ch="book", xmlChar* xch=BAD_CAST(ch)����xmlChar* xch=(const xmlChar *)(ch)
				//����xmlChar* xch=BAD_CAST("book")��char* ch=(char *)(xch)
				if (!xmlStrcmp(cur->name, BAD_CAST("link"))) {
					printf("rel: %s\n", ((char*)XML_GET_CONTENT(pxAttr->children)));
					break;
				}

				pxAttr = pxAttr->next;
			}

			cur = cur->xmlChildrenNode;

			while (cur != NULL)
			{
				//��ͬ��׼C�е�char����һ����xmlCharҲ�ж�̬�ڴ���䣬�ַ��������� ��غ���������xmlMalloc�Ƕ�̬�����ڴ�ĺ�����xmlFree�����׵��ͷ��ڴ溯����xmlStrcmp���ַ����ȽϺ����ȡ�
				//����char* ch="book", xmlChar* xch=BAD_CAST(ch)����xmlChar* xch=(const xmlChar *)(ch)
				//����xmlChar* xch=BAD_CAST("book")��char* ch=(char *)(xch)
				if (!xmlStrcmp(cur->name, BAD_CAST("href"))) {
					printf("title: %s\n", ((char*)XML_GET_CONTENT(cur->xmlChildrenNode)));
					break;
				}

				cur = cur->next;
			}
		}

		xmlXPathFreeObject(result);//�ͷŽ��ָ��
	}

	/*****************�ͷ���Դ********************/
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