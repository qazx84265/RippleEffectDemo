//
//  dyas.cpp
//
//
//  Created by  on 2018/3/23.
//
#include <stdint.h>
#include <random>
#include <time.h>
#include <string.h>
#include <map>

#include "dy_as_v1.h"
#include "md5.h"
#include "urlParser.h"
#include "tool.h"


void prepare_buffer(char* buffer, char* storeBuffer)
{

    char temp[8];
    for (int i = 0; i < 8; i++) {
        temp[i] = buffer[i];
    }
    
    char c = storeBuffer[0];
    c = temp[c-0x31];
    buffer[0] = c;//5
    
    c = storeBuffer[1];
    c = temp[c-0x31];
    buffer[1] = c; //9 a
    
    c = storeBuffer[2];
    c = temp[c-0x31];
    buffer[2] = c; //a b
    
    c = storeBuffer[3];
    c = temp[c-0x31];
    buffer[3] = c; //5 2
    
    c = storeBuffer[4];
    c = temp[c-0x31];
    buffer[4] = c;//2 9
    
    c = storeBuffer[5];
    c = temp[c-0x31];
    buffer[5] = c; //b a
    
    c = storeBuffer[6];
    c = temp[c-0x31];
    buffer[6] = c;//b c
    
    c = storeBuffer[7];
    c = temp[c-0x31];
    buffer[7] = c;//c b
    
    buffer[8] = 0;

}


const char* sub_10193394(int timestamp, const char* value, const char* random)
{

    MDJFKLDDDJLF53DF md5 = MDJFKLDDDJLF53DF(value);
	MDJFKLDDDJLF53DF* pMD5 = &md5;
    if (timestamp % 2 == 1) {
		MDJFKLDDDJLF53DF temp = MDJFKLDDDJLF53DF(md5.fmundcti5on());
        pMD5 = &temp;
    }
    string decrypt = pMD5->fmundcti5on();
    
    char buffer[512] = {0};
    sprintf(buffer, "%08x", timestamp);
    sprintf(buffer+0xa, "%08x", timestamp);

    char* p1 = buffer;
    char* p2 = buffer + 0xa;
    
    char* p3 = buffer + 0x14;
    *(long long*)p3 = 0x3633343831323735;
    
    char* p4 = buffer + 0x1e;
    *(long long*)p4 = 0x3436323738333531;
    
    prepare_buffer(p1, p3);
    prepare_buffer(p2, p4);

    int idx = 0;
    char* result = (char*)malloc(0x2c);
    result[0] = 0x61; // as 前缀第一位 'a'
    
    char secondPre = '2'; //1
    result[1] = secondPre;
    
    char* p = result + 0x2;
    do {
        *p = decrypt[idx];
        p += 0x2;
        idx++;
    } while (idx != 0x8);
    
    // spam
    if (((timestamp >> 8) & 0xFF) < 0) {
        idx = 0;
        do {
            *p = *(p1+idx);
            p += 0x2;
            idx++;
        } while (idx != 0x8);
    }

    idx = 0;
    p = result + 0x3;
    do {
        *p = *(p2 + idx);
        p += 0x2;
        idx++;
    } while (idx != 0x8);
    
    // spam
    if (((timestamp >> 4) & 0xFF) > 1000) {
        idx = 0;
        do {
            *p = *(p2+idx);
            p += 0x2;
            idx++;
        } while (idx != 0x8);
    }

    result[0x12] = random[0];
    result[0x13] = random[1];
    result[0x14] = random[2];

    random_device rd;
    result[0x15] = rd() % 0xA | 0x30;//0x31;//
    result[0x16] = 0;

    //
    char array4[0x20];
    p = array4;
    idx = 0;
    do {
        *p = *(p1+idx);
        p += 0x2;
        idx++;
    } while (idx != 0x8);
    
    // spam
    if (((timestamp >> 16) & 0xFF) < 0) {
        idx = 0;
        do {
            *p = decrypt[idx];
            p += 0x2;
            idx++;
        } while (idx != 0x8);
    }

    idx = 0;
    p = array4 + 0x1;
    do {
        *p = decrypt[0x18 + idx];
        p += 0x2;
        idx++;
    } while (idx < 0x8);
    
    // spam
    if (((timestamp >> 24) & 0xFF) > 1000) {
        idx = 0;
        do {
            *p = *(p1+idx);
            p += 0x2;
            idx++;
        } while (idx != 0x8);
    }

    array4[0x10] = 0x65;
    array4[0x11] = secondPre; //抖音 '1',  火山'2'
	array4[0x12] = rd() % 0x1A + 0x61;//
    array4[0x13] = rd() % 0x1A + 0x61;//
    array4[0x14] = rd() % 0x1A + 0x61;//
    array4[0x15] = rd() % 0x1A + 0x61;//
    array4[0x16] = 0;

    strncpy(result + 0x16, array4, 0x16);


    return result;
}

//生成3位随机字符串
void genernal_random_string(string& value)
{
	std::random_device rd;
    for (int time = 0; time < 3; time++) {
		value.push_back(rd() % 0xA | 0x30);
    }
    
    //value = "037";
    //printf("3r: %s\n", value.c_str());
}

string sub_1011389(int currentTime, map<string, string>* paramMap, string& deviceId)
{

    srand((unsigned)time(0));
    
    // 
    paramMap->insert(make_pair("rstr", "")); // 
    
    string values;
    map<string, string>::iterator iter = paramMap->begin();
    for (; iter != paramMap->end(); iter++) {
        string value = iter->second;
        values.append(value);
    }
	paramMap->erase("rstr");
    
    if (values.length() > 0) {
        for (int i = 0; i < values.length(); i++) {
            if (values[i] == ' ' || values[i] == '+') {
                values[i] = 'a';
            }
        }
    }

    size_t didlen = deviceId.length();
    if (didlen > 0) {
        values.append(deviceId);
    }
    else {
        values.append("0");
    }
    
    string tempStr;
    genernal_random_string(tempStr);
    values.append(tempStr);
    
    //printf("value: %s\n", values.c_str());
    const char* result = sub_10193394(currentTime, values.c_str(), tempStr.c_str());

	string as = "";
    if (result && strlen(result) > 0 /*&& stat == 0*/)
    {
		//printf("as: %s\r\n", result);
		as = string(result, 0, 0x16);
    }


    return as;
}

void splitString(const string& s, vector<string>& v, const string& c)
{
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));
        
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}

void parser_url(char* url, map<string, string>& map)
{
    if (!url || strlen(url) == 0) {
        return;
    }
    
    UrlParser *parser = new UrlParser(url);
    string query = parser->GetQuery();
    vector<string> v;
    splitString(query, v, "&"); //可按多个字符来分隔;
    if (v.size() == 0) {
        return;
    }
    for(vector<string>::size_type i = 0; i != v.size(); i++) {
        string item = v[i];
        vector<string> kv;
        splitString(item, kv, "=");
        if (kv.size() != 2) {
            continue;
        }
        
        string key = kv[0];
        if (key == "as" || key == "mas" || key == "ts" | key == "_rticket" || key == "rstr") {
            continue;
        }
        
        map.insert(make_pair(key, kv[1]));
        
    }
}


string fc74654a61f3727e6adfce1cff5025f(char* urlStr, unsigned int& ti)
{
    if (!urlStr || strlen(urlStr)==0) {
        return "";
    }
   
    map<string, string> mymap;
    parser_url(urlStr, mymap);
    
	uint32_t second = (uint32_t)time(NULL);//1536911321;// 
    char buffer[15];
    sprintf(buffer, "%d", second);
    mymap.insert(make_pair("ts", buffer));
    ti = second;
    //printf("ti: %d\nurl:%s\n", ti, urlStr);
    
    string as = sub_1011389(second, &mymap, mymap["device_id"]);
    
    return as;
}


