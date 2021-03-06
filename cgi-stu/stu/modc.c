#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

char * headname ="head.html";
//char * footname ="foot.html";

int cgiMain()
{

	FILE * fd;

	char cname[20] = "\0";
	char credit[20] = "\0";
	char cno[20] = "\0";
	char dname[20] = "\0";
	int status = 0;
	char ch;

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
		if(!(fd = fopen(headname, "r"))){
			fprintf(cgiOut, "Cannot open file, %s\n", headname);
			return -1;
		}
		ch = fgetc(fd);

		while(ch != EOF){
			fprintf(cgiOut, "%c", ch);
			ch = fgetc(fd);
		}
		fclose(fd);

	status = cgiFormString("cname",  cname, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cname error!\n");
		return 1;
	}

	status = cgiFormString("credit",  credit, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get credit error!\n");
		return 1;
	}

	status = cgiFormString("dname",  dname, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get dname error!\n");
		return 1;
	}

	status = cgiFormString("cno",  cno, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cno error!\n");
		return 1;
	}

	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);

	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}


	sprintf(sql, "update course set cname='%s', credit='%d', dname= '%s' where cno = %d and sta=1", cname, atoi(credit), dname, atoi(cno));

	mysql_set_character_set(db,"utf8");

	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}



	fprintf(cgiOut, "update course ok!\n");
	mysql_close(db);
	return 0;
}
