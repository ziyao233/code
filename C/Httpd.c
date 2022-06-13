/*
	code
	File:/C/Httpd.c
	Date:2021.08.26
	By MIT License.
	Copyright(C) 2021 Ziyao.All rights reserved.
*/

#include<assert.h>
#include<stdio.h>

#include<cwb/Httpd.h>

static const char *content = "<h1>Hello World</h1>";

static int handler(Cwb_Httpd_Conn *conn)
{
	return cwb_httpd_res_writes(conn,content);
}

int main(void)
{
	Cwb_Httpd *httpd = cwb_httpd_new();
	assert(httpd);
	httpd->conf.network.port = 10888;

	assert(!cwb_httpd_router_add(httpd,CWB_HTTPD_ROUTER_RULE_ANY,
				     handler));

	assert(!cwb_httpd_start(httpd));

	cwb_httpd_destroy(httpd);

	return 0;
}
