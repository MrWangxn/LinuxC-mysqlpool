#ifndef MYSQLPOOL_H
#define MYSQLPOOL_H

#include <mysql/mysql.h>


#define SQL_CONN_COUNT_MAX		20


////////////////////////////////////////////////////////////
// ���ӽڵ����ݽṹ
////////////////////////////////////////////////////////////
typedef struct _SQL_NODE
{
	MYSQL fd;								// MYSQL�����ļ�������
	MYSQL* mysql_sock;						// ָ���Ѿ����ӵ�MYSQL��ָ��
	pthread_mutex_t lock;					// ������
	int used;								// ʹ�ñ�־
	int index;								// �±�
	enum {
		DB_DISCONN, DB_CONN
	}sql_state;

}SQL_NODE;

////////////////////////////////////////////////////////////
// ���ӳ����ݽṹ
////////////////////////////////////////////////////////////
typedef struct _SQL_CONN_POOL
{
	SQL_NODE conn_pool[SQL_CONN_COUNT_MAX];	// һ������
	int shutdown;							// �Ƿ�ر�
	int conn_count;							// ��������
	int busy_count;							// ����ȡ�˵���������
	char ip[16];							// ���ݿ��ַ
	int port;								// ���ݿ�˿�
	char database[64];						// ���ݿ�����
	char user[64];							// ���ݿ��û�
	char passwd[64];						// ���ݿ�����

}SQL_CONN_POOL;


// �������ӳ�
SQL_CONN_POOL* sql_pool_create(int sql_conn_count, char ip[], int port, char database[], char user[], char passwd[]);
// �������ӳ�
void sql_pool_destroy(SQL_CONN_POOL* sql_conn_pool);
// ��չ���ӳ�
void sql_pool_expand(SQL_CONN_POOL* sql_conn_pool, int count);
// ѹ�����ӳ�
void sql_pool_reduce(SQL_CONN_POOL* sql_conn_pool, int count);
// ��������
int sql_conn_create(SQL_CONN_POOL* sql_conn_pool, SQL_NODE* sql_node);
// ȡ������
SQL_NODE* sql_conn_get(SQL_CONN_POOL* sql_conn_pool);
// �ͷ�����
void sql_conn_release(SQL_CONN_POOL* sql_conn_pool, SQL_NODE* sql_node);


#endif // !MYSQLPOOL_H
