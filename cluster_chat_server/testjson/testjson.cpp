#include "json.hpp"
using json = nlohmann::json; // 相当于一个typedef的操作，重命名，简化书写

#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

// json序列化示例1
string func1()
{
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "kaonijiwa";

    string sendBuf = js.dump(); // json数据对象===序列化为===>json字符串
    return sendBuf;
    // cout << js << endl;
    // cout << sendBuf << endl;
    // cout << sendBuf.c_str() << endl;
}

// json序列化示例2
string func2()
{
    json js;
    js["id"] = {1, 2, 3, 4, 5};
    js["name"] = "zhan san";
    js["msg"]["zhang san"] = "hello world";
    js["msg"]["liu shuo"] = "hello china";
    // 上面等同于下面这句一次性添加数组对象
    js["msg"] = {{"zhan san", "hello world"}, {"liu shuo", "hello china"}};

    // cout << js << endl;

    string sendBuf = js.dump();
    return sendBuf;
    // cout << sendBuf << endl;
}

// json序列化示例3
string func3()
{
    json js;
    // 序列化一个vector容器
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    js["list"] = vec;

    // 序列化一个map容器
    // 添加到一个数组中，不是一个自序列化子串中
    map<int, string> m;
    m.insert({1, "huan san"});
    m.insert({2, "huan san1"});
    m.insert({3, "huan san2"});
    js["path"] = m;

    string sendBuf = js.dump();
    return sendBuf;
    // cout << js << endl;
}

int main()
{
    // func2();
    string recvBuf = func3();

    // 数据的反序列化
    json jsbuf = json::parse(recvBuf);

    // cout << jsbuf["id"] << endl;
    // cout << jsbuf["msg"]["zhan san"] << endl;
    // cout << jsbuf["msg"]["zhan saan"] << endl;

    vector<int> vec = jsbuf["list"];
    cout << vec[1] << endl;

    map<int,string> m = jsbuf["path"];
    cout << m[1] << endl;
    auto mm = jsbuf["path"];  //自动推导的类型不一定是真实想要的类型
    cout << mm[1] << endl;

    return 0;
}