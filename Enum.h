#pragma once

enum {
    ItemBox_1,
    ItemBox_2,
    ItemBox_3,
    ItemBox_4,
    ItemBox_5,
    ItemBox_6,
    ItemBox_7,
    ItemBox_8,
    ItemBox_9,
    ItemBox_10,
    ItemBox_Max,
};

enum {
    Item_Herb,//やくそう
    Item_Key,//かぎ
    Item_CupperSword,//"どうのつるぎ"
    Item_Meil,//"かわのよろい"
    Item_unchi,//"うんち"
    Item_Orb,  //オーブ
    Item_Num_Max,
};

typedef struct {
    const char* map_name;
    int x;
    int y;
    int ItemNum;
}TRESURE;


static TRESURE tresure[] = {
    {"map_test_door.bmp",7,4,Item_Key},
};


enum {
    TRESURE_KingRoom_1,//KEY
    TRESURE_MAX,
};

