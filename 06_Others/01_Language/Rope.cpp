#include<ext/rope>///头文件
using namespace __gnu_cxx;
rope <int> x;
int main(){
    x.push_back(x); ///在末尾加x
    x.insert(pos, x); ///在pos位置加入x
    x.erase(pos, x); ///从pos位置删除x个元素
    x.copy(pos, len, x); ///从pos开始len个元素用x代替
    x.replace(pos, x); ///从pos开始全部换为x
    x.substr(pos, x); ///提取pos开始x个元素
    x.at(x)/[x]; ///访问第x个元素
    return 0;
}