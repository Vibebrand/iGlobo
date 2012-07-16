#include <stdio.h>
#include <string.h>
#include <libxml/xmlreader.h>

#include "LectorXML.h"

#ifdef LIBXML_READER_ENABLED

extern void streamFile(const char *filename, CallbackFunction callback );

static void processNode(xmlTextReaderPtr reader, CallbackFunction callback);
static void notificaElemento(CallbackFunction callback, int tipo, int Depth, int NodeType, const char * name, int IsEmptyElement, int HasValue, int HasAttributes, const char * value);
static void copiaStr(char *, const xmlChar *);

/**
 * processNode:
 * @reader: the xmlReader
 *
 * Dump information about the current node
 */
void processNode(xmlTextReaderPtr reader, CallbackFunction callback) {

	const xmlChar * name = xmlTextReaderConstName(reader);
	char * nombre = malloc((xmlStrlen(name) + 1) * sizeof(char));
	copiaStr(nombre, name);

	const xmlChar * value = xmlTextReaderConstValue(reader);
	char * valor = NULL;
	if(value != NULL) {
		valor = malloc((xmlStrlen(value) + 1) * sizeof(char));
		copiaStr(valor, value);
	}

	notificaElemento(callback, 0,
			xmlTextReaderDepth(reader),
			xmlTextReaderNodeType(reader),
			nombre,
			xmlTextReaderIsEmptyElement(reader),
			xmlTextReaderHasValue(reader),
			xmlTextReaderHasAttributes(reader),
			valor);

	free(nombre);
	free(valor);

	if(xmlTextReaderHasAttributes(reader) == 1)
	{
		if(xmlTextReaderMoveToFirstAttribute(reader) == 1) {
			do {
				const xmlChar * name = xmlTextReaderConstName(reader);
				char * nombre = malloc((xmlStrlen(name) + 1) * sizeof(char));
				copiaStr(nombre, name);

				const xmlChar * value = xmlTextReaderConstValue(reader);
				char * valor = NULL;
				if(value != NULL) {
					valor = malloc((xmlStrlen(value) + 1) * sizeof(char));
					copiaStr(valor, value);
				}


				notificaElemento(callback, 1,
						0,
						xmlTextReaderNodeType(reader),
						nombre,
						0,
						0,
						0,
						valor);

				free(nombre);
				free(valor);

			} while(xmlTextReaderMoveToNextAttribute(reader) == 1);
		}

		xmlTextReaderMoveToElement(reader);
	}
}

/**
 * streamFile:
 * @filename: the file name to parse
 *
 * Parse and print information about an XML file.
 */
void streamFile(const char *filename, CallbackFunction callback ) {

	/*
	 * this initialize the library and check potential ABI mismatches
	 * between the version it was compiled for and the actual shared
	 * library used.
	 */LIBXML_TEST_VERSION

	xmlTextReaderPtr reader;
	int ret;

	reader = xmlReaderForFile(filename, NULL, 0);
	if (reader != NULL) {
		ret = xmlTextReaderRead(reader);
		while (ret == 1) {
			processNode(reader, callback);
			ret = xmlTextReaderRead(reader);
		}
		xmlFreeTextReader(reader);
		if (ret != 0) {
			fprintf(stderr, "%s : failed to parse\n", filename);
		}
	} else {
		fprintf(stderr, "Unable to open %s\n", filename);
	}

	/*
	 * Cleanup function for the XML library.
	 */
	xmlCleanupParser();
	/*
	 * this is to debug memory for regression tests
	 */
	xmlMemoryDump();
}


static void notificaElemento(CallbackFunction callback, int tipo, int Depth, int NodeType, const char * name, int IsEmptyElement, int HasValue, int HasAttributes, const char * value)
{

#ifdef IMPRIME_PARSEO
	printf("%s\t" //0
			"%d\t" //1
			"%d\t" //2
			"%s\t" //3
			"%d\t" //4
			"%d\t" //5
			"%d\t", //6
			tipo == 0 ? "Elemento" : "Atributo", //0
			Depth, //1
			NodeType, //2
			name == NULL ? "--" : name, //3
			IsEmptyElement, //4
			HasValue, //5
			HasAttributes); //6

	//7
	if (value == NULL) {
		printf("\n");
	} else {
		if (strlen(value) > 40) {
			printf("%.40s\n", value);
		} else {
			printf("%s\n", value);
		}
	}

#endif

	(*callback)(tipo, Depth, NodeType, name, IsEmptyElement, HasValue, HasAttributes, value);
}

void copiaStr(char * destino, const xmlChar * origen) {
    strcpy(destino, (const char *)origen);
}

#endif
