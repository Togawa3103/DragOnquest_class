#pragma once
enum {
	magic_1,
	magic_2,
	magic_3,
	magic_4,
	magic_MAX,

};
enum {
	magic_Type_1,
	magic_Type_2,
	magic_Type_3,
	magic_Type_4,
	magic_Type_MAX,
};

typedef struct {
	int magic_num;
	int magic_type;
	int magic_power;
	int magic_mp;
	const char *magic_name;

}Magic;

static Magic magic[] = {
	{magic_1,magic_Type_1,25,2,"ホイミ"},
	{magic_2,magic_Type_2,5,2,"メラ"},
	{magic_3,magic_Type_3,5,3,"スカラ"},
	{magic_4,magic_Type_4,5,3,"ルカニ"},
};