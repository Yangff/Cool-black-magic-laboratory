#include <string>
#include <vector>
#include <cstdio>
using namespace std;
#include "tinydefines.h"

const size_t sizes[] = {
    sizeof(std::string),
    sizeof(std::vector<int>),
    sizeof(std::vector<PArg>),
    sizeof(std::vector<PBuff>),
    sizeof(std::vector<PSkill>),
    sizeof(std::vector<PUnit>),
    sizeof(std::vector<PFlight>),
    sizeof(std::vector<PArea>),
    sizeof(std::vector<Operation>),
};

int main(){
    freopen("stdconst.h", "w", stdout);
    printf("namespace _ { const size_t ss[] = {");
    for (int i = 0; i < 9; i++) {
        printf("%d,", sizes[i]);
    }
    printf("};\n");
    printf("template<class T> struct ToId { };\n");
    printf("template<> struct ToId<std::string> { const int invoke = 0; };\n");
    printf("template<> struct ToId<std::vector<int> > { const int invoke = 1; };\n");
    printf("template<> struct ToId<std::vector<PArg> > { const int invoke = 2; };\n");
    printf("template<> struct ToId<std::vector<PBuff> > { const int invoke = 3; };\n");
    printf("template<> struct ToId<std::vector<PSkill> > { const int invoke = 4; };\n");
    printf("template<> struct ToId<std::vector<PUnit> > { const int invoke = 5; };\n");
    printf("template<> struct ToId<std::vector<PFlight> > { const int invoke = 6; };\n");
    printf("template<> struct ToId<std::vector<PArea> > { const int invoke = 7; };\n");
    printf("template<> struct ToId<std::vector<Operation> > { const int invoke = 8; };\n");
    printf("};\n");
}